#include "QueryEvaluator.h"
#include "Parser.h"

#include <cstring>
#include <cassert>
#include <queue>
#include <set>

using std::list;
using std::string;
using std::map;
using std::queue;
using std::set;

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
        return a.argTwoSynType < b.argTwoSynType;
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
        pqlParser(), pkb(NULL), resultsProjector(),
        isAlive(true),
        graph_synMap(), graph_adjList(), graph_refToVertex(),
        graph_vertexCC(), graph_nrVertexCC(0), graph_isolatedRef(),
        partitionedClauses(),
        resultsTable()
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

void QueryEvaluator::reset()
{
    this->isAlive = true;
    this->partitionedClauses.clear();
    this->resultsTable.clear();
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
    assert(this->dispatchTable.find(evalSynArgDesc) ==
        this->dispatchTable.end());
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

    // Modifies(assign,var), 01
    evalSynArgDesc = EvalSynArgDesc(REL_MODIFIES, SYN_SYN_01, ENT_ASSIGN,
            ENT_VAR, RELARG_INVALID, RELARG_INVALID);
    tmpDispatch.reset();
    tmpDispatch.get_int_set_argOne_from_string_argTwo =
            &PKB::modifies_X_Y_get_int_X_from_string_Y;
    tmpDispatch.relRef_eval =
            &QueryEvaluator::ev_rr_ss_int_string_01;
    assert(this->dispatchTable.find(evalSynArgDesc) ==
                this->dispatchTable.end());
    this->dispatchTable[evalSynArgDesc] = tmpDispatch;
}

void QueryEvaluator::setup_uses()
{
    EvalSynArgDesc evalSynArgDesc;
    EvalPKBDispatch tmpDispatch;
    // Uses(assign,var), 01
    evalSynArgDesc = EvalSynArgDesc(REL_USES, SYN_SYN_01, ENT_ASSIGN,
            ENT_VAR, RELARG_INVALID, RELARG_INVALID);
    tmpDispatch.reset();
    tmpDispatch.get_all_int_argOne = &PKB::get_all_assign;
    tmpDispatch.get_int_set_argOne_from_string_argTwo =
            &PKB::uses_X_Y_get_int_X_from_string_Y;
    tmpDispatch.get_string_set_argTwo_from_int_argOne =
            &PKB::uses_X_Y_get_string_Y_from_int_X;
    tmpDispatch.relRef_eval =
            &QueryEvaluator::ev_rr_ss_int_string_01;
    this->dispatchTable[evalSynArgDesc] = tmpDispatch;
    // Uses(procedure,var), 01
    evalSynArgDesc = EvalSynArgDesc(REL_USES, SYN_SYN_01, ENT_PROC,
            ENT_VAR, RELARG_INVALID, RELARG_INVALID);
    tmpDispatch.reset();
    tmpDispatch.get_all_string_argOne = &PKB::get_all_procs;
    tmpDispatch.get_string_set_argOne_from_string_argTwo =
            &PKB::uses_X_Y_get_string_X_from_string_Y;
    tmpDispatch.get_string_set_argTwo_from_string_argOne =
            &PKB::uses_X_Y_get_string_Y_from_string_X;
    tmpDispatch.relRef_eval =
            &QueryEvaluator::ev_rr_ss_string_string_01;
    this->dispatchTable[evalSynArgDesc] = tmpDispatch;

    // Uses(procedure,var), 10
    evalSynArgDesc = EvalSynArgDesc(REL_USES, SYN_SYN_10, ENT_PROC,
            ENT_VAR, RELARG_INVALID, RELARG_INVALID);
    tmpDispatch.reset();
    tmpDispatch.get_all_string_argTwo = &PKB::get_all_vars;
    tmpDispatch.get_string_set_argOne_from_string_argTwo =
            &PKB::uses_X_Y_get_string_X_from_string_Y;
    tmpDispatch.get_string_set_argTwo_from_string_argOne =
            &PKB::uses_X_Y_get_string_Y_from_string_X;
    tmpDispatch.relRef_eval =
            &QueryEvaluator::ev_rr_ss_string_string_10;
    this->dispatchTable[evalSynArgDesc] = tmpDispatch;

    // Uses(assign,var), 10
    evalSynArgDesc = EvalSynArgDesc(REL_USES, SYN_SYN_10, ENT_ASSIGN,
            ENT_VAR, RELARG_INVALID, RELARG_INVALID);
    tmpDispatch.reset();
    tmpDispatch.get_all_string_argTwo = &PKB::get_all_vars;
    tmpDispatch.get_int_set_argOne_from_string_argTwo =
            &PKB::uses_X_Y_get_int_X_from_string_Y;
    tmpDispatch.get_string_set_argTwo_from_int_argOne =
            &PKB::uses_X_Y_get_string_Y_from_int_X;
    tmpDispatch.relRef_eval =
            &QueryEvaluator::ev_rr_ss_int_string_10;
    this->dispatchTable[evalSynArgDesc] = tmpDispatch;

    // Uses(procedure,var), 11
    evalSynArgDesc = EvalSynArgDesc(REL_USES, SYN_SYN_11, ENT_PROC,
            ENT_VAR, RELARG_INVALID, RELARG_INVALID);
    tmpDispatch.reset();
    tmpDispatch.f_string_argOne_string_argTwo =
            &PKB::uses_query_string_X_string_Y;
    tmpDispatch.relRef_eval =
            &QueryEvaluator::ev_rr_ss_string_string_11;
    this->dispatchTable[evalSynArgDesc] = tmpDispatch;

    // Uses(assign,var), 11
    evalSynArgDesc = EvalSynArgDesc(REL_USES, SYN_SYN_11, ENT_ASSIGN,
            ENT_VAR, RELARG_INVALID, RELARG_INVALID);
    tmpDispatch.reset();
    tmpDispatch.f_int_argOne_string_argTwo =
            &PKB::uses_query_int_X_string_Y;
    tmpDispatch.relRef_eval =
            &QueryEvaluator::ev_rr_ss_int_string_11;
    this->dispatchTable[evalSynArgDesc] = tmpDispatch;
}

