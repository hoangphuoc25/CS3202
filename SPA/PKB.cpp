#include <cassert>
#include "PKB.h"

PKB::PKB(){}

PKB::PKB(Node *root, ProcTable *pt, VarTable *vt, StmtBank *sb, vector<CFGNode*> *cfg){
    progRoot = root;
    procTable = pt;
    varTable = vt;
    stmtBank = sb;
    CFG = cfg;
}

set<string> PKB::modifies_X_Y_get_string_Y_from_int_X(DesignEnt xType,
        DesignEnt yType, int stmt) const
{
    assert(QueryInfo::is_valid_argOne_syn_type(REL_MODIFIES, xType));
    assert(yType == ENT_VAR);
    Node *node = NULL;
    switch (xType) {
    case ENT_ASSIGN:
        node = this->stmtBank->get_assignNode(stmt);
        break;
    case ENT_IF:
        node = this->stmtBank->get_ifNode(stmt);
        break;
    case ENT_WHILE:
        node = this->stmtBank->get_whileNode(stmt);
        break;
    case ENT_CALL:
        node = this->stmtBank->get_callNode(stmt);
        break;
    case ENT_STMT:
    case ENT_PROGLINE:
        node = this->stmtBank->get_stmtNode(stmt);
        break;
    }
    if (node == NULL) {
        return set<string>();
    } else {
        return node->get_modifies();
    }
}

set<string> PKB::modifies_X_Y_get_string_Y_from_string_X(DesignEnt xType,
        DesignEnt yType, const string& x) const
{
    assert(QueryInfo::is_valid_argOne_syn_type(REL_MODIFIES, xType));
    assert(yType == ENT_VAR);
    switch (xType) {
    case ENT_PROC:
        return this->procTable->get_modifies(x);
        break;
    }
    return set<string>();
}

set<int> PKB::modifies_X_Y_get_int_X_from_string_Y(DesignEnt xType,
        DesignEnt yType, const string& varName) const
{
    assert(QueryInfo::is_valid_argOne_syn_type(REL_MODIFIES, xType));
    assert(yType == ENT_VAR);
    switch (xType) {
    case ENT_ASSIGN:
        return this->varTable->get_assign_modifying_var(varName);
        break;
    case ENT_CALL:
        return this->varTable->get_call_modifying_var(varName);
        break;
    case ENT_WHILE:
        return this->varTable->get_while_modifying_var(varName);
        break;
    case ENT_IF:
        return this->varTable->get_if_modifying_var(varName);
        break;
    case ENT_STMT:
    case ENT_PROGLINE:
        return this->varTable->get_stmt_modifying_var(varName);
        break;
    }
    return set<int>();
}

set<string> PKB::modifies_X_Y_get_string_X_from_string_Y(DesignEnt xType,
        DesignEnt yType, const string& varName) const
{
    assert(QueryInfo::is_valid_argOne_syn_type(REL_MODIFIES, xType));
    assert(yType == ENT_VAR);
    switch (xType) {
    case ENT_PROC:
        return this->varTable->get_all_procedures_modifying(varName);
        break;
    }
    return set<string>();
}

set<int> PKB::uses_X_Y_get_int_X_from_string_Y(DesignEnt xType,
        DesignEnt yType, const string& varName) const
{
    assert(QueryInfo::is_valid_argOne_syn_type(REL_USES, xType));
    assert(yType == ENT_VAR);
    return this->varTable->get_X_using_var(xType, varName);
}

set<string> PKB::uses_X_Y_get_string_X_from_string_Y(DesignEnt xType,
        DesignEnt yType, const string& varName) const
{
    assert(QueryInfo::is_valid_argOne_syn_type(REL_USES, xType));
    assert(yType == ENT_VAR);
    return this->varTable->get_string_X_using_var(xType, varName);
}

set<string> PKB::uses_X_Y_get_string_Y_from_int_X(DesignEnt xType,
        DesignEnt yType, int stmtNo) const
{
    return EMPTY_STRINGSET;
}

