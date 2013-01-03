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
    updated = false;
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
void Node::set_root(Node *node)
{
    root = node;
}

void Node::add_leaf(Node *node){
    leaves.push_back(node);
    node->set_root(this);
}

Node* Node::get_root()
{
    return root;
}

vector<Node*> Node::get_leaves()
{
    return leaves;
}

// AST methods
Node* Node::get_parent()
{
    return parent;
}

vector<Node*> Node::get_children()
{
    return children;
}

Node* Node::get_predecessor()
{
    return predecessor;
}

Node* Node::get_successor()
{
    return successor;
}

set<string> Node::get_modifies()
{
    return modifies;
}

set<string> Node::get_uses()
{
    return uses;
}

string Node::get_control_var()
{
    return control_var;
}

void Node::set_parent(Node* n)
{
    parent = n;
}

void Node::add_child(Node* n)
{
    children.push_back(n);
    n->set_parent(this);
}

void Node::set_predecessor(Node* n)
{
    predecessor = n;
}

void Node::set_successor(Node* n)
{
    successor = n;
    n->set_predecessor(this);
}

void Node::add_modifies(string var)
{
    modifies.insert(var);
}

void Node::add_uses(string var)
{
    uses.insert(var);
}

void Node::set_control_var(string var)
{
    control_var = var;
}

void Node::set_uses(set<string> s)
{
    uses = s;
}

void Node::set_modifies(set<string> s)
{
    modifies = s;
}

void Node::set_updated()
{
    updated = true;
}

bool Node::is_updated()
{
    return updated;
}


// Helper
void Node::link_stmt(Node *n1)
{
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
void Node::dump(int n)
{
    while (n--) {
        putchar(' ');
    }
    printf("%s\n", nodeName.c_str());
}

void Node::preorder(int n)
{
    dump(n);
    int len = leaves.size();
    for (int i = 0; i < len; i++) {
        leaves[i]->preorder(n+4);
    }
}

void Node::out(int n, string name)
{
    FILE *fp;
    fp = fopen(name.c_str(), "w");
    preorder(n, fp);
    fclose(fp);
}

void Node::dump(int n, FILE *fp)
{
    while (n--) {
        fputc(' ', fp);
    }
    fprintf(fp,"%s\n", nodeName.c_str());
}

void Node::preorder(int n, FILE *fp)
{
    dump(n,fp);
    int len = leaves.size();
    for (int i = 0; i < len; i++) {
        leaves[i]->preorder(n+4, fp);
    }
}

void Node::dump_relationships()
{

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

    set<string>::iterator it;

    for (it = modifies.begin(); it != modifies.end(); it++) {
        printf("Modifies: %s\n", it->c_str());
    }

    for (it = uses.begin(); it != uses.end(); it++) {
        printf("Uses: %s\n", it->c_str());
    }

    putchar('\n');
}

void Node::dump_relationships(FILE *fp)
{

    fprintf(fp, "Current Node: (%s, %d)\n", nodeName.c_str(), nodeStmtNo);

    if (predecessor != NULL) {
        fprintf(fp, "Predecessor is: (%s, %d)\n", predecessor->get_name().c_str(), predecessor->get_stmtNo());
    }

    if (successor != NULL) {
        fprintf(fp, "Successor is: (%s, %d)\n", successor->get_name().c_str(), successor->get_stmtNo());
    }

    if (parent != NULL) {
        fprintf(fp, "Parent is: (%s, %d)\n", parent->get_name().c_str(), parent->get_stmtNo());
    } 

    int len = children.size();
    for (int i = 0; i < len; i++) {
        fprintf(fp, "%d child is: (%s, %d)\n", i, children[i]->get_name().c_str(), children[i]->get_stmtNo());
    }

    set<string>::iterator it;

    for (it = modifies.begin(); it != modifies.end(); it++) {
        fprintf(fp, "Modifies: %s\n", it->c_str());
    }

    for (it = uses.begin(); it != uses.end(); it++) {
        fprintf(fp, "Uses: %s\n", it->c_str());
    }

    fputc('\n', fp);
}

void Node::preorder_relationship(FILE *fp)
{
    dump_relationships(fp);
    int len = leaves.size();
    for (int i = 0; i < len; i++) {
        leaves[i]->preorder_relationship(fp);
    }
}

void Node::out_relationship(string name)
{
    FILE *fp;
    fp = fopen(name.c_str(), "w");
    preorder_relationship(fp);
    fclose(fp);
}
