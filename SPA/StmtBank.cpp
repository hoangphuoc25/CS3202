#include <cassert>
#include "StmtBank.h"
#include "SPAUtils.h"

const string StmtBank::EMPTY_NAME = "";

StmtBank::StmtBank(void)
{
}


StmtBank::~StmtBank(void)
{
}

void StmtBank::add_node_entry(int stmtNo, DesignEnt type, Node* node)
{
    directory[stmtNo] = type;
    switch(type) {
    case ENT_CALL:
        callBank[stmtNo] = node;
        break;
    case ENT_WHILE:
        whileBank[stmtNo] = node;
        break;
    case ENT_IF:
        ifBank[stmtNo] = node;
        break;
    case ENT_ASSIGN:
        assignBank[stmtNo] = node;
        break;
    }
}

bool StmtBank::add_constant(const std::string& n, char **errorMsg)
{
    int value = 0;
    bool ret = string_to_uint(n, &value, errorMsg);
    if (ret) {
        this->constBank.insert(value);
    }
    return ret;
}

void StmtBank::add_stmtLst(int stmtNo)
{
    this->stmtLstSet.insert(stmtNo);
}

Node* StmtBank::get_assignNode(int stmtNo) const
{
    map<int, Node*>::const_iterator it = this->assignBank.find(stmtNo);
    if (it == this->assignBank.end()) {
        return NULL;
    } else {
        return it->second;
    }
}

Node *StmtBank::get_ifNode(int stmtNo) const
{
    map<int, Node*>::const_iterator it = this->ifBank.find(stmtNo);
    if (it == this->ifBank.end()) {
        return NULL;
    } else {
        return it->second;
    }
}

Node *StmtBank::get_whileNode(int stmtNo) const
{
    map<int, Node*>::const_iterator it = this->whileBank.find(stmtNo);
    if (it == this->whileBank.end()) {
        return NULL;
    } else {
        return it->second;
    }
}

Node *StmtBank::get_callNode(int stmtNo) const
{
    map<int, Node*>::const_iterator it = this->callBank.find(stmtNo);
    if (it == this->callBank.end()) {
        return NULL;
    } else {
        return it->second;
    }
}

Node *StmtBank::get_stmtNode(int stmtNo) const
{
    map<int, DesignEnt>::const_iterator it = this->directory.find(stmtNo);
    if (it == this->directory.end()) {
        return NULL;
    } else {
        switch (it->second) {
        case ENT_CALL:
            return this->get_callNode(stmtNo);
            break;
        case ENT_WHILE:
            return this->get_whileNode(stmtNo);
            break;
        case ENT_IF:
            return this->get_ifNode(stmtNo);
            break;
        case ENT_ASSIGN:
            return this->get_assignNode(stmtNo);
            break;
        }
    }
}

set<int> StmtBank::get_all_assign() const
{
    // TODO: Improve efficiency
    set<int> ret;
    for (map<int, Node*>::const_iterator it = assignBank.begin();
            it != assignBank.end(); it++) {
        ret.insert(it->first);
    }
    return ret;
}

set<int> StmtBank::get_all_if() const
{
    // TODO: Improve efficiency
    set<int>ret;
    for (map<int, Node*>::const_iterator it = this->ifBank.begin();
            it != this->ifBank.end(); it++) {
        ret.insert(it->first);
    }
    return ret;
}

set<int> StmtBank::get_all_while() const
{
    // TODO: Improve efficiency
    set<int> ret;
    for (map<int, Node*>::const_iterator it = this->whileBank.begin();
            it != this->whileBank.end(); it++) {
        ret.insert(it->first);
    }
    return ret;
}

set<int> StmtBank::get_all_call() const
{
    // TODO: Improve efficiency
    set<int> ret;
    for (map<int, Node*>::const_iterator it = this->callBank.begin();
            it != this->callBank.end(); it++) {
        ret.insert(it->first);
    }
    return ret;
}

const set<int>& StmtBank::get_all_const() const
{
    return this->constBank;
}

set<int> StmtBank::get_all_stmt() const
{
    // TODO: Improve efficiency
    set<int> ret;
    for (map<int, DesignEnt>::const_iterator it = this->directory.begin();
                it != this->directory.end(); it++) {
        ret.insert(it->first);
    }
    return ret;
}

const set<int>& StmtBank::get_all_stmtLst() const
{
    return this->stmtLstSet;
}

 const set<string>& StmtBank::get_vars_used_by_stmt(DesignEnt entType,
        int stmtNo) const
 {
    Node *n = this->get_node(stmtNo);
    if (n != NULL) {
        bool returnUses = false;
        NodeType nodeType = n->get_type();
        if (entType == ENT_STMT || entType == ENT_PROGLINE) {
            returnUses = true;
        } else {
            switch (n->get_type()) {
            case CALL_STMT:
                returnUses = (entType == ENT_CALL);
                break;
            case WHILE_STMT:
                returnUses = (entType == ENT_WHILE);
                break;
            case IF_STMT:
                returnUses = (entType == ENT_IF);
                break;
            case ASSIGN_STMT:
                returnUses = (entType == ENT_ASSIGN);
                break;
            }
        }
        if (returnUses) {
            return n->get_uses();
        }
    }
    return EMPTY_STRINGSET;
 }

bool StmtBank::has_const(int n) const
{
    return this->constBank.find(n) != this->constBank.end();
}

string StmtBank::get_call_procName(int callStmt) const
{
    map<int, Node *>::const_iterator it = this->callBank.find(callStmt);
    if (it == this->callBank.end()) {
        return EMPTY_NAME;
    } else {
        Node *n = it->second;
        return n->get_name();
    }
}

map<int, DesignEnt> StmtBank::get_directory()
{
    return directory;
}

map<int, Node*> StmtBank::get_callBank()
{
    return callBank;
}

map<int, Node*> StmtBank::get_assignBank()
{
    return assignBank;
}

map<int, Node*> StmtBank::get_whileBank()
{
    return whileBank;
}

map<int, Node*> StmtBank::get_ifBank()
{
    return ifBank;
}

bool StmtBank::is_stmtType(int stmtNo, DesignEnt type)
{
    if (type == ENT_STMT || type == ENT_PROGLINE) {
        return true;
    }
    if (directory.find(stmtNo) != directory.end()) {
        return (directory[stmtNo] == type);
    } else {
        return false;
    }
}

bool StmtBank::is_valid_stmtNo(int stmtNo)
{
    return (directory.find(stmtNo) != directory.end());
}

Node* StmtBank::get_node(int stmtNo) const
{
    map<int, DesignEnt>::const_iterator it =
            this->directory.find(stmtNo);
    map<int, Node *>::const_iterator nodeIt;
    if (it != this->directory.end()) {
        DesignEnt type = it->second;
        switch(type) {
        case ENT_CALL:
            nodeIt = this->callBank.find(stmtNo);
            assert(nodeIt != this->callBank.end());
            return nodeIt->second;
            break;
        case ENT_WHILE:
            nodeIt = this->whileBank.find(stmtNo);
            assert(nodeIt != this->whileBank.end());
            return nodeIt->second;
            break;
        case ENT_IF:
            nodeIt = this->ifBank.find(stmtNo);
            assert(nodeIt != this->ifBank.end());
            return nodeIt->second;
            break;
        case ENT_ASSIGN:
            nodeIt = this->assignBank.find(stmtNo);
            assert(nodeIt != this->assignBank.end());
            return nodeIt->second;
            break;
        }
    }
    return NULL;
}
