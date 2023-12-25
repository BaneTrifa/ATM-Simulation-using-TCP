#include <sys/socket.h> //socket
#include <arpa/inet.h>  //inet_addr
#include <fcntl.h>     //for open
#include <unistd.h>    //for close
#include "../include/helper_functions_client.h"


int main(int argc , char *argv[])
{
    int sock, read_size = 0;
    struct sockaddr_in server;
    char uinput[DEFAULT_BUFLEN];    // user input option
    char message[DEFAULT_BUFLEN];   // recieved message from server

    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(DEFAULT_PORT);

    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }


    if(!receive_data(sock, message)) return 1;

    // Check initial (test) message
    if(strcmp(message, "ACCEPT") != 0){
        std::cout << "Initialization failed" << std::endl;
        return 1;
    } 

    
    while(1) {

        // Enter and send username or id
        do {
            login_menu(uinput);
            send_data(uinput,sock);

            //Receive identification confirmation
            if(!receive_data(sock, message)) return 1;

        } while(strcmp(message, "ACCEPT") != 0);


        // Enter and send pin
        do {
            pin_menu(uinput);
            send_data(uinput,sock);

            //Receive pin confirmation
            if(!receive_data(sock, message)) return 1;

        } while(strcmp(message, "ACCEPT") != 0);

        system("clear");

        while(1){
            // Enter option and send to server
            int option = user_menu(uinput);
            send_data(uinput,sock);

            if(option == 4) {
                system("clear");
                break;
            }

            if(!receive_data(sock, message)) return 1;

            // print feedback to client
            feedback(option, message);
        }
    }

    close(sock);

    return 0;
}