#include "../include/helper_functions_server.h"

std::vector<thread_t> thread_pool(MAX_ATM);


bool receive_data_server(int sock, char message[], int thread_id) {
    int read_size = recv(sock, message, DEFAULT_BUFLEN, 0);
    if(read_size <= 0) { 
        std::cout << "ATM No. " << thread_id << " disconnected!~" << std::endl;
        thread_pool[thread_id].active = false;
        return false;
    }
    message[read_size] = 0;
    
    return true;
} 

bool send_data_server(int sock, const char* message, int thread_id) {
    if( send(sock , message , strlen(message), 0) < 0)
    {
        std::cout << "ATM No. " << thread_id << " disconnected!~" << std::endl;
        thread_pool[thread_id].active = false;
        return false;
    }

    return true;
}

int get_free_atm() {
    int free_threads = 0;
    for(int i = 0; i < MAX_ATM; i++) {
        if(!thread_pool[i].active) free_threads++;
    }

    return free_threads;
}

/*
    return value: database name
*/
const char* get_DB_name() {
    std::string s = "atm.db";

    return s.c_str();
}

/*
    if vaule is false return DECLINE
    else return ACCEPT
*/
const char* get_message(bool value) { 
    std::string true_val = "ACCEPT";
    std::string false_val = "DECLINE";

    if(value) 
        return true_val.c_str();
    else 
        return false_val.c_str();
}
