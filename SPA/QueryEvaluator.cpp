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
        graph_vertexCC(), graph_nrVertexCC(0), graph_isolatedClauses(),
        partitionedClauses(),
        resultsTable()
{}

void QueryEvaluator::reset()
{
    this->isAlive = true;
    this->partitionedClauses.clear();
    this->resultsTable.clear();
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

    // Evaluate isolated clauses (stuff with no synonyms)
    for (set<int>::const_iterator it =
            this->graph_isolatedClauses.begin();
            this->isAlive && it != this->graph_isolatedClauses.end();
            it++) {
        if (!this->ev_isolated_clause(qinfo, *it)) {
            this->isAlive = false;
            break;
        }
    }
    if (this->isAlive) {
        // Evaluate everything (sequentially for now)
        // NOTE: Take care when we parallelize this
        int nrPartitions = this->partitionedClauses.size();
        ClauseType clauseType;
        for (int rTableIdx = 0; rTableIdx < nrPartitions; rTableIdx++) {
            const vector<int>& vec = this->partitionedClauses[rTableIdx];
            int nrClauses = vec.size();
            const ResultsTable& rTable = this->resultsTable[rTableIdx];
            for (int k = 0; k < nrClauses && rTable.is_alive(); k++) {
                int clauseIdx = vec[k];
                const GenericRef *genericRef =
                        qinfo->get_nth_clause(clauseIdx, &clauseType);
                assert(INVALID_CLAUSE != clauseType);
                assert(NULL != genericRef);
                switch (clauseType) {
                case SUCHTHAT_CLAUSE:
                    this->evaluate_relRef(rTableIdx, genericRef);
                    break;
                case WITH_CLAUSE:
                    // TODO: Implement when pql parser is done
                    break;
                case PATTERN_CLAUSE:
                    this->evaluate_patCl(rTableIdx, genericRef);
                    break;
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
    } else {
        // query failed. kill rTable
        rTable.kill();
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

void QueryEvaluator::partition_evaluation(const QueryInfo *qinfo)
{
    ClauseType clauseType;
    int nrClauses = qinfo->get_nr_clauses();
    this->graph_synMap.clear();
    this->graph_adjList.clear();
    this->graph_refToVertex = vector<int>(nrClauses+5, -1);
    this->graph_vertexCC.clear();
    this->graph_isolatedClauses.clear();
    this->partitionedClauses.clear();

    // Build graph based on clauses
    for (int i = 0; i < nrClauses; i++) {
        const GenericRef *genericRef =
                qinfo->get_nth_clause(i, &clauseType);
        assert(INVALID_CLAUSE != clauseType);
        assert(NULL != genericRef);
        switch (clauseType) {
        case SUCHTHAT_CLAUSE:
            this->partition_process_relRef(i, genericRef);
            break;
        case WITH_CLAUSE:
            // TODO: Implement
            break;
        case PATTERN_CLAUSE:
            this->partition_process_patCl(i, genericRef);
            break;
        }
    }

    // Connected components for synonym graph
    this->partition_evaluation_cc();
    // Actual partitioning
    this->partition_evaluation_partition(nrClauses);
}

void QueryEvaluator::partition_process_relRef(int clauseIdx,
        const GenericRef *genRef)
{
    const RelRef *relRef =
        dynamic_cast<const RelRef *>(genRef);
    assert(NULL != relRef);
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
        this->graph_isolatedClauses.insert(clauseIdx);
    }
}

void QueryEvaluator::partition_process_patCl(int idx,
        const GenericRef *genRef)
{
    const PatCl *patCl =
        dynamic_cast<const PatCl *>(genRef);
    assert(NULL != patCl);
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
            assert(this->graph_isolatedClauses.find(i) !=
                    this->graph_isolatedClauses.end());
        } else {
            component = this->graph_vertexCC[this->graph_refToVertex[i]];
            this->partitionedClauses[component].push_back(i);
        }
    }
}

bool QueryEvaluator::ev_isolated_clause(const QueryInfo *qinfo,
        int clauseIdx) const
{
    ClauseType clauseType;
    const GenericRef *genericRef =
            qinfo->get_nth_clause(clauseIdx, &clauseType);
    assert(NULL != genericRef);
    assert(INVALID_CLAUSE != clauseType);
    // pattern clause can NEVER be isolated
    assert(PATTERN_CLAUSE != clauseType);
    switch (clauseType) {
    case SUCHTHAT_CLAUSE:
        return this->ev_isolated_relation_clause(genericRef);
        break;
    case WITH_CLAUSE:
        return this->ev_isolated_with_clause(genericRef);
        break;
    }
}

bool QueryEvaluator::ev_isolated_relation_clause(const GenericRef *genRef)
        const
{
    const RelRef *relRef = dynamic_cast<const RelRef *>(genRef);
    assert(NULL != relRef);
    assert(RelRef::valid(*relRef));
    int score = 0;
    switch (relRef->argOneType) {
    case RELARG_STRING:
        score += 10;
        break;
    case RELARG_INT:
        score += 20;
        break;
    case RELARG_WILDCARD:
        score += 30;
        break;
    }
    switch (relRef->argTwoType) {
    case RELARG_STRING:
        score += 1;
        break;
    case RELARG_INT:
        score += 2;
        break;
    case RELARG_WILDCARD:
        score += 3;
        break;
    }
    assert(score > 10);
    // dispatch on argument type
    switch (score) {
    case 11: // string, string
        return this->ev_isolated_relation_string_string(relRef);
        break;
    case 12: // string, int
        return this->ev_isolated_relation_string_int(relRef);
        break;
    case 13: // string, _
        return this->ev_isolated_relation_string_wild(relRef);
        break;
    case 21: // int, string
        return this->ev_isolated_relation_int_string(relRef);
        break;
    case 22: // int, int
        return this->ev_isolated_relation_int_int(relRef);
        break;
    case 23: // int, _
        return this->ev_isolated_relation_int_wild(relRef);
        break;
    case 31: // _, string
        return this->ev_isolated_relation_wild_string(relRef);
        break;
    case 32: // _, int
        return this->ev_isolated_relation_wild_int(relRef);
        break;
    case 33: // _, _
        return this->ev_isolated_relation_wild_wild(relRef);
        break;
    }
    assert(false);
    return false;
}

bool QueryEvaluator::ev_isolated_relation_string_string(
        const RelRef *relRef) const
{
    switch (relRef->relType) {
    case REL_MODIFIES:
        return this->pkb->modifies_query_string_X_string_Y(ENT_PROC,
                           relRef->argOneString, ENT_VAR,
                           relRef->argTwoString);
        break;
    case REL_USES:
        // TODO: Implement
        break;
    case REL_CALLS:
        // TODO: Implement
        break;
    case REL_CALLS_STAR:
        // TODO: Implement
        break;
    }
    assert(false);
    return false;
}

bool QueryEvaluator::ev_isolated_relation_string_int(
        const RelRef *relRef) const
{
    // Never be valid since no Relation has (string,int) args
    assert(false);
    return false;
}

bool QueryEvaluator::ev_isolated_relation_string_wild(
        const RelRef *relRef) const
{
    switch (relRef->relType) {
    case REL_MODIFIES:
        return this->pkb->modifies_X_Y_string_X_smth(ENT_PROC,
                       relRef->argOneString);
        break;
    case REL_USES:
        // TODO: Implement
        break;
    case REL_CALLS:
        // TODO: Implement
        break;
    case REL_CALLS_STAR:
        // TODO: Implement
        break;
    }
    assert(false);
    return false;
}

bool QueryEvaluator::ev_isolated_relation_int_string(
        const RelRef *relRef) const
{
    switch (relRef->relType) {
    case REL_MODIFIES:
        return this->pkb->modifies_query_int_X_string_Y(ENT_STMT,
                           relRef->argOneInt, ENT_VAR,
                           relRef->argTwoString);
        break;
    case REL_USES:
        // TODO: Implement
        break;
    }
    assert(false);
    return false;
}

bool QueryEvaluator::ev_isolated_relation_int_int(
        const RelRef *relRef) const
{
    switch (relRef->relType) {
    case REL_PARENT:
        // TODO: Implement
        break;
    case REL_PARENT_STAR:
        // TODO: Implement
        break;
    case REL_FOLLOWS:
        // TODO: Implement
        break;
    case REL_FOLLOWS_STAR:
        // TODO: Implement
        break;
    case REL_NEXT:
        // TODO: Implement
        break;
    case REL_NEXT_STAR:
        // TODO: Implement
        break;
    case REL_AFFECTS:
        // TODO: Implement
        break;
    case REL_AFFECTS_STAR:
        // TODO: Implement
        break;
    }
    assert(false);
    return false;
}

bool QueryEvaluator::ev_isolated_relation_int_wild(
        const RelRef *relRef) const
{
    switch (relRef->relType) {
    case REL_MODIFIES:
        return this->pkb->modifies_X_Y_int_X_smth(ENT_STMT,
                       relRef->argOneInt);
        break;
    case REL_USES:
        // TODO: Implement
        break;
    case REL_PARENT:
        // TODO: Implement
        break;
    case REL_PARENT_STAR:
        // TODO: Implement
        break;
    case REL_FOLLOWS:
        // TODO: Implement
        break;
    case REL_FOLLOWS_STAR:
        // TODO: Implement
        break;
    case REL_NEXT:
        // TODO: Implement
        break;
    case REL_NEXT_STAR:
        // TODO: Implement
        break;
    case REL_AFFECTS:
        // TODO: Implement
        break;
    case REL_AFFECTS_STAR:
        // TODO: Implement
        break;
    }
    assert(false);
    return false;
}

bool QueryEvaluator::ev_isolated_relation_wild_string(
        const RelRef *relRef) const
{
    switch (relRef->relType) {
    case REL_MODIFIES:
        return this->pkb->modifies_X_Y_smth_string_Y(ENT_VAR,
                       relRef->argTwoString);
        break;
    case REL_USES:
        // TODO: Implement
        break;
    case REL_CALLS:
        // TODO: Implement
        break;
    case REL_CALLS_STAR:
        // TODO: Implement
        break;
    }
    assert(false);
    return false;
}

bool QueryEvaluator::ev_isolated_relation_wild_int(
        const RelRef *relRef) const
{
    switch (relRef->relType) {
    case REL_PARENT:
        // TODO: Implement
        break;
    case REL_PARENT_STAR:
        // TODO: Implement
        break;
    case REL_FOLLOWS:
        // TODO: Implement
        break;
    case REL_FOLLOWS_STAR:
        // TODO: Implement
        break;
    case REL_NEXT:
        // TODO: Implement
        break;
    case REL_NEXT_STAR:
        // TODO: Implement
        break;
    case REL_AFFECTS:
        // TODO: Implement
        break;
    case REL_AFFECTS_STAR:
        // TODO: Implement
        break;
    }
    assert(false);
    return false;
}

bool QueryEvaluator::ev_isolated_relation_wild_wild(
        const RelRef *relRef) const
{
    switch (relRef->relType) {
    case REL_MODIFIES:
        return this->pkb->has_any_ent(ENT_ASSIGN);
        break;
    case REL_USES:
        // TODO: Implement
        break;
    case REL_CALLS:
        // TODO: Implement
        break;
    case REL_CALLS_STAR:
        // TODO: Implement
        break;
    case REL_PARENT:
        // TODO: Implement
        break;
    case REL_PARENT_STAR:
        // TODO: Implement
        break;
    case REL_FOLLOWS:
        // TODO: Implement
        break;
    case REL_FOLLOWS_STAR:
        // TODO: Implement
        break;
    case REL_NEXT:
        // TODO: Implement
        break;
    case REL_NEXT_STAR:
        // TODO: Implement
        break;
    case REL_AFFECTS:
        // TODO: Implement
        break;
    case REL_AFFECTS_STAR:
        // TODO: Implement
        break;
    }
    assert(false);
    return false;
}

bool QueryEvaluator::ev_isolated_with_clause(const GenericRef *genRef)
        const
{
    // TODO: Implement
    return false;
}

void QueryEvaluator::evaluate_relRef(int rTableIdx,
        const GenericRef *genRef)
{
    const RelRef *relRef =
        dynamic_cast<const RelRef *>(genRef);
    assert(NULL != relRef);
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

void QueryEvaluator::ev_relRef_syn_syn(int rTableIdx,
        const RelRef *relRef)
{
    enum SynInGraph synInGraph = SYN_ARGS_INVALID;
    EvalSynArgDesc evalSynArgDesc;
    EvalPKBDispatch pkbDispatch;
    const ResultsTable& rTable = this->resultsTable[rTableIdx];
    if (rTable.has_synonym(relRef->argOneString) &&
            rTable.has_synonym(relRef->argTwoString)) {
        if (rTable.syn_in_same_table(relRef->argOneString,
                relRef->argTwoString)) {
            synInGraph = SYN_SYN_11;
        } else {
            synInGraph = SYN_SYN_22;
        }
        this->ev_relRef_syn_syn_11_22_setup(synInGraph, pkbDispatch,
                relRef);
    } else if (rTable.has_synonym(relRef->argOneString)) {
        synInGraph = SYN_SYN_10;
        this->ev_relRef_syn_syn_10_setup(pkbDispatch, relRef);
    } else if (rTable.has_synonym(relRef->argTwoString)) {
        synInGraph = SYN_SYN_01;
        this->ev_relRef_syn_syn_01_setup(pkbDispatch, relRef);
    } else {
        synInGraph = SYN_SYN_00;
        this->ev_relRef_syn_syn_00_setup(pkbDispatch, relRef);
    }
    evalSynArgDesc.synInGraph = synInGraph;
    evalSynArgDesc.relRefType = relRef->relType;
    evalSynArgDesc.argOneSynType = relRef->argOneSyn;
    evalSynArgDesc.argTwoSynType = relRef->argTwoSyn;

    assert(pkbDispatch.relRef_eval != NULL);
    // evaluate relRef
    (this->*(pkbDispatch.relRef_eval)) (rTableIdx, relRef, pkbDispatch);
}

void QueryEvaluator::ev_relRef_syn_syn_00_setup(
        EvalPKBDispatch& pkbDispatch, const RelRef *relRef) const
{
    RelRefArgType argOneType =
            designEnt_to_relRefArgType(relRef->argOneSyn);
    RelRefArgType argTwoType =
            designEnt_to_relRefArgType(relRef->argTwoSyn);
    assert(argOneType == RELARG_STRING || argOneType == RELARG_INT);
    assert(argTwoType == RELARG_STRING || argTwoType == RELARG_INT);
    if (argOneType == RELARG_STRING && argTwoType == RELARG_STRING) {
        pkbDispatch.get_all_string_argOne =
                this->pkbd_setup_get_all_string_method(
                        relRef->argOneSyn);
        pkbDispatch.get_all_string_argTwo =
                this->pkbd_setup_get_all_string_method(
                        relRef->argTwoSyn);
        pkbDispatch.get_string_set_argOne_from_string_argTwo =
                this->pkbd_setup_get_1SS_From_2SS(relRef->relType);
        pkbDispatch.get_string_set_argTwo_from_string_argOne =
                this->pkbd_setup_get_2SS_From_1SS(relRef->relType);
        pkbDispatch.relRef_eval =
                &QueryEvaluator::ev_rr_ss_string_string_00_from_argOne;
    } else if (argOneType == RELARG_STRING && argTwoType == RELARG_INT) {
        pkbDispatch.get_all_string_argOne =
                this->pkbd_setup_get_all_string_method(
                        relRef->argOneSyn);
        pkbDispatch.get_all_int_argTwo =
                this->pkbd_setup_get_all_int_method(relRef->argTwoSyn);
        pkbDispatch.get_string_set_argOne_from_int_argTwo =
                this->pkbd_setup_get_1SS_From_2IS(relRef->relType);
        pkbDispatch.get_int_set_argTwo_from_string_argOne =
                this->pkbd_setup_get_2IS_From_1SS(relRef->relType);
        pkbDispatch.relRef_eval =
                &QueryEvaluator::ev_rr_ss_string_int_00_from_argOne;
    } else if (argOneType == RELARG_INT && argTwoType == RELARG_STRING) {
        pkbDispatch.get_all_int_argOne =
                this->pkbd_setup_get_all_int_method(relRef->argOneSyn);
        pkbDispatch.get_all_string_argTwo =
                this->pkbd_setup_get_all_string_method(
                        relRef->argTwoSyn);
        pkbDispatch.get_int_set_argOne_from_string_argTwo =
                this->pkbd_setup_get_1IS_From_2SS(relRef->relType);
        pkbDispatch.get_string_set_argTwo_from_int_argOne =
                this->pkbd_setup_get_2SS_From_1IS(relRef->relType);
        pkbDispatch.relRef_eval =
                &QueryEvaluator::ev_rr_ss_int_string_00_from_argOne;
    } else if (argOneType == RELARG_INT && argTwoType == RELARG_INT) {
        pkbDispatch.get_all_int_argOne =
                this->pkbd_setup_get_all_int_method(relRef->argOneSyn);
        pkbDispatch.get_all_int_argTwo =
                this->pkbd_setup_get_all_int_method(relRef->argTwoSyn);
        pkbDispatch.get_int_set_argOne_from_int_argTwo =
                this->pkbd_setup_get_1IS_From_2IS(relRef->relType);
        pkbDispatch.get_int_set_argTwo_from_int_argOne =
                this->pkbd_setup_get_2IS_From_1IS(relRef->relType);
        pkbDispatch.relRef_eval =
                &QueryEvaluator::ev_rr_ss_int_int_00_from_argOne;
    }
}

void QueryEvaluator::ev_relRef_syn_syn_01_setup(
        EvalPKBDispatch& pkbDispatch, const RelRef *relRef) const
{
    RelRefArgType argOneType =
            designEnt_to_relRefArgType(relRef->argOneSyn);
    RelRefArgType argTwoType =
            designEnt_to_relRefArgType(relRef->argTwoSyn);
    assert(RELARG_INT == argOneType || RELARG_STRING == argOneType);
    assert(RELARG_INT == argTwoType || RELARG_STRING == argTwoType);
    if (RELARG_STRING == argOneType && RELARG_STRING == argTwoType) {
        pkbDispatch.get_string_set_argOne_from_string_argTwo =
                this->pkbd_setup_get_1SS_From_2SS(relRef->relType);
        pkbDispatch.relRef_eval =
                &QueryEvaluator::ev_rr_ss_string_string_01;
    } else if (RELARG_STRING == argOneType && RELARG_INT == argTwoType) {
        pkbDispatch.get_string_set_argOne_from_int_argTwo =
                this->pkbd_setup_get_1SS_From_2IS(relRef->relType);
        pkbDispatch.relRef_eval =
                &QueryEvaluator::ev_rr_ss_string_int_01;
    } else if (RELARG_INT == argOneType && RELARG_STRING == argTwoType) {
        pkbDispatch.get_int_set_argOne_from_string_argTwo =
                this->pkbd_setup_get_1IS_From_2SS(relRef->relType);
        pkbDispatch.relRef_eval =
                &QueryEvaluator::ev_rr_ss_int_string_01;
    } else if (RELARG_INT == argOneType && RELARG_INT == argTwoType) {
        pkbDispatch.get_int_set_argOne_from_int_argTwo =
                this->pkbd_setup_get_1IS_From_2IS(relRef->relType);
        pkbDispatch.relRef_eval =
                &QueryEvaluator::ev_rr_ss_int_int_01;
    }
}

void QueryEvaluator::ev_relRef_syn_syn_10_setup(
        EvalPKBDispatch& pkbDispatch, const RelRef *relRef) const
{
        RelRefArgType argOneType =
            designEnt_to_relRefArgType(relRef->argOneSyn);
    RelRefArgType argTwoType =
            designEnt_to_relRefArgType(relRef->argTwoSyn);
    assert(RELARG_INT == argOneType || RELARG_STRING == argOneType);
    assert(RELARG_INT == argTwoType || RELARG_STRING == argTwoType);
    if (RELARG_STRING == argOneType && RELARG_STRING == argTwoType) {
        pkbDispatch.get_string_set_argTwo_from_string_argOne =
                this->pkbd_setup_get_2SS_From_1SS(relRef->relType);
        pkbDispatch.relRef_eval =
                &QueryEvaluator::ev_rr_ss_string_string_10;
    } else if (RELARG_STRING == argOneType && RELARG_INT == argTwoType) {
        pkbDispatch.get_int_set_argTwo_from_string_argOne =
                this->pkbd_setup_get_2IS_From_1SS(relRef->relType);
        pkbDispatch.relRef_eval =
                &QueryEvaluator::ev_rr_ss_string_int_10;
    } else if (RELARG_INT == argOneType && RELARG_STRING == argTwoType) {
        pkbDispatch.get_string_set_argTwo_from_int_argOne =
                this->pkbd_setup_get_2SS_From_1IS(relRef->relType);
        pkbDispatch.relRef_eval =
                &QueryEvaluator::ev_rr_ss_int_string_10;
    } else if (RELARG_INT == argOneType && RELARG_INT == argTwoType) {
        pkbDispatch.get_int_set_argTwo_from_int_argOne =
                this->pkbd_setup_get_2IS_From_1IS(relRef->relType);
        pkbDispatch.relRef_eval =
                &QueryEvaluator::ev_rr_ss_int_int_10;
    }
}

void QueryEvaluator::ev_relRef_syn_syn_11_22_setup(
        SynInGraph synInGraph, EvalPKBDispatch& pkbDispatch,
        const RelRef *relRef) const
{
    assert(SYN_SYN_11 == synInGraph || SYN_SYN_22 == synInGraph);
    RelRefArgType argOneType =
            designEnt_to_relRefArgType(relRef->argOneSyn);
    RelRefArgType argTwoType =
            designEnt_to_relRefArgType(relRef->argTwoSyn);
    assert(RELARG_INT == argOneType || RELARG_STRING == argOneType);
    assert(RELARG_INT == argTwoType || RELARG_STRING == argTwoType);
    if (RELARG_STRING == argOneType && RELARG_STRING == argTwoType) {
        switch (relRef->relType) {
        case REL_MODIFIES:
            pkbDispatch.f_string_argOne_string_argTwo =
                    &PKB::modifies_query_string_X_string_Y;
            break;
        case REL_USES:
            pkbDispatch.f_string_argOne_string_argTwo =
                    &PKB::uses_query_string_X_string_Y;
            break;
        case REL_CALLS:
            pkbDispatch.f_string_argOne_string_argTwo =
                    &PKB::calls_query_string_X_string_Y;
            break;
        case REL_CALLS_STAR:
            pkbDispatch.f_string_argOne_string_argTwo =
                    &PKB::callsStar_query_string_X_string_Y;
            break;
        default:
            assert(false);
        }
        if (SYN_SYN_11 == synInGraph) {
            pkbDispatch.relRef_eval =
                    &QueryEvaluator::ev_rr_ss_string_string_11;
        } else {
            pkbDispatch.relRef_eval =
                    &QueryEvaluator::ev_rr_ss_string_string_22;
        }
    } else if (RELARG_STRING == argOneType && RELARG_INT == argTwoType) {
        // no Rel has (string,int) arguments
        assert(false);
    } else if (RELARG_INT == argOneType && RELARG_STRING == argTwoType) {
        switch (relRef->relType) {
        case REL_MODIFIES:
            pkbDispatch.f_int_argOne_string_argTwo =
                    &PKB::modifies_query_int_X_string_Y;
            break;
        case REL_USES:
            pkbDispatch.f_int_argOne_string_argTwo =
                    &PKB::uses_query_int_X_string_Y;
            break;
        default:
            assert(false);
        }
        if (SYN_SYN_11 == synInGraph) {
            pkbDispatch.relRef_eval =
                    &QueryEvaluator::ev_rr_ss_int_string_11;
        } else {
            pkbDispatch.relRef_eval =
                    &QueryEvaluator::ev_rr_ss_int_string_22;
        }
    } else if (RELARG_INT == argOneType && RELARG_INT == argTwoType) {
        switch (relRef->relType) {
        case REL_PARENT:
            pkbDispatch.f_int_argOne_int_argTwo =
                    &PKB::parent_query_int_X_int_Y;
            break;
        case REL_PARENT_STAR:
            pkbDispatch.f_int_argOne_int_argTwo =
                    &PKB::parentStar_query_int_X_int_Y;
            break;
        case REL_FOLLOWS:
            pkbDispatch.f_int_argOne_int_argTwo =
                    &PKB::follows_query_int_X_int_Y;
            break;
        case REL_FOLLOWS_STAR:
            pkbDispatch.f_int_argOne_int_argTwo =
                    &PKB::followsStar_query_int_X_int_Y;
            break;
        case REL_NEXT:
            pkbDispatch.f_int_argOne_int_argTwo =
                    &PKB::next_query_int_X_int_Y;
            break;
        case REL_NEXT_STAR:
            pkbDispatch.f_int_argOne_int_argTwo =
                    &PKB::nextStar_query_int_X_int_Y;
            break;
        case REL_AFFECTS:
            pkbDispatch.f_int_argOne_int_argTwo =
                    &PKB::affects_query_int_X_int_Y;
            break;
        case REL_AFFECTS_STAR:
            pkbDispatch.f_int_argOne_int_argTwo =
                    &PKB::affectsStar_query_int_X_int_Y;
            break;
        default:
            assert(false);
        }
        if (SYN_SYN_11 == synInGraph) {
            pkbDispatch.relRef_eval =
                    &QueryEvaluator::ev_rr_ss_int_int_11;
        } else {
            pkbDispatch.relRef_eval =
                    &QueryEvaluator::ev_rr_ss_int_int_22;
        }
    }
}

QueryEvaluator::pkbGetAllStringFn
QueryEvaluator::pkbd_setup_get_all_string_method(DesignEnt ent) const
{
    assert (ent == ENT_PROC || ent == ENT_VAR);
    if (ent == ENT_PROC) {
        return &PKB::get_all_procs;
    } else if (ent == ENT_VAR) {
        return &PKB::get_all_vars;
    }
    return NULL;
}

QueryEvaluator::pkbGetAllIntFn
QueryEvaluator::pkbd_setup_get_all_int_method(DesignEnt ent) const
{
    assert(RELARG_INT == designEnt_to_relRefArgType(ent));
    switch (ent) {
    case ENT_STMTLST:
        return &PKB::get_all_stmtLst;
        break;
    case ENT_STMT:
        return &PKB::get_all_stmt;
        break;
    case ENT_PROGLINE:
        return &PKB::get_all_progline;
        break;
    case ENT_ASSIGN:
        return &PKB::get_all_assign;
        break;
    case ENT_CALL:
        return &PKB::get_all_call;
        break;
    case ENT_IF:
        return &PKB::get_all_if;
        break;
    case ENT_WHILE:
        return &PKB::get_all_while;
        break;
    case ENT_CONST:
        return &PKB::get_all_const;
        break;
    }
}

QueryEvaluator::pkbGet_1SS_From_2SS
QueryEvaluator::pkbd_setup_get_1SS_From_2SS(RelRefType relType) const
{
    switch (relType) {
    case REL_MODIFIES:
        return &PKB::modifies_X_Y_get_string_X_from_string_Y;
        break;
    case REL_USES:
        return &PKB::uses_X_Y_get_string_X_from_string_Y;
        break;
    case REL_CALLS:
        return &PKB::calls_X_Y_get_string_X_from_string_Y;
        break;
    case REL_CALLS_STAR:
        return &PKB::callsStar_X_Y_get_string_X_from_string_Y;
        break;
    default:
        assert(false);
    }
    return NULL;
}

QueryEvaluator::pkbGet_1SS_From_2IS
QueryEvaluator::pkbd_setup_get_1SS_From_2IS(RelRefType relType) const
{
    // no relation has (string,int) arguments
    assert(false);
    return NULL;
}

QueryEvaluator::pkbGet_1IS_From_2SS
QueryEvaluator::pkbd_setup_get_1IS_From_2SS(RelRefType relType) const
{
    switch (relType) {
    case REL_MODIFIES:
        return &PKB::modifies_X_Y_get_int_X_from_string_Y;
        break;
    case REL_USES:
        return &PKB::uses_X_Y_get_int_X_from_string_Y;
        break;
    default:
        assert(false);
    }
    return NULL;
}

QueryEvaluator::pkbGet_1IS_From_2IS
QueryEvaluator::pkbd_setup_get_1IS_From_2IS(RelRefType relType) const
{
    switch (relType) {
    case REL_PARENT:
        return &PKB::parent_X_Y_get_int_X_from_int_Y;
        break;
    case REL_PARENT_STAR:
        return &PKB::parentStar_X_Y_get_int_X_from_int_Y;
        break;
    case REL_FOLLOWS:
        return &PKB::follows_X_Y_get_int_X_from_int_Y;
        break;
    case REL_FOLLOWS_STAR:
        return &PKB::followsStar_X_Y_get_int_X_from_int_Y;
        break;
    case REL_NEXT:
        return &PKB::next_X_Y_get_int_X_from_int_Y;
        break;
    case REL_NEXT_STAR:
        return &PKB::nextStar_X_Y_get_int_X_from_int_Y;
        break;
    case REL_AFFECTS:
        return &PKB::affects_X_Y_get_int_X_from_int_Y;
        break;
    case REL_AFFECTS_STAR:
        return &PKB::affectsStar_X_Y_get_int_X_from_int_Y;
        break;
    default:
        assert(false);
    }
    return NULL;
}

QueryEvaluator::pkbGet_2SS_From_1SS
QueryEvaluator::pkbd_setup_get_2SS_From_1SS(RelRefType relType) const
{
    switch (relType) {
    case REL_MODIFIES:
        return &PKB::modifies_X_Y_get_string_Y_from_string_X;
        break;
    case REL_USES:
        return &PKB::uses_X_Y_get_string_Y_from_string_X;
        break;
    case REL_CALLS:
        return &PKB::calls_X_Y_get_string_Y_from_string_X;
        break;
    case REL_CALLS_STAR:
        return &PKB::callsStar_X_Y_get_string_Y_from_string_X;
        break;
    default:
        assert(false);
    }
    return NULL;
}

QueryEvaluator::pkbGet_2SS_From_1IS
QueryEvaluator::pkbd_setup_get_2SS_From_1IS(RelRefType relType) const
{
    switch (relType) {
    case REL_MODIFIES:
        return &PKB::modifies_X_Y_get_string_Y_from_int_X;
        break;
    case REL_USES:
        return &PKB::uses_X_Y_get_string_Y_from_int_X;
        break;
    default:
        assert(false);
    }
    return NULL;
}

QueryEvaluator::pkbGet_2IS_From_1SS
QueryEvaluator::pkbd_setup_get_2IS_From_1SS(RelRefType relType) const
{
    // no Rel with (string,int) as arguments
    assert(false);
    return NULL;
}

QueryEvaluator::pkbGet_2IS_From_1IS
QueryEvaluator::pkbd_setup_get_2IS_From_1IS(RelRefType relType) const
{
    switch (relType) {
    case REL_PARENT:
        return &PKB::parent_X_Y_get_int_Y_from_int_X;
        break;
    case REL_PARENT_STAR:
        return &PKB::parentStar_X_Y_get_int_Y_from_int_X;
        break;
    case REL_FOLLOWS:
        return &PKB::follows_X_Y_get_int_Y_from_int_X;
        break;
    case REL_FOLLOWS_STAR:
        return &PKB::followsStar_X_Y_get_int_Y_from_int_X;
        break;
    case REL_NEXT:
        return &PKB::next_X_Y_get_int_Y_from_int_X;
        break;
    case REL_NEXT_STAR:
        return &PKB::nextStar_X_Y_get_int_Y_from_int_X;
        break;
    case REL_AFFECTS:
        return &PKB::affects_X_Y_get_int_Y_from_int_X;
        break;
    case REL_AFFECTS_STAR:
        return &PKB::affectsStar_X_Y_get_int_Y_from_int_X;
        break;
    default:
        assert(false);
    }
    return NULL;
}

void QueryEvaluator::ev_rr_ss_string_string_00_from_argOne(
        int rTableIdx, const RelRef *relRef,
        const EvalPKBDispatch& disp)
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
        int rTableIdx, const RelRef *relRef,
        const EvalPKBDispatch& disp)
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
        const RelRef *relRef, const EvalPKBDispatch& disp)
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
        const RelRef *relRef, const EvalPKBDispatch& disp)
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
        const RelRef *relRef, const EvalPKBDispatch& disp)
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
        const RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(NULL != disp.f_string_argOne_string_argTwo);
    assert(NULL != disp.relRef_eval);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    pair<pair<const vector<Record> *, int>,
         pair<const vector<Record> *, int> > pvriPair =
            rTable.syn_22_transaction_begin(relRef->argOneString,
                    relRef->argTwoString);
    const vector<Record>& argOneVec = *(pvriPair.first.first);
    int argOneCol = pvriPair.first.second;
    int nrArgOne = argOneVec.size();
    // Collect inner loop stuff once
    const vector<Record>& argTwoVec = *(pvriPair.second.first);
    int argTwoCol = pvriPair.second.second;
    int nrArgTwo = argTwoVec.size();
    vector<const string *> a2Vec;
    for (int i = 0; i < nrArgTwo; i++) {
        const Record& recTwo = argTwoVec[i];
        const pair<string, int>& pairTwo =
                recTwo.get_column(argTwoCol);
        a2Vec.push_back(&(pairTwo.first));
    }
    for (int i = 0; i < nrArgOne; i++) {
        for (int k = 0; k < nrArgTwo; k++) {
            const Record& recOne = argOneVec[i];
            const pair<string, int>& pairOne =
                    recOne.get_column(argOneCol);
            const string& argOneVal = pairOne.first;
            const string& argTwoVal = *(a2Vec[k]);
            if ((this->pkb->*(disp.f_string_argOne_string_argTwo))
                        (relRef->argOneSyn, argOneVal,
                         relRef->argTwoSyn, argTwoVal)) {
                rTable.syn_22_add_row(i, k);
            }
        }
    }
    rTable.syn_22_transaction_end();
}

