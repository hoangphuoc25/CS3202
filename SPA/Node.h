#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

using std::vector;
using std::string;

enum NodeType {
    PROGRAM, PROCEDURE, STMTLST, CALL_STMT, WHILE_STMT, 
    IF_STMT, ASSIGN_STMT, OPERATOR_, VARIABLE_, CONSTANT_
};

class Node {

public:
    Node();
    Node(string name, NodeType type, int stmtNo);

    // Node methods
    const string& get_name() const;
    NodeType get_type() const;
    int get_stmtNo() const;

    void add_leaf(Node *node);
    Node* get_root();
    void link_stmt(Node *n1); //helper to link stmt nodes


private:
    // Node Fields
    string nodeName;
    NodeType nodeType;
    int nodeStmtNo;

    Node *root;
    vector<Node*> leaves;
    void set_root(Node* node);

};

#endif
