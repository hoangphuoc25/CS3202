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
    int start;
    int end;
    set<string> calledBy;
    set<string> calls;
    set<string> modifies;
    set<string> uses;
    // CFG root node
    ProcElements();
    ProcElements(string name);
};


class ProcTable{

public:
    ProcTable();
    int get_index(string procName);
    string get_proc_name(int index);
    Node* get_root(string procName);

    void update_table(VarTable *vt);

    void set_start(string procName, int stmtNo);
    void set_end(string procName, int stmtNo);
    void set_proc_root(string procName, Node *root);
    int insert_proc(string procName);
    void add_modifies(string procName, string varName);
    void add_uses(string procName, string varName);
    void add_calls(string proc1, string proc2); 

    int get_start(string procName);
    int get_end(string procName);
    set<string> get_calls(string procName);
    set<string> get_called_by(string procName);
    set<string> get_modifies(string procName);
    set<string> get_uses(string procName);
    set<string> get_all_procs();

    set<string> get_calls(int index);
    set<string> get_called_by(int index);
    Node* get_root(int index);

private:
    void add_called_by(string proc1, string proc2); 
    const set<string> EMPTY_STRINGSET;
    vector<ProcElements> procTable;
    map<string, int> nameToIndex;
    vector<int> updated;
    void update(string procName);
    void combine_up(string proc1, string proc2);
    VarTable *varTable;

};

#endif