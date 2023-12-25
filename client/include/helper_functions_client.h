#ifndef HELPER_FN_CLIENT__H
#define HELPER_FN_CLIENT_H

#include <iostream>
#include <string.h>
#include <sys/socket.h> //socket

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT   27015

/**
 * Display login menu on the terminal and waits for user input (credit card id or username)
 * @param uinput A variable that returns user input.
*/
void login_menu(char* uinput);

/**
 * Display pin menu on the terminal and waits for user input (credit card pin)
 * @param uinput A variable that returns user input.
*/
void pin_menu(char* uinput);

/**
 * Display user menu on the terminal and waits for user input (one of the options - Change Pin,
 * Check Status, Withdraw Money and Logout)
 * @param uinput A variable that returns user input.
*/
int user_menu(char* uinput);

/**
 * Based on the user's choice and the server's feedback, 
 * it prints whether the selected action was successfully or 
 * unsuccessfully executed.
 * @param option Option that user selected.
 * @param message Feedback message from server (ACCEPT/DECLINE).
*/
void feedback(int option, char* message);

/**
 * Function responsible for sending messages to the server.
 * @param message Message.
 * @param sock Number of client's socket on which it is connected to the server.
*/
void send_data(char* message, int sock);

/**
 * Function responsible for recieving messages from the server.
 * @param message Buffer for recieving incoming message from server.
 * @param sock Number of client's socket on which it is connected to the server.
*/
bool receive_data(int sock, char message[]);

#endif