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
    void add_constant(string n);

    // Banks
    map<int, stmtType> get_directory();
    map<int, Node*> get_callBank();
    map<int, Node*> get_ifBank();
    map<int, Node*> get_whileBank();
    map<int, Node*> get_assignBank();
    set<string> get_constBank();

    bool is_stmt_type(int stmtNo, stmtType type);

    //Utility
    Node* get_node(int stmtNo);

private:
    map<int, stmtType> directory; 
    map<int, Node*> callBank;
    map<int, Node*> whileBank;
    map<int, Node*> ifBank;
    map<int, Node*> assignBank;
    set<string> constBank;
};

#endif
