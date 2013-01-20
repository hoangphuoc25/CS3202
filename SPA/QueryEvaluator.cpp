#include "QueryEvaluator.h"
#include "Parser.h"

#include <cstring>
#include <cassert>

using std::list;
using std::string;
using std::map;

//////////////////////////////////////////////////////////////////////
// EvalSynArgDesc
//////////////////////////////////////////////////////////////////////

EvalSynArgDesc::EvalSynArgDesc()
    : relRefType(REL_INVALID), synInGraph(SYN_ARGS_INVALID),
      argOneSynType(ENT_INVALID), argTwoSynType(ENT_INVALID),
      argOneOtherType(RELARG_INVALID), argTwoOtherType(RELARG_INVALID)
      {}

EvalSynArgDesc::EvalSynArgDesc(enum RelRefType rtype, enum SynInGraph sig,
        enum DesignEnt a1SType, enum DesignEnt a2SType,
        enum RelRefArgType a1OtherType, enum RelRefArgType a2OtherType)
    : relRefType(rtype), synInGraph(sig), argOneSynType(a1SType),
      argTwoSynType(a2SType), argOneOtherType(a1OtherType),
      argTwoOtherType(a2OtherType) {}

bool EvalSynArgDescCmp::operator()(const EvalSynArgDesc &a,
        const EvalSynArgDesc &b) const
{
    if (a.relRefType != b.relRefType) {
        return a.relRefType < b.relRefType;
    } else if (a.synInGraph != b.synInGraph) {
        return a.synInGraph < b.synInGraph;
    } else if (a.argOneSynType != b.argOneSynType) {
        return a.argOneSynType < b.argOneSynType;
    } else if (a.argTwoSynType != b.argTwoSynType) {
        return a.argOneSynType < b.argOneSynType;
    } else if (a.argOneOtherType != b.argOneOtherType) {
        return a.argOneOtherType < b.argOneOtherType;
    } else {
        return a.argTwoOtherType < b.argTwoOtherType;
    }
}

//////////////////////////////////////////////////////////////////////
// EvalPKBDispatch
//////////////////////////////////////////////////////////////////////

EvalPKBDispatch::EvalPKBDispatch()
    : get_string_set_argTwo_from_string_argOne(NULL),
      get_string_set_argTwo_from_int_argOne(NULL),
      get_int_set_argTwo_from_string_argOne(NULL),
      get_int_set_argTwo_from_int_argOne(NULL),
      get_string_set_argOne_from_string_argTwo(NULL),
      get_string_set_argOne_from_int_argTwo(NULL),
      get_int_set_argOne_from_string_argTwo(NULL),
      get_int_set_argOne_from_int_argTwo(NULL),
      get_all_string_argOne(NULL),
      get_all_int_argOne(NULL),
      get_all_string_argTwo(NULL),
      get_all_int_argTwo(NULL),
      f_string_argOne_string_argTwo(NULL),
      f_string_argOne_int_argTwo(NULL),
      f_int_argOne_string_argTwo(NULL),
      f_int_argOne_int_argTwo(NULL),
      relRef_eval(NULL) {}

void EvalPKBDispatch::reset()
{
    this->get_string_set_argTwo_from_string_argOne = NULL;
    this->get_string_set_argTwo_from_int_argOne = NULL;
    this->get_int_set_argTwo_from_string_argOne = NULL;
    this->get_int_set_argTwo_from_int_argOne = NULL;
    this->get_string_set_argOne_from_string_argTwo = NULL;
    this->get_string_set_argOne_from_int_argTwo = NULL;
    this->get_int_set_argOne_from_string_argTwo = NULL;
    this->get_int_set_argOne_from_int_argTwo = NULL;
    this->get_all_string_argOne = NULL;
    this->get_all_int_argOne = NULL;
    this->get_all_string_argTwo = NULL;
    this->get_all_int_argTwo = NULL;
    this->f_string_argOne_string_argTwo = NULL;
    this->f_string_argOne_int_argTwo = NULL;
    this->f_int_argOne_string_argTwo = NULL;
    this->f_int_argOne_int_argTwo = NULL;
    this->relRef_eval = NULL;
}
//////////////////////////////////////////////////////////////////////
// Query Evaluator
//////////////////////////////////////////////////////////////////////

