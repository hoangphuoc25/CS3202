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
    procTable.update_called_by();
    set<string> s = procTable.get_all_procs();
    set<string>::iterator it;
    for (it = s.begin(); it != s.end(); it++) {
        update_vars(*it);
    }
    for (it = s.begin(); it != s.end(); it++) {
        update_procVarTable(*it);
    }
}

void PKB::update_vars(string procName){
    VarTable *v = procTable.get_varTable(procName);
    set<string> s;
    set<string>::iterator it;
    set<int> n;
    set<int>::iterator iter;
    queue<int> q;
    int temp, stmtNo;
    int index = procTable.get_index(procName);
    Node *node, *parent;
    s = v->get_all_vars();
    for (it = s.begin(); it != s.end(); it++) {
        n = v->get_modified_by(*it);
        if (!n.empty()){
            procTable.add_modifies(procName, *it);
            procVarTable.add_modified_by(*it, index);
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
            procVarTable.add_used_by(*it, index);
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


void PKB::update_procVarTable(string procName){
    set<string> s,v;
    set<string>::iterator it, var;
    int index = procTable.get_index(procName);
    s = procTable.get_calls(procName);
    for (it = s.begin(); it != s.end(); it++) {
        v = procTable.get_modifies(*it);
        for (var = v.begin(); var != v.end(); var++) {
            procTable.add_modifies(procName, *var);
            procVarTable.add_modified_by(*var, index);
        }
        v = procTable.get_uses(*it);
        for (var = v.begin(); var != v.end(); var++) {
            procTable.add_uses(procName, *var);
            procVarTable.add_used_by(*var, index);
        }
    }
}


set<int> PKB::get_modifies_var(string var){
    set<int> s = procVarTable.get_modified_by(var);
    set<int> temp, result;
    set<int>::iterator p,it;
    VarTable* v;
    for (p = s.begin(); p != s.end(); p++) {
        v = procTable.get_varTable(*p);
        temp = v->get_modified_by(var);
        for (it = temp.begin(); it != temp.end(); it++) {
            result.insert(*it);
        }
    }
    return result;
}

set<int> PKB::get_uses_var(string var){
    set<int> s = procVarTable.get_used_by(var);
    set<int> temp, result;
    set<int>::iterator p,it;
    VarTable* v;
    for (p = s.begin(); p != s.end(); p++) {
        v = procTable.get_varTable(*p);
        temp = v->get_used_by(var);
        for (it = temp.begin(); it != temp.end(); it++) {
            result.insert(*it);
        }
    }
    return result;
}

set<string> PKB::get_proc_modifies_var(string var){
    set<string> result;
    set<int> s = procVarTable.get_modified_by(var);
    set<int>::iterator it;
    for (it = s.begin(); it != s.end(); it++) {
        result.insert(procTable.get_proc_name(*it));
    }
    return result;
}

set<string> PKB::get_proc_uses_var(string var){
    set<string> result;
    set<int> s = procVarTable.get_used_by(var);
    set<int>::iterator it;
    for (it = s.begin(); it != s.end(); it++) {
        result.insert(procTable.get_proc_name(*it));
    }
    return result;
}

set<string> PKB::get_var_by_proc(string procName){
    int index = procTable.get_index(procName);
    if (index != -1) {
        return procTable.get_varTable(index)->get_all_vars();
    } else {
        return EMPTY_STRINGSET;
    }
}

set<string> PKB::get_modifies_var_by_proc(string procName){
    return procTable.get_modifies(procName);
}

set<string> PKB::get_uses_var_by_proc(string procName){
    return procTable.get_uses(procName);
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

