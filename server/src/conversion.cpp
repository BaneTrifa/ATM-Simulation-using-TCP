#include "../include/conversion.h"


std::string char_to_string(const char* input) { 
    std::string s;
    s.assign(input, strlen(input));

    return s;
}

int char_to_int(char* input) {
    int rv = 0;
    sscanf(input, "%d", &rv);

    return rv;
}

const char* double_to_char(double input) {
    std::string s =  std::to_string(input);

    return s.c_str();
}