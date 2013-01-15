#include "StmtBank.h"

StmtBank::StmtBank(void)
{
}


StmtBank::~StmtBank(void)
{
}

void StmtBank::add_node_entry(int stmtNo, stmtType type, Node* node)
{
    directory[stmtNo] = type;
    switch(type) {
    case CALLTYPE:
        callBank[stmtNo] = node;
        break;
    case WHILETYPE:
        whileBank[stmtNo] = node;
        break;
    case IFTYPE:
        ifBank[stmtNo] = node;
        break;
    case ASSIGNTYPE:
        assignBank[stmtNo] = node;
        break;
    }
}

void StmtBank::add_constant(string n)
{
    constBank.insert(n);
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
    map<int, stmtType>::const_iterator it = this->directory.find(stmtNo);
    if (it == this->directory.end()) {
        return NULL;
    } else {
        switch (it->second) {
        case CALLTYPE:
            return this->get_callNode(stmtNo);
            break;
        case WHILETYPE:
            return this->get_whileNode(stmtNo);
            break;
        case IFTYPE:
            return this->get_ifNode(stmtNo);
            break;
        case ASSIGNTYPE:
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

map<int, stmtType> StmtBank::get_directory()
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

set<string> StmtBank::get_constBank()
{
    return constBank;
}

bool StmtBank::is_stmtType(int stmtNo, stmtType type)
{
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

Node* StmtBank::get_node(int stmtNo)
{
    if (directory.find(stmtNo) != directory.end()) {
        stmtType type = directory[stmtNo];
        switch(type) {
        case CALLTYPE:
            return callBank[stmtNo];
            break;
        case WHILETYPE:
            return whileBank[stmtNo];
            break;
        case IFTYPE:
            return ifBank[stmtNo];
            break;
        case ASSIGNTYPE:
            return assignBank[stmtNo];
            break;
        }
    } else {
        return NULL;
    }
}