set<string> PKB::uses_X_Y_get_string_Y_from_string_X(DesignEnt xType,
        DesignEnt yType, const string& x) const
{
    assert(QueryInfo::is_valid_argOne_syn_type(REL_USES, xType));
    assert(yType == ENT_VAR);
    switch (xType) {
    case ENT_PROC:
        return this->procTable->get_vars_used_by_proc(x);
        break;
    }
    return EMPTY_STRINGSET;
}

set<string> PKB::calls_X_Y_get_string_X_from_string_Y(DesignEnt xType,
        DesignEnt yType, const string& y) const
{
    assert(QueryInfo::is_valid_argOne_syn_type(REL_CALLS, xType));
    assert(QueryInfo::is_valid_argTwo_syn_type(REL_CALLS, yType));
    switch (xType) {
    case ENT_PROC:
        switch (yType) {
        case ENT_PROC:
            return this->procTable->get_called_by(y);
            break;
        }
        break;
    }
    return set<string>();
}

set<string> PKB::calls_X_Y_get_string_Y_from_string_X(DesignEnt xType,
        DesignEnt yType, const string& x) const
{
    assert(QueryInfo::is_valid_argOne_syn_type(REL_CALLS, xType));
    assert(QueryInfo::is_valid_argTwo_syn_type(REL_CALLS, yType));
    switch (xType) {
    case ENT_PROC:
        switch (yType) {
        case ENT_PROC:
            return this->procTable->get_calls(x);
            break;
        }
        break;
    }
    return set<string>();
}

set<string> PKB::callsStar_X_Y_get_string_X_from_string_Y
        (DesignEnt xType, DesignEnt yType, const string& y) const
{
    return EMPTY_STRINGSET;
}

set<string> PKB::callsStar_X_Y_get_string_Y_from_string_X
        (DesignEnt xType, DesignEnt yType, const string& x) const
{
    return EMPTY_STRINGSET;
}

set<int> PKB::parent_X_Y_get_int_X_from_int_Y(DesignEnt xType,
        DesignEnt yType, int y) const
{
    assert(QueryInfo::is_valid_argOne_syn_type(REL_PARENT, xType));
    assert(QueryInfo::is_valid_argTwo_syn_type(REL_PARENT, yType));
    set<int> ret;
    Node *node = NULL;
    switch (xType) {
    case ENT_ASSIGN:
        node = this->stmtBank->get_assignNode(y);
        break;
    case ENT_CALL:
        node = this->stmtBank->get_callNode(y);
        break;
    case ENT_IF:
        node = this->stmtBank->get_ifNode(y);
        break;
    case ENT_WHILE:
        node = this->stmtBank->get_whileNode(y);
        break;
    case ENT_STMT:
    case ENT_PROGLINE:
        node = this->stmtBank->get_stmtNode(y);
        break;
    }
    if (node != NULL) {
        Node *par = node->get_parent();
        if (par != NULL) {
            int parStmt = par->get_stmtNo();
            if (this->stmtBank->is_stmtType(parStmt, xType)) {
                ret.insert(parStmt);
            }
        }
    }
    return ret;
}

set<int> PKB::parent_X_Y_get_int_Y_from_int_X(DesignEnt xType,
        DesignEnt yType, int x) const
{
    // TODO:
    // Change how we obtain children nodes
    //   might want to store set<int> of assign children, call children,
    //   if children, etc.
    assert(QueryInfo::is_valid_argOne_syn_type(REL_PARENT, xType));
    assert(QueryInfo::is_valid_argTwo_syn_type(REL_PARENT, yType));
    set<int> ret;
    Node *node = NULL;
    switch (xType) {
    case ENT_WHILE:
        node = this->stmtBank->get_whileNode(x);
        break;
    case ENT_IF:
        node = this->stmtBank->get_ifNode(x);
        break;
    case ENT_STMT:
    case ENT_PROGLINE:
        node = this->stmtBank->get_stmtNode(x);
        break;
    }
    if (node != NULL) {
        vector<Node*> v = node->get_children();
        int sz = v.size();
        for(int i = 0; i < sz; i++) {
            int stmt = v[i]->get_stmtNo();
            if (this->stmtBank->is_stmtType(stmt, yType)) {
                ret.insert(stmt);
            }
        }
    }
    return ret;
}

set<int> PKB::parentStar_X_Y_get_int_X_from_int_Y(DesignEnt xType,
        DesignEnt yType, int y) const
{
    return EMPTY_INTSET;
}

