#ifndef T11_PARSER_H
#define T11_PARSER_H

#include <cstdio>
#include <string>
#include <cctype>
#include <cstdarg>
#include <stack>
#include "Tokenizer.h"
#include "Node.h"
#include "VarTable.h"
#include <map>
#include <set>

using std::map;
using std::set;
using std::stack;

class Parser {
public:
    Parser();
    Parser(string s ,ReadMode mode);
	VarTable varTable;
    void init();
    Node *get_ast_root();
    Node* yard();


private:
    Node *astRoot;
    Tokenizer tokenizer;
    Token nextToken;
    Token currToken;
    map<tokenType, string> printer; 

    int stmtNo;

    Node *procRoot;
    Node *currNode;
    Node *nextNode;
    Node *tempNode;
    Node *assignNode;

    stack<Node*> opStack;
    stack<Node*> outStack;

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
    void create_node(string name, NodeType type);

    // Shunting Yard
    void join();
    void check_pre(Node *op);
    map<string, int> op_pre;

};

#endif
