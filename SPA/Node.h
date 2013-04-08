#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <set>

using std::vector;
using std::string;
using std::set;

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
    Node* get_root() const;
    const std::vector<Node*>& get_leaves() const;

    // AST methods
    Node* get_parent() const;
    const std::vector<Node*>& get_children() const;
    Node* get_predecessor() const;
    Node* get_successor() const;
    const std::set<std::string>& get_modifies() const;
    const std::set<std::string>& get_uses() const;
    const std::string& get_control_var() const;

    void add_child(Node* n);
    void set_successor(Node* n);
    void add_modifies(string var);
    void add_uses(string var);
    void set_modifies(set<string> s);
    void set_uses(set<string> s);
    void set_control_var(string var);
    void set_updated();

    bool is_updated() const;

    // Helper
    void link_stmt(Node *n1); //helper to link stmt nodes

    // Printer
    void dump(int n) const;
    void dump(int n, FILE *fp) const;
    void preorder(int n) const;
    void preorder(int n, FILE *fp) const;
    void out(int n, string name) const;

    void dump_relationships() const;
    void dump_relationships(FILE *fp) const;
    void preorder_relationship(FILE *fp) const;
    void out_relationship(string name) const;

private:
    // Node Fields
    string nodeName;
    NodeType nodeType;
    int nodeStmtNo;
    bool updated;

    // Physical
    Node *root;
    vector<Node*> leaves;
    void set_root(Node* node);

    // AST relationships
    Node *parent;
    vector<Node*> children;
    Node *predecessor;
    Node *successor;
    set<string> modifies;
    set<string> uses;
    string control_var;

    void set_parent(Node* n);
    void set_predecessor(Node* n);
};

#endif
