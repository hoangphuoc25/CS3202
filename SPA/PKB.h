#ifndef T11_PKB_H
#define T11_PKB_H
#include <map>
#include <set>
#include <string>
#include <queue>
#include <stack>
#include "PQL.h"
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

    /*
     * Modifies(X,var); Retrieves all var modified by X, where X is
     * a synonym represented by integers.
     * @param xType type of X
     * @param useless type of variable, which is ENT_VAR. Since the
     *                second synonym argument of Modifies must be ENT_VAR,
     *                this field is effectively useless and ignored
     * @return a set of variable names modified by X
     */
    std::set<std::string> get_all_vars_modified_by_int_X(DesignEnt xType,
            DesignEnt useless, int stmt) const;
    /*
     * Modifies(X,var); Retrieves all var modified by X, where X is
     * a synonym represented by strings.
     * @param useless type of variable, which is ENT_VAR. Since the
     *                second synonym argument of Modifies must be ENT_VAR,
     *                this field is effectively useless and ignored
     * @return a set of variable names modified by X
     */
    std::set<std::string> get_all_vars_modified_by_string_X(DesignEnt xType,
            DesignEnt useless, const std::string& x) const;
    /*
     * Modifies(X,var); Given a varname, retrieves all X modifying it,
     * where X is a synonym with integer values.
     * @param xType type of X
     * @param useless type of variable, which is ENT_VAR. Since the
     *                second synonym argument of Modifies must be ENT_VAR,
     *                this field is effectively useless and ignored
     * @param varName variable name
     */
    std::set<int> get_all_int_X_modifying_var(DesignEnt xType,
            DesignEnt useless, const std::string& varName) const;
    /*
     * Modifies(X,var); Given a varname, retrieves all X modifying it,
     * where X is a synonym with string values.
     * @param xType type of X
     * @param useless type of variable, which is ENT_VAR. Since the
     *                second synonym argument of Modifies must be ENT_VAR,
     *                this field is effectively useless and ignored
     * @param varName variable name
     */
    std::set<std::string> get_all_string_X_modifying_var(DesignEnt xType,
            DesignEnt useless, const std::string& varName) const;

    // Retrieve everything
    std::set<int> get_all_assign() const;
    std::set<int> get_all_if() const;
    std::set<int> get_all_while() const;
    std::set<int> get_all_call() const;
    std::set<int> get_all_stmt() const;
    std::set<int> get_all_progline() const;
    std::set<int> get_all_stmtLst() const;
    std::set<std::string> get_all_vars() const;
    std::set<std::string> get_all_procs() const;
    std::set<int> get_all_const() const;

    /*
     * Returns the procedure called by the call stmt, or an
     * empty string if the statement does not exist or is not
     * a call statement.
     */
    std::string get_call_procName(int callStmt) const;
    
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
    bool has_const(int n) const;

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