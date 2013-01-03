#include "CFGNode.h"


CFGNode::CFGNode()
{
}

CFGNode::CFGNode(int n){
    stmtNo = n;
    inOne = NULL;
    inTwo = NULL;
    inThree = NULL;
    outOne = NULL;
    outTwo = NULL;
}

void CFGNode::set_edge(CFGNode *node, edge e, int i){
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

CFGNode* CFGNode::get_edge(edge e, int i){
    switch (e) {
    case IN:
        switch (i) {
            case 1:
                return inOne;
                break;
            case 2:
                return inTwo;
                break;
            case 3:
                return inThree;
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

int CFGNode::get_stmtNo(){
    return stmtNo;
}

void CFGNode::print(){
    printf("Stmtno: %d\n", stmtNo);
    if (inOne != NULL) {
        printf("inOne: %d\n", inOne->get_stmtNo());
    }
    if (inTwo != NULL) {
        printf("inTwo: %d\n", inTwo->get_stmtNo());
    }
    if (inThree != NULL) {
        printf("inThree: %d\n", inThree->get_stmtNo());
    }
    if (outOne != NULL) {
        printf("outOne: %d\n", outOne->get_stmtNo());
    }
    if (outTwo != NULL) {
        printf("outTwo: %d\n", outTwo->get_stmtNo());
    }
    putchar('\n');
}
