#ifndef T11_PARSER_H
#define T11_PARSER_H

#include <cstdio>
#include <string>
#include <cctype>
#include <cstdarg>
#include <queue>
#include "Tokenizer.h"
#include "Node.h"
#include "VarTable.h"
#include <map>
#include <set>

using std::map;
using std::set;

class Parser {
public:
    Parser();
    Parser(string s ,ReadMode mode);
	VarTable varTable;
    void init();
    Node *get_ast_root();


private:
    Node *astRoot;
    Tokenizer tokenizer;
    Token nextToken;
    Token currToken;

    std::queue<Node*> varQueue;
    map<int,Node*> assignBank;
    map<int,Node*> whileBank;
    set<int> constTable;
    map<tokenType, string> printer; 

    int stmtNo;

    Node *currNode;
    Node *nextNode;
    Node *tempNode;
    Node *assignNode;

    //Match functions
    void match(tokenType type);
    void match(string str);
    void match_mul(int amt, tokenType type, ...);
    void match_mul(int amt, char* str, ...);
    void error();

    //Grammer rules
    void program();
    void procedure();
    void stmt_lst();
    void stmt();
    void call_stmt();
    void while_stmt();
    void if_stmt();
    void assign();
    void expr();
    void term();
    void factor();

    //Printer functions
    void token_out();
    
    //Helper


};

#endif