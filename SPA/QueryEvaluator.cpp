#include "QueryEvaluator.h"

#include <cassert>

using std::list;
using std::string;

QueryEvaluator::QueryEvaluator(): pqlParser(), results() {}

void QueryEvaluator::evaluate(const string& queryStr,
        list<string>& resultSet)
{
    QueryInfo *qinfo;
    results.reset();
    this->pqlParser.parse(queryStr, true, true);
    qinfo = this->pqlParser.get_queryinfo();
    qinfo->optimize();
    int nrClauses = qinfo->get_nr_clauses();
    RelRef *relRef;
    PatCl *patCl;
    void *retPtr;
    ClauseType clauseType;
    for (int i = 0; i < nrClauses; i++) {
        retPtr = NULL;
        clauseType = qinfo->get_nth_clause(i, &retPtr);
        assert(clauseType != INVALID_CLAUSE);
        switch (clauseType) {
        case SUCHTHAT_CLAUSE:
            relRef = reinterpret_cast<RelRef *>(retPtr);
            break;
        case WITH_CLAUSE:
            // TODO: Implement when pql parser is done
            break;
        case PATTERN_CLAUSE:
            patCl = reinterpret_cast<PatCl *>(retPtr);
            break;
        }
    }
}

void QueryEvaluator::evaluate_relRef(RelRef *relRef)
{
    switch (relRef->relType) {
    case REL_MODIFIES:
        this->evaluate_modifies(relRef);
        break;
    case REL_USES:
        this->evaluate_uses(relRef);
        break;
    case REL_CALLS:
        break;
    case REL_CALLS_STAR:
        break;
    case REL_PARENT:
        break;
    case REL_PARENT_STAR:
        break;
    case REL_FOLLOWS:
        break;
    case REL_FOLLOWS_STAR:
        break;
    case REL_NEXT:
        break;
    case REL_NEXT_STAR:
        break;
    case REL_AFFECTS:
        break;
    case REL_AFFECTS_STAR:
        break;
    }
}

void QueryEvaluator::evaluate_modifies(RelRef *relRef)
{
}

void QueryEvaluator::evaluate_uses(RelRef *relRef)
{
}

void QueryEvaluator::evaluate_patCl(PatCl *patCl)
{
}