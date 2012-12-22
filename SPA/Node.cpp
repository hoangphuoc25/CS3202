#include <iostream>
#include <string>
#include <vector>
#include "Node.h"

Node::Node(string name, NodeType type, int stmtNo)
{
	nodeName = name;
	nodeType = type;
	nodeStmtNo = stmtNo;
    parent = NULL;
    predecessor = NULL;
    successor = NULL;
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

    
    if (predecessor != NULL) {
        printf("Predecessor is: %s\n", predecessor->get_name().c_str());
    }

    if (successor != NULL) {
        printf("Successor is: %s\n", successor->get_name().c_str());
    }

    if (parent != NULL) {
        printf("Parent is: %s\n", parent->get_name().c_str());
    } 

    int len = children.size();
    for (int i = 0; i < len; i++) {
        printf("%d child is: %s\n", i, children[i]->get_name().c_str());
    }

}

void Node::preorder(int n){
    //dump(n);
    dumpR();
    int len = leaves.size();
    for (int i = 0; i < len; i++) {
        leaves[i]->preorder(n+4);
    }
}

void Node::dumpR(){

    printf("Current Node: (%s, %d)\n", nodeName.c_str(), nodeStmtNo);

    if (predecessor != NULL) {
        printf("Predecessor is: (%s, %d)\n", predecessor->get_name().c_str(), predecessor->get_stmtNo());
    }

    if (successor != NULL) {
        printf("Successor is: (%s, %d)\n", successor->get_name().c_str(), successor->get_stmtNo());
    }

    if (parent != NULL) {
        printf("Parent is: (%s, %d)\n", parent->get_name().c_str(), parent->get_stmtNo());
    } 

    int len = children.size();
    for (int i = 0; i < len; i++) {
        printf("%d child is: (%s, %d)\n", i, children[i]->get_name().c_str(), children[i]->get_stmtNo());
    }

    putchar('\n');
}


