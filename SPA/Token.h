#ifndef T11_TOKEN_H
#define T11_TOKEN_H
#include <string>

//Global definitions
enum tokenType {PROC_NAME, VAR_NAME, OPERATOR, EQUALSIGN, CONSTANT,
    BRACES, BRACKETS, KEYWORD, NONE}; 

class Token {

public:
    Token();
    Token(std::string name, tokenType type);
    tokenType get_type();
    std::string get_name();

private:
    std::string tokName;
    tokenType tokType;

};

#endif
