#include <cassert>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

#include "VarTable.h"

using std::map;


VarElements::VarElements() {}

VarElements::VarElements(int id, string name)
{
    index = id;
    var = name;
}

VarElements::VarElements(const struct VarElements &other)
{
    if (this != &other) {
        index = other.index;
        var = other.var;
        assignModifying = other.assignModifying;
        ifModifying = other.ifModifying;
        whileModifying = other.whileModifying;
        stmtModifying = other.stmtModifying;
        usedBy = other.usedBy;
        this->procModifying = other.procModifying;
        this->assignUsing = other.assignUsing;
        this->ifUsing = other.ifUsing;
        this->whileUsing = other.whileUsing;
        this->callUsing = other.callUsing;
        this->stmtUsing = other.stmtUsing;
        this->usedByProc = other.usedByProc;
    }
}

VarElements& VarElements::operator=(const struct VarElements &other)
{
    if (this != &other) {
        index = other.index;
        var = other.var;
        assignModifying = other.assignModifying;
        ifModifying = other.ifModifying;
        whileModifying = other.whileModifying;
        stmtModifying = other.stmtModifying;
        this->procModifying = other.procModifying;
        usedBy = other.usedBy;
        this->assignUsing = other.assignUsing;
        this->ifUsing = other.ifUsing;
        this->whileUsing = other.whileUsing;
        this->callUsing = other.callUsing;
        this->stmtUsing = other.stmtUsing;
        this->usedByProc = other.usedByProc;
    }
    return *this;
}

VarTable::VarTable()
        : varSet_()
{}

VarTable::VarTable(const VarTable &other)
        : varSet_(other.varSet_)
{
    if (this != &other) {
        varTable = other.varTable;
        nameToIndex = other.nameToIndex;
    }
}

VarTable& VarTable::operator=(const VarTable &other)
{
    if (this != &other) {
        varTable = other.varTable;
        varSet_ = other.varSet_;
        nameToIndex = other.nameToIndex;
    }
    return *this;
}

VarTable::~VarTable() {}

int VarTable::get_index(string var) const
{
    map<string,int>::const_iterator it = nameToIndex.find(var);
    if (it == nameToIndex.end()) {
        return -1;
    } else {
        return it->second;
    }
}

const string& VarTable::get_var_name(int index) const
{
    int sz = varTable.size();
    if (index < 0 || index >= sz) {
        return "";
    } else {
        return varTable[index].var;
    }
}

int VarTable::insert_var(string var)
{
    if (nameToIndex.find(var) != nameToIndex.end()) {
        return nameToIndex[var];
    }

    int index = varTable.size();
    varSet_.insert(var);
    nameToIndex[var] = index;
    VarElements varEntry = VarElements(index, var);
    varTable.push_back(varEntry);
    return index;
}

void VarTable::add_assign_modifies_var(int assign, const string& var)
{
    int index = get_index(var);
    if (index >= 0) {
        varTable[index].assignModifying.insert(assign);
        varTable[index].stmtModifying.insert(assign);
    }
}

void VarTable::add_if_modifies_var(int ifStmt, const string& var)
{
    int index = get_index(var);
    if (index >= 0) {
        varTable[index].ifModifying.insert(ifStmt);
        varTable[index].stmtModifying.insert(ifStmt);
    }
}

void VarTable::add_while_modifies_var(int whileStmt, const string& var)
{
    int index = get_index(var);
    if (index >= 0) {
        varTable[index].whileModifying.insert(whileStmt);
    }
}

void VarTable::add_call_modifies_var(int callStmt, const string& var)
{
    int index = get_index(var);
    if (index >= 0) {
        varTable[index].callModifying.insert(callStmt);
        varTable[index].stmtModifying.insert(callStmt);
    }
}

void VarTable::add_stmt_modifies_var(int stmtNo, const string& var)
{
    int index = get_index(var);
    if (index >= 0) {
        varTable[index].stmtModifying.insert(stmtNo);
    }
}

void VarTable::add_proc_modifies_var(const string& procName,
        const string& var)
{
    int index = get_index(var);
    if (index >= 0) {
        varTable[index].procModifying.insert(procName);
    }
}

void VarTable::add_used_by(string var, DesignEnt entType, int stmtNo)
{
    assert(QueryInfo::is_valid_argOne_syn_type(REL_USES, entType));
    int index = get_index(var);
    if (index >= 0) {
        VarElements& varElem = varTable[index];
        switch (entType) {
        case ENT_ASSIGN:
            varElem.assignUsing.insert(stmtNo);
            break;
        case ENT_CALL:
            varElem.callUsing.insert(stmtNo);
            break;
        case ENT_IF:
            varElem.ifUsing.insert(stmtNo);
            break;
        case ENT_WHILE:
            varElem.whileUsing.insert(stmtNo);
            break;
        }
        // insert into used by stmt since every design ent here
        // is of stmt type
        varElem.stmtUsing.insert(stmtNo);
    }
}

void VarTable::add_used_by(string var, DesignEnt entType, string procName)
{
    assert(entType == ENT_PROC);
    int index = get_index(var);
    if (index >= 0) {
        varTable[index].usedByProc.insert(procName);
    }
}

