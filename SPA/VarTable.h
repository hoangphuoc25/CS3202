#ifndef T11_TABLES_AST_H
#define T11_TABLES_AST_H

#include <vector>
#include <utility>
#include <string>
#include <map>

using std::vector;
using std::pair;
using std::string;

struct VarElements {
	int index;
	string var;
	vector<int> modifies;
	vector<int> uses;
    VarElements();
	VarElements(int id, string name);
    VarElements(const struct VarElements &other);
    VarElements& operator=(const struct VarElements &other);
};


class VarTable {
public:
    VarTable();
    VarTable(const VarTable &other);
    VarTable& operator=(const VarTable &other);
    ~VarTable();
	// #method for varTable#
	int insert_var(string var);
	void add_modifies(string var, int stmtNo);
	void add_uses(string var, int stmtNo);

	int get_index(string var) const;
	string get_varName(int index) const;
	const vector<int>& get_modifies(string var) const;
	const vector<int>& get_modifies(int index) const;
	const vector<int>& get_uses(string var) const;
	const vector<int>& get_uses(int index) const;
	vector<string> get_allVars() const;

private:
    const vector<int> EMPTY_INTVEC;
	vector<VarElements> varTable;
	std::map<string,int> nameToIndex;
};

#endif