#ifndef T11_QUERY_EVALUATOR_H
#define T11_QUERY_EVALUATOR_H

#include <list>
#include <string>
#include "PKB.h"
#include "PQLParser.h"
#include "ResultsGraph.h"

class QueryEvaluator {
public:
    QueryEvaluator();
    void parseSimple(const std::string& simple);
    void evaluate(const std::string& queryStr,
            std::list<std::string>& resultSet);
private:
    void evaluate_relRef(RelRef *relRef);
    void evaluate_patCl(PatCl *patCl);

    void evaluate_modifies(RelRef *relRef);
    void evaluate_uses(RelRef *relRef);

    PQLParser pqlParser;
    PKB *pkb;
    ResultsGraph results;
};

#endif