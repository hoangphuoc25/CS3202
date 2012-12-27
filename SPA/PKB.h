#ifndef T11_PKB_H
#define T11_PKB_H
#include <map>
#include <set>
#include "VarTable.h"
#include "Node.h"

using std::map;
using std::set;

enum stmtType {CALLTYPE, WHILETYPE, IFTYPE, ASSIGNTYPE};

class PKB{


public:
    PKB();
    PKB(Node* root);

    // Builder methods
    void add_modifies(string var, int stmtNo);
    void add_uses(string var, int stmtNo);
    void add_node_entry(int stmtNo, stmtType type, Node* node);

    // Printers

private:
    Node* progRoot;
    VarTable varTable;
    map<int, stmtType> directory; 
    map<int, Node*> callBank;
    map<int, Node*> whileBank;
    map<int, Node*> ifBank;
    map<int, Node*> assignBank;

};









#endif