// TODO: Fix cyclic call chain issue with regards to updating
//       modifies and uses, ie. A->B->C->A type of call chain
void QueryEvaluator::setup_calls()
{
    EvalSynArgDesc evalSynArgDesc;
    EvalPKBDispatch tmpDispatch;

    // Calls(procedure,procedure), 00
    evalSynArgDesc = EvalSynArgDesc(REL_CALLS, SYN_SYN_00, ENT_PROC,
            ENT_PROC, RELARG_INVALID, RELARG_INVALID);
    tmpDispatch.reset();
    tmpDispatch.get_all_string_argOne = &PKB::get_all_procs;
    tmpDispatch.get_all_string_argTwo = &PKB::get_all_procs;
    tmpDispatch.get_string_set_argOne_from_string_argTwo =
            &PKB::calls_X_Y_get_string_X_from_string_Y;
    tmpDispatch.get_string_set_argTwo_from_string_argOne =
            &PKB::calls_X_Y_get_string_Y_from_string_X;
    tmpDispatch.relRef_eval =
            &QueryEvaluator::ev_rr_ss_string_string_00_from_argOne;
    this->dispatchTable[evalSynArgDesc] = tmpDispatch;
}

void QueryEvaluator::setup_callsStar()
{
}

void QueryEvaluator::setup_parent()
{
    EvalSynArgDesc evalSynArgDesc;
    EvalPKBDispatch tmpDispatch;
    // Parent(while,assign), 00
    evalSynArgDesc = EvalSynArgDesc(REL_PARENT, SYN_SYN_00, ENT_WHILE,
            ENT_ASSIGN, RELARG_INVALID, RELARG_INVALID);
    tmpDispatch.reset();
    tmpDispatch.get_all_int_argOne = &PKB::get_all_while;
    tmpDispatch.get_all_int_argTwo = &PKB::get_all_assign;
    tmpDispatch.get_int_set_argOne_from_int_argTwo =
            &PKB::parent_X_Y_get_int_X_from_int_Y;
    tmpDispatch.get_int_set_argTwo_from_int_argOne =
            &PKB::parent_X_Y_get_int_Y_from_int_X;
    tmpDispatch.relRef_eval =
            &QueryEvaluator::ev_rr_ss_int_int_00_from_argOne;
    this->dispatchTable[evalSynArgDesc] = tmpDispatch;
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
    this->reset();
    this->pqlParser.parse(queryStr, true, true);
    qinfo = this->pqlParser.get_queryinfo();
    this->partition_evaluation(qinfo);

    // Evaluate isolated refs
    for (set<int>::const_iterator it = this->graph_isolatedRef.begin();
            this->isAlive && it != this->graph_isolatedRef.end(); it++) {
        // TODO: Implement!!!
    }
    if (this->isAlive) {
        // Evaluate everything (sequentially for now)
        // NOTE: Take care when we parallelize this
        int nrPartitions = this->partitionedClauses.size();
        for (int rTableIdx = 0; rTableIdx < nrPartitions; rTableIdx++) {
            const vector<int>& vec = this->partitionedClauses[rTableIdx];
            int nrClauses = vec.size();
            const ResultsTable& rTable = this->resultsTable[rTableIdx];
            for (int k = 0; k < nrClauses && rTable.is_alive(); k++) {
                int clauseIdx = vec[k];
                ClauseType clauseType =
                        qinfo->get_nth_clause_type(clauseIdx);
                assert(clauseType != INVALID_CLAUSE);
                GenericRef *genericRef =
                        qinfo->get_nth_clause(clauseIdx);
                assert(genericRef != NULL);
                if (clauseType == SUCHTHAT_CLAUSE) {
                    RelRef *relRef = dynamic_cast<RelRef *>(genericRef);
                    assert(relRef != NULL);
                    this->evaluate_relRef(rTableIdx, relRef);
                } else if (clauseType == WITH_CLAUSE) {
                    // TODO: Implement when pql parser is done
                } else if (clauseType == PATTERN_CLAUSE) {
                    PatCl *patCl = dynamic_cast<PatCl *>(genericRef);
                    assert(patCl != NULL);
                    this->evaluate_patCl(rTableIdx, patCl);
                }
            }
            if (!rTable.is_alive()) {
                this->isAlive = false;
                break;
            }
        }
    }
    ResultsTable rTable;
    if (this->isAlive) {
        int len = this->resultsTable.size();
        for (int i = 0; i < len; i++) {
            if (this->resultsTable[i].is_alive()) {
                rTable.absorb_ResultsTable(this->resultsTable[i]);
            } else {
                rTable.kill();
                break;
            }
        }
    }
    this->resultsProjector.get_results(rTable, qinfo, pkb, resultSet);

    /*
    int nrClauses = qinfo->get_nr_clauses();
    GenericRef *genericRef;
    for (int i = 0; i < nrClauses; i++) {
    }
    ClauseType clauseType;
    for (int i = 0; i < nrClauses && this->results.is_alive(); i++) {
        clauseType = qinfo->get_nth_clause_type(i);
        assert(clauseType != INVALID_CLAUSE);
        genericRef = qinfo->get_nth_clause(i);
        assert(genericRef != NULL);
        switch (clauseType) {
        case SUCHTHAT_CLAUSE:
            relRef = dynamic_cast<RelRef *>(genericRef);
            assert(relRef != NULL);
            this->evaluate_relRef(relRef);
            break;
        case WITH_CLAUSE:
            // TODO: Implement when pql parser is done
            break;
        case PATTERN_CLAUSE:
            patCl = dynamic_cast<PatCl *>(genericRef);
            assert(patCl != NULL);
            this->evaluate_patCl(patCl);
            break;
        }
    }
    this->resultsProjector.get_results(this->results, qinfo, pkb, resultSet);
    */
}

