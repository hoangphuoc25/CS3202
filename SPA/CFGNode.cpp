#include "CFGNode.h"
#include <cassert>

CFGNode::CFGNode()
{
}

CFGNode::CFGNode(int n)
{
    stmtNo = n;
    inOne = NULL;
    inTwo = NULL;
    inThree = NULL;
    outOne = NULL;
    outTwo = NULL;
}

void CFGNode::set_edge(CFGNode *node, edge e, int i)
{
    switch (e) {
    case IN:
        switch (i) {
        case 1:
            inOne = node;
            break;
        case 2:
            inTwo = node;
            break;
        case 3:
            inThree = node;
            break;
        }
        break;
    case OUT:
        switch (i) {
        case 1:
            outOne = node;
            break;
        case 2:
            outTwo = node;
            break;
        }
        break;
    }
}

CFGNode* CFGNode::get_edge(edge e, int i) const
{
    switch (e) {
    case IN:
        switch (i) {
            case 1:
                return inOne;
                break;
            case 2:
                return inTwo;
                break;
        }
        break;
    case OUT:
        switch (i) {
            case 1:
                return outOne;
                break;
            case 2:
                return outTwo;
                break;
        }
        break;
    }
}

int CFGNode::get_stmtNo() const
{
    return stmtNo;
}

set<int> CFGNode::get_before() const
{
    set<int> s, temp;
    int n;
    if (inOne != NULL) {
        n = inOne->get_stmtNo();
        if (n != -1) {
            s.insert(n);
        } else {
            s = inOne->get_before();
        }
    }
    if (inTwo != NULL) {
        n = inTwo->get_stmtNo();
        if (n != -1) {
            s.insert(n);
        } else {
            temp = inTwo->get_before();
            s.insert(temp.begin(),temp.end());
        }
    }
    return s;
}

set<int> CFGNode::get_after() const
{
    set<int> s,temp;
    int n;
    if (outOne != NULL) {
        n = outOne->get_stmtNo();
        if (n != -1) {
            s.insert(n);
        } else {
            // Dummy nodes only have outOne.
            s =  outOne->get_after();
        }
    }
    if (outTwo != NULL) {
        n = outTwo->get_stmtNo();
        assert(n != -1);
        s.insert(n);
    }
    return s;
}


void CFGNode::print() const
{
    printf("Stmtno: %d\n", stmtNo);
    if (inOne != NULL) {
        printf("inOne: %d\n", inOne->get_stmtNo());
    }
    if (inTwo != NULL) {
        printf("inTwo: %d\n", inTwo->get_stmtNo());
    }
    if (outOne != NULL) {
        printf("outOne: %d\n", outOne->get_stmtNo());
    }
    if (outTwo != NULL) {
        printf("outTwo: %d\n", outTwo->get_stmtNo());
    }
    putchar('\n');
}
