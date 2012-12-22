#include "Parser.h"


Parser::Parser()
{

}

Parser::Parser(string s, ReadMode mode)
{
    tokenizer = *new Tokenizer(s.c_str(), mode);
    nextToken = tokenizer.get_token();
    stmtNo = 0;
    printer[PROC_NAME] = "PROC_NAME";
    printer[VAR_NAME] = "VAR_NAME";
    printer[OPERATOR] = "OPERATOR";
    printer[EQUALSIGN] = "EQUALSIGN";
    printer[CONSTANT] = "CONSTANT";
    printer[BRACES] = "BRACES";
    printer[BRACKETS] = "BRACKETS";
    printer[KEYWORD] = "KEYWORD";
    printer[NONE] = "NONE";
}


void Parser::init()
{
    program();
    tokenizer.closeInputFile();
}

Node *Parser::get_ast_root()
{
    return astRoot;
}


/**** match functions ***/
//match token type
void Parser::match(tokenType type)
{
    if (nextToken.get_type() == type) {
        token_out();
        currToken = nextToken;
        nextToken = tokenizer.get_token();
    } else {
        error();
    }
}

//match with a string
void Parser::match(string str)
{
     if (!str.compare(nextToken.get_name())) {
         token_out(); 
         currToken = nextToken;
         nextToken = tokenizer.get_token();
     } else {
         error();
     }
}

//match against multiple token types
void Parser::match_mul(int amt, tokenType type, ...)
{
    va_list vl;
    va_start(vl,type);
    tokenType temp;
    bool flag = false;
    
    if (nextToken.get_type() == type) {
         token_out(); 
         currToken = nextToken;
         nextToken = tokenizer.get_token();
         flag = true;
    }
    
    for (int i = 1; i < amt; i++) {
        if (flag) {
            break;
        }
        temp = (tokenType)va_arg(vl,int);    
        if (nextToken.get_type() == temp) {
            token_out();
            currToken = nextToken;
            nextToken = tokenizer.get_token();
            flag = true;
        }
    }
    
    if (flag == false) {
        error();
    }
}

//match against multiple strings
void Parser::match_mul(int amt, char* str, ...)
{
     va_list vl;
     va_start(vl,str);
     string temp;
     bool flag = false;
     temp = str;
     if (!temp.compare(nextToken.get_name())) {
         token_out();
         currToken = nextToken;
         nextToken = tokenizer.get_token();
         flag = true;
     }
     
     for (int i = 1; i < amt; i++) {
        if (flag == true) {
            break;
        }
        temp = string(va_arg(vl,char*));
        if (!temp.compare(nextToken.get_name())) {
            token_out();
            currToken = nextToken;
            nextToken = tokenizer.get_token();
            flag = true;
        }
     }

     if (flag == false) {
         error();
     }
}



//For now just exit on error
void Parser::error()
{
     printf("Error!!!\n");
     token_out();
     getchar();
     exit(1);
}


/**** Grammer rules ***/

void Parser::program(){
// handle multiple procedure

    procedure();
}

void Parser::procedure(){
    match("procedure");
    match(PROC_NAME);
    currNode = procRoot = new Node(currToken.get_name(), PROCEDURE, stmtNo);
    match("{");
    nextNode = new Node("stmt_lst", STMTLST, stmtNo);
    stmt_lst();
    match("}");
}

void Parser::stmt_lst(){
    stmt();
    if (nextToken.get_name().compare("}")) {
        stmt_lst();
    }
}

void Parser::stmt(){
    stmtNo++;
    string s = nextToken.get_name();
    if (s == "call") {
        call_stmt();
    } else if (s == "while") {
        while_stmt();
    } else if (s == "if") {
        if_stmt();
    } else {
        assign();
    }
}

void Parser::call_stmt(){
    match("call");
    if (nextToken.get_type() == VAR_NAME) {
        nextToken = Token(nextToken.get_name(), PROC_NAME);
    }
    match(PROC_NAME);
    match(";");
}

void Parser::while_stmt(){
    match("while");
    match(VAR_NAME);
    match("{");
    stmt_lst();
    match("}");
}

void Parser::if_stmt(){
    match("if");
    match(VAR_NAME);
    match("then");
    match("{");
    stmt_lst();
    match("}");
    match("else");
    match("{");
    stmt_lst();
    match("}");
}
void Parser::assign(){
    match(VAR_NAME);
    match("=");
    expr();
    match(";");
}

void Parser::expr(){
    term();
    string s = nextToken.get_name();
    if (s == "+") {
        match("+");
        expr();
    } else if (s == "-") {
        match("-");
        expr();
    }
}

void Parser::term(){
    factor();
    if (nextToken.get_name() == "*") {
        match("*");
        term();
    }
}

void Parser::factor(){
    tokenType t = nextToken.get_type();
    if (t == VAR_NAME) {
        match(VAR_NAME);
    } else if (t == CONSTANT) {
        match(CONSTANT);
    } else {
        match("(");
        expr();
        match(")");
    }
}

// Helpers


/**** Printer functions ***/


void Parser::token_out(){
    printf("Token parsed: (%s , %s)\n",nextToken.get_name().c_str(),printer[nextToken.get_type()].c_str());     

}     