set<int> PKB::parentStar_X_Y_get_int_Y_from_int_X(DesignEnt xType,
        DesignEnt yType, int x) const
{
    return EMPTY_INTSET;
}

set<int> PKB::follows_X_Y_get_int_X_from_int_Y(DesignEnt xType,
        DesignEnt yType, int y) const
{
    return EMPTY_INTSET;
}

set<int> PKB::follows_X_Y_get_int_Y_from_int_X(DesignEnt xType,
        DesignEnt yType, int x) const
{
    return EMPTY_INTSET;
}

set<int> PKB::followsStar_X_Y_get_int_X_from_int_Y(DesignEnt xType,
        DesignEnt yType, int y) const
{
    return EMPTY_INTSET;
}

set<int> PKB::followsStar_X_Y_get_int_Y_from_int_X(DesignEnt xType,
        DesignEnt yType, int x) const
{
    return EMPTY_INTSET;
}

set<int> PKB::next_X_Y_get_int_X_from_int_Y(DesignEnt xType,
        DesignEnt yType, int y) const
{
    return EMPTY_INTSET;
}

set<int> PKB::next_X_Y_get_int_Y_from_int_X(DesignEnt xType,
        DesignEnt yType, int x) const
{
    return EMPTY_INTSET;
}

set<int> PKB::nextStar_X_Y_get_int_X_from_int_Y(DesignEnt xType,
        DesignEnt yType, int y) const
{
    return EMPTY_INTSET;
}

set<int> PKB::nextStar_X_Y_get_int_Y_from_int_X(DesignEnt xType,
        DesignEnt yType, int x) const
{
    return EMPTY_INTSET;
}

set<int> PKB::affects_X_Y_get_int_X_from_int_Y(DesignEnt xType,
        DesignEnt yType, int y) const
{
    return EMPTY_INTSET;
}

set<int> PKB::affects_X_Y_get_int_Y_from_int_X(DesignEnt xType,
        DesignEnt yType, int x) const
{
    return EMPTY_INTSET;
}

set<int> PKB::affectsStar_X_Y_get_int_X_from_int_Y(DesignEnt xType,
        DesignEnt yType, int y) const
{
    return EMPTY_INTSET;
}

set<int> PKB::affectsStar_X_Y_get_int_Y_from_int_X(DesignEnt xType,
        DesignEnt yType, int x) const
{
    return EMPTY_INTSET;
}

set<int> PKB::get_all_assign() const
{
    return this->stmtBank->get_all_assign();
}

set<int> PKB::get_all_if() const
{
    return this->stmtBank->get_all_if();
}

set<int> PKB::get_all_while() const
{
    return this->stmtBank->get_all_while();
}

set<int> PKB::get_all_call() const
{
    return this->stmtBank->get_all_call();
}

set<int> PKB::get_all_stmt() const
{
    return this->stmtBank->get_all_stmt();
}

set<int> PKB::get_all_progline() const
{
    return this->get_all_stmt();
}

set<int> PKB::get_all_stmtLst() const
{
    return this->stmtBank->get_all_stmtLst();
}

set<string> PKB::get_all_vars() const
{
    return varTable->get_all_vars();
}

set<string> PKB::get_all_procs() const
{
    return this->procTable->get_all_procs();
}

set<int> PKB::get_all_const() const
{
    return this->stmtBank->get_all_const();
}

string PKB::get_call_procName(int callStmt) const
{
    return this->stmtBank->get_call_procName(callStmt);
}

// Variables
string PKB::get_control_var(int stmtNo){
    if (is_valid_stmtNo(stmtNo)) {
        return stmtBank->get_node(stmtNo)->get_control_var();
    } else {
        return "";
    }
}

set<string> PKB::get_all_vars_by_proc(string procName){
    set<string> s,res;
    set<string>::iterator it;
    s = procTable->get_modifies(procName);
    for (it = s.begin(); it != s.end(); it++) {
        res.insert(*it);
    }
    s = procTable->get_vars_used_by_proc(procName);
    for (it = s.begin(); it != s.end(); it++) {
        res.insert(*it);
    }
    return res;
}

