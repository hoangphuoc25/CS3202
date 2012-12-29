#include "ProcTable.h"

ProcElements::ProcElements(){}

ProcElements::ProcElements(string name, Node *root){
    procName = name;
    procRoot = root;
    varTable = new VarTable();
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

void ProcTable::update_called_by(){
    int sz = procTable.size();
    for (int i = 0; i < sz; i++){
        set<string>::iterator it;
        set<string> s = procTable[i].calls;
        string name = procTable[i].procName; 
        for (it = s.begin(); it != s.end(); it++) {
            add_called_by(*it, name); 
        }
    }
}



int ProcTable::insert_proc(string procName, Node *root){
    if (nameToIndex.find(procName) != nameToIndex.end()) {
        return nameToIndex[procName];
    }
    int index = procTable.size();
    nameToIndex[procName] = index;
    ProcElements procEntry = ProcElements(procName, root);
    procTable.push_back(procEntry);
    return index;
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
    }
}

void ProcTable::add_called_by(string proc1, string proc2){
    if (nameToIndex.find(proc1) != nameToIndex.end()) {
        int index1 = nameToIndex[proc1];
        procTable[index1].calledBy.insert(proc2);
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

VarTable* ProcTable::get_varTable(string procName){
    if (nameToIndex.find(procName) != nameToIndex.end()) {
        return procTable[nameToIndex[procName]].varTable;
    } else {
        return NULL;
    }
}

VarTable* ProcTable::get_varTable(int index){
    int sz = procTable.size();
    if (index < 0 || index >= sz) {
        return NULL;
    } else {
        return procTable[index].varTable;
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

set<string> ProcTable::get_all_procs(){
    set<string> result;
    int sz = procTable.size();
    for (int i = 0; i < sz; i++) {
        result.insert(procTable[i].procName);
    }
    return result;
}
