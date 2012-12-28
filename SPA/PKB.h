#ifndef T11_PKB_H
#define T11_PKB_H
#include <map>
#include <set>
#include <string>
#include "VarTable.h"
#include "Node.h"

using std::map;
using std::set;
using std::string;

enum stmtType {CALLTYPE, WHILETYPE, IFTYPE, ASSIGNTYPE};

class PKB{


public:
    PKB();
    PKB(Node* root);
    
    // Builder methods
    void add_modifies(string var, int stmtNo);
    void add_uses(string var, int stmtNo);
    void add_node_entry(int stmtNo, stmtType type, Node* node);

    // Design extractor
    void extract_design();

    // Query methods
    // varTable
    set<int> get_modifies_var(string var);
    set<int> get_uses_var(string var);

    // procTable
  
    // AST
    bool is_stmt_type(int stmtNo, stmtType type);
    bool is_stmt_modifies(int stmtNo);
    bool is_stmt_uses(int stmtNo);
    set<int> get_stmt_modifies(int stmtNo);
    set<int> get_stmt_uses(int stmtNo);
    int get_control_var(int stmtNo);

    //Utility
    Node* get_node(int stmtNo);

    // Printers

private:
    Node* progRoot;
    VarTable varTable;
    map<int, stmtType> directory; 
    map<int, Node*> callBank;
    map<int, Node*> whileBank;
    map<int, Node*> ifBank;
    map<int, Node*> assignBank;

};









#endif