// Calls
bool PKB::is_calls(string proc1, string proc2){
    set<string> s = procTable->get_calls(proc1); 
    return (s.find(proc2) != s.end());
}

bool PKB::is_calls_star(string proc1, string proc2){
    queue<string> q;
    set<string>::iterator it;
    set<string> s = procTable->get_calls(proc1); 
    for (it = s.begin(); it != s.end(); it++) {
        q.push(*it);
    }
    while (!q.empty()) {
        if (q.front() == proc2) {
            return true;
        } else {
            s = procTable->get_calls(q.front());
            for (it = s.begin(); it != s.end(); it++) {
                q.push(*it);
            }
            q.pop();
        }
    }
    return false;
}

set<string> PKB::get_calls(string procName){
    return procTable->get_calls(procName);
}

set<string> PKB::get_calls_star(string procName){
    queue<string> q;
    set<string> res;
    set<string>::iterator it;
    set<string> s = procTable->get_calls(procName); 
    for (it = s.begin(); it != s.end(); it++) {
        q.push(*it);
    }
    while (!q.empty()) {
        res.insert(q.front());
        s = procTable->get_calls(q.front());
        for (it = s.begin(); it != s.end(); it++) {
            q.push(*it);
        }
        q.pop();
    }
    return res;
}

set<string> PKB::get_called_by(string procName){
    return procTable->get_called_by(procName);
}

set<string> PKB::get_called_by_star(string procName){
    queue<string> q;
    set<string> res;
    set<string>::iterator it;
    set<string> s = procTable->get_called_by(procName); 
    for (it = s.begin(); it != s.end(); it++) {
        q.push(*it);
    }
    while (!q.empty()) {
        res.insert(q.front());
        s = procTable->get_called_by(q.front());
        for (it = s.begin(); it != s.end(); it++) {
            q.push(*it);
        }
        q.pop();
    }
    return res;
}

// Modifies
bool PKB::is_modifies(string procName, string varName){
    set<string> s = procTable->get_modifies(procName);
    return (s.find(varName) != s.end());
}

bool PKB::is_modifies(int stmtNo, string varName){
    if (is_valid_stmtNo(stmtNo)) {
        set<string> s = stmtBank->get_node(stmtNo)->get_modifies();
        return (s.find(varName) != s.end());
    } else {
        return false;
    }
}

set<string> PKB::get_proc_modifies(string var){
    return varTable->get_modified_by_proc(var);
}

set<int> PKB::get_stmt_modifies(const string& var) const
{
    return varTable->get_stmt_modifying_var(var);
}

set<string> PKB::get_var_proc_modifies(string procName){
    return procTable->get_modifies(procName);
}

set<string> PKB::get_var_stmt_modifies(int stmtNo){
    if (is_valid_stmtNo(stmtNo)) {
        return stmtBank->get_node(stmtNo)->get_modifies();
    } else {
        return EMPTY_STRINGSET;
    }
}

// Uses
bool PKB::is_uses(string procName, string varName){
    set<string> s = procTable->get_vars_used_by_proc(procName);
    return (s.find(varName) != s.end());
}

bool PKB::is_uses(int stmtNo, string varName){
    if (is_valid_stmtNo(stmtNo)) {
        set<string> s = stmtBank->get_node(stmtNo)->get_uses();
        return (s.find(varName) != s.end());
    } else {
        return false;
    }
}

set<string> PKB::get_proc_uses(string var){
    return varTable->get_used_by_proc(var);
}

set<int> PKB::get_stmt_uses(string var){
    return varTable->get_used_by(var);
}

set<string> PKB::get_var_proc_uses(string procName)
{
    return procTable->get_vars_used_by_proc(procName);
}

set<string> PKB::get_var_stmt_uses(int stmtNo){
    if (is_valid_stmtNo(stmtNo)) {
        return stmtBank->get_node(stmtNo)->get_uses();
    } else {
        return EMPTY_STRINGSET;
    }
}

// Parent
bool PKB::is_parent(int stmt1, int stmt2){
    if (is_valid_stmtNo(stmt1) && is_valid_stmtNo(stmt2)) {
        return (stmtBank->get_node(stmt2)->get_parent()->get_stmtNo() == stmt1);
    } else {
        return false;
    }
}