void QueryEvaluator::partition_evaluation(QueryInfo *qinfo)
{
    ClauseType clauseType;
    GenericRef *genericRef;
    RelRef *relRef;
    AttrRef *attrRef;
    PatCl *patCl;
    int nrClauses = qinfo->get_nr_clauses();
    this->graph_synMap.clear();
    this->graph_adjList.clear();
    this->graph_refToVertex = vector<int>(nrClauses+5, -1);
    this->graph_vertexCC.clear();
    this->graph_isolatedRef.clear();
    this->partitionedClauses.clear();

    // Build graph based on clauses
    for (int i = 0; i < nrClauses; i++) {
        clauseType = qinfo->get_nth_clause_type(i);
        assert(clauseType != INVALID_CLAUSE);
        genericRef = qinfo->get_nth_clause(i);
        assert(genericRef != NULL);
        switch (clauseType) {
        case SUCHTHAT_CLAUSE:
            relRef = dynamic_cast<RelRef *>(genericRef);
            assert(relRef != NULL);
            this->partition_process_relRef(i, relRef);
            break;
        case WITH_CLAUSE:
            // TODO: Implement
            break;
        case PATTERN_CLAUSE:
            patCl = dynamic_cast<PatCl *>(genericRef);
            assert(patCl != NULL);
            this->partition_process_patCl(i, patCl);
            break;
        }
    }

    // Connected components for synonym graph
    this->partition_evaluation_cc();
    // Actual partitioning
    this->partition_evaluation_partition(nrClauses);
}