QueryEvaluator::QueryEvaluator():
        pqlParser(), pkb(NULL), results(), resultsProjector()
{
    this->setup_modifies();
    this->setup_uses();
    this->setup_calls();
    this->setup_callsStar();
    this->setup_parent();
    this->setup_parentStar();
    this->setup_follows();
    this->setup_followsStar();
    this->setup_next();
    this->setup_nextStar();
    this->setup_affects();
    this->setup_affectsStar();
}

void QueryEvaluator::setup_modifies()
{
    struct EvalPKBDispatch tmpDispatch;
    struct EvalSynArgDesc evalSynArgDesc;

    // Modifies(assign,var), 00
    evalSynArgDesc = EvalSynArgDesc(REL_MODIFIES, SYN_SYN_00, ENT_ASSIGN,
        ENT_VAR, RELARG_INVALID, RELARG_INVALID);
    tmpDispatch.reset();
    tmpDispatch.get_all_int_argOne =
        &PKB::get_all_assign;
    tmpDispatch.get_all_string_argTwo =
        &PKB::get_all_vars;
    tmpDispatch.get_string_set_argTwo_from_int_argOne =
        &PKB::modifies_X_Y_get_string_Y_from_int_X;
    tmpDispatch.get_int_set_argOne_from_string_argTwo =
        &PKB::modifies_X_Y_get_int_X_from_string_Y;
    tmpDispatch.relRef_eval =
        &QueryEvaluator::ev_rr_ss_int_string_00_from_argOne;
    this->dispatchTable[evalSynArgDesc] = tmpDispatch;

    // Modifies(procedure,var), 00
    evalSynArgDesc = EvalSynArgDesc(REL_MODIFIES, SYN_SYN_00, ENT_PROC,
            ENT_VAR, RELARG_INVALID, RELARG_INVALID);
    tmpDispatch.reset();
    tmpDispatch.get_all_string_argOne = &PKB::get_all_procs;
    tmpDispatch.get_all_string_argTwo = &PKB::get_all_vars;
    tmpDispatch.get_string_set_argOne_from_string_argTwo =
            &PKB::modifies_X_Y_get_string_X_from_string_Y;
    tmpDispatch.get_string_set_argTwo_from_string_argOne =
            &PKB::modifies_X_Y_get_string_Y_from_string_X;
    tmpDispatch.relRef_eval =
            &QueryEvaluator::ev_rr_ss_string_string_00_from_argOne;
    this->dispatchTable[evalSynArgDesc] = tmpDispatch;

    // Modifies(call,var), 00
    evalSynArgDesc = EvalSynArgDesc(REL_MODIFIES, SYN_SYN_00, ENT_CALL,
            ENT_VAR, RELARG_INVALID, RELARG_INVALID);
    tmpDispatch.reset();
    tmpDispatch.get_all_int_argOne = &PKB::get_all_call;
    tmpDispatch.get_all_string_argTwo = &PKB::get_all_vars;
    tmpDispatch.get_int_set_argOne_from_string_argTwo =
            &PKB::modifies_X_Y_get_int_X_from_string_Y;
    tmpDispatch.get_string_set_argTwo_from_int_argOne =
            &PKB::modifies_X_Y_get_string_Y_from_int_X;
    tmpDispatch.relRef_eval =
            &QueryEvaluator::ev_rr_ss_int_string_00_from_argOne;
    this->dispatchTable[evalSynArgDesc] = tmpDispatch;

    // Modifies(while,var), 00
    evalSynArgDesc = EvalSynArgDesc(REL_MODIFIES, SYN_SYN_00, ENT_WHILE,
            ENT_VAR, RELARG_INVALID, RELARG_INVALID);
    tmpDispatch.reset();
    tmpDispatch.get_all_int_argOne = &PKB::get_all_while;
    tmpDispatch.get_all_string_argTwo = &PKB::get_all_vars;
    tmpDispatch.get_int_set_argOne_from_string_argTwo =
            &PKB::modifies_X_Y_get_int_X_from_string_Y;
    tmpDispatch.get_string_set_argTwo_from_int_argOne =
            &PKB::modifies_X_Y_get_string_Y_from_int_X;
    tmpDispatch.relRef_eval =
            &QueryEvaluator::ev_rr_ss_int_string_00_from_argOne;
    this->dispatchTable[evalSynArgDesc] = tmpDispatch;

    // Modifies(if,var), 00
    evalSynArgDesc = EvalSynArgDesc(REL_MODIFIES, SYN_SYN_00, ENT_IF,
            ENT_VAR, RELARG_INVALID, RELARG_INVALID);
    tmpDispatch.reset();
    tmpDispatch.get_all_int_argOne = &PKB::get_all_if;
    tmpDispatch.get_all_string_argTwo = &PKB::get_all_vars;
    tmpDispatch.get_int_set_argOne_from_string_argTwo =
            &PKB::modifies_X_Y_get_int_X_from_string_Y;
    tmpDispatch.get_string_set_argTwo_from_int_argOne =
            &PKB::modifies_X_Y_get_string_Y_from_int_X;
    tmpDispatch.relRef_eval =
            &QueryEvaluator::ev_rr_ss_int_string_00_from_argOne;
    this->dispatchTable[evalSynArgDesc] = tmpDispatch;

    // Modifies(stmt,var), 00
    evalSynArgDesc = EvalSynArgDesc(REL_MODIFIES, SYN_SYN_00, ENT_STMT,
            ENT_VAR, RELARG_INVALID, RELARG_INVALID);
    tmpDispatch.reset();
    tmpDispatch.get_all_int_argOne = &PKB::get_all_stmt;
    tmpDispatch.get_all_string_argTwo = &PKB::get_all_vars;
    tmpDispatch.get_int_set_argOne_from_string_argTwo =
            &PKB::modifies_X_Y_get_int_X_from_string_Y;
    tmpDispatch.get_string_set_argTwo_from_int_argOne =
            &PKB::modifies_X_Y_get_string_Y_from_int_X;
    tmpDispatch.relRef_eval =
            &QueryEvaluator::ev_rr_ss_int_string_00_from_argOne;
    this->dispatchTable[evalSynArgDesc] = tmpDispatch;

    // Modifies(prog_line,var), 00
    evalSynArgDesc = EvalSynArgDesc(REL_MODIFIES, SYN_SYN_00, ENT_PROGLINE,
            ENT_VAR, RELARG_INVALID, RELARG_INVALID);
    tmpDispatch.reset();
    tmpDispatch.get_all_int_argOne = &PKB::get_all_progline;
    tmpDispatch.get_all_string_argTwo = &PKB::get_all_vars;
    tmpDispatch.get_int_set_argOne_from_string_argTwo =
            &PKB::modifies_X_Y_get_int_X_from_string_Y;
    tmpDispatch.get_string_set_argTwo_from_int_argOne =
            &PKB::modifies_X_Y_get_string_Y_from_int_X;
    tmpDispatch.relRef_eval =
            &QueryEvaluator::ev_rr_ss_int_string_00_from_argOne;
    this->dispatchTable[evalSynArgDesc] = tmpDispatch;
}

