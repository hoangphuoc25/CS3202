#include "PKB.h"

PKB::PKB(){}

PKB::PKB(Node* root){
    progRoot = root;
}

void PKB::add_modifies(string var, int stmtNo){
    //globalVarTable.insert_var(var);
    //globalVarTable.add_modified_by(var, stmtNo);
}

void PKB::add_uses(string var, int stmtNo){
    //globalVarTable.insert_var(var);
    //globalVarTable.add_used_by(var, stmtNo);
}

void PKB::add_node_entry(int stmtNo, stmtType type, Node* node){
    directory[stmtNo] = type;
    switch(type) {
        case CALLTYPE:
            callBank[stmtNo] = node;
            break;
        case WHILETYPE:
            whileBank[stmtNo] = node;
            break;
        case IFTYPE:
            ifBank[stmtNo] = node;
            break;
        case ASSIGNTYPE:
            assignBank[stmtNo] = node;
            break;
    }
}

void PKB::add_constant(string n){


}