void QueryEvaluator::partition_process_relRef(int clauseIdx, RelRef *relRef)
{
    assert(relRef->relType != REL_INVALID);
    if (relRef->argOneType == RELARG_SYN &&
            relRef->argTwoType == RELARG_SYN) {
        this->partition_add_edge(clauseIdx, relRef->argOneString,
                relRef->argTwoString);
    } else if (relRef->argOneType == RELARG_SYN) {
        this->partition_add_vertex(clauseIdx, relRef->argOneString);
    } else if (relRef->argTwoType == RELARG_SYN) {
        this->partition_add_vertex(clauseIdx, relRef->argTwoString);
    } else {
        // no synonym, push to isolated
        this->graph_isolatedRef.insert(clauseIdx);
    }
}

void QueryEvaluator::partition_process_patCl(int idx, PatCl *patCl)
{
    assert(patCl->type != PATCL_INVALID);
    if (patCl->varRefType == PATVARREF_SYN) {
        this->partition_add_edge(idx, patCl->syn, patCl->varRefString);
    } else {
        this->partition_add_vertex(idx, patCl->syn);
    }
}

int QueryEvaluator::partition_add_vertex(int clauseIdx, const string& syn)
{
    map<string, int>::const_iterator it = this->graph_synMap.find(syn);
    if (it == this->graph_synMap.end()) {
        int nextLabel = this->graph_synMap.size();
        this->graph_synMap[syn] = nextLabel;
        this->graph_adjList.push_back(set<int>());
        this->graph_refToVertex[clauseIdx] = nextLabel;
        return nextLabel;
    } else {
        return this->graph_refToVertex[clauseIdx] = it->second;
    }
}

void QueryEvaluator::partition_add_edge(int clauseIdx, const string& synOne,
        const string& synTwo)
{
    int vertexOne = this->partition_add_vertex(clauseIdx, synOne);
    int vertexTwo = this->partition_add_vertex(clauseIdx, synTwo);
    if (vertexOne != vertexTwo) {
        set<int>& adjOne = this->graph_adjList[vertexOne];
        set<int>& adjTwo = this->graph_adjList[vertexTwo];
        adjOne.insert(vertexTwo);
        adjTwo.insert(vertexOne);
    }
}

void QueryEvaluator::partition_evaluation_cc()
{
    int nrSyn = this->graph_synMap.size();
    this->graph_vertexCC = vector<int>(nrSyn+5, -1);
    this->graph_nrVertexCC = 0;
    for (int i = 0; i < nrSyn; i++) {
        if (this->graph_vertexCC[i] == -1) {
            partition_evaluation_cc_bfs(i);
            this->graph_nrVertexCC++;
        }
    }
}

void QueryEvaluator::partition_evaluation_cc_bfs(int syn)
{
    queue<int> q;
    q.push(syn);
    int v;
    while (!q.empty()) {
        v = q.front();
        q.pop();
        if (this->graph_vertexCC[v] == -1) {
            this->graph_vertexCC[v] = this->graph_nrVertexCC;
            const set<int>& adjList = this->graph_adjList[v];
            for (set<int>::const_iterator it = adjList.begin();
                    it != adjList.end(); it++) {
                if (this->graph_vertexCC[*it] == -1) {
                    q.push(*it);
                }
            }
        }
    }
}

void QueryEvaluator::partition_evaluation_partition(int nrClauses)
{
    this->partitionedClauses.clear();
    this->resultsTable.clear();
    for (int i = 0; i < this->graph_nrVertexCC; i++) {
        this->partitionedClauses.push_back(vector<int>());
    }
    for (int i = 0; i < this->graph_nrVertexCC; i++) {
        this->resultsTable.push_back(ResultsTable());
    }
    // map clauses to component
    int component;
    for (int i = 0; i < nrClauses; i++) {
        if (this->graph_refToVertex[i] == -1) {
            // no synonym
            assert(this->graph_isolatedRef.find(i) !=
                    this->graph_isolatedRef.end());
        } else {
            component = this->graph_vertexCC[this->graph_refToVertex[i]];
            this->partitionedClauses[component].push_back(i);
        }
    }
}

void QueryEvaluator::evaluate_relRef(int rTableIdx, RelRef *relRef)
{
    if (relRef->argOneType == RELARG_SYN &&
            relRef->argTwoType == RELARG_SYN) {
        this->ev_relRef_syn_syn(rTableIdx, relRef);
    } else if (relRef->argOneType == RELARG_SYN) {
        this->ev_relRef_syn_X(rTableIdx, relRef);
    } else if (relRef->argTwoType == RELARG_SYN) {
        this->ev_relRef_X_syn(rTableIdx, relRef);
    } else {
        this->ev_relRef_X_X(rTableIdx, relRef);
    }
}