void QueryEvaluator::setup_uses()
{
}

void QueryEvaluator::setup_calls()
{
}

void QueryEvaluator::setup_callsStar()
{
}

void QueryEvaluator::setup_parent()
{
}

void QueryEvaluator::setup_parentStar()
{
}

void QueryEvaluator::setup_follows()
{
}

void QueryEvaluator::setup_followsStar()
{
}

void QueryEvaluator::setup_next()
{
}

void QueryEvaluator::setup_nextStar()
{
}

void QueryEvaluator::setup_affects()
{
}

void QueryEvaluator::setup_affectsStar()
{
}

void QueryEvaluator::parseSimple(const string& simple)
{
    Parser parser(simple, FROMSTRING);
    parser.init();
    this->pkb = parser.get_pkb();
}

bool QueryEvaluator::relRef_arg_use_string(DesignEnt entType) const
{
    return (entType == ENT_PROC || entType == ENT_VAR);
}

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
    for (int i = 0; i < nrClauses && this->results.is_alive(); i++) {
        retPtr = NULL;
        clauseType = qinfo->get_nth_clause(i, &retPtr);
        assert(clauseType != INVALID_CLAUSE);
        switch (clauseType) {
        case SUCHTHAT_CLAUSE:
            relRef = reinterpret_cast<RelRef *>(retPtr);
            this->evaluate_relRef(relRef);
            break;
        case WITH_CLAUSE:
            // TODO: Implement when pql parser is done
            break;
        case PATTERN_CLAUSE:
            patCl = reinterpret_cast<PatCl *>(retPtr);
            break;
        }
    }
    this->resultsProjector.get_results(this->results, qinfo, pkb, resultSet);
}

