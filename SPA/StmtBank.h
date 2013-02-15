#ifndef T11_STMT_BANK_H
#define T11_STMT_BANK_H

#include <map>
#include "Node.h"
#include "PQL.h"

using std::map;

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

    /*
     * Retrieves the set of variables used by a statement.
     * @param entType type of statement
     * @param stmtNo statement number
     * @return a set of variables (strings) used by that statement
     */
    const std::set<std::string>& get_vars_used_by_stmt(DesignEnt entType,
            int stmtNo) const;

    // query methods
    bool has_const(int n) const;

    /*
     * Returns the procedure called by the call stmt, or an
     * empty string if the statement does not exist or is not
     * a call statement.
     */
    std::string get_call_procName(int callStmt) const;

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
    map<int, DesignEnt> directory;
    map<int, Node*> callBank;
    map<int, Node*> whileBank;
    map<int, Node*> ifBank;
    map<int, Node*> assignBank;
    std::set<int> constBank;
    std::set<int> stmtLstSet;
    const std::set<std::string> EMPTY_STRINGSET;
};

#endif
