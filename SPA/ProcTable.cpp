#include "ProcTable.h"

ProcElements::ProcElements(){}

ProcElements::ProcElements(string name){
    procName = name;
}

ProcTable::ProcTable(){}

int ProcTable::get_index(string procName) const
{
    map<string, int>::const_iterator it = this->nameToIndex.find(procName);
    if (it != this->nameToIndex.end()) {
        return it->second;
    } else {
        return -1;
    }
}

const string& ProcTable::get_proc_name(int index) const
{
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

    s = this->get_vars_used_by_proc(callee);
    for (it = s.begin(); it != s.end(); it++) {
        procTable[index].uses.insert(*it);
        this->varTable->add_used_by(*it, ENT_PROC, caller);
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

int ProcTable::get_start(const string& procName) const
{
    int idx = this->get_index(procName);
    if (-1 != idx) {
        return procTable[idx].start;
    } else {
        return -1;
    }
}


int ProcTable::get_end(const string& procName) const
{
    int idx = this->get_index(procName);
    if (-1 != idx) {
        return procTable[idx].end;
    } else {
        return -1;
    }
}

Node* ProcTable::get_root(const string& procName) const
{
    int idx = this->get_index(procName);
    if (-1 != idx) {
        return procTable[idx].procRoot;
    } else {
        return NULL;
    }
}

Node* ProcTable::get_root(int index) const
{
    int sz = procTable.size();
    if (index < 0 || index >= sz) {
        return NULL;
    } else {
        return procTable[index].procRoot;
    }
}

const set<string>& ProcTable::get_calls(const string& procName) const
{
    map<string, int>::const_iterator it = this->nameToIndex.find(procName);
    if (it != this->nameToIndex.end()) {
        return this->procTable[it->second].calls;
    } else {
        return EMPTY_STRINGSET;
    }
}

const set<string>& ProcTable::get_calls(int index) const
{
    int sz = procTable.size();
    if (index < 0 || index >= sz) {
        return EMPTY_STRINGSET;
    } else {
        return this->procTable[index].calls;
    }
}

const set<string>& ProcTable::get_called_by(const string& procName) const
{
    map<string, int>::const_iterator it = this->nameToIndex.find(procName);
    if (it != this->nameToIndex.end()) {
        return this->procTable[it->second].calledBy;
    } else {
        return EMPTY_STRINGSET;
    }
}

bool ProcTable::does_procedure_modify_var(const string& procName,
        const string& varName) const
{
    int idx = this->get_index(procName);
    if (idx != -1) {
        const ProcElements& procElem = this->procTable[idx];
        return procElem.modifies.find(varName) !=
                procElem.modifies.end();
    }
    return false;
}

const set<string>& ProcTable::get_called_by(int index) const
{
    int sz = procTable.size();
    if (index < 0 || index >= sz) {
        return EMPTY_STRINGSET;
    } else {
        return this->procTable[index].calledBy;
    }
}

const set<string>& ProcTable::get_modifies(const string& procName) const
{
    int index = this->get_index(procName);
    if (index != -1) {
        return procTable[index].modifies;
    } else {
        return EMPTY_STRINGSET;
    }
}

const set<string>& ProcTable::get_vars_used_by_proc(
        const string& procName) const
{
    int index = get_index(procName);
    if (index != -1) {
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

bool ProcTable::uses_query_procedure_var(const string& proc,
            const string& var) const
{
    int idx = this->get_index(proc);
    if (idx >= 0) {
        const ProcElements& p = this->procTable[idx];
        return (p.uses.find(var) != p.uses.end());
    }
    return false;
}

const string& ProcTable::which_proc(int stmtNo) const
{
    return this->procFinder.lower_bound(stmtNo)->second;
}

bool ProcTable::has_any_proc() const
{
    return (this->procTable.size() > 0);
}

bool ProcTable::at_least_one_var_used() const
{
    for (vector<ProcElements>::const_iterator it =
            this->procTable.begin();
            it != this->procTable.end(); it++) {
        if (it->uses.size() > 0) {
            return true;
        }
    }
    return false;
}