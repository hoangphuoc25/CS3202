#ifndef T11_PKB_H
#define T11_PKB_H
#include <map>
#include <set>
#include <string>
#include <queue>
#include "ProcTable.h"
#include "VarTable.h"
#include "Node.h"

using std::map;
using std::set;
using std::string;
using std::queue;

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

    // Design extractor
    void extract_design();
    void update_vars(string procName);
    void insert_procVarTable(string procName);
    void update_procVarTable(string procName);

    // Query methods
    // varTable
    /*set<int> get_modifies_var(string var);
    set<int> get_uses_var(string var);
    set<string> get_proc_modifies_var(string var);
    set<string> get_proc_uses_var(string var); */
    set<string> get_var_by_proc(string procName);
    //set<string> get_modifies_var_by_proc(string procName);
    //set<string> get_uses_var_by_proc(string procName);

    // procTable
    set<string> get_calls(string procNAme);
    set<string> get_called_by(string procName);

    // AST
    bool is_stmt_type(int stmtNo, stmtType type);
    bool is_stmt_modifies(int stmtNo, string varName);
    bool is_stmt_uses(int stmtNo, string varName);
    set<string> get_stmt_modifies(int stmtNo);
    set<string> get_stmt_uses(int stmtNo);
    string get_control_var(int stmtNo);

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
    VarTable procVarTable;
    const set<string> EMPTY_STRINGSET;
};

#endif