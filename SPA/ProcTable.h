#ifndef T11_PROC_TABLE_H
#define T11_PROC_TABLE_H
#include <map>
#include <set>
#include <string>
#include <vector>
#include "VarTable.h"
#include "Node.h"

using std::vector;
using std::string;
using std::set;
using std::map;

struct ProcElements {
    string procName;
    Node *procRoot;
    VarTable *varTable;
    set<string> calledBy;
    set<string> calls;
    set<string> modifies;
    set<string> uses;
    // CFG root node
    // start end
    ProcElements();
    ProcElements(string name, Node *root);
};


class ProcTable{

public:
    ProcTable();
    int get_index(string procName);
    string get_proc_name(int index);

    void update_called_by(); // update get_calls

    int insert_proc(string procName, Node *root);
    void add_modifies(string procName, string varName);
    void add_uses(string procName, string varName);
    void add_calls(string proc1, string proc2); 

    set<string> get_calls(string procName);
    set<string> get_calls(int index);
    set<string> get_called_by(string procName);
    set<string> get_called_by(int index);
    VarTable* get_varTable(string procName);
    VarTable* get_varTable(int index);
    Node* get_root(string procName);
    Node* get_root(int index);
    set<string> get_modifies(string procName);
    set<string> get_uses(string procName);
    set<string> get_all_procs();

private:
    void add_called_by(string proc1, string proc2); 
    const set<string> EMPTY_STRINGSET;
    vector<ProcElements> procTable;
    map<string, int> nameToIndex; 

};

#endif