// Currently, nothing uses this and it does not seem it will be used
void QueryEvaluator::ev_rr_ss_string_int_00_from_argOne(int rTableIdx,
        const RelRef *relRef, const EvalPKBDispatch& disp)
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
        const RelRef *relRef, const EvalPKBDispatch& disp)
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
        const RelRef *relRef, const EvalPKBDispatch& disp)
{
}

// Currently, nothing uses this and it does not seem it will be used
void QueryEvaluator::ev_rr_ss_string_int_10(int rTableIdx,
        const RelRef *relRef, const EvalPKBDispatch& disp)
{
}

// Currently, nothing uses this and it does not seem it will be used
void QueryEvaluator::ev_rr_ss_string_int_11(int rTableIdx,
        const RelRef *relRef, const EvalPKBDispatch& disp)
{
}

// Currently, nothing uses this and it does not seem it will be used
void QueryEvaluator::ev_rr_ss_string_int_22(int rTableIdx,
        const RelRef *relRef, const EvalPKBDispatch& disp)
{
}

void QueryEvaluator::ev_rr_ss_int_string_00_from_argOne(int rTableIdx,
        const RelRef *relRef, const EvalPKBDispatch& disp)
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
        const RelRef *relRef, const EvalPKBDispatch& disp)
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
        const RelRef *relRef, const EvalPKBDispatch& disp)
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
        const RelRef *relRef, const EvalPKBDispatch& disp)
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
        const RelRef *relRef, const EvalPKBDispatch& disp)
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
        const RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(NULL != disp.f_int_argOne_string_argTwo);
    assert(NULL != disp.relRef_eval);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    pair<pair<const vector<Record> *, int>,
         pair<const vector<Record> *, int> > pvriPair =
            rTable.syn_22_transaction_begin(relRef->argOneString,
                    relRef->argTwoString);
    const vector<Record>& argOneVec = *(pvriPair.first.first);
    int argOneCol = pvriPair.first.second;
    int nrArgOne = argOneVec.size();
    // Collect inner loop stuff once
    const vector<Record>& argTwoVec = *(pvriPair.second.first);
    int argTwoCol = pvriPair.second.second;
    int nrArgTwo = argTwoVec.size();
    vector<const string *> a2Vec;
    for (int i = 0; i < nrArgTwo; i++) {
        const Record& recTwo = argTwoVec[i];
        const pair<string, int>& pairTwo =
                recTwo.get_column(argTwoCol);
        a2Vec.push_back(&(pairTwo.first));
    }
    for (int i = 0; i < nrArgOne; i++) {
        for (int k = 0; k < nrArgTwo; k++) {
            const Record& recOne = argOneVec[i];
            const pair<string, int>& pairOne =
                    recOne.get_column(argOneCol);
            int argOneVal = pairOne.second;
            const string& argTwoVal = *(a2Vec[k]);
            if ((this->pkb->*(disp.f_int_argOne_string_argTwo))
                        (relRef->argOneSyn, argOneVal,
                         relRef->argTwoSyn, argTwoVal)) {
                rTable.syn_22_add_row(i, k);
            }
        }
    }
    rTable.syn_22_transaction_end();
}