void QueryEvaluator::ev_relRef_syn_syn(int rTableIdx, RelRef *relRef)
{
    enum SynInGraph synInGraph = SYN_ARGS_INVALID;
    EvalSynArgDesc evalSynArgDesc;
    const ResultsTable& rTable = this->resultsTable[rTableIdx];
    if (rTable.has_synonym(relRef->argOneString) &&
            rTable.has_synonym(relRef->argTwoString)) {
        synInGraph = SYN_SYN_11;
    } else if (rTable.has_synonym(relRef->argOneString)) {
        synInGraph = SYN_SYN_10;
    } else if (rTable.has_synonym(relRef->argTwoString)) {
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
    (this->*(it->second.relRef_eval)) (rTableIdx, relRef, it->second);
}

void QueryEvaluator::ev_rr_ss_string_string_00_from_argOne(
        int rTableIdx, RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(disp.get_all_string_argOne != NULL);
    assert(disp.get_string_set_argTwo_from_string_argOne != NULL);
    set<string> argOneSet = (this->pkb->*(disp.get_all_string_argOne))();
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    rTable.syn_00_transaction_begin(relRef->argOneString, RV_STRING,
            relRef->argTwoString, RV_STRING);
    for (set<string>::const_iterator it = argOneSet.begin();
            it != argOneSet.end(); it++) {
        set<string> argTwoSet =
                (this->pkb->*(disp.get_string_set_argTwo_from_string_argOne))
                    (relRef->argOneSyn, relRef->argTwoSyn, *it);
        for (set<string>::const_iterator kt = argTwoSet.begin();
                kt != argTwoSet.end(); kt++) {
            rTable.syn_00_add_row(*it, *kt);
        }
    }
    rTable.syn_00_transaction_end();
}

// Currently, nothing uses this and it does not seem it will be used
void QueryEvaluator::ev_rr_ss_string_string_00_from_argTwo(
        int rTableIdx, RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(disp.get_all_string_argTwo != NULL);
    assert(disp.get_string_set_argOne_from_string_argTwo != NULL);
    set<string> argTwoSet = (this->pkb->*(disp.get_all_string_argTwo))();
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    rTable.syn_00_transaction_begin(relRef->argOneString, RV_STRING,
            relRef->argTwoString, RV_STRING);
    for (set<string>::const_iterator it = argTwoSet.begin();
            it != argTwoSet.end(); it++) {
        set<string> argOneSet =
                (this->pkb->*
                    (disp.get_string_set_argOne_from_string_argTwo))
                        (relRef->argOneSyn, relRef->argTwoSyn, *it);
        for (set<string>::const_iterator kt = argOneSet.begin();
                kt != argOneSet.end(); kt++) {
            rTable.syn_00_add_row(*kt, *it);
        }
    }
    rTable.syn_00_transaction_end();
}

void QueryEvaluator::ev_rr_ss_string_string_01(int rTableIdx,
        RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(disp.get_string_set_argOne_from_string_argTwo != NULL);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    pair<const vector<Record> *, int> viPair =
            rTable.syn_01_transaction_begin(relRef->argOneString,
                    relRef->argTwoString, RV_STRING);
    const vector<Record>& argTwoVec = *(viPair.first);
    int colIdx = viPair.second;
    int nrRecords = argTwoVec.size();
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = argTwoVec[i];
        const pair<string, int> recPair = record.get_column(colIdx);
        const string& argTwoVal = recPair.first;
        set<string> argOneSet =
            (this->pkb->*(disp.get_string_set_argOne_from_string_argTwo))
                    (relRef->argOneSyn, relRef->argTwoSyn, argTwoVal);
        for (set<string>::const_iterator argOneIt = argOneSet.begin();
                argOneIt != argOneSet.end(); argOneIt++) {
            rTable.syn_01_augment_new_row(i, *argOneIt);
        }
    }
    rTable.syn_01_transaction_end();
}

