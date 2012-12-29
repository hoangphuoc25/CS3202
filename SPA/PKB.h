#ifndef T11_PKB_H
#define T11_PKB_H
#include <map>
#include <set>
#include <string>
#include "ProcTable.h"
#include "VarTable.h"
#include "Node.h"

using std::map;
using std::set;
using std::string;

enum stmtType {CALLTYPE, WHILETYPE, IFTYPE, ASSIGNTYPE};

class PKB{


public:
    PKB();
    PKB(Node *root);

    // Builder methods
    VarTable* add_proc(string proc, Node* proc_root); 
    void add_node_entry(int stmtNo, stmtType type, Node* node);
    void add_constant(string n);
    void add_calls(string proc1, string proc2);

    /* Global varTable
    void add_modifies(string var, int stmtNo);
    void add_uses(string var, int stmtNo);
    void add_var(string proc, string var);
    */

    // Design extractor
    void extract_design();

    // Query methods
    // varTable
    set<int> get_modifies_var(string var);
    set<int> get_uses_var(string var);
    set<string> get_proc_modifies_var(string var);
    set<string> get_proc_uses_var(string var);
    set<string> get_var_by_proc(string proc);
    set<string> get_modifies_var_by_proc(string proc);
    set<string> get_uses_var_by_proc(string proc);

    // procTable
    set<string> get_calls(string proc);
    set<string> get_called_by(string proc);

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
    Node *progRoot;
    ProcTable procTable;
    map<int, stmtType> directory; 
    map<int, Node*> callBank;
    map<int, Node*> whileBank;
    map<int, Node*> ifBank;
    map<int, Node*> assignBank;
    map<string, vector<int> > varBank;
    set<string> constBank;
    VarTable globalVarTable;
};









#endif