#include "Token.h"

using std::string;

Token::Token(){
    tokName = "empty";
    tokType = NONE;
}

Token::Token(string name,tokenType type)
{
    tokName = name;
    tokType = type;
}

string Token::get_name()
{
    return tokName;
}

tokenType Token::get_type()
{
    return tokType;
}
