#ifndef T11_PKB_H
#define T11_PKB_H
#include <map>
#include <set>
#include <string>
#include <queue>
#include "ProcTable.h"
#include "VarTable.h"
#include "Node.h"
#include "StmtBank.h"

using std::map;
using std::set;
using std::string;
using std::queue;

class PKB{


public:
    PKB();
    PKB(Node *root, ProcTable *pt, VarTable *vt, StmtBank *sb);

    // Query methods
    
    // Variables
    
    string get_control_var(int stmtNo);
    set<string> get_all_vars();
    set<string> get_all_vars_by_proc(string procName);

    // Calls
    bool is_calls(string proc1, string proc2);
    bool is_calls_star(string proc1, string proc2);

    set<string> get_calls(string procName);
    set<string> get_calls_star(string procName);

    set<string> get_called_by(string procName);
    set<string> get_called_by_star(string procName);

    // Modifies
    bool is_modifies(string procName, string varName);
    bool is_modifies(int stmtNo, string varName);
        
    set<string> get_proc_modifies(string var);
    set<int> get_stmt_modifies(string var);
    
    set<string> get_var_proc_modifies(string procName);
    set<string> get_var_stmt_modifies(int stmtNo);

    // Uses
    bool is_uses(string procName, string varName);
    bool is_uses(int stmtNo, string varName);

    set<string> get_proc_uses(string var);
    set<int> get_stmt_uses(string var);
    
    set<string> get_var_proc_uses(string procName);
    set<string> get_var_stmt_uses(int stmtNo); 

    // Parent
    bool is_parent(int stmt1, int stmt2);
    bool is_parent_star(int stmt1, int stmt2);

    int get_parent(int stmtNo);
    set<int> get_parent_star(int stmtNo);
    
    set<int> get_children(int stmtNo);
    set<int> get_children_star(int stmtNo);

    // Follows
    bool is_follows(int stmt1, int stmt2);
    bool is_follows_star(int stmt1, int stmt2);

    int get_successor(int stmtNo);
    set<int> get_successor_star(int stmNo);

    int get_predecessor(int stmtNo);
    set<int> get_predecessor_star(int stmtNo);

    // Constant
    set<string> get_all_const();
    bool is_const_exist(string n);

    // Others
    bool is_stmtType(int stmtNo, stmtType type);

    set<int> get_all_stmt();
    set<int> get_all_stmt_by_proc(string procName);

    set<int> filter_by_proc(string procName, set<int> s);
    set<int> filter_by_stmtType(stmtType type, set<int> s);
    int filter_by_stmtType(stmtType type, int stmtNo);

    // Debuugers
    Node* get_progRoot();
    ProcTable* get_procTable();
    StmtBank* get_stmtBank();
    VarTable* get_varTable();


private:

    Node *progRoot;
    ProcTable *procTable;
    VarTable *varTable;
    StmtBank *stmtBank;

    const set<string> EMPTY_STRINGSET;
    const set<int> EMPTY_INTSET;
};

#endif