const set<int>& VarTable::get_assign_modifying_var(const string& var) const
{
    int index = get_index(var);
    if (index == -1) {
        return EMPTY_INTSET;
    } else {
        return varTable[index].assignModifying;
    }
}

const set<int>& VarTable::get_if_modifying_var(const string& var) const
{
    int index = get_index(var);
    if (index == -1) {
        return EMPTY_INTSET;
    } else {
        return varTable[index].ifModifying;
    }
}

const set<int>& VarTable::get_while_modifying_var(const string& var) const
{
    int index = get_index(var);
    if (index == -1) {
        return EMPTY_INTSET;
    } else {
        return varTable[index].whileModifying;
    }
}

const set<int>& VarTable::get_call_modifying_var(const string& var) const
{
    int index = get_index(var);
    if (index == -1) {
        return EMPTY_INTSET;
    } else {
        return varTable[index].callModifying;
    }
}

const set<int>& VarTable::get_stmt_modifying_var(const string& var) const
{
    int index = get_index(var);
    if (index == -1) {
        return EMPTY_INTSET;
    } else {
        return varTable[index].stmtModifying;
    }
}

const set<string>&
VarTable::get_all_procedures_modifying(const string& var) const
{
    int index = this->get_index(var);
    if (index == -1) {
        return EMPTY_STRINGSET;
    } else {
        return varTable[index].procModifying;
    }
}

const set<int>& VarTable::get_modified_by(int index) const
{
    int sz = varTable.size();
    if (index < 0 || index >= sz) {
        return EMPTY_INTSET;
    }
    return varTable[index].stmtModifying;
}

const set<int>& VarTable::get_used_by(string var) const
{
    int index = get_index(var);
    if (index == -1) {
        return EMPTY_INTSET;
    }
    return varTable[index].usedBy;
}

const set<int>& VarTable::get_used_by(int index) const
{
    int sz = varTable.size();
    if (index < 0 || index >= sz) {
        return EMPTY_INTSET;
    }
    return varTable[index].usedBy;
}

bool VarTable::uses_query_int_X_var(DesignEnt xType, int x,
            const string& var) const
{
    int idx = this->get_index(var);
    if (idx >= 0) {
        const VarElements& varElement = this->varTable[idx];
        switch (xType) {
        case ENT_ASSIGN:
            return (varElement.assignUsing.find(x) !=
                    varElement.assignUsing.end());
            break;
        case ENT_CALL:
            return (varElement.callUsing.find(x) !=
                    varElement.callUsing.end());
            break;
        case ENT_IF:
            return (varElement.ifUsing.find(x) !=
                    varElement.ifUsing.end());
            break;
        case ENT_WHILE:
            return (varElement.whileUsing.find(x) !=
                    varElement.whileUsing.end());
            break;
        case ENT_STMT:
        case ENT_PROGLINE:
            return (varElement.stmtUsing.find(x) !=
                    varElement.stmtUsing.end());
            break;
        }
    }
    return false;
}

const set<int>& VarTable::get_X_using_var(DesignEnt entType,
        const string& var) const
{
    assert(QueryInfo::is_valid_argOne_syn_type(REL_USES, entType));
    int index = get_index(var);
    if (index == -1) {
        return EMPTY_INTSET;
    }
    const VarElements &varElem = this->varTable[index];
    switch (entType) {
    case ENT_ASSIGN:
        return varElem.assignUsing;
        break;
    case ENT_CALL:
        return varElem.callUsing;
        break;
    case ENT_IF:
        return varElem.ifUsing;
        break;
    case ENT_WHILE:
        return varElem.whileUsing;
        break;
    case ENT_STMT:
    case ENT_PROGLINE:
        return varElem.stmtUsing;
        break;
    }
    return EMPTY_INTSET;
}

const set<string>& VarTable::get_string_X_using_var(DesignEnt entType,
        const string& var) const
{
    assert(QueryInfo::is_valid_argOne_syn_type(REL_USES, entType));
    int idx = get_index(var);
    if (idx >= 0) {
        const VarElements& varElem = this->varTable[idx];
        switch (entType) {
        case ENT_PROC:
            return varElem.usedByProc;
            break;
        }
    }
    return EMPTY_STRINGSET;
}

set<string> VarTable::get_modified_by_proc(string var){
    int index = get_index(var);
    if (index == -1) {
        return EMPTY_STRINGSET;
    }
    return varTable[index].procModifying;
}

set<string> VarTable::get_used_by_proc(string var){
    int index = get_index(var);
    if (index == -1) {
        return EMPTY_STRINGSET;
    }
    return varTable[index].usedByProc;
}

const set<string>& VarTable::get_all_vars() const
{
    return this->varSet_;
}

bool VarTable::has_any_var() const
{
    return (this->varTable.size() > 0);
}

bool VarTable::anyone_uses_this_var(const string& varName) const
{
    int varIdx = this->get_index(varName);
    if (varIdx != -1) {
        const VarElements& varElem = this->varTable[varIdx];
        return ((!varElem.assignUsing.empty()) ||
                (!varElem.ifUsing.empty()) ||
                (!varElem.whileUsing.empty()) ||
                (!varElem.callUsing.empty()) ||
                (!varElem.stmtUsing.empty()) ||
                (!varElem.usedByProc.empty()));
    }
    return false;
}