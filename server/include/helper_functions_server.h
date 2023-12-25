#ifndef HELPER_FN_SERVER__H
#define HELPER_FN_SERVER_H

#include <iostream>
#include <sys/socket.h> //socket
#include <arpa/inet.h>  //inet_addr
#include <vector>
#include <thread>
#include <string.h>

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT   27015
#define DB "atm.db"
#define MAX_ATM 5

struct thread_t {
    std::thread thread;
    bool active;
};
extern std::vector<thread_t> thread_pool; // Vecotr that cointains all available ATMs (active or inactive)

/**
 * Function responsible for recieving messages from the client.
 * @param sock Number of client's socket on which it is connected to the server.
 * @param message Buffer for recieving incoming message from the client.
 * @param thread_id ID of thread which corespods to active ATM
 * @return Return false if client disconnected or return true if message is recieved properly
*/
bool receive_data_server(int sock, char message[], int thread_id);

/**
 * Function responsible for sending messages to the client.
 * @param sock Number of client's socket on which it is connected to the server.
 * @param message Buffer for recieving incoming message from the client.
 * @param thread_id ID of thread which corespods to active ATM
 * @return Return true if message is sent properly else return false
*/
bool send_data_server(int sock, const char* message, int thread_id);

/**
 * @return Return number of free threds (ATMs)
*/
int get_free_atm();

/**
 * @return Return database name in type - const char*
*/
const char* get_DB_name();

/**
 * @return Returns "ACCEPT" if value is true else return "DELINE" in type - const char*
*/
const char* get_message(bool value);

#endif
