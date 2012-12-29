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

void PKB::extract_design(){

}

void PKB::update_vars(string procName){
    VarTable *v = procTable.get_varTable(procName);
    set<string> s;
    set<string>::iterator it;
    set<int> n;
    set<int>::iterator iter;
    queue<int> q;
    int temp, stmtNo;
    Node *node, *parent;
    s = v->get_all_vars();
    for (it = s.begin(); it != s.end(); it++) {
        n = v->get_modified_by(*it);
        if (!n.empty()){
            procTable.add_modifies(procName, *it);
            for (iter = n.begin(); iter != n.end(); iter++) {
                q.push(*iter);
            }
            while (!q.empty()) {
                temp = q.front();
                node = get_node(temp);
                parent = node->get_parent();
                if(parent != NULL) {
                    stmtNo = node->get_parent()->get_stmtNo();
                    v->add_modified_by(*it, stmtNo);
                    q.push(stmtNo);
                    parent->add_modifies(*it);
                }
                q.pop();
            }
        }

        n = v->get_used_by(*it);
        if(!n.empty()) {
            procTable.add_uses(procName, *it);
            for (iter = n.begin(); iter != n.end(); iter++) {
                q.push(*iter);
            }
            while (!q.empty()) {
                temp = q.front();
                node = get_node(temp);
                parent = node->get_parent();
                if(parent != NULL) {
                    stmtNo = node->get_parent()->get_stmtNo();
                    v->add_used_by(*it, stmtNo);
                    q.push(stmtNo);
                    parent->add_uses(*it);
                }
                q.pop();
            }
        }
    }
}




set<string> PKB::get_var_by_proc(string procName){
    int index = procTable.get_index(procName);
    if (index != -1) {
        return procTable.get_varTable(index)->get_all_vars();
    } else {
        return EMPTY_STRINGSET;
    }
}

//procTable
set<string> PKB::get_calls(string procName){
    return procTable.get_calls(procName);
}

set<string> PKB::get_called_by(string procName){
    return procTable.get_called_by(procName);
}

// AST
bool PKB::is_stmt_type(int stmtNo, stmtType type){
    if (directory.find(stmtNo) != directory.end()) {
        return (directory[stmtNo] == type);
    } else {
        return false;
    }
}

bool PKB::is_stmt_modifies(int stmtNo, string varName) {
    set<string> s = get_stmt_modifies(stmtNo);
    if (s.find(varName) != s.end()) {
        return true;
    } else {
        return false;
    }
}

bool PKB::is_stmt_uses(int stmtNo, string varName) {
    set<string> s = get_stmt_uses(stmtNo);
    if (s.find(varName) != s.end()) {
        return true;
    } else {
        return false;
    }
}

set<string> PKB::get_stmt_modifies(int stmtNo){
    Node *n = get_node(stmtNo);
    if (n != NULL) {
        return n->get_modifies();
    } else {
        return EMPTY_STRINGSET;
    }
}

set<string> PKB::get_stmt_uses(int stmtNo){
    Node *n = get_node(stmtNo);
    if (n != NULL) {
        return n->get_uses();
    } else {
        return EMPTY_STRINGSET;
    }
}

string PKB::get_control_var(int stmtNo) {
    if (directory.find(stmtNo) != directory.end()) {
        return get_node(stmtNo)->get_control_var();
    } else {
        return "";
    }
}








// Ultiliy
Node* PKB::get_node(int stmtNo) {
    if (directory.find(stmtNo) != directory.end()) {
        stmtType type = directory[stmtNo];
        switch(type) {
            case CALLTYPE:
                return callBank[stmtNo];
                break;
            case WHILETYPE:
                return whileBank[stmtNo];
                break;
            case IFTYPE:
                return ifBank[stmtNo];
                break;
            case ASSIGNTYPE:
                return assignBank[stmtNo];
                break;
        }
    } else {
        return NULL;
    }
}

