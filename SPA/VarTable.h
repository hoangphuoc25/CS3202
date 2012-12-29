#ifndef T11_TABLES_AST_H
#define T11_TABLES_AST_H

#include <vector>
#include <utility>
#include <string>
#include <map>
#include <set>

using std::vector;
using std::pair;
using std::string;
using std::set;

struct VarElements {
    int index;
    string var;
    set<int> modifiedBy;
    set<int> usedBy;
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

    int get_index(string var) const;
    string get_var_name(int index) const;

    int insert_var(string var);
    void add_modified_by(string var, int stmtNo);
    void add_used_by(string var, int stmtNo);

    const set<int>& get_modified_by(string var) const;
    const set<int>& get_modified_by(int index) const;
    const set<int>& get_used_by(string var) const;
    const set<int>& get_used_by(int index) const;
    set<string> get_all_vars() const;

private:
    const set<int> EMPTY_INTSET;
    vector<VarElements> varTable;
    std::map<string,int> nameToIndex;
};

#endif