void QueryEvaluator::evaluate_relRef(RelRef *relRef)
{
    if (relRef->argOneType == RELARG_SYN &&
            relRef->argTwoType == RELARG_SYN) {
        this->ev_relRef_syn_syn(relRef);
    } else if (relRef->argOneType == RELARG_SYN) {
        this->ev_relRef_syn_X(relRef);
    } else if (relRef->argTwoType == RELARG_SYN) {
        this->ev_relRef_X_syn(relRef);
    } else {
        this->ev_relRef_X_X(relRef);
    }
}

void QueryEvaluator::ev_relRef_syn_syn(RelRef *relRef)
{
    enum SynInGraph synInGraph = SYN_ARGS_INVALID;
    EvalSynArgDesc evalSynArgDesc;
    if (this->results.has_syn(relRef->argOneString) &&
            this->results.has_syn(relRef->argTwoString)) {
        synInGraph = SYN_SYN_11;
    } else if (this->results.has_syn(relRef->argOneString)) {
        synInGraph = SYN_SYN_10;
    } else if (this->results.has_syn(relRef->argTwoString)) {
        synInGraph = SYN_SYN_01;
    } else {
        synInGraph = SYN_SYN_00;
    }
    evalSynArgDesc.synInGraph = synInGraph;
    evalSynArgDesc.relRefType = relRef->relType;
    evalSynArgDesc.argOneSynType = relRef->argOneSyn;
    evalSynArgDesc.argTwoSynType = relRef->argTwoSyn;
    map<EvalSynArgDesc, EvalPKBDispatch, EvalSynArgDescCmp>::const_iterator
        it = this->dispatchTable.find(evalSynArgDesc);
    assert(it != this->dispatchTable.end());
    assert(it->second.relRef_eval != NULL);
    // evaluate relRef
    (this->*(it->second.relRef_eval)) (relRef, it->second);
    // prune
    this->results.prune(relRef->argOneString, relRef->argTwoString);
}

void QueryEvaluator::ev_rr_ss_string_string_00_from_argOne(RelRef *relRef,
            const EvalPKBDispatch& disp)
{
    assert(disp.get_all_string_argOne != NULL);
    assert(disp.get_string_set_argTwo_from_string_argOne != NULL);
    set<string> argOneSet = (this->pkb->*(disp.get_all_string_argOne))();
    for (set<string>::const_iterator it = argOneSet.begin();
            it != argOneSet.end(); it++) {
        set<string> argTwoSet =
                (this->pkb->*(disp.get_string_set_argTwo_from_string_argOne))
                    (relRef->argOneSyn, relRef->argTwoSyn, *it);
        for (set<string>::const_iterator kt = argTwoSet.begin();
                kt != argTwoSet.end(); kt++) {
            this->results.add_edge(relRef->argOneSyn, relRef->argOneString,
                    *it, relRef->argTwoSyn, relRef->argTwoString, *kt);
        }
    }
}

