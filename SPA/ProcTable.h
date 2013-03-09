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
    set<string> modifies; // Variables modified by procedure
    set<string> uses;
    // CFG root node
    ProcElements();
    ProcElements(string name);
};


class ProcTable{

public:
    ProcTable();
    int get_index(string procName) const;
    string get_proc_name(int index);

    void update_table(VarTable *vt);

    int insert_proc(string procName);

    void set_start(string procName, int stmtNo);
    void set_end(string procName, int stmtNo);
    void set_proc_root(string procName, Node *root);

    void add_modifies(string procName, string varName);
    void add_uses(string procName, string varName);
    void add_calls(string proc1, string proc2); 

    int get_start(string procName);
    int get_end(string procName);
    Node* get_root(string procName);
    Node* get_root(int index);

    const std::set<std::string>& get_calls(const std::string& procName)
            const;
    const std::set<std::string>& get_calls(int index) const;
    const std::set<std::string>& get_called_by
            (const std::string& procName) const;
    const std::set<std::string>& get_called_by(int index) const;

    bool does_procedure_modify_var(const std::string& procName,
            const std::string& varName) const;
    const std::set<std::string>&
        get_modifies(const std::string& procName) const;
    const std::set<std::string>& get_vars_used_by_proc(
            const std::string& procName) const;
    std::set<std::string> get_all_procs() const;

    /*
     * Given a procedure proc and variable var, returns true if
     * Uses(proc, var)
     * @param proc name of procedure
     * @param var name of variable
     * @return true if Uses(proc,var), false otherwise
     */
    bool uses_query_procedure_var(const std::string& proc,
            const std::string& var) const;

    string which_proc(int stmtNo);

    /// Checks if there is at least one procedure in the ProcTable
    /// @return true if there is atl east one procedure in the
    ///         ProcTable, false otherwise
    bool has_any_proc() const;

    /// Checks if at least one variable is being used by any procedure
    /// @return true if there is at least one variable used by a
    ///         procedure, false otherwise
    bool at_least_one_var_used() const;

private:
    void add_called_by(string proc1, string proc2); 
    
    void update(string procName);
    void combine_up(string proc1, string proc2);
    vector<int> updated;

    const set<string> EMPTY_STRINGSET;

    map<int, string> procFinder; 
    map<string, int> nameToIndex;
    vector<ProcElements> procTable;
    VarTable *varTable;

};

#endif