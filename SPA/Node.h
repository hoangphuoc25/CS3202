#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

using std::vector;
using std::string;

enum NodeType {
    PROGRAM, PROCEDURE, STMTLST, CALL_STMT, WHILE_STMT, 
    IF_STMT, ASSIGN_STMT, OPERATOR_, VARIABLE_, CONSTANT_, BRACKETS_
};

class Node {

public:
    Node();
    Node(string name, NodeType type, int stmtNo);

    // Only can set relationships downwards

    // Node methods
    const string& get_name() const;
    NodeType get_type() const;
    int get_stmtNo() const;

    // Physical methods
    void add_leaf(Node *node);
    Node* get_root();

    // AST methods
    Node* get_parent();
    vector<Node*> get_children();
    Node* get_predecessor();
    Node* get_successor();

    void add_child(Node* n);
    void set_successor(Node* n);
    void add_modifies(string var);
    void add_uses(string var);

    // Helper
    void link_stmt(Node *n1); //helper to link stmt nodes

    // Printer
    void dump(int n);
    void preorder(int n);
    void dumpR();

private:
    // Node Fields
    string nodeName;
    NodeType nodeType;
    int nodeStmtNo;

    // Physical
    Node *root;
    vector<Node*> leaves;
    void set_root(Node* node);

    // AST relationships
    Node *parent;
    vector<Node*> children;
    Node *predecessor;
    Node *successor;
    vector<string> modifies;
    vector<string> uses;

    void set_parent(Node* n);
    void set_predecessor(Node* n);



};

#endif
