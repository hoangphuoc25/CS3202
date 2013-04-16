#ifndef T11_STMT_BANK_H
#define T11_STMT_BANK_H

#include <map>
#include "Node.h"
#include "PQL.h"

using std::map;

/// Stores information relating to statments
class StmtBank {
public:
    // returned by get_call_procName if the call stmt is invalid
    static const std::string EMPTY_NAME;
    StmtBank(void);
    ~StmtBank(void);

    void add_node_entry(int stmtNo, DesignEnt type, Node* node);
    bool add_constant(const std::string& n, char **errorMsg);
    void add_stmtLst(int stmtNo);

    Node *get_assignNode(int stmtNo) const;
    Node *get_ifNode(int stmtNo) const;
    Node *get_whileNode(int stmtNo) const;
    Node *get_callNode(int stmtNo) const;
    Node *get_stmtNode(int stmtNo) const;
    // TODO: Improve efficiency of get_all_* methods
    std::set<int> get_all_assign() const;
    std::set<int> get_all_if() const;
    std::set<int> get_all_while() const;
    std::set<int> get_all_call() const;
    const std::set<int>& get_all_const() const;
    std::set<int> get_all_stmt() const;
    const std::set<int>& get_all_stmtLst() const;

    /// Checks if the StmtBank has an entity of a given type
    /// @param entType the type of statement. One of ENT_ASSIGN,
    ///                ENT_CALL, ENT_IF, ENT_WHILE, ENT_STMT,
    ///                ENT_PROGLINE, ENT_CONST, ENT_STMTLST
    /// @return true if the StmtBank has at least one statement of
    ///         entType, false otherwise
    bool has_any_ent(DesignEnt entType) const;

    /// Checks if there is any call statement inside the StmtBank
    /// @return true if there is at least one call statement
    ///         inside the StmtBank, false otherwise
    bool has_any_call() const;

    /*
     * Retrieves the set of variables used by a statement.
     * @param entType type of statement
     * @param stmtNo statement number
     * @return a set of variables (strings) used by that statement
     */
    const std::set<std::string>& get_vars_used_by_stmt(DesignEnt entType,
            int stmtNo) const;

    // query methods
    bool has_stmtLst(int stmt) const;
    bool has_const(int n) const;
    /// Checks if any call statement calls a given procedure
    /// @procName the procedure to check for
    /// @return true if a call statement calls the given procedure,
    ///         false otherwise
    bool has_call_procName(const std::string& procName) const;

    /*
     * Returns the procedure called by the call stmt, or an
     * empty string if the statement does not exist or is not
     * a call statement.
     */
    std::string get_call_procName(int callStmt) const;
    /// Returns all call stmts that call a certain procedure.
    /// @param proc name of procedure being called
    /// @return set of integers of all the call statements calling
    ///         procedure proc
    const std::set<int>& get_call_stmt_calling(
            const std::string& proc) const;

    // Banks
    map<int, DesignEnt> get_directory();
    map<int, Node*> get_callBank();
    map<int, Node*> get_ifBank();
    map<int, Node*> get_whileBank();
    map<int, Node*> get_assignBank();

    bool is_stmtType(int stmtNo, DesignEnt type) const;
    bool is_valid_stmtNo(int stmtNo);

    /*
     * Retrieves a Node given by the statement number
     * @param stmtNo statement number
     * @return a pointer to Node representing that statement
     */
    Node *get_node(int stmtNo) const;

private:
    /// Adds a call statement node to the StmtBank
    /// @param call statement number
    /// @param node the Node representing the call stmt
    void add_call_node_entry(int stmtNo, Node *node);

    map<int, DesignEnt> directory;
    map<int, Node*> callBank;
    map<int, Node*> whileBank;
    map<int, Node*> ifBank;
    map<int, Node*> assignBank;
    std::set<int> constBank;
    std::set<int> stmtLstSet;
    std::set<std::string> callProcNameSet;
    map<string, set<int> > procNameToCallStmtSet;
    const std::set<std::string> EMPTY_STRINGSET;
    const std::set<int> EMPTY_INTSET;
};

#endif
