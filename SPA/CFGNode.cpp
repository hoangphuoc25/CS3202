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
    outOne = NULL;
    outTwo = NULL;
    terminator = false;
    last = false;
    caller = false;
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

void CFGNode::set_BIPedge(CFGNode *node, edge e)
{
    if (e == IN) {
        bipIn.insert(node);
    } else if (e == OUT) {
        bipOut.insert(node);
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

set<int> CFGNode::get_before_helper() const
{
    set<int> s, temp;
    int n;
    if (inOne != NULL) {
        n = inOne->get_stmtNo();
        if (n != DUMMY) {
            if(!inOne->is_caller()){
                s.insert(n);
            }
        } else {
            s = inOne->get_before_helper();
        }
    }
    if (inTwo != NULL) {
        n = inTwo->get_stmtNo();
        if (n != DUMMY) {
            if (!inTwo->is_caller()) {
                s.insert(n);
            }
        } else {
            temp = inTwo->get_before_helper();
            s.insert(temp.begin(),temp.end());
        }
    }
    return s;
}

set<int> CFGNode::get_after_helper() const
{
    set<int> s,temp;
    int n;
    if (caller) {
        return s;
    }
    if (outOne != NULL) {
        n = outOne->get_stmtNo();
        if (n != DUMMY) {
            s.insert(n);
        } else {
            // Dummy nodes only have outOne.
            s =  outOne->get_after_helper();
        }
    }
    if (outTwo != NULL) {
        n = outTwo->get_stmtNo();
        assert(n != DUMMY);
        s.insert(n);
    }
    return s;
}

set<int> CFGNode::get_before_BIP() const
{
    set<int> s;
    for (set<CFGNode*>::iterator it = bipIn.begin(); it != bipIn.end(); it++) {
        if((*it)->is_terminator()){
            set<int> t = (*it)->get_before_helper();
            s.insert(t.begin(),t.end());
            t = (*it)->get_before_BIP();
            s.insert(t.begin(),t.end());
        } else {
            s.insert((*it)->get_stmtNo());
        }
    }
    return s;
}

set<int> CFGNode::get_after_BIP() const
{
    set<int> s;
    if (last && !caller) {
        assert(outOne != NULL);
        s = outOne->get_after_BIP();
    }
    for (set<CFGNode*>::iterator it = bipOut.begin(); it != bipOut.end(); it++) {
        if((*it)->is_terminator()){
            set<int> t = (*it)->get_after_BIP();
            s.insert(t.begin(),t.end());
        } else {
            s.insert((*it)->get_stmtNo());
        }
    }
    return s;
}

bool CFGNode::has_Bip(edge e) const
{
    if (e == IN) {
        return (bipIn.size() != 0);
    } else if (e == OUT) {
        return (bipOut.size() != 0);
    }
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

void CFGNode::set_terminator()
{
    terminator = true;
}

bool CFGNode::is_terminator() const
{
    return terminator;
}

void CFGNode::set_last()
{
    last = true;
}

bool CFGNode::is_last() const
{
    return last;
}

void CFGNode::set_caller()
{
    caller = true;
}

bool CFGNode::is_caller() const
{
    return caller;
}
