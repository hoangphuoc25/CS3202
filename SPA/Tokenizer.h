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
    Tokenizer(string s, ReadMode mode);
    ~Tokenizer();

    void closeInputFile();

    Token get_token();
    bool is_done();

private:
    StringBuffer strBuffer;
    string tokenString;
    char currChar;
    int tokenNo;
    bool done;

    string inputString;
    int start;
    int end;
    ReadMode fmode;
    FILE *pFile;

    Token nextToken();
    char myget();
    void nextChar();

    bool is_name(string t);
    bool is_const(string t);
    bool is_oper(string t);
    bool is_equalsign(string t);
    bool is_braces(string t);
    bool is_brackets(string t);
    bool is_keyword(string t);

};


#endif
