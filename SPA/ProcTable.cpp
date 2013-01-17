#include "ProcTable.h"

ProcElements::ProcElements(){}

ProcElements::ProcElements(string name){
    procName = name;
}

ProcTable::ProcTable(){}

int ProcTable::get_index(string procName){
    if (nameToIndex.find(procName) != nameToIndex.end()) {
        return nameToIndex[procName];
    } else {
        return -1;
    }
}

string ProcTable::get_proc_name(int index) {
    int sz = procTable.size();
    if (index < 0 || index >= sz) {
        return "";
    } else {
        return procTable[index].procName;
    }
}

void ProcTable::update_table(VarTable *vt){
    varTable = vt;
    int sz = procTable.size();
    updated.assign(sz, -1);
    for (int i = 0; i < sz; i++) {
        update(procTable[i].procName);
    }
}

void ProcTable::update(string procName){
    set<string>::iterator it;
    int index = get_index(procName);
    if (updated[index] == -1) {
        set<string> calls = get_calls(procName);
        for (it = calls.begin(); it != calls.end(); it++) {
            update(*it);
            combine_up(procName, *it);
        }
        updated[index] = 1;
    }
}

void ProcTable::combine_up(string caller, string callee){
    set<string>::iterator it;
    set<string> s;
    int index = get_index(caller);

    s = get_modifies(callee);
    for (it = s.begin(); it != s.end(); it++) {
        procTable[index].modifies.insert(*it);
        varTable->add_proc_modifies_var(caller, *it);
    }

    s = get_uses(callee);
    for (it = s.begin(); it != s.end(); it++) {
        procTable[index].uses.insert(*it);
        varTable->add_used_by(*it, caller);
    }
}

int ProcTable::insert_proc(string procName){
    if (nameToIndex.find(procName) != nameToIndex.end()) {
        return nameToIndex[procName];
    }
    int index = procTable.size();
    nameToIndex[procName] = index;
    ProcElements procEntry = ProcElements(procName);
    procTable.push_back(procEntry);
    return index;
}

void ProcTable::set_start(string procName, int stmtNo){
    int index = get_index(procName);
    if (index != -1){
        procTable[index].start = stmtNo;
        procFinder[stmtNo] = procName;
    }

}

void ProcTable::set_end(string procName, int stmtNo){
    int index = get_index(procName);
    if (index != -1){
        procTable[index].end = stmtNo;
        procFinder[stmtNo] = procName;
    }
}

void ProcTable::set_proc_root(string procName, Node *root){
    int index = get_index(procName);
    if (index != -1){
        procTable[index].procRoot = root;
    }
}

void ProcTable::add_modifies(string procName, string varName){
    int index = get_index(procName);
    if (index != -1){
        procTable[index].modifies.insert(varName);
    }
}

void ProcTable::add_uses(string procName, string varName){
    int index = get_index(procName);
    if (index != -1){
        procTable[index].uses.insert(varName);
    }
}

void ProcTable::add_calls(string proc1, string proc2){
    if (nameToIndex.find(proc1) != nameToIndex.end()) {
        int index1 = nameToIndex[proc1];
        procTable[index1].calls.insert(proc2);
        int index2 = insert_proc(proc2);
        procTable[index2].calledBy.insert(proc1);
    }
}

void ProcTable::add_called_by(string proc1, string proc2){
    if (nameToIndex.find(proc1) != nameToIndex.end()) {
        int index1 = nameToIndex[proc1];
        procTable[index1].calledBy.insert(proc2);
    }
}

int ProcTable::get_start(string procName){
    if (nameToIndex.find(procName) != nameToIndex.end()) {
        return procTable[nameToIndex[procName]].start;
    } else {
        return -1;
    }
}


int ProcTable::get_end(string procName){
    if (nameToIndex.find(procName) != nameToIndex.end()) {
        return procTable[nameToIndex[procName]].end;
    } else {
        return -1;
    }
}

Node* ProcTable::get_root(string procName){
    if (nameToIndex.find(procName) != nameToIndex.end()) {
        return procTable[nameToIndex[procName]].procRoot;
    } else {
        return NULL;
    }
}

Node* ProcTable::get_root(int index){
    int sz = procTable.size();
    if (index < 0 || index >= sz) {
        return NULL;
    } else {
        return procTable[index].procRoot;
    }
}

set<string> ProcTable::get_calls(string procName){
    if (nameToIndex.find(procName) != nameToIndex.end()) {
        return procTable[nameToIndex[procName]].calls;
    } else {
        return EMPTY_STRINGSET;
    }
}

set<string> ProcTable::get_calls(int index){
    int sz = procTable.size();
    if (index < 0 || index >= sz) {
        return EMPTY_STRINGSET;
    } else {
        return procTable[index].calls;
    }
}

set<string> ProcTable::get_called_by(string procName){
    if (nameToIndex.find(procName) != nameToIndex.end()) {
        return procTable[nameToIndex[procName]].calledBy;
    } else {
        return EMPTY_STRINGSET;
    }
}

set<string> ProcTable::get_called_by(int index){
    int sz = procTable.size();
    if (index < 0 || index >= sz) {
        return EMPTY_STRINGSET;
    } else {
        return procTable[index].calledBy;
    }
}

set<string> ProcTable::get_modifies(string procName){
    int index = get_index(procName);
    if (index != -1){
        return procTable[index].modifies;
    } else {
        return EMPTY_STRINGSET;
    }
}

set<string> ProcTable::get_uses(string procName){
    int index = get_index(procName);
    if (index != -1){
        return procTable[index].uses;
    } else {
        return EMPTY_STRINGSET;
    }
}

// TODO: Improve efficiency of this method
set<string> ProcTable::get_all_procs() const
{
    set<string> result;
    int sz = procTable.size();
    for (int i = 0; i < sz; i++) {
        result.insert(procTable[i].procName);
    }
    return result;
}

string ProcTable::which_proc(int stmtNo)
{
    return procFinder.lower_bound(stmtNo)->second;
}