void QueryEvaluator::ev_rr_ss_string_string_10(int rTableIdx,
        RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(disp.get_string_set_argTwo_from_string_argOne != NULL);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    pair<const vector<Record> *, int> viPair =
            rTable.syn_10_transaction_begin(relRef->argOneString,
                    relRef->argTwoString, RV_STRING);
    const vector<Record>& argOneVec = *(viPair.first);
    int nrRecords = argOneVec.size();
    int colIdx = viPair.second;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = argOneVec[i];
        const pair<string, int>& recPair = record.get_column(colIdx);
        const string& argOneVal = recPair.first;
        set<string> argTwoSet =
                (this->pkb->*(disp.get_string_set_argTwo_from_string_argOne))
                        (relRef->argOneSyn, relRef->argTwoSyn, argOneVal);
        for (set<string>::const_iterator argTwoIt = argTwoSet.begin();
                argTwoIt != argTwoSet.end(); argTwoIt++) {
            rTable.syn_10_augment_new_row(i, *argTwoIt);
        }
    }
    rTable.syn_10_transaction_end();
}

void QueryEvaluator::ev_rr_ss_string_string_11(int rTableIdx,
        RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(disp.f_string_argOne_string_argTwo != NULL);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    pair<const vector<Record> *, pair<int, int> > viiPair =
            rTable.syn_11_transaction_begin(relRef->argOneString,
                    relRef->argTwoString);
    const vector<Record>& records = *(viiPair.first);
    int nrRecords = records.size();
    int colOne = viiPair.second.first;
    int colTwo = viiPair.second.second;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = records[i];
        const pair<string, int>& pairOne = record.get_column(colOne);
        const pair<string, int>& pairTwo = record.get_column(colTwo);
        const string& argOneVal = pairOne.first;
        const string& argTwoVal = pairTwo.first;
        if ((this->pkb->*(disp.f_string_argOne_string_argTwo))
                        (relRef->argOneSyn, argOneVal,
                         relRef->argTwoSyn, argTwoVal)) {
            rTable.syn_11_mark_row_ok(i);
        }
    }
    rTable.syn_11_transaction_end();
}

void QueryEvaluator::ev_rr_ss_string_string_22(int rTableIdx,
        RelRef *relRef, const EvalPKBDispatch& disp)
{
    // TODO: Implement
}

// Currently, nothing uses this and it does not seem it will be used
void QueryEvaluator::ev_rr_ss_string_int_00_from_argOne(int rTableIdx,
        RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(disp.get_all_string_argOne != NULL);
    assert(disp.get_int_set_argTwo_from_string_argOne != NULL);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    rTable.syn_00_transaction_begin(relRef->argOneString, RV_STRING,
            relRef->argOneString, RV_INT);
    set<string> argOneSet = (this->pkb->*(disp.get_all_string_argOne))();
    for (set<string>::const_iterator it = argOneSet.begin();
            it != argOneSet.end(); it++) {
        set<int> argTwoSet =
            (this->pkb->*(disp.get_int_set_argTwo_from_string_argOne))
                    (relRef->argOneSyn, relRef->argTwoSyn, *it);
        for (set<int>::const_iterator kt = argTwoSet.begin();
                kt != argTwoSet.end(); kt++) {
            rTable.syn_00_add_row(*it, *kt);
        }
    }
    rTable.syn_00_transaction_end();
}

// Currently, nothing uses this and it does not seem it will be used
void QueryEvaluator::ev_rr_ss_string_int_00_from_argTwo(int rTableIdx,
        RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(disp.get_all_int_argTwo != NULL);
    assert(disp.get_string_set_argOne_from_int_argTwo != NULL);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    rTable.syn_00_transaction_begin(relRef->argOneString, RV_STRING,
            relRef->argOneString, RV_INT);
    set<int> argTwoSet = (this->pkb->*(disp.get_all_int_argTwo))();
    for (set<int>::const_iterator it = argTwoSet.begin();
            it != argTwoSet.end(); it++) {
        set<string> argOneSet =
            (this->pkb->*(disp.get_string_set_argOne_from_int_argTwo))
                    (relRef->argOneSyn, relRef->argTwoSyn, *it);
        for (set<string>::const_iterator kt = argOneSet.begin();
                kt != argOneSet.end(); kt++) {
            rTable.syn_00_add_row(*kt, *it);
        }
    }
    rTable.syn_00_transaction_end();
}

// Currently, nothing uses this and it does not seem it will be used
void QueryEvaluator::ev_rr_ss_string_int_01(int rTableIdx,
        RelRef *relRef, const EvalPKBDispatch& disp)
{
}

// Currently, nothing uses this and it does not seem it will be used
void QueryEvaluator::ev_rr_ss_string_int_10(int rTableIdx,
        RelRef *relRef, const EvalPKBDispatch& disp)
{
}

