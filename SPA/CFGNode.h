#ifndef T11_CFG_NODE_H
#define T11_CFG_NODE_H
#include <cstdio>
#include <set>

using std::set;

enum edge {IN, OUT};

class CFGNode
{

public:
    CFGNode();
    CFGNode(int n);

    int get_stmtNo() const;

    void set_edge(CFGNode *node, edge e, int i);
    CFGNode* get_edge(edge e, int i) const;
    set<int> get_before() const;
    set<int> get_after() const;

    void print() const;

private:
    int stmtNo;
    CFGNode *inOne, *inTwo, *inThree;
    CFGNode *outOne, *outTwo;

};

#endif