void QueryEvaluator::ev_rr_ss_int_int_00_from_argOne(int rTableIdx,
        const RelRef *relRef, const EvalPKBDispatch& disp)
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
        const RelRef *relRef, const EvalPKBDispatch& disp)
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

void QueryEvaluator::ev_rr_ss_int_int_01(int rTableIdx,
        const RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(NULL != disp.get_int_set_argOne_from_int_argTwo);
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
        int argTwoVal = siPair.second;
        set<int> argOneSet =
                (this->pkb->*
                        (disp.get_int_set_argOne_from_int_argTwo))
                                (relRef->argOneSyn, relRef->argTwoSyn,
                                 argTwoVal);
        for (set<int>::const_iterator argOneIt = argOneSet.begin();
                argOneIt != argOneSet.end(); argOneIt++){
            rTable.syn_01_augment_new_row(i, *argOneIt);
        }
    }
    rTable.syn_01_transaction_end();
}

void QueryEvaluator::ev_rr_ss_int_int_10(int rTableIdx,
        const RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(disp.get_int_set_argTwo_from_int_argOne != NULL);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    pair<const vector<Record> *, int> viPair =
            rTable.syn_10_transaction_begin(relRef->argOneString,
                    relRef->argTwoString, RV_INT);
    const vector<Record>& argOneVec = *(viPair.first);
    int nrRecords = argOneVec.size();
    int colIdx = viPair.second;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = argOneVec[i];
        const pair<string, int>& siPair = record.get_column(colIdx);
        int argOneVal = siPair.second;
        set<int> argTwoSet =
                (this->pkb->*(disp.get_int_set_argTwo_from_int_argOne))
                        (relRef->argOneSyn, relRef->argTwoSyn,
                         argOneVal);
        for (set<int>::const_iterator argTwoIt = argTwoSet.begin();
                argTwoIt != argTwoSet.end(); argTwoIt++) {
            rTable.syn_10_augment_new_row(i, *argTwoIt);
        }
    }
    rTable.syn_10_transaction_end();
}

