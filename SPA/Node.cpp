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

void Node::link_stmt(Node *n1){
    if (nodeType == STMTLST) {
        add_leaf(n1);
    } else {
        root->add_leaf(n1);
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