void QueryEvaluator::ev_rr_ss_string_string_00_from_argTwo(RelRef *relRef,
        const EvalPKBDispatch& disp)
{
}

void QueryEvaluator::ev_rr_ss_string_string_01(RelRef *relRef,
        const EvalPKBDispatch& disp)
{
}

void QueryEvaluator::ev_rr_ss_string_string_10(RelRef *relRef,
        const EvalPKBDispatch& disp)
{
}

void QueryEvaluator::ev_rr_ss_string_string_11(RelRef *relRef,
        const EvalPKBDispatch& disp)
{
}

void QueryEvaluator::ev_rr_ss_string_int_00_from_argOne(RelRef *relRef,
        const EvalPKBDispatch& disp)
{
}

void QueryEvaluator::ev_rr_ss_string_int_00_from_argTwo(RelRef *relRef,
        const EvalPKBDispatch& disp)
{
}

void QueryEvaluator::ev_rr_ss_string_int_01(RelRef *relRef,
        const EvalPKBDispatch& disp)
{
}

void QueryEvaluator::ev_rr_ss_string_int_10(RelRef *relRef,
        const EvalPKBDispatch& disp)
{
}

void QueryEvaluator::ev_rr_ss_string_int_11(RelRef *relRef,
        const EvalPKBDispatch& disp)
{
}

void QueryEvaluator::ev_rr_ss_int_string_00_from_argOne(RelRef *relRef,
        const EvalPKBDispatch& disp)
{
    assert(disp.get_all_int_argOne != NULL);
    assert(disp.get_string_set_argTwo_from_int_argOne != NULL);
    set<int> argOneSet = (this->pkb->*(disp.get_all_int_argOne))();
    for (set<int>::const_iterator it = argOneSet.begin();
            it != argOneSet.end(); it++) {
        set<string> argTwoSet =
                (this->pkb->*(disp.get_string_set_argTwo_from_int_argOne))
                    (relRef->argOneSyn, relRef->argTwoSyn, *it);
        for (set<string>::const_iterator kt = argTwoSet.begin();
                kt != argTwoSet.end(); kt++) {
            this->results.add_edge(relRef->argOneSyn, relRef->argOneString,
                    *it, relRef->argTwoSyn, relRef->argTwoString, *kt);
        }
    }
}

void QueryEvaluator::ev_rr_ss_int_string_00_from_argTwo(RelRef *relRef,
        const EvalPKBDispatch& disp)
{
}

void QueryEvaluator::ev_rr_ss_int_string_01(RelRef *relRef,
        const EvalPKBDispatch& disp)
{
}

void QueryEvaluator::ev_rr_ss_int_string_10(RelRef *relRef,
        const EvalPKBDispatch& disp)
{
}

void QueryEvaluator::ev_rr_ss_int_string_11(RelRef *relRef,
        const EvalPKBDispatch& disp)
{
}

void QueryEvaluator::ev_rr_ss_int_int_00_from_argOne(RelRef *relRef,
        const EvalPKBDispatch& disp)
{
}

void QueryEvaluator::ev_rr_ss_int_int_00_from_argTwo(RelRef *relRef,
        const EvalPKBDispatch& disp)
{
}

void QueryEvaluator::ev_rr_ss_int_int_01(RelRef *relRef,
        const EvalPKBDispatch& disp)
{
}

void QueryEvaluator::ev_rr_ss_int_int_10(RelRef *relRef,
        const EvalPKBDispatch& disp)
{
}

void QueryEvaluator::ev_rr_ss_int_int_11(RelRef *relRef,
        const EvalPKBDispatch& disp)
{
}

void QueryEvaluator::ev_relRef_syn_X(RelRef *relRef)
{
}

void QueryEvaluator::ev_relRef_X_syn(RelRef *relRef)
{
}

void QueryEvaluator::ev_relRef_X_X(RelRef *relRef)
{
}

void QueryEvaluator::evaluate_patCl(PatCl *patCl)
{
}