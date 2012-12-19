#ifndef T11_PQLAST_H
#define T11_PQLAST_H

#include <vector>

// Interface
class PQLAst {
public:
    virtual void dump() = 0;
private:
};

class PQLAstList: public PQLAst {
public:
    virtual void append(PQLAst *n) = 0;
private:
};

class QueryNode: public PQLAst {
public:
    QueryNode();
private:
};

#endif