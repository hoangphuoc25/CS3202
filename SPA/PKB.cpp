#include "PKB.h"

PKB::PKB(){}

PKB::PKB(Node *root){
    progRoot = root;
}

/*
void PKB::add_modifies(string var, int stmtNo){
    //globalVarTable.insert_var(var);
    //globalVarTable.add_modified_by(var, stmtNo);
}

void PKB::add_uses(string var, int stmtNo){
    //globalVarTable.insert_var(var);
    //globalVarTable.add_used_by(var, stmtNo);
}
*/

VarTable* PKB::add_proc(string procName, Node *procRoot){
    int index = procTable.insert_proc(procName, procRoot);
    return procTable.get_varTable(index);
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
    constBank.insert(n);
}

void PKB::add_calls(string proc1, string proc2){
    procTable.add_calls(proc1, proc2);
}