// Currently, nothing uses this and it does not seem it will be used
void QueryEvaluator::ev_rr_ss_string_int_11(int rTableIdx,
        RelRef *relRef, const EvalPKBDispatch& disp)
{
}

// Currently, nothing uses this and it does not seem it will be used
void QueryEvaluator::ev_rr_ss_string_int_22(int rTableIdx,
        RelRef *relRef, const EvalPKBDispatch& disp)
{
}

void QueryEvaluator::ev_rr_ss_int_string_00_from_argOne(int rTableIdx,
        RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(disp.get_all_int_argOne != NULL);
    assert(disp.get_string_set_argTwo_from_int_argOne != NULL);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    rTable.syn_00_transaction_begin(relRef->argOneString, RV_INT,
            relRef->argTwoString, RV_STRING);
    set<int> argOneSet = (this->pkb->*(disp.get_all_int_argOne))();
    for (set<int>::const_iterator it = argOneSet.begin();
            it != argOneSet.end(); it++) {
        set<string> argTwoSet =
                (this->pkb->*(disp.get_string_set_argTwo_from_int_argOne))
                        (relRef->argOneSyn, relRef->argTwoSyn, *it);
        for (set<string>::const_iterator kt = argTwoSet.begin();
                kt != argTwoSet.end(); kt++) {
            rTable.syn_00_add_row(*it, *kt);
        }
    }
    rTable.syn_00_transaction_end();
}

// not used for now
void QueryEvaluator::ev_rr_ss_int_string_00_from_argTwo(int rTableIdx,
        RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(disp.get_all_string_argTwo != NULL);
    assert(disp.get_int_set_argOne_from_string_argTwo != NULL);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    rTable.syn_00_transaction_begin(relRef->argOneString, RV_INT,
            relRef->argTwoString, RV_STRING);
    set<string> argTwoSet = (this->pkb->*(disp.get_all_string_argTwo))();
    for (set<string>::const_iterator it = argTwoSet.begin();
            it != argTwoSet.end(); it++) {
        set<int> argOneSet =
                (this->pkb->*(disp.get_int_set_argOne_from_string_argTwo))
                        (relRef->argOneSyn, relRef->argTwoSyn, *it);
        for (set<int>::const_iterator kt = argOneSet.begin();
                kt != argOneSet.end(); kt++) {
            rTable.syn_00_add_row(*kt, *it);
        }
    }
    rTable.syn_00_transaction_end();
}

void QueryEvaluator::ev_rr_ss_int_string_01(int rTableIdx,
        RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(disp.get_int_set_argOne_from_string_argTwo != NULL);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    pair<const vector<Record> *, int> viPair =
            rTable.syn_01_transaction_begin(relRef->argOneString,
                    relRef->argTwoString, RV_INT);
    const vector<Record>& argTwoVec = *(viPair.first);
    int nrRecords = argTwoVec.size();
    int colIdx = viPair.second;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = argTwoVec[i];
        const pair<string, int>& siPair = record.get_column(colIdx);
        const string& argTwoVal = siPair.first;
        set<int> argOneSet =
                (this->pkb->*
                        (disp.get_int_set_argOne_from_string_argTwo))
                                (relRef->argOneSyn, relRef->argTwoSyn,
                                 argTwoVal);
        for (set<int>::const_iterator argOneIt = argOneSet.begin();
                argOneIt != argOneSet.end(); argOneIt++){
            rTable.syn_01_augment_new_row(i, *argOneIt);
        }
    }
    rTable.syn_01_transaction_end();
}

void QueryEvaluator::ev_rr_ss_int_string_10(int rTableIdx,
        RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(disp.get_string_set_argTwo_from_int_argOne != NULL);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    pair<const vector<Record> *, int> viPair =
            rTable.syn_10_transaction_begin(relRef->argOneString,
                    relRef->argTwoString, RV_STRING);
    const vector<Record>& argOneVec = *(viPair.first);
    int nrRecords = argOneVec.size();
    int colIdx = viPair.second;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = argOneVec[i];
        const pair<string, int>& siPair = record.get_column(colIdx);
        int argOneVal = siPair.second;
        set<string> argTwoSet =
                (this->pkb->*(disp.get_string_set_argTwo_from_int_argOne))
                        (relRef->argOneSyn, relRef->argTwoSyn,
                         argOneVal);
        for (set<string>::const_iterator argTwoIt = argTwoSet.begin();
                argTwoIt != argTwoSet.end(); argTwoIt++) {
            rTable.syn_10_augment_new_row(i, *argTwoIt);
        }
    }
    rTable.syn_10_transaction_end();
}

