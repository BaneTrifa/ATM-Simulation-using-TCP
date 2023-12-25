#ifndef DATA_BASE_H
#define DATA_BASE_H

#include <iostream>
#include <sqlite3.h>
#include "conversion.h"

using namespace std;

class Database {
private: 
    int __id; // ID field in database
    string __username; // USername field in database
    string __card_number; // Card nuber field in database
    int __pin; // Pin field in database
    float __balance; // Balance field in database

    sqlite3* db; // sqlite3 object for communicating between database and c++

    /**
     * Function for opening database.
     * @param data_base Database name.
     * @return True if database is successfully open else false.
    */
    bool open_database(const char* data_base);

public:

    // getters for fields in database
    int get_id();
    string get_username();
    string get_card_number();
    int get_pin();

    // setters for fields in database
    float get_balance();
    void set_balance(double balance);

    /**
     * Find user by username or credit card number
     * @param login_data Username or credit card number of the user.
     * @param data_base Database name
     * @return If the user exist return true else return false
    */
    bool find_user(char* login_data, const char* data_base);

    /**
     * Function for changing user's pin.
     * @param new_pin New pin.
     * @param data_base Database name
     * @return If it changes successfully, return true else return false.
    */
    bool change_pin(int new_pin, const char* data_base);

    /**
     * Function for changing user's balance.
     * @param new_pin New balance.
     * @param data_base Database name
     * @return If it changes successfully, return true else return false.
    */
    bool change_balance(double new_balance, const char* data_base);
};



#endif