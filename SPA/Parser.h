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

enum stmtType {CALLTYPE, WHILETYPE, IFTYPE, ASSIGNTYPE};

class Parser {
public:
    Parser();
    Parser(string s ,ReadMode mode);
    void init();
    Node *get_ast_root();
    Node *get_proc_root();
    Node* yard();

    void dumpBank();


private:
    // Tokens
    Tokenizer tokenizer;
    Token nextToken;
    Token currToken;

    // AST info
    Node *astRoot;
    int stmtNo;
    VarTable varTable;
    map<int, stmtType> directory; 
    map<int, Node*> callBank;
    map<int, Node*> whileBank;
    map<int, Node*> ifBank;
    map<int, Node*> assignBank;

    // AST builder nodes
    Node *procRoot;
    Node *currNode;
    Node *nextNode;
    Node *tempNode;
    Node *assignNode;

    // Shunting yard stacks
    stack<Node*> opStack;
    stack<Node*> outStack;

    // Printer data
    map<tokenType, string> printer; 

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
    void add_modifies(Node* n, string var);
    void add_uses(Node* n, string var);

    // Shunting Yard
    void join();
    void check_pre(Node *op);
    map<string, int> op_pre;

};

#endif
