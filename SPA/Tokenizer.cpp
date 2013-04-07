// disable warnings about using fopen
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Tokenizer.h"

/**** Tokeniser functions ***/

Tokenizer::Tokenizer()
{
    strBuffer.clear();
    tokenNo = 0;
    currChar = ' ';
    done = false;
    procFlag = false;
}

Tokenizer::Tokenizer(string s, ReadMode mode)
{
    strBuffer.clear();
    tokenNo = 0;
    currChar = ' ';
    done = false;
    procFlag = false;
    fmode = mode;
    if (mode == 0) {
        pFile = fopen(s.c_str(),"r");
        printf("%s opened.\n",s.c_str());
        if (pFile == NULL) {
            perror ("Error opening file");
        }
    } else {
        inputString = s;
        end = s.length();
        start = 0;
    }
}

Tokenizer::~Tokenizer() {}

void Tokenizer::closeInputFile()
{
    if (fmode == FROMFILE && pFile) {
        fclose(pFile);
        pFile = NULL;
    }
}



char Tokenizer::myget()
{
    if (start >= end) {
        return EOF;
    }
    return inputString[start++];
}

void Tokenizer::nextChar()
{
    if (fmode == 0) {
    currChar = fgetc(pFile);
    } else {
    currChar = myget();
    }
}

bool Tokenizer::is_name(string t)
{
    int len = t.length();
    bool flag = false;
    if (isalpha(t[0])) {
        flag = true;
        for (int i = 1; i < len; i++) {
            if (!isalnum(t[i])) {
                flag = false;
                break;
            }
        }
    }
    return flag;
}

bool Tokenizer::is_const(string t)
{
    int len = t.length();
    bool flag = true;
    for (int i = 0; i < len; i++){
        if (!isdigit(t[i])) {
            flag = false;
            break;
        }
    }
    return flag;
}

bool Tokenizer::is_oper(string t)
{
    return (t.length() == 1 && (t[0] == '+' || t[0] == '-'
        || t[0] == '*' || t[0] == '/'));
}

bool Tokenizer::is_equalsign(string t)
{
    return (t.length() == 1 && t[0] == '=');
}

bool Tokenizer::is_braces(string t)
{
    return (t.length() == 1 && (t[0] == '{' || t[0] == '}'));
}

bool Tokenizer::is_brackets(string t)
{
    return (t.length() == 1 && (t[0] == '(' || t[0] == ')'));
}

bool Tokenizer::is_keyword(string t)
{
    return (!t.compare("procedure") || !t.compare("call")
        || !t.compare("while") || !t.compare("if")
        || !t.compare("then") || !t.compare("else"));
}

Token Tokenizer::get_token()
{
    //bool flag = false;  
    if (currChar == ' ' || currChar== '\n' || currChar == '\t' || isalnum(currChar) || currChar == EOF) {
        while (true) {
            if (!isalnum(currChar)) {
                if (fmode == 0) {
                    if ((currChar = fgetc(pFile)) == EOF) {
                        break;
                    }
                } else {
                    if ((currChar = myget()) == EOF) {
                        break;
                    }
                }
            }
          
            // remove blank spaces, tabs and newline
            if (currChar == ' ' || currChar== '\n' || currChar == '\t') {
                continue;
            }
    
            // get tokenString
            if (!isalnum(currChar)) {
                strBuffer.append(currChar);
                /* if (!flag) {
                    nextChar();
                } */
                nextChar();
            } else {
                while(isalnum(currChar)) {
                    //flag = true;
                    strBuffer.append(currChar);
                    nextChar();
                }
            }

            break;
        }
    } else {
        strBuffer.append(currChar);
        nextChar();
    }
            
    tokenString = strBuffer.toString();
    strBuffer.clear();
    if (tokenString.empty()) {
        done = true;
        return Token("Empty",NONE);
    }

    // determine token type
    tokenNo++;
    if (!tokenString.compare("procedure")) {
        procFlag = true;
    }

    if (is_keyword(tokenString)) {
        return Token(tokenString, KEYWORD);
    } else if (is_name(tokenString)) {
        if (procFlag) {
            procFlag = false;
            return Token(tokenString, PROC_NAME);
        } else {
            return Token(tokenString, VAR_NAME);
        }
    } else if (is_const(tokenString)) {
        return Token(tokenString, CONSTANT);
    } else if (is_oper(tokenString)) {
        return Token(tokenString, OPERATOR);
    } else if (is_equalsign(tokenString)) {
        return Token(tokenString, EQUALSIGN);
    } else if (is_braces(tokenString)) {
        return Token(tokenString, BRACES);
    } else if (is_brackets(tokenString)) {
        return Token(tokenString, BRACKETS);
    } else {
        return Token(tokenString, NONE);
    }
}

bool Tokenizer::is_done()
{
    return done;
}

