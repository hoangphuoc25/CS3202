#ifndef T11_TOKENIZER_H
#define T11_TOKENIZER_H

#include <cstdio>
#include <string>
#include <cctype>
#include "StringBuffer.h"
#include "Token.h"

using std::string;

enum ReadMode {
    FROMFILE, FROMSTRING
};

class Tokenizer {

public:
    Tokenizer();
    Token get_token();
    Tokenizer(string s, ReadMode mode);
    ~Tokenizer();
    void closeInputFile();
    void reset();
    bool is_done();

private:
    StringBuffer strBuffer;
    string tokenString;
    Token nextToken();
    char currChar;
    int tokenNo;

    string inputString;
    char myget();
    void nextChar();
    int start;
    int end;
    ReadMode fmode;
    FILE *pFile;
    bool done;

    bool is_name(string t);
    bool is_const(string t);
    bool is_oper(string t);
    bool is_equalsign(string t);
    bool is_braces(string t);
    bool is_brackets(string t);
    bool is_keyword(string t);


};


#endif
