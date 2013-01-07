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

    int get_stmtNo();

    void set_edge(CFGNode *node, edge e, int i);
    CFGNode* get_edge(edge e, int i);
    set<int> get_before();
    set<int> get_after();

    void print();

private:
    int stmtNo;
    CFGNode *inOne, *inTwo, *inThree;
    CFGNode *outOne, *outTwo;

};

#endif

