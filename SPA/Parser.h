#ifndef T11_PARSER_H
#define T11_PARSER_H

#include <cstdio>
#include <string>
#include <stack>
#include <map>
#include <set>
#include <queue>
#include "Tokenizer.h"
#include "Node.h"
#include "VarTable.h"
#include "PKB.h"
#include "CFGNode.h"

using std::map;
using std::set;
using std::stack;
using std::queue;

class Parser {
public:
    Parser();
    Parser(string s ,ReadMode mode);

    void init();
    PKB* get_pkb();

    Node *get_ast_root();
    Node *get_proc_root();

    Node* yard();

private:
    // Tokens
    Tokenizer tokenizer;
    Token nextToken;
    Token currToken;
    string state;

    // Info structures
    int stmtNo;
    string procName;
   
    Node *astRoot;
    VarTable *varTable;
    StmtBank *stmtBank;
    ProcTable *procTable;
    vector<CFGNode*> *CFG;

    // AST builder nodes
    Node *procRoot;
    Node *currNode;
    Node *nextNode;
    Node *tempNode;
    Node *assignNode;

    // Shunting yard stacks
    stack<Node*> opStack;
    stack<Node*> outStack;
    bool makeTree;
    bool treeError;
    Node *treeNode;

    // Printer data
    map<tokenType, string> printer; 

    // Updaters
    void update_tables();
    void update_calls();
    void update_nodes(Node *n);
    void combine_node_up(Node *n1, Node* n2);

    //Match functions
    void match(tokenType type);
    void match(string str);
    void error();
    void error(tokenType type);
    void error(string s);

    //Grammer rules
    void program();
    void procedure();
    void stmt_lst();
    // returns the statement number
    int stmt();
    void call_stmt();
    void while_stmt();
    void if_stmt();
    void assign();
    void expr();
    void term();
    void factor();

    // Shunting Yard
    void join();
    void check_pre(Node *op);
    map<string, int> op_pre;

    // CFG builders
    void init_CFG();
    CFGNode* build_CFG(int stmtNo);
    void make_CFG();
    void set_edge(CFGNode* outNode, CFGNode* inNode, int out, int in);



    //Printer functions
    void token_out();

    //Helper
    void create_node(string name, NodeType type);
    void add_modifies(Node* n, const std::string& var);
    void add_uses(Node* n, string var);

};

#endif
