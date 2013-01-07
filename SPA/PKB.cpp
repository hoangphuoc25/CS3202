#include "PKB.h"

PKB::PKB(){}

PKB::PKB(Node *root, ProcTable *pt, VarTable *vt, StmtBank *sb, vector<CFGNode*> *cfg){
    progRoot = root;
    procTable = pt;
    varTable = vt;
    stmtBank = sb;
    CFG = cfg;
}

// Variables
string PKB::get_control_var(int stmtNo){
    return stmtBank->get_node(stmtNo)->get_control_var();
}

set<string> PKB::get_all_vars(){
    return varTable->get_all_vars();
}

set<string> PKB::get_all_vars_by_proc(string procName){
    set<string> s,res;
    set<string>::iterator it;
    s = procTable->get_modifies(procName);
    for (it = s.begin(); it != s.end(); it++) {
        res.insert(*it);
    }
    s = procTable->get_uses(procName);
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
    set<string> s = stmtBank->get_node(stmtNo)->get_modifies();
    return (s.find(varName) != s.end());
}

set<string> PKB::get_proc_modifies(string var){
    return varTable->get_modified_by_proc(var);
}

set<int> PKB::get_stmt_modifies(string var){
    return varTable->get_modified_by(var);
}

set<string> PKB::get_var_proc_modifies(string procName){
    return procTable->get_modifies(procName);
}

set<string> PKB::get_var_stmt_modifies(int stmtNo){
    return stmtBank->get_node(stmtNo)->get_modifies();
}

// Uses
bool PKB::is_uses(string procName, string varName){
    set<string> s = procTable->get_uses(procName);
    return (s.find(varName) != s.end());
}

bool PKB::is_uses(int stmtNo, string varName){
    set<string> s = stmtBank->get_node(stmtNo)->get_uses();
    return (s.find(varName) != s.end());
}

set<string> PKB::get_proc_uses(string var){
    return varTable->get_used_by_proc(var);
}

set<int> PKB::get_stmt_uses(string var){
    return varTable->get_used_by(var);
}

set<string> PKB::get_var_proc_uses(string procName){
    return procTable->get_uses(procName);
}

set<string> PKB::get_var_stmt_uses(int stmtNo){
    return stmtBank->get_node(stmtNo)->get_uses();
} 

// Parent
bool PKB::is_parent(int stmt1, int stmt2){
    return (stmtBank->get_node(stmt2)->get_parent()->get_stmtNo() == stmt1);
}

bool PKB::is_parent_star(int stmt1, int stmt2){
    Node *n = stmtBank->get_node(stmt2)->get_parent();
    while (n != NULL) {
        if (n->get_stmtNo() == stmt1) {
            return true;
        } else {
            n = n->get_parent();
        }
    }
    return false;
}

int PKB::get_parent(int stmtNo){
    Node *n = stmtBank->get_node(stmtNo)->get_parent();
    if (n != NULL) {
        return n->get_stmtNo();
    } else {
        return -1;
    }
}

set<int> PKB::get_parent_star(int stmtNo){
    set<int> res;
    Node *n = stmtBank->get_node(stmtNo)->get_parent();
    while (n != NULL) {
        res.insert(n->get_stmtNo());
        n = n->get_parent();
    }
    return res;
}

set<int> PKB::get_children(int stmtNo){
    set<int> s;
    vector<Node*> v = stmtBank->get_node(stmtNo)->get_children(); 
    int sz = v.size();
    for(int i = 0; i< sz; i++) {
        s.insert(v[i]->get_stmtNo());
    }
    return s;
}

set<int> PKB::get_children_star(int stmtNo){
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
}

// Follows
bool PKB::is_follows(int stmt1, int stmt2){
    return (stmtBank->get_node(stmt1)->get_successor()->get_stmtNo() == stmt2);
}

bool PKB::is_follows_star(int stmt1, int stmt2){
    Node *n = stmtBank->get_node(stmt1)->get_successor();
    while (n != NULL) {
        if (n->get_stmtNo() == stmt2) {
            return true;
        } else {
            n = n->get_successor();
        }
    }
    return false;
}

int PKB::get_successor(int stmtNo){
    Node *n = stmtBank->get_node(stmtNo)->get_successor();
    if (n != NULL) {
        return n->get_stmtNo();
    } else {
        return -1;
    }
}

