#ifndef T11_STMT_BANK_H
#define T11_STMT_BANK_H

#include <map>
#include "Node.h"

using std::map;

enum stmtType {
    CALLTYPE, WHILETYPE, IFTYPE, ASSIGNTYPE
};

class StmtBank {
public:
    StmtBank(void);
    ~StmtBank(void);

    void add_node_entry(int stmtNo, stmtType type, Node* node);
    bool add_constant(const std::string& n, char **errorMsg);

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

    // query methods
    bool has_const(int n) const;

    // Banks
    map<int, stmtType> get_directory();
    map<int, Node*> get_callBank();
    map<int, Node*> get_ifBank();
    map<int, Node*> get_whileBank();
    map<int, Node*> get_assignBank();

    bool is_stmtType(int stmtNo, stmtType type);
    bool is_valid_stmtNo(int stmtNo);

    //Utility
    Node* get_node(int stmtNo);

private:
    map<int, stmtType> directory; 
    map<int, Node*> callBank;
    map<int, Node*> whileBank;
    map<int, Node*> ifBank;
    map<int, Node*> assignBank;
    std::set<int> constBank;
};

#endif
