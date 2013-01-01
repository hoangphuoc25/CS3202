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

    // Builder methods



    //to modify
    /*// Design extractor/*
    void extract_design();
    void update_vars(string procName);
    void update_procVarTable(string procName); //propagate calls info
    */
    // to update
    // Query methods
    // varTable
    set<int> get_modifies_var(string var);
    set<int> get_uses_var(string var);
    set<string> get_proc_modifies_var(string var);
    set<string> get_proc_uses_var(string var); 
    set<string> get_var_by_proc(string procName);
    set<string> get_modifies_var_by_proc(string procName);
    set<string> get_uses_var_by_proc(string procName);
/*
    set<string> get_all_vars_by_proc(string procName);
    set<string> get_all_vars();
    */

    // procTable
    set<string> get_calls(string procName);
    set<string> get_called_by(string procName);
    ProcTable get_procTable();

    // AST

    bool is_stmt_modifies(int stmtNo, string varName);
    bool is_stmt_uses(int stmtNo, string varName);
    set<string> get_stmt_modifies(int stmtNo);
    set<string> get_stmt_uses(int stmtNo);
    string get_control_var(int stmtNo);
    Node* get_progRoot();





    // Printers

private:

    Node *progRoot;
    ProcTable *procTable;
    VarTable *varTable;
    StmtBank *stmtBank;

    const set<string> EMPTY_STRINGSET;

};

#endif