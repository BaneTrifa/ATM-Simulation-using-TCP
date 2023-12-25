#include "../include/data_base.h"

// Structure for filling with user information from database (operation SELECT*)
struct row {
    int id;
    string username;
    string card_number;
    int pin;
    float balance;
};

static int callback(void* data, int argc, char** argv, char** colName) {

    struct row* el = (row*) data;

    for(int i = 0; i < argc; i++) {
        if(strcmp(colName[i],"id") == 0)
            el->id = atoi(argv[i]);
        else if(strcmp(colName[i],"username") == 0)
            el->username = argv[i];
        else if(strcmp(colName[i],"card_number") == 0)
            el->card_number = argv[i];
        else if(strcmp(colName[i],"pin") == 0)
            el->pin = atoi(argv[i]);
        else if(strcmp(colName[i],"balance") == 0)
            el->balance = atof(argv[i]);
        
    }

    return 0;
}


bool Database::open_database(const char* data_base) {
    int exit = sqlite3_open(data_base, &db);
    if (exit != SQLITE_OK) {
        fprintf(stderr, "Can't open database %s: %s\n", data_base, sqlite3_errmsg(db));

        return false;
    }

    return true;
}


bool Database::find_user(char* login_data, const char* data_base) {
    bool rv = false;

    if(!open_database(data_base))
        return false;

    // select
    std::string sql = "SELECT * FROM USERS WHERE username='" + char_to_string(login_data) + "'"
                      " OR card_number='" + login_data + "' ;";
    

    // Fill 'element' with user information
    struct row element;
    int exit = sqlite3_exec(db, sql.c_str(), callback, &element, NULL);

    // Assign information to class fields
    if (exit == SQLITE_OK && element.username != "") {
        rv = true;

        __id = element.id;
        __username = element.username;
        __card_number = element.card_number;
        __pin = element.pin;
        __balance = element.balance;

    } else if (exit == SQLITE_OK && element.username == ""){ 
        cout << "Can't find user " << login_data <<  " in database " << data_base << endl;
    } else {
        cout << "Can't find user " << login_data <<  " in database " << data_base << endl;
    }

    sqlite3_close(db);
    return rv;
}

bool Database::change_pin(int new_pin, const char* data_base) {

    if(!open_database(data_base))
        return false;

    std::string sql( "UPDATE USERS set pin=" + to_string(new_pin) + " WHERE id=" + to_string(__id) ); 
    int exit = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);

    if(exit == SQLITE_OK) 
        return true;
    else 
        return false;
}

bool Database::change_balance(double new_balance, const char* data_base) {
    if(!open_database(data_base))
        return false;

    std::string sql( "UPDATE USERS set balance=" + to_string(new_balance) + " WHERE id=" + to_string(__id) ); 
    int exit = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);

    if(exit == SQLITE_OK) 
        return true;
    else 
        return false;
}

int Database::get_id() {
    return __id;
}
string Database::get_username(){
    return __username;
}
string Database::get_card_number(){
    return __card_number;
}
int Database::get_pin(){
    return __pin;
}
float Database::get_balance(){
    return __balance;
}
void Database::set_balance(double balance){
    __balance = balance;
}