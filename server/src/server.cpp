#include <iostream>
#include <string.h>
#include <sstream>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>
#include <time.h>
#include "../include/data_base.h"
#include "../include/helper_functions_server.h"

using namespace std;

// main thread function
int process_transaction(int client_sock, int thread_id, string db_name) {

    while(1) {

        char message[DEFAULT_BUFLEN];
        Database db;

        //receive and check username or id 
        while(1) { 
            
            // Recieve username or id 
            if( !receive_data_server(client_sock, message, thread_id) ) return 1;

            // Check username or id 
            if( db.find_user(message, db_name.c_str()) && send_data_server(client_sock, get_message(true), thread_id) ) {
                break;
            } else if(!send_data_server(client_sock, get_message(false), thread_id)) {
                return 1;
            }
            
        }
        
        //receive and check pin
        while(1){

            // Recieve pin
            if( !receive_data_server(client_sock, message, thread_id) ) return 1;

            // Check pin
            if( message == to_string(db.get_pin()) && send_data_server(client_sock, get_message(true), thread_id) ) {
                break;
            } else if(!send_data_server(client_sock, get_message(false), thread_id)) {
                return 1;
            }
        }

        // Provide service
        int logout = 0;
        while(1) {
            if(!receive_data_server(client_sock, message, thread_id) ) return 1; // Recieve user option

            int recv_data = char_to_int(message);

            int new_pin, withdraw_amount, balance;
            switch(recv_data % 10) {

                case 1: // Changing a the pin
                    new_pin = recv_data / 10;
                    if( db.change_pin(new_pin, DB) ) 
                        strcpy(message, "ACCEPT");
                    else
                        strcpy(message, "DECLINE");
                    break;

                case 2: // Checking account status
                    strcpy(message, double_to_char(db.get_balance()) );
                    break;

                case 3: // Withdraw money
                    withdraw_amount = recv_data / 10;
                    balance = db.get_balance();
                    if(balance < withdraw_amount) 
                        strcpy(message, "DECLINE");
                    else if(db.change_balance(balance - withdraw_amount, DB)) { 
                        db.set_balance(balance - withdraw_amount);
                        strcpy(message, "ACCEPT"); 
                    }
                    else       
                        strcpy(message, "DECLINE");
                    break;
                case 4: // Logout
                    std::cout << "client " << "NO. " << thread_id << " logged out!~" << std::endl;
                    logout = 1;
                    break;
                default:
                    std::cout << "ERROR!" << std::endl;
            }

            if(logout == 1) break;

            // Sending confirmation message weather or not user action is successful
            if(!send_data_server(client_sock, message, thread_id))
                return 1;

        }
        
    }

    return 0;
}


int main() {

    int server_sock, client_sock, len_sockaddr;
    struct sockaddr_in server, client;

    // Create socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(server_sock == -1) {
        cout << "Could not create socket" << endl;
        exit(1);
    }
    cout << "Socket created" << endl;


    // Prepare structure
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(DEFAULT_PORT);


    // Bind
    if(bind(server_sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        cout << "Bind failed" << endl;
        exit(1);
    }
    cout << "Bind successfully" << endl;


    listen(server_sock, 5);
    len_sockaddr = sizeof(sockaddr_in);

    // Accepting all connections
    while(1) {
        cout << "Waiting for incoming connections" << endl;

        client_sock = accept(server_sock, (struct sockaddr *)&client, (socklen_t*)&len_sockaddr);

        if (client_sock < 0)
        {
            cout << "Accept failed" << endl;
            exit(1);
        }
        cout << "Connection accepted" << endl;

        // Checking if there is available (inactive ATMs)
        int free_atm = get_free_atm();

        if(free_atm > 0) { // There are free ATMs
            int thread_id = MAX_ATM - free_atm;
            thread_pool[thread_id].active = true; // Set ATM as active

            string message = "ACCEPT";
            if(send(client_sock , message.c_str() , message.length(), 0) < 0) {// Send inital message to client
                cout << "Connection lost!" << endl;
            } else { // Run ATM
                thread_pool[thread_id].thread = thread(process_transaction, client_sock, thread_id, DB);
                thread_pool[thread_id].thread.detach();
            }

        } else { // No free ATMs
            string message = "Not resource available";
            send(client_sock , message.c_str() , message.length(), 0);
        }

        for(int i = 0; i < MAX_ATM; ++i) {
            cout << "ATM No. " << (i+1) << ": " << thread_pool[i].active << endl;
        }

    }
    
    close(server_sock);

    return 0;
}