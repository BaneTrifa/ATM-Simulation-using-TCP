#include "../include/helper_functions_client.h"


void login_menu(char* uinput){
    std::cout << "Enter your Username or card ID: \t";
    std::cin >> uinput;
}

void pin_menu(char* uinput){
        std::cout << "Enter your PIN: \t";
        std::cin >> uinput;
}

int user_menu(char* uinput) {
    int option;

    std::cout << "\n1. Change Pin \n";
    std::cout << "2. Check Status \n";
    std::cout << "3. Withdraw Money\n";
    std::cout << "4. Logout\n";

    do {
        std::cout << "Enter option: \t";
        std::cin >> option;
    } while (option > 4 || option < 1);

    switch (option) {
        case 1:
            std::cout << "\n" << std::endl;
            std::cout << "Enter New Pin: \t";
            std::cin >> uinput;
            strcat(uinput, "1");
            break;
        case 2:
            strcpy(uinput, "2");
            break;
        case 3:
            std::cout << "\n" << std::endl;
            std::cout << "Enter Amount: \t";
            std::cin >> uinput;
            strcat(uinput, "3");
            break;
        case 4:
            strcpy(uinput, "4");
            break;
        default:
            std::cout << "ERROR!" << std::endl;
    }

    return option;
}

void feedback(int option, char* message) {

    switch (option) {
        case 1:
            if(strcmp(message, "ACCEPT") == 0)
                std::cout << "\nPin code changed successfully." << std::endl;
            else 
                std::cout << "\nPin code change failed." << std::endl;
            break;
        case 2:
            std::cout << "\nBalance: " << message << std::endl;
            break;
        case 3:
            if(strcmp(message, "ACCEPT") == 0)
                std::cout << "\nWithdrawal successfully." << std::endl;
            else 
                std::cout << "\nWithdrawal failed. Not enough funds." << std::endl;
            break;
        case 4:
            if(strcmp(message, "ACCEPT") == 0)
                std::cout << "\nYou are logged out!" << std::endl;
            else 
                std::cout << "\nLogout failed" << std::endl;
            break;
        default:
            std::cout << "ERROR!" << std::endl;
    }
}

void send_data(char* message, int sock){
    if( send(sock , message , strlen(message), 0) < 0)
    {
        puts("Send failed");
        exit(1);
    }
}

bool receive_data(int sock, char message[]) {
    int read_size = recv(sock, message, DEFAULT_BUFLEN, 0);
    if(read_size <= 0) { 
        std::cout << "Connection error with server!" << std::endl;
        return false;
    }
    message[read_size] = 0;
    
    return true;
} 

