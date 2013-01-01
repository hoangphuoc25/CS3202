#include "PKB.h"

PKB::PKB(){}

PKB::PKB(Node *root, ProcTable *pt, VarTable *vt, StmtBank *sb){
    progRoot = root;
    procTable = pt;
    varTable = vt;
    stmtBank = sb;
}


Node* PKB::get_progRoot(){
    return progRoot;
}


/*
void PKB::extract_design(){

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
*/

set<int> PKB::get_modifies_var(string var){
    return *new set<int>;
}

set<int> PKB::get_uses_var(string var){
        return *new set<int>;
}

set<string> PKB::get_proc_modifies_var(string var){
        return *new set<string>;
}

set<string> PKB::get_proc_uses_var(string var){
            return *new set<string>;
}

set<string> PKB::get_var_by_proc(string procName){
            return *new set<string>;
}

set<string> PKB::get_modifies_var_by_proc(string procName){
    return procTable->get_modifies(procName);
}

set<string> PKB::get_uses_var_by_proc(string procName){
    return procTable->get_uses(procName);
}

/*
set<string> PKB::get_all_vars_by_proc(string procName){}

set<string> PKB::get_all_vars(){}
*/


//procTable
set<string> PKB::get_calls(string procName){
    return procTable->get_calls(procName);
}

set<string> PKB::get_called_by(string procName){
    return procTable->get_called_by(procName);
}

ProcTable PKB::get_procTable(){
    return *procTable;
}

// AST


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
            return *new set<string>;
}

set<string> PKB::get_stmt_uses(int stmtNo){
            return *new set<string>;
}

string PKB::get_control_var(int stmtNo) {
    return "test";
}







// Ultiliy


