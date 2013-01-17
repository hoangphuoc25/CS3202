#ifndef T11_PKB_H
#define T11_PKB_H
#include <map>
#include <set>
#include <string>
#include <queue>
#include <stack>
#include "ProcTable.h"
#include "VarTable.h"
#include "Node.h"
#include "StmtBank.h"
#include "CFGNode.h"

using std::map;
using std::set;
using std::string;
using std::queue;
using std::stack;


class PKB{


public:
    PKB();
    PKB(Node *root, ProcTable *pt, VarTable *vt, StmtBank *sb, vector<CFGNode*> *cfg);

    // Query methods

    std::set<std::string> get_all_vars_modified_by_assign(int assign) const;
    std::set<std::string> get_all_vars_modified_by_if(int ifStmt) const;
    std::set<std::string> get_all_vars_modified_by_while(int whileStmt) const;
    std::set<std::string> get_all_vars_modified_by_call(int callStmt) const;
    std::set<std::string> get_all_vars_modified_by_stmt(int stmtNo) const;
    std::set<int> get_all_assign_modifying_var(const std::string& var) const;

    // Retrieve everything
    std::set<int> get_all_assign() const;
    std::set<int> get_all_if() const;
    std::set<int> get_all_while() const;
    std::set<int> get_all_call() const;
    std::set<std::string> get_all_vars() const;
    std::set<std::string> get_all_procs() const;
    std::setint> get_all_const();
    
    // Variables
    string get_control_var(int stmtNo);
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
    set<int> get_stmt_modifies(const std::string& var) const;
    
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

    // Next
    bool is_next(int stmt1, int stmt2);
    bool is_next_star(int stmt1, int stmt2);

    set<int> get_before(int stmtNo);
    set<int> get_before_star(int stmtNo);

    set<int> get_after(int stmtNo);
    set<int> get_after_star(int stmtNo);

    // Affects
    bool is_affects(int stmt1, int stmt2);
    bool is_affects_star(int stmt1, int stmt2);

    set<int> get_affects(int stmtNo);
    set<int> get_affects_star(int stmtNo);

    set<int> get_affected_by(int stmtNo);
    set<int> get_affected_by_star(int stmtNo);

    // Others
    bool is_stmtType(int stmtNo, stmtType type);
    bool is_valid_stmtNo(int stmtNo);

    set<int> get_all_stmt();
    set<int> get_all_stmt_by_proc(string procName);

    set<int> filter_by_proc(string procName, set<int> s);
    set<int> filter_by_stmtType(stmtType type, set<int> s);
    int filter_by_stmtType(stmtType type, int stmtNo);

    // Constant
    bool is_const_exist(string n);

    // Debuggers
    Node* get_progRoot();
    ProcTable* get_procTable();
    StmtBank* get_stmtBank();
    VarTable* get_varTable();
    vector<CFGNode*>* get_CFG();
    set<int> visited;
    void dfs(CFGNode *node);

private:

    Node *progRoot;
    ProcTable *procTable;
    VarTable *varTable;
    StmtBank *stmtBank;
    vector<CFGNode*> *CFG;

    const set<string> EMPTY_STRINGSET;
    const set<int> EMPTY_INTSET;
};

#endif