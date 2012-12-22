#include <iostream>
#include <string>
#include <vector>
#include "Node.h"

Node::Node(string name, NodeType type, int stmtNo)
{
	nodeName = name;
	nodeType = type;
	nodeStmtNo = stmtNo;
}

const string& Node::get_name() const
{
	return nodeName;
}

NodeType Node::get_type() const
{
	return nodeType;
}

int Node::get_stmtNo() const
{
    return nodeStmtNo;
}

// Physical methods
void Node::set_root(Node *node){
    root = node;
}

void Node::add_leaf(Node *node){
    leaves.push_back(node);
    node->set_root(this);
}

Node* Node::get_root(){
    return root;
}

// AST methods
Node* Node::get_parent(){
    return parent;
}

vector<Node*> Node::get_children(){
    return children;
}

Node* Node::get_predecessor(){
    return predecessor;
}

Node* Node::get_successor(){
    return successor;
}

void Node::set_parent(Node* n){
    parent = n;
}

void Node::add_child(Node* n){
    children.push_back(n);
    n->set_parent(this);
}

void Node::set_predecessor(Node* n){
    predecessor = n;
}

void Node::set_successor(Node* n){
    successor = n;
    n->set_predecessor(this);
}

// Helper
void Node::link_stmt(Node *n1){
    if (nodeType == STMTLST) {
        add_leaf(n1);
        NodeType t = root->get_type();
        if (t == WHILE_STMT || t == IF_STMT) {
            root->add_child(n1);
        }
    } else {
        root->add_leaf(n1);
        if (parent != NULL) {
            parent->add_child(n1);
        }
        set_successor(n1);
    }
}

// Printer
void Node::dump(int n){
    while (n--) {
        putchar(' ');
    }
    printf("%s\n", nodeName.c_str());
}

void Node::preorder(int n){
    dump(n);
    int len = leaves.size();
    for (int i = 0; i < len; i++) {
        leaves[i]->preorder(n+4);
    }
}
