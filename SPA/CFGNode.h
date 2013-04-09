#ifndef T11_CFG_NODE_H
#define T11_CFG_NODE_H
#include <cstdio>
#include <set>

#define DUMMY -1

using std::set;

enum edge {IN, OUT};

class CFGNode
{

public:
    CFGNode();
    CFGNode(int n);

    int get_stmtNo() const;

    void set_edge(CFGNode *node, edge e, int i);
    void set_BIPedge(CFGNode *node, edge e);

    CFGNode* get_edge(edge e, int i) const;
    set<CFGNode*> get_bip_edge(edge e) const;
    set<int> get_before() const;
    set<int> get_after() const;
    set<int> get_before_helper() const;
    set<int> get_after_helper() const;
    set<int> get_before_BIP() const;
    set<int> get_after_BIP() const;

    void set_terminator();
    void set_last();
    void set_caller();

    bool has_Bip(edge e) const;
    bool is_terminator() const;
    bool is_last() const;
    bool is_caller() const;

    void print() const;

private:
    int stmtNo;
    CFGNode *inOne, *inTwo;
    CFGNode *outOne, *outTwo;
    set <CFGNode*> bipIn, bipOut;
    bool terminator, last, caller;
};

#endif