set<int> PKB::get_successor_star(int stmtNo){
    set<int> res;
    Node *n = stmtBank->get_node(stmtNo)->get_successor();
    while (n != NULL) {
        res.insert(n->get_stmtNo());
        n = n->get_successor();
    }
    return res;
}

int PKB::get_predecessor(int stmtNo){
    Node *n = stmtBank->get_node(stmtNo)->get_predecessor();
    if (n != NULL) {
        return n->get_stmtNo();
    } else {
        return -1;
    }
}

set<int> PKB::get_predecessor_star(int stmtNo){
    set<int> res;
    Node *n = stmtBank->get_node(stmtNo)->get_predecessor();
    while (n != NULL) {
        res.insert(n->get_stmtNo());
        n = n->get_predecessor();
    }
    return res;
}

// Next
bool PKB::is_next(int stmt1, int stmt2)
{
    set<int> s =  CFG->at(stmt1)->get_after();
    return (s.find(stmt2) != s.end());
}

bool PKB::is_next_star(int stmt1, int stmt2)
{
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
}

set<int> PKB::get_before(int stmtNo)
{
    return CFG->at(stmtNo)->get_before();
}

set<int> PKB::get_before_star(int stmtNo) {
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
}

set<int> PKB::get_after(int stmtNo)
{
    return CFG->at(stmtNo)->get_after();
}

set<int> PKB::get_after_star(int stmtNo) {
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
}

// Affects
bool PKB::is_affects(int stmt1, int stmt2)
{
    set<int> visited; 
    set<string> temp;
    stack<CFGNode*> s;
    int n;
    string var = *get_var_stmt_modifies(stmt1).begin();

    // Initial checks
    if (!is_stmtType(stmt1, ASSIGNTYPE) || !is_stmtType(stmt2, ASSIGNTYPE)) {
        return false;
    }
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
        // If not visited
        if (visited.find(n) == visited.end()) {
            visited.insert(n);
            // Reached stmt2 -> done
            if (n == stmt2) {
                return true;
            }
            // Check stmt only when it is assign stmt
            if (is_stmtType(n, ASSIGNTYPE)) {
                temp = get_var_stmt_modifies(n);
                if (temp.find(var) != temp.end()) {
                    return false;
                }
            }
            s.pop();
            s.push(curr->get_edge(OUT, 1));
            s.push(curr->get_edge(OUT, 2));
        }
        s.pop();
    }
    return false;
}

bool PKB::is_affects_star(int stmt1, int stmt2)
{
    if (!is_stmtType(stmt1, ASSIGNTYPE) || !is_stmtType(stmt2, ASSIGNTYPE)) {
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
    if (!is_stmtType(stmtNo, ASSIGNTYPE)) {
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
        // If not visited
        if (visited.find(n) == visited.end()) {
            visited.insert(n);
            // Check stmt only when it is assign stmt
            if (is_stmtType(n, ASSIGNTYPE)) {
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
        s.pop();
    }
    return res;
}

set<int> PKB::get_affects_star(int stmtNo)
{
    if (!is_stmtType(stmtNo, ASSIGNTYPE)) {
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
    if (!is_stmtType(stmtNo, ASSIGNTYPE)) {
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
    if (!is_stmtType(stmtNo, ASSIGNTYPE)) {
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
set<string> PKB::get_all_const(){
    return stmtBank->get_constBank();
}

bool PKB::is_const_exist(string n){
    set<string> s = stmtBank->get_constBank();
    return (s.find(n) != s.end());
}


// Others
bool PKB::is_stmtType(int stmtNo, stmtType type){
    map<int, stmtType> m = stmtBank->get_directory();
    if (m.find(stmtNo) != m.end()) {
        return (stmtBank->get_directory()[stmtNo] == type);
    } else {
        return false;
    }
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

int PKB::filter_by_stmtType(stmtType type, int stmtNo){
    if(is_stmtType(stmtNo, type)) {
        return stmtNo;
    } else {
        return -1;
    }
}

set<int> PKB::filter_by_stmtType(stmtType type, set<int> s){
    set<int> res;
    set<int>::iterator it;
    map<int, stmtType> m = stmtBank->get_directory();
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