void QueryEvaluator::ev_rr_ss_int_int_11(int rTableIdx,
        const RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(disp.f_int_argOne_int_argTwo != NULL);
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
        int argTwoVal = pairTwo.second;
        if ((this->pkb->*(disp.f_int_argOne_int_argTwo))
                    (relRef->argOneSyn, argOneVal,
                        relRef->argTwoSyn, argTwoVal)) {
            rTable.syn_11_mark_row_ok(i);
        }
    }
    rTable.syn_11_transaction_end();
}

void QueryEvaluator::ev_rr_ss_int_int_22(int rTableIdx,
        const RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(NULL != disp.f_int_argOne_int_argTwo);
    assert(NULL != disp.relRef_eval);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    pair<pair<const vector<Record> *, int>,
         pair<const vector<Record> *, int> > pvriPair =
            rTable.syn_22_transaction_begin(relRef->argOneString,
                    relRef->argTwoString);
    const vector<Record>& argOneVec = *(pvriPair.first.first);
    int argOneCol = pvriPair.first.second;
    int nrArgOne = argOneVec.size();
    // Collect inner loop stuff once
    const vector<Record>& argTwoVec = *(pvriPair.second.first);
    int argTwoCol = pvriPair.second.second;
    int nrArgTwo = argTwoVec.size();
    vector<int> a2Vec;
    for (int i = 0; i < nrArgTwo; i++) {
        const Record& recTwo = argTwoVec[i];
        const pair<string, int>& pairTwo =
                recTwo.get_column(argTwoCol);
        a2Vec.push_back(pairTwo.second);
    }
    for (int i = 0; i < nrArgOne; i++) {
        for (int k = 0; k < nrArgTwo; k++) {
            const Record& recOne = argOneVec[i];
            const pair<string, int>& pairOne =
                    recOne.get_column(argOneCol);
            int argOneVal = pairOne.second;
            int argTwoVal = a2Vec[k];
            if ((this->pkb->*(disp.f_int_argOne_int_argTwo))
                        (relRef->argOneSyn, argOneVal,
                         relRef->argTwoSyn, argTwoVal)) {
                rTable.syn_22_add_row(i, k);
            }
        }
    }
    rTable.syn_22_transaction_end();
}