void QueryEvaluator::ev_rr_ss_int_string_11(int rTableIdx,
        RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(disp.f_int_argOne_string_argTwo != NULL);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    pair<const vector<Record> *, pair<int, int> > viiPair =
            rTable.syn_11_transaction_begin(relRef->argOneString,
                    relRef->argTwoString);
    const vector<Record>& records = *(viiPair.first);
    int nrRecords = records.size();
    int colOne = viiPair.second.first;
    int colTwo = viiPair.second.second;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = records[i];
        const pair<string, int>& pairOne = record.get_column(colOne);
        const pair<string, int>& pairTwo = record.get_column(colTwo);
        int argOneVal = pairOne.second;
        const string& argTwoVal = pairTwo.first;
        if ((this->pkb->*(disp.f_int_argOne_string_argTwo))
                    (relRef->argOneSyn, argOneVal,
                        relRef->argTwoSyn, argTwoVal)) {
            rTable.syn_11_mark_row_ok(i);
        }
    }
    rTable.syn_11_transaction_end();
}

void QueryEvaluator::ev_rr_ss_int_string_22(int rTableIdx,
        RelRef *relRef, const EvalPKBDispatch& disp)
{
    // TODO: Implement
}

void QueryEvaluator::ev_rr_ss_int_int_00_from_argOne(int rTableIdx,
        RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(disp.get_all_int_argOne != NULL);
    assert(disp.get_int_set_argTwo_from_int_argOne != NULL);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    rTable.syn_00_transaction_begin(relRef->argOneString, RV_INT,
            relRef->argTwoString, RV_INT);
    set<int> argOneSet = (this->pkb->*(disp.get_all_int_argOne))();
    for (set<int>::const_iterator it = argOneSet.begin();
            it != argOneSet.end(); it++) {
        set<int> argTwoSet =
                (this->pkb->*(disp.get_int_set_argTwo_from_int_argOne))
                        (relRef->argOneSyn, relRef->argTwoSyn, *it);
        for (set<int>::const_iterator kt = argTwoSet.begin();
                kt != argTwoSet.end(); kt++) {
            rTable.syn_00_add_row(*it, *kt);
        }
    }
    rTable.syn_00_transaction_end();
}

void QueryEvaluator::ev_rr_ss_int_int_00_from_argTwo(int rTableIdx,
        RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(disp.get_all_int_argTwo != NULL);
    assert(disp.get_int_set_argOne_from_int_argTwo != NULL);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    rTable.syn_00_transaction_begin(relRef->argOneString, RV_INT,
            relRef->argTwoString, RV_INT);
    set<int> argTwoSet = (this->pkb->*(disp.get_all_int_argTwo))();
    for (set<int>::const_iterator it = argTwoSet.begin();
            it != argTwoSet.end(); it++) {
        set<int> argOneSet =
                (this->pkb->*(disp.get_int_set_argOne_from_int_argTwo))
                        (relRef->argOneSyn, relRef->argTwoSyn, *it);
        for (set<int>::const_iterator kt = argOneSet.begin();
                kt != argOneSet.end(); kt++) {
            rTable.syn_00_add_row(*kt, *it);
        }
    }
    rTable.syn_00_transaction_end();
}

void QueryEvaluator::ev_rr_ss_int_int_01(int rTableIdx, RelRef *relRef,
        const EvalPKBDispatch& disp)
{
}

void QueryEvaluator::ev_rr_ss_int_int_10(int rTableIdx, RelRef *relRef,
        const EvalPKBDispatch& disp)
{
}

void QueryEvaluator::ev_rr_ss_int_int_11(int rTableIdx, RelRef *relRef,
        const EvalPKBDispatch& disp)
{
}

void QueryEvaluator::ev_rr_ss_int_int_22(int rTableIdx, RelRef *relRef,
        const EvalPKBDispatch& disp)
{
    // TODO: Implement
}

void QueryEvaluator::ev_relRef_syn_X(int rTableIdx, RelRef *relRef)
{
}

void QueryEvaluator::ev_relRef_X_syn(int rTableIdx, RelRef *relRef)
{
}

void QueryEvaluator::ev_relRef_X_X(int rTableIdx, RelRef *relRef)
{
}

void QueryEvaluator::evaluate_patCl(int rTableIdx, PatCl *patCl)
{
}