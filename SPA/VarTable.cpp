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
        modifies = other.modifies;
        uses = other.uses;
    }
}

VarElements& VarElements::operator=(const struct VarElements &other)
{
    if (this != &other) {
        index = other.index;
        var = other.var;
        modifies = other.modifies;
        uses = other.uses;
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

string VarTable::get_varName(int index) const
{
    int sz = varTable.size();
    if (index < 0 || index >= sz) {
        return "";
    } else {
        return varTable[index].var;
    }
}

void VarTable::add_modifies(string var, int stmtNo)
{
	int index = get_index(var);
    if (index >= 0) {
        varTable[index].modifies.push_back(stmtNo);
    }
}

void VarTable::add_uses(string var, int stmtNo)
{
	int index = get_index(var);
    if (index >= 0) {
	    varTable[index].uses.push_back(stmtNo);
    }
}

const vector<int>& VarTable::get_modifies(string var) const
{
	int index = get_index(var);
    if (index == -1) {
        return EMPTY_INTVEC;
    } else {
	    return varTable[index].modifies;
    }
}

const vector<int>& VarTable::get_modifies(int index) const
{
    int sz = varTable.size();
    if (index < 0 || index >= sz) {
        return EMPTY_INTVEC;
    }
	return varTable[index].modifies;
}

const vector<int>& VarTable::get_uses(string var) const
{
	int index = get_index(var);
    if (index == -1) {
        return EMPTY_INTVEC;
    }
	return varTable[index].uses;
}

const vector<int>& VarTable::get_uses(int index) const
{
    int sz = varTable.size();
    if (index < 0 || index >= sz) {
        return EMPTY_INTVEC;
    }
	return varTable[index].uses;
}

vector<string> VarTable::get_allVars() const
{
	vector<string> result;
    int len = varTable.size();
	for(int i = 0; i < len; i ++) {
		result.push_back(varTable[i].var);
	}
	return result;
}