void QueryEvaluator::ev_relRef_syn_X(int rTableIdx,
        const RelRef *relRef)
{
}

void QueryEvaluator::ev_relRef_X_syn(int rTableIdx,
        const RelRef *relRef)
{
}

void QueryEvaluator::ev_relRef_X_X(int rTableIdx,
        const RelRef *relRef)
{
}

void QueryEvaluator::evaluate_patCl(int rTableIdx,
        const GenericRef *genRef)
{
    const PatCl *patCl =
        dynamic_cast<const PatCl *>(genRef);
    assert(NULL != patCl);
    assert(PATCL_INVALID != patCl->type);
    switch (patCl->type) {
    case PATCL_ASSIGN:
        this->evaluate_patCl_assign(rTableIdx, patCl);
        break;
    case PATCL_IF:
        this->evaluate_patCl_if(rTableIdx, patCl);
        break;
    case PATCL_WHILE:
        this->evaluate_patCl_while(rTableIdx, patCl);
        break;
    }
}

void QueryEvaluator::evaluate_patCl_assign(int rTableIdx,
        const PatCl *patCl)
{
}

void QueryEvaluator::evaluate_patCl_if(int rTableIdx,
        const PatCl *patCl)
{
    assert(PATVARREF_SYN == patCl->varRefType ||
            PATVARREF_STRING == patCl->varRefType ||
            PATVARREF_WILDCARD == patCl->varRefType);
    if (PATVARREF_SYN == patCl->varRefType) {
        this->evaluate_patCl_if_var_syn(rTableIdx, patCl);
    } else if (PATVARREF_STRING == patCl->varRefType) {
        this->evaluate_patCl_if_var_string(rTableIdx, patCl);
    } else if (PATVARREF_WILDCARD == patCl->varRefType) {
        this->evaluate_patCl_if_var_wildcard(rTableIdx, patCl);
    }
}

