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
        modifiedBy = other.modifiedBy;
        usedBy = other.usedBy;
    }
}

VarElements& VarElements::operator=(const struct VarElements &other)
{
    if (this != &other) {
        index = other.index;
        var = other.var;
        modifiedBy = other.modifiedBy;
        usedBy = other.usedBy;
    }
    return *this;
}

VarTable::VarTable() {}

VarTable::VarTable(const VarTable &other)
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
        nameToIndex = other.nameToIndex;
    }
    return *this;
}

VarTable::~VarTable() {}

int VarTable::insert_var(string var)
{
    if (nameToIndex.find(var) != nameToIndex.end()) {
        return nameToIndex[var];
    }

    int index = varTable.size();
    nameToIndex[var] = index;
    VarElements varEntry = VarElements(index, var);
    varTable.push_back(varEntry);
    return index;
}

int VarTable::get_index(string var) const
{
    map<string,int>::const_iterator it = nameToIndex.find(var);
    if (it == nameToIndex.end()) {
        return -1;
    } else {
        return it->second;
    }
}

string VarTable::get_var_name(int index) const
{
    int sz = varTable.size();
    if (index < 0 || index >= sz) {
        return "";
    } else {
        return varTable[index].var;
    }
}

void VarTable::add_modified_by(string var, int stmtNo)
{
    int index = get_index(var);
    if (index >= 0) {
        varTable[index].modifiedBy.insert(stmtNo);
    }
}

void VarTable::add_used_by(string var, int stmtNo)
{
    int index = get_index(var);
    if (index >= 0) {
        varTable[index].usedBy.insert(stmtNo);
    }
}

const set<int>& VarTable::get_modified_by(string var) const
{
    int index = get_index(var);
    if (index == -1) {
        return EMPTY_INTSET;
    } else {
        return varTable[index].modifiedBy;
    }
}

const set<int>& VarTable::get_modified_by(int index) const
{
    int sz = varTable.size();
    if (index < 0 || index >= sz) {
        return EMPTY_INTSET;
    }
    return varTable[index].modifiedBy;
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

vector<string> VarTable::get_all_vars() const
{
    vector<string> result;
    int len = varTable.size();
    for(int i = 0; i < len; i ++) {
        result.push_back(varTable[i].var);
    }
    return result;
}