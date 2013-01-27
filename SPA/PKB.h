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
     * @param yType type of Y. This can only be ENT_VAR
     * @return a set of variable names modified by X
     */
    std::set<std::string> modifies_X_Y_get_string_Y_from_int_X
        (DesignEnt xType, DesignEnt yType, int stmt) const;
    /*
     * Modifies(X,var); Retrieves all var modified by X, where X is
     * a synonym represented by strings.
     * @param yType type of Y. This can only be ENT_VAR
     * @return a set of variable names modified by X
     */
    std::set<std::string> modifies_X_Y_get_string_Y_from_string_X
        (DesignEnt xType, DesignEnt yType, const std::string& x) const;
    /*
     * Modifies(X,var); Given a varname, retrieves all X modifying it,
     * where X is a synonym with integer values.
     * @param xType type of X
     * @param yType type of Y. This can only be ENT_VAR
     * @param varName variable name
     */
    std::set<int> modifies_X_Y_get_int_X_from_string_Y(DesignEnt xType,
            DesignEnt yType, const std::string& varName) const;
    /*
     * Modifies(X,var); Given a varname, retrieves all X modifying it,
     * where X is a synonym with string values.
     * @param xType type of X
     * @param yType type of Y. This can only be ENT_VAR
     * @param varName variable name
     */
    std::set<std::string> modifies_X_Y_get_string_X_from_string_Y
            (DesignEnt xType, DesignEnt yType,
                const std::string& varName) const;

    /*
     * Uses(X,Y); given synonym Y (string), retrieve all X (int)
     * such that Uses(X,Y) holds.
     * @param xType type of X
     * @param yType type of Y. This can only be ENT_VAR
     * @param varName variable name of Y
     * @return set of X such that Uses(X,Y)
     */
    std::set<int> uses_X_Y_get_int_X_from_string_Y(DesignEnt xType,
            DesignEnt yType, const std::string& varName) const;
    /*
     * Uses(X,Y); given synonym Y (string), retrieve all X (string)
     * such that Uses(X,Y) holds.
     * @param xType type of X
     * @param yType type of Y. This can only be ENT_VAR
     * @param varName variable name of Y
     * @return set of X such that Uses(X,Y)
     */
    std::set<std::string> uses_X_Y_get_string_X_from_string_Y
            (DesignEnt xType, DesignEnt yType,
                const std::string& varName) const;
    /*
     * Uses(X,Y); given synonym X (int), retrieve all Y (string)
     * such that Uses(X,Y) holds.
     * @param xType type of X
     * @param yType type of Y. This can only be ENT_VAR
     * @param stmtNo statement number of X
     * @return set of Y such that Uses(X,Y)
     */
    std::set<std::string> uses_X_Y_get_string_Y_from_int_X
            (DesignEnt xType, DesignEnt yType, int stmtNo) const;
    /*
     * Uses(X,Y); given synonym X (string), retrieve all Y (string)
     * such that Uses(X,Y) holds.
     * @param xType type of X
     * @param yType type of Y. This can only be ENT_VAR
     * @param x string value of X
     * @return set of Y such that Uses(X,Y)
     */
    std::set<std::string> uses_X_Y_get_string_Y_from_string_X
            (DesignEnt xType, DesignEnt yType,
                const std::string& x) const;
    /*
     * Given X (string) and Y (string), checks if Uses(X,Y) is true.
     * @param xType type of X
     * @param x value of X
     * @param yType type of Y
     * @param y value of Y
     * @return true if Uses(X,Y), false otherwise
     */
    bool uses_query_string_X_string_Y(DesignEnt xType,
            const std::string& x, DesignEnt yType, const std::string& y)
                const;

    /*
     * Calls(X,Y); given Y (string), get all X (string) such that
     * Calls(X,Y)
     * @param xType type of X
     * @param yType type of Y
     * @param y string value of Y
     * @return set of X (string) such that Calls(X,Y)
     */
    std::set<std::string> calls_X_Y_get_string_X_from_string_Y
            (DesignEnt xType, DesignEnt yType,
                const std::string& y) const;
    /*
     * Calls(X,Y); given X (string), get all Y (string) such that
     * Calls(X,Y)
     * @param xType type of X
     * @param yType type of Y
     * @param x string value of X
     * @return set of Y (string) such that Calls(X,Y)
     */
    std::set<std::string> calls_X_Y_get_string_Y_from_string_X
            (DesignEnt xType, DesignEnt yType,
                const std::string& x) const;

    /*
     * Calls*(X,Y); given Y (string), get all X (string) such that
     * Calls*(X,Y)
     * @param xType type of X
     * @param yType type of Y
     * @param y string value of Y
     * @return set of X (string) such that Calls*(X,Y)
     */
    std::set<std::string> callsStar_X_Y_get_string_X_from_string_Y
            (DesignEnt xType, DesignEnt yType,
                const std::string& y) const;
    /*
     * Calls*(X,Y); given X (string), get all Y (string) such that
     * Calls*(X,Y)
     * @param xType type of X
     * @param yType type of Y
     * @param x string value of X
     * @return set of Y (string) such that Calls*(X,Y)
     */
    std::set<std::string> callsStar_X_Y_get_string_Y_from_string_X
            (DesignEnt xType, DesignEnt yType,
                const std::string& x) const;

    /*
     * Parent(X,Y); given Y (int), retrieve all X (int) such that
     * Parent(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param y integer value of Y
     * @return set of X (int) such that Parent(X,Y)
     */
    std::set<int> parent_X_Y_get_int_X_from_int_Y(DesignEnt xType,
            DesignEnt yType, int y) const;
    /*
     * Parent(X,Y); given X (int), retrieve all Y (int) such that
     * Parent(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param x integer value of X
     * @return set of Y (int) such that Parent(X,Y)
     */
    std::set<int> parent_X_Y_get_int_Y_from_int_X(DesignEnt xType,
            DesignEnt yType, int x) const;

    /*
     * Parent*(X,Y); given Y (int), retrieve all X (int) such that
     * Parent*(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param y integer value of Y
     * @return set of X (int) such that Parent*(X,Y)
     */
    std::set<int> parentStar_X_Y_get_int_X_from_int_Y(DesignEnt xType,
            DesignEnt yType, int y) const;
    /*
     * Parent*(X,Y); given X (int), retrieve all Y (int) such that
     * Parent*(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param x integer value of X
     * @return set of Y (int) such that Parent*(X,Y)
     */
    std::set<int> parentStar_X_Y_get_int_Y_from_int_X(DesignEnt xType,
            DesignEnt yType, int x) const;

    /*
     * Follows(X,Y); given Y (int), retrieve all X (int) such that
     * Follows(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param y integer value of Y
     * @return set of X (int) such that Follows(X,Y)
     */
    std::set<int> follows_X_Y_get_int_X_from_int_Y(DesignEnt xType,
            DesignEnt yType, int y) const;
    /*
     * Follows(X,Y); given X (int), retrieve all Y (int) such that
     * Follows(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param x integer value of X
     * @return set of Y (int) such that Follows(X,Y)
     */
    std::set<int> follows_X_Y_get_int_Y_from_int_X(DesignEnt xType,
            DesignEnt yType, int x) const;

    /*
     * Follows*(X,Y); given Y (int), retrieve all X (int) such that
     * Follows*(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param y integer value of Y
     * @return set of X (int) such that Follows*(X,Y)
     */
    std::set<int> followsStar_X_Y_get_int_X_from_int_Y(DesignEnt xType,
            DesignEnt yType, int y) const;
    /*
     * Follows*(X,Y); given X (int), retrieve all Y (int) such that
     * Follows*(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param x integer value of X
     * @return set of Y (int) such that Follows*(X,Y)
     */
    std::set<int> followsStar_X_Y_get_int_Y_from_int_X(DesignEnt xType,
            DesignEnt yType, int x) const;

    /*
     * Next(X,Y); given Y (int), retrieve all X (int) such that
     * Next(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param y integer value of Y
     * @return set of X (int) such that Next(X,Y)
     */
    std::set<int> next_X_Y_get_int_X_from_int_Y(DesignEnt xType,
            DesignEnt yType, int y) const;
    /*
     * Next(X,Y); given X (int), retrieve all Y (int) such that
     * Next(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param x integer value of X
     * @return set of Y (int) such that Next(X,Y)
     */
    std::set<int> next_X_Y_get_int_Y_from_int_X(DesignEnt xType,
            DesignEnt yType, int x) const;

    /*
     * Next*(X,Y); given Y (int), retrieve all X (int) such that
     * Next*(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param y integer value of Y
     * @return set of X (int) such that Next*(X,Y)
     */
    std::set<int> nextStar_X_Y_get_int_X_from_int_Y(DesignEnt xType,
            DesignEnt yType, int y) const;
    /*
     * Next*(X,Y); given X (int), retrieve all Y (int) such that
     * Next*(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param x integer value of X
     * @return set of Y (int) such that Next*(X,Y)
     */
    std::set<int> nextStar_X_Y_get_int_Y_from_int_X(DesignEnt xType,
            DesignEnt yType, int x) const;

    /*
     * Affects(X,Y); given Y (int), retrieve all X (int) such that
     * Affects(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param y integer value of Y
     * @return set of X (int) such that Affects(X,Y)
     */
    std::set<int> affects_X_Y_get_int_X_from_int_Y(DesignEnt xType,
            DesignEnt yType, int y) const;
    /*
     * Affects(X,Y); given X (int), retrieve all Y (int) such that
     * Affects(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param x integer value of X
     * @return set of Y (int) such that Affects(X,Y)
     */
    std::set<int> affects_X_Y_get_int_Y_from_int_X(DesignEnt xType,
            DesignEnt yType, int x) const;

    /*
     * Affects*(X,Y); given Y (int), retrieve all X (int) such that
     * Affects*(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param y integer value of Y
     * @return set of X (int) such that Affects*(X,Y)
     */
    std::set<int> affectsStar_X_Y_get_int_X_from_int_Y(DesignEnt xType,
            DesignEnt yType, int y) const;
    /*
     * Affects*(X,Y); given X (int), retrieve all Y (int) such that
     * Affects*(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param x integer value of X
     * @return set of Y (int) such that Affects*(X,Y)
     */
    std::set<int> affectsStar_X_Y_get_int_Y_from_int_X(DesignEnt xType,
            DesignEnt yType, int x) const;
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
    bool is_stmtType(int stmtNo, DesignEnt type);
    bool is_valid_stmtNo(int stmtNo);

    set<int> get_all_stmt();
    set<int> get_all_stmt_by_proc(string procName);

    set<int> filter_by_proc(string procName, set<int> s);
    set<int> filter_by_stmtType(DesignEnt type, set<int> s);
    int filter_by_stmtType(DesignEnt type, int stmtNo);

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