void QueryEvaluator::evaluate_patCl_if_var_syn(int rTableIdx,
        const PatCl *patCl)
{
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    bool hasIfSyn = rTable.has_synonym(patCl->syn);
    bool hasVarSyn = rTable.has_synonym(patCl->varRefString);
    if (hasIfSyn && hasVarSyn) {
        if (rTable.syn_in_same_table(patCl->syn, patCl->varRefString)) {
            // pattern ifSyn(varSyn,_,_)
            // both in SAME table. This is a 11 transaction
            // For the ifSyn and varSyn in same row, check if varSyn
            // is a control variable of ifSyn. If so, mark as ok.
            this->evaluate_patCl_if_var_syn_11(rTable, patCl);
        } else {
            // pattern ifSyn(varSyn,_,_)
            // both in DIFFERENT table. merge. This is a 22 transaction
            this->evaluate_patCl_if_var_syn_22(rTable, patCl);
        }
    } else if (hasIfSyn) {
        // pattern ifSyn(varSyn,_,_)
        // varSyn is not seen
        // for each ifSyn, get its control variable and
        // augment the row.
        // Make this a 01 transaction using augment_new_row
    } else if (hasVarSyn) {
        // pattern ifSyn(varSyn,_,_)
        // ifSyn is not seen
        // for each varSyn, get the if statement it is a control
        // variable (if any) and augment the row.
        // Make this a 01 transaction using augment_new_row
    } else {
        // pattern ifSyn(varSyn,_,_)
        // both not seen. This is a 00 transaction, but it is
        // advised to get all if stmts, then get their control
        // variable, and add the new row.
    }
}