bool PKB::is_parent_star(int stmt1, int stmt2){
    if (is_valid_stmtNo(stmt1) && is_valid_stmtNo(stmt2)) {
        Node *n = stmtBank->get_node(stmt2)->get_parent();
        while (n != NULL) {
            if (n->get_stmtNo() == stmt1) {
                return true;
            } else {
                n = n->get_parent();
            }
        }
        return false;
    } else {
        return false;
    }
}

int PKB::get_parent(int stmtNo){
    if (is_valid_stmtNo(stmtNo)) {
        Node *n = stmtBank->get_node(stmtNo)->get_parent();
        if (n != NULL) {
            return n->get_stmtNo();
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

set<int> PKB::get_parent_star(int stmtNo){
    if (is_valid_stmtNo(stmtNo)) {
        set<int> res;
        Node *n = stmtBank->get_node(stmtNo)->get_parent();
        while (n != NULL) {
            res.insert(n->get_stmtNo());
            n = n->get_parent();
        }
        return res;
    } else {
        return EMPTY_INTSET;
    }
}

set<int> PKB::get_children(int stmtNo){
    if (is_valid_stmtNo(stmtNo)) {
        set<int> s;
        vector<Node*> v = stmtBank->get_node(stmtNo)->get_children(); 
        int sz = v.size();
        for(int i = 0; i< sz; i++) {
            s.insert(v[i]->get_stmtNo());
        }
        return s;
    } else {
        return EMPTY_INTSET;
    }
}

set<int> PKB::get_children_star(int stmtNo){
    if (is_valid_stmtNo(stmtNo)) {
        queue<Node*> q;
        set<int> res;
        Node *n = stmtBank->get_node(stmtNo);
        vector<Node*> v = n->get_children();
        int sz = v.size();
        for (int i = 0; i < sz; i++) {
            q.push(v[i]);
        }
        while (!q.empty()) {
            n = q.front();
            res.insert(n->get_stmtNo());
            v = n->get_children();
            sz = v.size();
            for (int i = 0; i < sz; i++) {
                q.push(v[i]);
            }
            q.pop();
        }
        return res;
    } else { 
        return EMPTY_INTSET;
    }
}

// Follows
bool PKB::is_follows(int stmt1, int stmt2){
    if (is_valid_stmtNo(stmt1) && is_valid_stmtNo(stmt2)) {
    return (stmtBank->get_node(stmt1)->get_successor()->get_stmtNo() == stmt2);
    } else {
        return false;
    }
}

bool PKB::is_follows_star(int stmt1, int stmt2){
    if (is_valid_stmtNo(stmt1) && is_valid_stmtNo(stmt2)) {
        Node *n = stmtBank->get_node(stmt1)->get_successor();
        while (n != NULL) {
            if (n->get_stmtNo() == stmt2) {
                return true;
            } else {
                n = n->get_successor();
            }
        }
        return false;
    } else { 
        return false;
    }
}

int PKB::get_successor(int stmtNo){
    if (is_valid_stmtNo(stmtNo)) {
        Node *n = stmtBank->get_node(stmtNo)->get_successor();
        if (n != NULL) {
            return n->get_stmtNo();
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

set<int> PKB::get_successor_star(int stmtNo){
    if (is_valid_stmtNo(stmtNo)) {
        set<int> res;
        Node *n = stmtBank->get_node(stmtNo)->get_successor();
        while (n != NULL) {
            res.insert(n->get_stmtNo());
            n = n->get_successor();
        }
        return res;
    } else {
        return EMPTY_INTSET;
    }
}

int PKB::get_predecessor(int stmtNo){
    if (is_valid_stmtNo(stmtNo)) {
        Node *n = stmtBank->get_node(stmtNo)->get_predecessor();
        if (n != NULL) {
            return n->get_stmtNo();
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

set<int> PKB::get_predecessor_star(int stmtNo){
    if (is_valid_stmtNo(stmtNo)) {
        set<int> res;
        Node *n = stmtBank->get_node(stmtNo)->get_predecessor();
        while (n != NULL) {
            res.insert(n->get_stmtNo());
            n = n->get_predecessor();
        }
        return res;
    } else {
        return EMPTY_INTSET;
    }
}

// Next
bool PKB::is_next(int stmt1, int stmt2)
{
    if (is_valid_stmtNo(stmt1) && is_valid_stmtNo(stmt2)) {
        set<int> s =  CFG->at(stmt1)->get_after();
        return (s.find(stmt2) != s.end());
    } else {
        return false;
    }
}

bool PKB::is_next_star(int stmt1, int stmt2)
{
    if (is_valid_stmtNo(stmt1) && is_valid_stmtNo(stmt2)) {
        set<int> s =  CFG->at(stmt1)->get_after();
        set<int>::iterator it;
        queue<int> q;
        for (it = s.begin(); it != s.end(); it++) {
            q.push(*it);
        }
        while (!q.empty()) {
            if (q.front() == stmt2) {
                return true;
            } else {
                s = CFG->at(q.front())->get_after();
                for (it = s.begin(); it != s.end(); it++) {
                    q.push(*it);
                }
                q.pop();
            }
        }
        return false;
    } else {
        return false;
    }
}

set<int> PKB::get_before(int stmtNo)
{
    if (is_valid_stmtNo(stmtNo)) {
        return CFG->at(stmtNo)->get_before();
    } else {
        return EMPTY_INTSET;
    }
}

set<int> PKB::get_before_star(int stmtNo) {
    if (is_valid_stmtNo(stmtNo)) {
        set<int> s =  CFG->at(stmtNo)->get_before();
        set<int>::iterator it;
        set<int> res , visited;
        queue<int> q;
        for (it = s.begin(); it != s.end(); it++) {
            q.push(*it);
        }
        while (!q.empty()) {
            if (visited.find(q.front()) == visited.end()) {
                visited.insert(q.front());
                res.insert(q.front());
                s = CFG->at(q.front())->get_before();
                for (it = s.begin(); it != s.end(); it++) {
                    q.push(*it);
                }
            }
            q.pop();
        }
        return res;
    } else {
        return EMPTY_INTSET;
    }

}

set<int> PKB::get_after(int stmtNo)
{
    if (is_valid_stmtNo(stmtNo)) {
        return CFG->at(stmtNo)->get_after();
    } else {
        return EMPTY_INTSET;
    }
}

set<int> PKB::get_after_star(int stmtNo) {
    if (is_valid_stmtNo(stmtNo)) {
        set<int> s =  CFG->at(stmtNo)->get_after();
        set<int>::iterator it;
        set<int> res, visited;
        queue<int> q;
        for (it = s.begin(); it != s.end(); it++) {
            q.push(*it);
        }
        while (!q.empty()) {
            if (visited.find(q.front()) == visited.end()) {
                visited.insert(q.front());
                res.insert(q.front());
                s = CFG->at(q.front())->get_after();
                for (it = s.begin(); it != s.end(); it++) {
                    q.push(*it);
                }
            }
            q.pop();
        }
        return res;
    } else {
        return EMPTY_INTSET;
    }
}

// Affects
bool PKB::is_affects(int stmt1, int stmt2)
{
    if (!is_stmtType(stmt1, ENT_ASSIGN) || !is_stmtType(stmt2, ENT_ASSIGN)) {
        return false;
    }

    set<int> visited; 
    set<string> temp;
    stack<CFGNode*> s;
    int n;
    string var = *get_var_stmt_modifies(stmt1).begin();

    // Initial checks
    temp = get_var_stmt_uses(stmt2);
    if (temp.find(var) == temp.end()) {
        return false;
    }

    CFGNode *curr = CFG->at(stmt1);
    s.push(curr->get_edge(OUT, 1));
    s.push(curr->get_edge(OUT, 2));
    visited.insert(curr->get_stmtNo());
    while (!s.empty()) {
        if (s.top() == NULL) {
            s.pop();
            continue;
        }
        curr = s.top();
        n = curr->get_stmtNo();
        // Dummy node -> continue
        if (n == -1) {
            s.pop();
            s.push(curr->get_edge(OUT, 1));
            continue;
        }
        // If visited
        if (visited.find(n) != visited.end()) {
            s.pop();
            continue;
        } else {
            visited.insert(n);
            // Reached stmt2 -> done
            if (n == stmt2) {
                return true;
            }
            // Check stmt only when it is assign stmt or calls
            if (is_stmtType(n, ENT_ASSIGN) || is_stmtType(n, ENT_CALL)) {
                temp = get_var_stmt_modifies(n);
                // Path broken
                if (temp.find(var) != temp.end()) {
                    continue;
                }
            }
            s.pop();
            s.push(curr->get_edge(OUT, 1));
            s.push(curr->get_edge(OUT, 2));
        }
    }
    return false;
}

bool PKB::is_affects_star(int stmt1, int stmt2)
{
    if (!is_stmtType(stmt1, ENT_ASSIGN) || !is_stmtType(stmt2, ENT_ASSIGN)) {
        return false;
    }

    set<int> processed;
    queue<int> q;
    set<int> temp;
    set<int>::iterator it;
    int n;
    temp = get_affects(stmt1);
    for (it = temp.begin(); it != temp.end(); it++) {
        q.push(*it);
    }
    while (!q.empty()) {
        n = q.front();
        if (processed.find(n) != processed.end()){
            q.pop();
            continue;
        } else {
            if (n == stmt2) {
                return true;
            }
            processed.insert(n);
            temp = get_affects(n);
            for (it = temp.begin(); it != temp.end(); it++) {
                q.push(*it);
            }
            q.pop();
        }
    }
    return false;
}

set<int> PKB::get_affects(int stmtNo)
{
    if (!is_stmtType(stmtNo, ENT_ASSIGN)) {
        return EMPTY_INTSET;
    }

    set<int> res;
    set<int> visited; 
    set<string> temp;
    stack<CFGNode*> s;
    int n;
    string var = *get_var_stmt_modifies(stmtNo).begin();
    CFGNode *curr = CFG->at(stmtNo);
    s.push(curr->get_edge(OUT, 1));
    s.push(curr->get_edge(OUT, 2));
    visited.insert(curr->get_stmtNo());
    while (!s.empty()) {
        if (s.top() == NULL) {
            s.pop();
            continue;
        }
        curr = s.top();
        n = curr->get_stmtNo();
        // Dummy node -> continue
        if (n == -1) {
            s.pop();
            s.push(curr->get_edge(OUT, 1));
            continue;
        }
        // If visited
        if (visited.find(n) != visited.end()) {
            s.pop();
            continue;
        } else {
            visited.insert(n);
            // Check if calls modifies
            if (is_stmtType(n, ENT_CALL)) {
                temp = get_var_stmt_modifies(n);
                // Current path broken.
                if (temp.find(var) != temp.end()) {
                    s.pop();
                    continue;
                }
            }
            // Check stmt only when it is assign stmt
            if (is_stmtType(n, ENT_ASSIGN)) {
                // stmt uses var: affects allows this stmt to modify var
                temp = get_var_stmt_uses(n);
                if (temp.find(var) != temp.end()){
                    res.insert(n);
                }
                temp = get_var_stmt_modifies(n);
                // Current path broken.
                if (temp.find(var) != temp.end()) {
                    s.pop();
                    continue;
                }
            }
            s.pop();
            s.push(curr->get_edge(OUT, 1));
            s.push(curr->get_edge(OUT, 2));
        }
    }
    return res;
}

set<int> PKB::get_affects_star(int stmtNo)
{
    if (!is_stmtType(stmtNo, ENT_ASSIGN)) {
        return EMPTY_INTSET;
    }
    set<int> processed;
    set<int> res;
    queue<int> q;
    set<int> temp;
    set<int>::iterator it;
    int n;
    temp = get_affects(stmtNo);
    for (it = temp.begin(); it != temp.end(); it++) {
        q.push(*it);
        res.insert(*it);
    }
    while (!q.empty()) {
        n = q.front();
        processed.insert(n);
        temp = get_affects(n);
        for (it = temp.begin(); it != temp.end(); it++) {
            q.push(*it);
            res.insert(*it);
        }
        q.pop();
    }
    return res;
}

set<int> PKB::get_affected_by(int stmtNo)
{
    if (!is_stmtType(stmtNo, ENT_ASSIGN)) {
        return EMPTY_INTSET;
    }
    set<string> var = get_var_stmt_uses(stmtNo);
    string procName = procTable->which_proc(stmtNo);
    set<int> s, res;
    set<int>::iterator it_stmt;
    set<string>::iterator it_var;
    for (it_var = var.begin(); it_var != var.end(); it_var++) {
        s = filter_by_proc(procName, get_stmt_modifies(*it_var));
        for (it_stmt = s.begin(); it_stmt != s.end(); it_stmt++) {
            if (is_affects(*it_stmt, stmtNo)) {
                res.insert(*it_stmt);
            }
        }
    }
    return res;
}

set<int> PKB::get_affected_by_star(int stmtNo)
{
    if (!is_stmtType(stmtNo, ENT_ASSIGN)) {
        return EMPTY_INTSET;
    }
    queue<int> q;
    set<int> temp, res, processed;
    set<int>::iterator it;
    int n;
    temp = get_affected_by(stmtNo);
    for (it = temp.begin(); it != temp.end(); it++) {
        q.push(*it);
    }
    while (!q.empty()) {
        n = q.front();
        if (processed.find(n) != processed.end()) {
            q.pop();
            continue;
        } else {
            processed.insert(n);
            res.insert(n);
            temp = get_affected_by(n);
            for (it = temp.begin(); it != temp.end(); it++) {
                q.push(*it);
            }
            q.pop();
        }
    }
    return res;
}




// Constant
bool PKB::has_const(int n) const
{
    return this->stmtBank->has_const(n);
}

// Others
bool PKB::is_stmtType(int stmtNo, DesignEnt type){
    return stmtBank->is_stmtType(stmtNo, type);
}

bool PKB::is_valid_stmtNo(int stmtNo)
{
    return stmtBank->is_valid_stmtNo(stmtNo);
}

set<int> PKB::get_all_stmt(){
    int sz = stmtBank->get_directory().size();
    set<int> res;
    for (int i = 1; i <= sz; i++) {
        res.insert(i);
    }
    return res;
}

set<int> PKB::get_all_stmt_by_proc(string procName){
    int start, end;
    start = procTable->get_start(procName);
    end = procTable->get_end(procName);
    if (start == -1 || end == -1) {
        return EMPTY_INTSET;
    } else {
        set<int> res;
        for (int i = start; i <= end; i++) {
            res.insert(i);
        }
        return res;
    }
}

set<int> PKB::filter_by_proc(string procName, set<int> s){
    int start, end;
    start = procTable->get_start(procName);
    end = procTable->get_end(procName);
    if (start == -1 || end == -1) {
        return EMPTY_INTSET;
    } else {
        set<int> res;
        std::set<int>::iterator it, low, high;
        low = s.lower_bound(start);
        high = s.upper_bound(end);
        for (it = low; it != high; it++) {
            res.insert(*it);
        }
        return res;
    }
}

int PKB::filter_by_stmtType(DesignEnt type, int stmtNo){
    if(is_stmtType(stmtNo, type)) {
        return stmtNo;
    } else {
        return -1;
    }
}

set<int> PKB::filter_by_stmtType(DesignEnt type, set<int> s){
    set<int> res;
    set<int>::iterator it;
    map<int, DesignEnt> m = stmtBank->get_directory();
    for (it = s.begin(); it != s.end(); it++) {
        if (m[*it] == type) {
            res.insert(*it);
        }
    }
    return res;
}


void PKB::dfs(CFGNode *node)
{
    if (node == NULL) {
        return;
    }
    int n = node->get_stmtNo();
    if (n == -1){
        dfs(node->get_edge(OUT, 1));
    } else {
        if (visited.find(n) == visited.end()) {
            printf("AT node %d,\n", n);
            visited.insert(n);
            if (node->get_edge(OUT, 2) != NULL){
                dfs(node->get_edge(OUT, 2));
            }

            if(node->get_edge(OUT, 1) != NULL) {
                dfs(node->get_edge(OUT, 1));
            }

        }
    }

}


// Debuugers
Node* PKB::get_progRoot(){
    return progRoot;
}

ProcTable* PKB::get_procTable(){
    return procTable;
}
StmtBank* PKB::get_stmtBank(){
    return stmtBank;
}

VarTable* PKB::get_varTable(){
    return varTable;
}

vector<CFGNode*>* PKB::get_CFG()
{
    return CFG;
}