void QueryEvaluator::evaluate_patCl_if_var_syn_11(ResultsTable &rTable,
        const PatCl *patCl)
{
    pair<const vector<Record> *, pair<int, int> > viiPair =
            rTable.syn_11_transaction_begin(patCl->syn,
                    patCl->varRefString);
    const vector<Record>& records = *(viiPair.first);
    int nrRecords = records.size();
    int ifSynCol = viiPair.second.first;
    int varSynCol = viiPair.second.second;
    for (int i = 0; i < nrRecords; i++) {
        const Record& rec = records[i];
        const pair<string, int>& ifPair = rec.get_column(ifSynCol);
        const pair<string, int>& varPair = rec.get_column(varSynCol);
        int ifStmt = ifPair.second;
        const string& controlVar = varPair.first;
        if (this->pkb->has_control_variable(ENT_IF, ifStmt,
                    controlVar)) {
            rTable.syn_11_mark_row_ok(i);
        }
    }
    rTable.syn_11_transaction_end();
}

void QueryEvaluator::evaluate_patCl_if_var_syn_22(ResultsTable& rTable,
        const PatCl *patCl)
{
    pair<pair<const vector<Record> *, int>,
         pair<const vector<Record> *, int> > vipPair =
            rTable.syn_22_transaction_begin(patCl->syn,
                    patCl->varRefString);
    const vector<Record>& ifSynVec = *(vipPair.first.first);
    int ifSynCol = vipPair.first.second;
    int nrIfSyn = ifSynVec.size();
    // Retrieve contents of inner loop ONCE
    const vector<Record>& controlVarVec = *(vipPair.second.first);
    int controlVarCol = vipPair.second.second;
    int nrControlVar = controlVarVec.size();
    vector<const string *> cVarVec;
    for (int i = 0; i < nrControlVar; i++) {
        const Record& controlVarRecord = controlVarVec[i];
        const pair<string, int>& controlVarPair =
                    controlVarRecord.get_column(controlVarCol);
        cVarVec.push_back(&(controlVarPair.first));
    }
    for (int i = 0; i < nrIfSyn; i++) {
        const Record& ifSynRecord = ifSynVec[i];
        const pair<string, int>& ifSynPair =
                ifSynRecord.get_column(ifSynCol);
        int ifSynVal = ifSynPair.second;
        for (int k = 0; k < nrControlVar; k++) {
            const string& controlVarName = *(cVarVec[k]);
            if (this->pkb->has_control_variable(ENT_IF, ifSynVal,
                        controlVarName)) {
                rTable.syn_22_add_row(i, k);
            }
        }
    }
    rTable.syn_22_transaction_end();
}

void QueryEvaluator::evaluate_patCl_if_var_string(int rTableIdx,
        const PatCl *patCl)
{
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    if (rTable.has_synonym(patCl->syn)) {
        // ifSyn("someVarString",_,_)
        // ifSyn is seen. Use ResultsTable::syn_1_transaction
        // Loop through each ifSyn, then use syn_1_mark_row_ok
        // to mark the ifSyn with "someVarString" as control variable
    } else {
        // ifSyn("someVarString",_,_)
        // ifSyn is NOT seen. Use ResultsTable::syn_0_transaction
        // Retrieve all if stmt. Loop and only syn_0_add_row
        // those with "someVarString" as control variable
    }
}

void QueryEvaluator::evaluate_patCl_if_var_wildcard(int rTableIdx,
        const PatCl *patCl)
{
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    if (rTable.has_synonym(patCl->syn)) {
        // ifSyn(_,_)
        // ifSyn is seen. we dont need to do anything here
    } else {
        // ifSyn(_,_)
        // ifSyn is not seen. grab all if statements and put
        // inside the table. this is a syn_0 transaction
    }
}

void QueryEvaluator::evaluate_patCl_while(int rTableIdx,
        const PatCl *patCl)
{
}