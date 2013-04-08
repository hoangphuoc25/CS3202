#include "QueryEvaluator.h"
#include "Parser.h"

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <fstream>
#include <queue>
#include <set>
#include <pthread.h>

using std::getline;
using std::ifstream;
using std::list;
using std::string;
using std::map;
using std::max;
using std::min;
using std::ofstream;
using std::queue;
using std::set;

struct QEThreadInfo {
    /// the actual thread
    pthread_t thread_;
    /// start component number
    int startIdx_;
    /// end component number, exclusive
    int endIdx_;
    /// total number of partitions/components
    int nrPartitions_;
    /// Pointer to actual partitioned clauses
    std::vector<std::vector<int> > *partitionedClauses_;
    /// Pointer to actual vector of ResultsTable
    std::vector<ResultsTable> *resultsTable_;
    /// PKB
    PKB *pkb_;
    /// QueryInfo
    const QueryInfo *qinfo_;
};

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
      f_string_argOne_smth(NULL),
      f_int_argOne_string_argTwo(NULL),
      f_int_argOne_int_argTwo(NULL),
      f_int_argOne_smth(NULL),
      f_smth_string_argTwo(NULL),
      f_smth_int_argTwo(NULL),
      has_any_int(NULL),
      has_any_string(NULL),
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
    this->f_string_argOne_smth = NULL;
    this->f_int_argOne_string_argTwo = NULL;
    this->f_int_argOne_int_argTwo = NULL;
    this->f_int_argOne_smth = NULL;
    this->f_smth_string_argTwo = NULL;
    this->f_smth_int_argTwo = NULL;
    this->has_any_int = NULL;
    this->has_any_string = NULL;
    this->relRef_eval = NULL;
}
//////////////////////////////////////////////////////////////////////
// Query Evaluator
//////////////////////////////////////////////////////////////////////

const RelRefType QueryEvaluator::EV_SAME_SYN_RELATION_ARR[
                                         EV_SAME_SYN_RELATION_ARR_SZ
                                 ] = {
    REL_NEXT, REL_NEXT_STAR, REL_AFFECTS, REL_AFFECTS_STAR
};

const set<RelRefType> QueryEvaluator::EV_SAME_SYN_RELATION(
        QueryEvaluator::EV_SAME_SYN_RELATION_ARR,
        QueryEvaluator::EV_SAME_SYN_RELATION_ARR +
                EV_SAME_SYN_RELATION_ARR_SZ);

QueryEvaluator::QueryEvaluator():
        pqlParser(), pkb(NULL), resultsProjector(),
        isAlive(true), optMultithreaded_(false),
        maxThreads_(QE_DEFAULT_NR_THREADS),
        graph_synMap(), graph_adjList(), graph_refToVertex(),
        graph_vertexCC(), graph_nrVertexCC(0), graph_isolatedClauses(),
        partitionedClauses(),
        resultsTable()
{
    this->read_config(SPACONFIG_FNAME);
}

QueryEvaluator::QueryEvaluator(const map<string, string>& flags):
        pqlParser(), pkb(NULL), resultsProjector(),
        isAlive(true), optMultithreaded_(false),
        maxThreads_(QE_DEFAULT_NR_THREADS),
        graph_synMap(), graph_adjList(), graph_refToVertex(),
        graph_vertexCC(), graph_nrVertexCC(0), graph_isolatedClauses(),
        partitionedClauses(),
        resultsTable()
{
    this->read_config_from_map(flags);
}

QueryEvaluator::QueryEvaluator(const string& configFname):
        pqlParser(), pkb(NULL), resultsProjector(),
        isAlive(true), optMultithreaded_(false),
        maxThreads_(QE_DEFAULT_NR_THREADS),
        graph_synMap(), graph_adjList(), graph_refToVertex(),
        graph_vertexCC(), graph_nrVertexCC(0), graph_isolatedClauses(),
        partitionedClauses(),
        resultsTable()
{
    this->read_config(configFname);
}

// private
QueryEvaluator::QueryEvaluator(const QueryEvaluator& o) {}

// private
QueryEvaluator& QueryEvaluator::operator=(const QueryEvaluator& o)
{
    return *this;
}

void QueryEvaluator::reset_for_pql_query()
{
    this->isAlive = true;
    this->partitionedClauses.clear();
    this->resultsTable.clear();
}

void QueryEvaluator::reset(const map<string, string>& settings)
{
    this->optMultithreaded_ = false;
    this->maxThreads_ = QE_DEFAULT_NR_THREADS;
    this->read_config_from_map(settings);
    this->reset_for_pql_query();
}

void QueryEvaluator::read_config_from_map(
        const map<string, string>& settings)
{
    ofstream of(TEMP_SPACONFIG_FNAME);
    for (map<string, string>::const_iterator it = settings.begin();
            it != settings.end(); it++) {
        of << it->first << " = " << it->second << std::endl;
    }
    of.close();
    this->read_config(TEMP_SPACONFIG_FNAME);
}

void QueryEvaluator::read_config(const string& configFile)
{
    ifstream infs(configFile);
    string s;
    const char *str;
    char *p, *keyStart, *keyEnd, *valStart, *valEnd;
    while (infs.good()) {
        getline(infs, s);
        str = s.c_str();
        keyStart = (char *)str;
        while (*keyStart && isspace(*keyStart)) {
            *keyStart++ = '\0';
        }
        // skip comment lines
        if ('#' == *keyStart) {
            continue;
        }
        p = (char *) strchr(keyStart, '=');
        if (p) {
            valEnd = (char *)str + strlen(keyStart) - 1;
            *p = '\0';
            valStart = p+1;
            keyEnd = p-1;
            while (keyEnd > keyStart && isspace(*keyEnd)) {
                *keyEnd-- = '\0';
            }
            while (*valStart && isspace(*valStart)) {
                *valStart++ = '\0';
            }
            while (valStart < valEnd && isspace(*valEnd)) {
                *valEnd-- = '\0';
            }
            if (!strcmp(keyStart,  QE_MAXTHREADS_STR)) {
                int x = atoi(valStart);
                this->maxThreads_ = min(QE_MAX_THREADS,
                                            max(x, QE_MIN_THREADS));
            } else if (!strcmp(keyStart, QE_THREADSON_STR)) {
                if (!strcmp(valStart, YES_STR)) {
                    this->optMultithreaded_ = true;
                } else if (!strcmp(valStart, NO_STR)) {
                    this->optMultithreaded_ = false;
                }
            }
        }
    }
    infs.close();
}

bool QueryEvaluator::is_multithreaded() const
{
    return this->optMultithreaded_;
}

int QueryEvaluator::get_maxThreads() const
{
    return this->maxThreads_;
}

void QueryEvaluator::parseSimple(const string& simple)
{
    Parser parser(simple, FROMSTRING);
    parser.init();
    this->pkb = parser.get_pkb();
}

void QueryEvaluator::parseSimple_from_file(const string& fname)
{
    Parser parser(fname, FROMFILE);
    parser.init();
    this->pkb = parser.get_pkb();
}

void QueryEvaluator::evaluate(const string& queryStr,
        list<string>& resultSet)
{
    QueryInfo *qinfo;
    this->reset_for_pql_query();
    this->pqlParser.parse(queryStr, true, true);
    qinfo = this->pqlParser.get_queryinfo();
    resultSet.clear();
    if (!qinfo->is_alive()) {
        return;
    }
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
        if (optMultithreaded_) {
            this->evaluate_parallel(qinfo);
        } else {
            int nrPartitions = this->partitionedClauses.size();
            ClauseType clauseType;
            for (int rTableIdx = 0; rTableIdx < nrPartitions; rTableIdx++) {
                const vector<int>& vec = this->partitionedClauses[rTableIdx];
                int nrClauses = vec.size();
                ResultsTable& rTable = this->resultsTable[rTableIdx];
                for (int k = 0; k < nrClauses && rTable.is_alive(); k++) {
                    int clauseIdx = vec[k];
                    const GenericRef *genericRef =
                            qinfo->get_nth_clause(clauseIdx, &clauseType);
                    assert(INVALID_CLAUSE != clauseType);
                    assert(NULL != genericRef);
                    switch (clauseType) {
                    case SUCHTHAT_CLAUSE:
                        QueryEvaluator::evaluate_relRef(rTable, pkb,
                                genericRef);
                        break;
                    case WITH_CLAUSE:
                        this->evaluate_withClause(rTableIdx, genericRef);
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

void QueryEvaluator::evaluate_parallel(const QueryInfo *qinfo)
{
    int nrPartitions = this->partitionedClauses.size();
    if (0 >= nrPartitions) {
        return;
    }
    int totalThreads =
            ((maxThreads_ > nrPartitions) ? nrPartitions : maxThreads_);
    int rem = nrPartitions % totalThreads;
    int componentsPerThread =
            nrPartitions / totalThreads + ((rem == 0) ? 0 : 1);
    int retVal;
    void *threadRet;
    pthread_attr_t threadAttr;
    retVal = pthread_attr_init(&threadAttr);
    if (retVal) {
        fprintf(stderr, "pthread_attr_init error\n");
        exit(1);
    }
    struct QEThreadInfo *qeThreads;
    qeThreads = (struct QEThreadInfo *)calloc(totalThreads,
                        sizeof(struct QEThreadInfo));
    if (!qeThreads) {
        fprintf(stderr, "evaluate_parallel: "
                "Fail to allocate memory for threads");
        exit(1);
    }
    // initialize data structures
    for (int i = 0; i < totalThreads; i++) {
        qeThreads[i].startIdx_ = i * componentsPerThread;
        qeThreads[i].endIdx_ = (i+1) * componentsPerThread;
        if (qeThreads[i].endIdx_ > nrPartitions) {
            qeThreads[i].endIdx_ = nrPartitions;
        }
        qeThreads[i].nrPartitions_ = nrPartitions;
        qeThreads[i].partitionedClauses_ = &(this->partitionedClauses);
        qeThreads[i].resultsTable_ = &(this->resultsTable);
        qeThreads[i].pkb_ = this->pkb;
        qeThreads[i].qinfo_ = qinfo;
    }
    // start threading
    for (int i = 0; i < totalThreads; i++) {
        pthread_create(&qeThreads[i].thread_, &threadAttr,
                &thread_evaluate, &qeThreads[i]);
    }
    // join
    for (int i = 0; i < totalThreads; i++) {
        pthread_join(qeThreads[i].thread_, &threadRet);
    }
    for (int i = 0; i < nrPartitions; i++) {
        this->isAlive = this->isAlive && this->resultsTable[i].is_alive();
    }
    free(qeThreads);
}

void * __cdecl thread_evaluate(void *qetInfo)
{
    struct QEThreadInfo *threadInfo = (struct QEThreadInfo *)qetInfo;
    const QueryInfo *qinfo = threadInfo->qinfo_;
    PKB *pkb = threadInfo->pkb_;
    ClauseType clauseType;
    for (int i = threadInfo->startIdx_; i < threadInfo->endIdx_; i++) {
        // TODO: Reorder queries here
        const vector<int>& vec =
                (*(threadInfo->partitionedClauses_))[i];
        int nrClauses = vec.size();
        ResultsTable& rTable = (*threadInfo->resultsTable_)[i];
        for (int k = 0; k < nrClauses && rTable.is_alive(); k++) {
            int clauseIdx = vec[k];
            const GenericRef *genericRef =
                    qinfo->get_nth_clause(clauseIdx, &clauseType);
            assert(INVALID_CLAUSE != clauseType);
            assert(NULL != genericRef);
            switch (clauseType) {
            case SUCHTHAT_CLAUSE:
                QueryEvaluator::evaluate_relRef(rTable, pkb, genericRef);
                break;
            case WITH_CLAUSE:
                //this->evaluate_withClause(rTableIdx, genericRef);
                break;
            case PATTERN_CLAUSE:
                //this->evaluate_patCl(rTableIdx, genericRef);
                break;
            }
        }
        if (!rTable.is_alive()) {
            break;
        }
    }
    return NULL;
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
            this->partition_process_withClause(i, genericRef);
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

void QueryEvaluator::partition_process_withClause(int clauseIdx,
        const GenericRef *genRef)
{
    const WithClause *withClause =
        dynamic_cast<const WithClause *>(genRef);
    assert(NULL != withClause);
    // LHS of WithClause _must_ be AttrRef
    assert(REF_ATTRREF == withClause->leftRef.refType);
    assert(REF_INVALID != withClause->rightRef.refType);
    if (REF_ATTRREF == withClause->leftRef.refType &&
            REF_ATTRREF == withClause->rightRef.refType) {
        this->partition_add_edge(clauseIdx,
                withClause->leftRef.refStringVal,
                withClause->rightRef.refStringVal);
    } else if (REF_ATTRREF == withClause->leftRef.refType) {
        this->partition_add_vertex(clauseIdx,
                withClause->leftRef.refStringVal);
    } else {
        assert(false);
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
    // with clause can NEVER be isolated
    // with clause with 2 concrete args is either tautology or will
    // cause query to be false, handled in QueryInfo::add_withClause
    assert(WITH_CLAUSE != clauseType);
    switch (clauseType) {
    case SUCHTHAT_CLAUSE:
        return this->ev_isolated_relation_clause(genericRef);
        break;
    default:
        assert(false);
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
        return this->pkb->uses_query_string_X_string_Y(ENT_PROC,
                       relRef->argOneString, ENT_VAR,
                       relRef->argTwoString);
        break;
    case REL_CALLS:
        return this->pkb->calls_query_string_X_string_Y(ENT_PROC,
                       relRef->argOneString, ENT_PROC,
                       relRef->argTwoString);
        break;
    case REL_CALLS_STAR:
        return this->pkb->callsStar_query_string_X_string_Y(ENT_PROC,
                       relRef->argOneString, ENT_PROC,
                       relRef->argTwoString);
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
        return this->pkb->uses_X_Y_string_X_smth(ENT_PROC,
                       relRef->argOneString);
        break;
    case REL_CALLS:
        return this->pkb->calls_X_Y_string_X_smth(ENT_PROC,
                       relRef->argOneString);
        break;
    case REL_CALLS_STAR:
        return this->pkb->calls_X_Y_string_X_smth(ENT_PROC,
                       relRef->argOneString);
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
        return this->pkb->uses_query_int_X_string_Y(ENT_STMT,
                       relRef->argOneInt, ENT_VAR, relRef->argTwoString);
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
        return this->pkb->parent_query_int_X_int_Y(ENT_STMT,
                       relRef->argOneInt, ENT_STMT, relRef->argTwoInt);
        break;
    case REL_PARENT_STAR:
        return this->pkb->parentStar_query_int_X_int_Y(ENT_STMT,
                       relRef->argOneInt, ENT_STMT, relRef->argTwoInt);
        break;
    case REL_FOLLOWS:
        return this->pkb->follows_query_int_X_int_Y(ENT_STMT,
                       relRef->argOneInt, ENT_STMT, relRef->argTwoInt);
        break;
    case REL_FOLLOWS_STAR:
        return this->pkb->followsStar_query_int_X_int_Y(ENT_STMT,
                       relRef->argOneInt, ENT_STMT, relRef->argTwoInt);
        break;
    case REL_NEXT:
        return this->pkb->next_query_int_X_int_Y(ENT_STMT,
                       relRef->argOneInt, ENT_STMT, relRef->argTwoInt);
        break;
    case REL_NEXT_STAR:
        return this->pkb->nextStar_query_int_X_int_Y(ENT_STMT,
                       relRef->argOneInt, ENT_STMT, relRef->argTwoInt);
        break;
    case REL_AFFECTS:
        return this->pkb->affects_query_int_X_int_Y(ENT_ASSIGN,
                       relRef->argOneInt, ENT_ASSIGN, relRef->argTwoInt);
        break;
    case REL_AFFECTS_STAR:
        return this->pkb->affectsStar_query_int_X_int_Y(ENT_ASSIGN,
                       relRef->argOneInt, ENT_ASSIGN, relRef->argTwoInt);
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
        return this->pkb->uses_X_Y_int_X_smth(ENT_STMT,
                       relRef->argOneInt);
        break;
    case REL_PARENT:
        return this->pkb->parent_X_Y_int_X_smth(ENT_STMT,
                       relRef->argOneInt);
        break;
    case REL_PARENT_STAR:
        return this->pkb->parentStar_X_Y_int_X_smth(ENT_STMT,
                       relRef->argOneInt);
        break;
    case REL_FOLLOWS:
        return this->pkb->follows_X_Y_int_X_smth(ENT_STMT,
                       relRef->argOneInt);
        break;
    case REL_FOLLOWS_STAR:
        return this->pkb->followsStar_X_Y_int_X_smth(ENT_STMT,
                       relRef->argOneInt);
        break;
    case REL_NEXT:
        return this->pkb->next_X_Y_int_X_smth(ENT_STMT,
                       relRef->argOneInt);
        break;
    case REL_NEXT_STAR:
        return this->pkb->nextStar_X_Y_int_X_smth(ENT_STMT,
                       relRef->argOneInt);
        break;
    case REL_AFFECTS:
        return this->pkb->affects_X_Y_int_X_smth(ENT_ASSIGN,
                       relRef->argOneInt);
        break;
    case REL_AFFECTS_STAR:
        return this->pkb->affectsStar_X_Y_int_X_smth(ENT_ASSIGN,
                       relRef->argOneInt);
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
        return this->pkb->uses_X_Y_smth_string_Y(ENT_VAR,
                       relRef->argTwoString);
        break;
    case REL_CALLS:
        return this->pkb->calls_X_Y_smth_string_Y(ENT_PROC,
                       relRef->argTwoString);
        break;
    case REL_CALLS_STAR:
        return this->pkb->callsStar_X_Y_smth_string_Y(ENT_PROC,
                       relRef->argTwoString);
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
        this->pkb->parent_X_Y_smth_int_Y(ENT_STMT, relRef->argTwoInt);
        break;
    case REL_PARENT_STAR:
        this->pkb->parentStar_X_Y_smth_int_Y(ENT_STMT, relRef->argTwoInt);
        break;
    case REL_FOLLOWS:
        this->pkb->follows_X_Y_smth_int_Y(ENT_STMT, relRef->argTwoInt);
        break;
    case REL_FOLLOWS_STAR:
        this->pkb->followsStar_X_Y_smth_int_Y(ENT_STMT, relRef->argTwoInt);
        break;
    case REL_NEXT:
        this->pkb->next_X_Y_smth_int_Y(ENT_STMT, relRef->argTwoInt);
        break;
    case REL_NEXT_STAR:
        this->pkb->nextStar_X_Y_smth_int_Y(ENT_STMT, relRef->argTwoInt);
        break;
    case REL_AFFECTS:
        this->pkb->affects_X_Y_smth_int_Y(ENT_ASSIGN, relRef->argTwoInt);
        break;
    case REL_AFFECTS_STAR:
        this->pkb->affectsStar_X_Y_smth_int_Y(ENT_ASSIGN, relRef->argTwoInt);
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
        return this->pkb->uses_X_Y_smth_smth();
        break;
    case REL_CALLS:
    case REL_CALLS_STAR:
        return this->pkb->has_any_call();
        break;
    case REL_PARENT:
        return this->pkb->has_any_ent(ENT_WHILE) ||
                this->pkb->has_any_ent(ENT_IF);
        break;
    case REL_PARENT_STAR:
        return this->pkb->has_any_ent(ENT_WHILE) ||
                this->pkb->has_any_ent(ENT_IF);
        break;
    case REL_FOLLOWS:
    case REL_FOLLOWS_STAR:
        return this->pkb->has_any_follows();
        break;
    case REL_NEXT:
    case REL_NEXT_STAR:
        return this->pkb->has_any_next();
        break;
    case REL_AFFECTS:
    case REL_AFFECTS_STAR:
        return this->pkb->has_any_affects();
        break;
    }
    assert(false);
    return false;
}

void __cdecl QueryEvaluator::evaluate_relRef(ResultsTable& rTable,
        PKB *pkb, const GenericRef *genRef)
{
    const RelRef *relRef =
        dynamic_cast<const RelRef *>(genRef);
    assert(NULL != relRef);
    if (relRef->argOneType == RELARG_SYN &&
            relRef->argTwoType == RELARG_SYN) {
        QueryEvaluator::ev_relRef_syn_syn(rTable, pkb, relRef);
    } else if (relRef->argOneType == RELARG_SYN) {
        QueryEvaluator::ev_relRef_syn_X(rTable, pkb, relRef);
    } else if (relRef->argTwoType == RELARG_SYN) {
        QueryEvaluator::ev_relRef_X_syn(rTable, pkb, relRef);
    } else {
        // isolated clauses should no longer be evaluated here
        assert(false);
    }
}

void __cdecl QueryEvaluator::ev_relRef_syn_syn(ResultsTable& rTable,
        PKB *pkb, const RelRef *relRef)
{
    enum SynInGraph synInGraph = SYN_ARGS_INVALID;
    EvalSynArgDesc evalSynArgDesc;
    EvalPKBDispatch pkbDispatch;
    if (rTable.has_synonym(relRef->argOneString) &&
            rTable.has_synonym(relRef->argTwoString)) {
        bool setupDone = false;
        if (rTable.syn_in_same_table(relRef->argOneString,
                relRef->argTwoString)) {
            // handle case of same synonym argument
            // TODO: We can simplify some of these to false
            //       at the parsing phase
            if (0 == relRef->argOneString.compare(
                             relRef->argTwoString)) {
                QueryEvaluator::ev_relRef_syn_syn_1_setup(pkbDispatch,
                        relRef);
                setupDone = true;
            } else {
                // different synonym arguments, 11 case
                synInGraph = SYN_SYN_11;
            }
        } else {
            synInGraph = SYN_SYN_22;
        }
        // else different synonyms in different table, 22 case
        if (!setupDone) {
            QueryEvaluator::ev_relRef_syn_syn_11_22_setup(synInGraph,
                    pkbDispatch, relRef);
        }
    } else if (rTable.has_synonym(relRef->argOneString)) {
        synInGraph = SYN_SYN_10;
        QueryEvaluator::ev_relRef_syn_syn_10_setup(pkbDispatch, relRef);
    } else if (rTable.has_synonym(relRef->argTwoString)) {
        synInGraph = SYN_SYN_01;
        QueryEvaluator::ev_relRef_syn_syn_01_setup(pkbDispatch, relRef);
    } else {
        synInGraph = SYN_SYN_00;
        // TODO: We can simplify some of these to false
        //       at the parsing phase
        if (0 == relRef->argOneString.compare(
                         relRef->argTwoString)) {
            // both synonym arguments are same and not seen
            QueryEvaluator::ev_relRef_syn_syn_0_setup(pkbDispatch,
                    relRef);
        } else {
            // both synonym arguments different and seen
            QueryEvaluator::ev_relRef_syn_syn_00_setup(pkbDispatch,
                    relRef);
        }
    }
    evalSynArgDesc.synInGraph = synInGraph;
    evalSynArgDesc.relRefType = relRef->relType;
    evalSynArgDesc.argOneSynType = relRef->argOneSyn;
    evalSynArgDesc.argTwoSynType = relRef->argTwoSyn;

    assert(pkbDispatch.relRef_eval != NULL);
    // evaluate relRef
    (pkbDispatch.relRef_eval)(rTable, pkb, relRef, pkbDispatch);
}

void __cdecl QueryEvaluator::ev_relRef_syn_syn_0_setup(
        EvalPKBDispatch& pkbDispatch, const RelRef *relRef)
{
    assert(0 == relRef->argOneString.compare(relRef->argTwoString));
    assert(RELARG_INVALID != relRef->argOneType);
    assert(RELARG_INVALID != relRef->argTwoType);
    // valid type
    assert(QueryEvaluator::EV_SAME_SYN_RELATION.end() !=
                   QueryEvaluator::EV_SAME_SYN_RELATION.find(
                           relRef->relType));
    assert(relRef->argOneType == relRef->argTwoType);
    RelRefArgType argType =
            designEnt_to_relRefArgType(relRef->argOneSyn);
    assert(RELARG_INT == argType);
    pkbDispatch.get_all_int_argOne =
            QueryEvaluator::pkbd_setup_get_all_int_method(
                    relRef->argOneSyn);
    switch (relRef->relType) {
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
    }
    pkbDispatch.relRef_eval =
            &QueryEvaluator::ev_rr_ss_int_int_0;
}

void __cdecl QueryEvaluator::ev_relRef_syn_syn_1_setup(
        EvalPKBDispatch& pkbDispatch, const RelRef *relRef)
{
    assert(0 == relRef->argOneString.compare(relRef->argTwoString));
    assert(RELARG_INVALID != relRef->argOneType);
    assert(RELARG_INVALID != relRef->argTwoType);
    // valid type
    assert(QueryEvaluator::EV_SAME_SYN_RELATION.end() !=
                   QueryEvaluator::EV_SAME_SYN_RELATION.find(
                           relRef->relType));
    assert(relRef->argOneType == relRef->argTwoType);
    RelRefArgType argType =
            designEnt_to_relRefArgType(relRef->argOneSyn);
    assert(RELARG_INT == argType);
    switch (relRef->relType) {
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
    }
    pkbDispatch.relRef_eval =
            &QueryEvaluator::ev_rr_ss_int_int_1;
}

void __cdecl QueryEvaluator::ev_relRef_syn_syn_00_setup(
        EvalPKBDispatch& pkbDispatch, const RelRef *relRef)
{
    RelRefArgType argOneType =
            designEnt_to_relRefArgType(relRef->argOneSyn);
    RelRefArgType argTwoType =
            designEnt_to_relRefArgType(relRef->argTwoSyn);
    assert(argOneType == RELARG_STRING || argOneType == RELARG_INT);
    assert(argTwoType == RELARG_STRING || argTwoType == RELARG_INT);
    if (argOneType == RELARG_STRING && argTwoType == RELARG_STRING) {
        pkbDispatch.get_all_string_argOne =
                QueryEvaluator::pkbd_setup_get_all_string_method(
                        relRef->argOneSyn);
        pkbDispatch.get_all_string_argTwo =
                QueryEvaluator::pkbd_setup_get_all_string_method(
                        relRef->argTwoSyn);
        pkbDispatch.get_string_set_argOne_from_string_argTwo =
                QueryEvaluator::pkbd_setup_get_1SS_From_2SS(
                        relRef->relType);
        pkbDispatch.get_string_set_argTwo_from_string_argOne =
                QueryEvaluator::pkbd_setup_get_2SS_From_1SS(
                        relRef->relType);
        pkbDispatch.relRef_eval =
                &QueryEvaluator::ev_rr_ss_string_string_00_from_argOne;
    } else if (argOneType == RELARG_STRING && argTwoType == RELARG_INT) {
        pkbDispatch.get_all_string_argOne =
                QueryEvaluator::pkbd_setup_get_all_string_method(
                        relRef->argOneSyn);
        pkbDispatch.get_all_int_argTwo =
                QueryEvaluator::pkbd_setup_get_all_int_method(
                        relRef->argTwoSyn);
        pkbDispatch.get_string_set_argOne_from_int_argTwo =
                QueryEvaluator::pkbd_setup_get_1SS_From_2IS(
                        relRef->relType);
        pkbDispatch.get_int_set_argTwo_from_string_argOne =
                QueryEvaluator::pkbd_setup_get_2IS_From_1SS(
                        relRef->relType);
        pkbDispatch.relRef_eval =
                &QueryEvaluator::ev_rr_ss_string_int_00_from_argOne;
    } else if (argOneType == RELARG_INT && argTwoType == RELARG_STRING) {
        pkbDispatch.get_all_int_argOne =
                QueryEvaluator::pkbd_setup_get_all_int_method(
                        relRef->argOneSyn);
        pkbDispatch.get_all_string_argTwo =
                QueryEvaluator::pkbd_setup_get_all_string_method(
                        relRef->argTwoSyn);
        pkbDispatch.get_int_set_argOne_from_string_argTwo =
                QueryEvaluator::pkbd_setup_get_1IS_From_2SS(
                        relRef->relType);
        pkbDispatch.get_string_set_argTwo_from_int_argOne =
                QueryEvaluator::pkbd_setup_get_2SS_From_1IS(
                        relRef->relType);
        pkbDispatch.relRef_eval =
                &QueryEvaluator::ev_rr_ss_int_string_00_from_argOne;
    } else if (argOneType == RELARG_INT && argTwoType == RELARG_INT) {
        pkbDispatch.get_all_int_argOne =
                QueryEvaluator::pkbd_setup_get_all_int_method(
                        relRef->argOneSyn);
        pkbDispatch.get_all_int_argTwo =
                QueryEvaluator::pkbd_setup_get_all_int_method(
                        relRef->argTwoSyn);
        pkbDispatch.get_int_set_argOne_from_int_argTwo =
                QueryEvaluator::pkbd_setup_get_1IS_From_2IS(
                        relRef->relType);
        pkbDispatch.get_int_set_argTwo_from_int_argOne =
                QueryEvaluator::pkbd_setup_get_2IS_From_1IS(
                        relRef->relType);
        pkbDispatch.relRef_eval =
                &QueryEvaluator::ev_rr_ss_int_int_00_from_argOne;
    }
}

void __cdecl QueryEvaluator::ev_relRef_syn_syn_01_setup(
        EvalPKBDispatch& pkbDispatch, const RelRef *relRef)
{
    RelRefArgType argOneType =
            designEnt_to_relRefArgType(relRef->argOneSyn);
    RelRefArgType argTwoType =
            designEnt_to_relRefArgType(relRef->argTwoSyn);
    assert(RELARG_INT == argOneType || RELARG_STRING == argOneType);
    assert(RELARG_INT == argTwoType || RELARG_STRING == argTwoType);
    if (RELARG_STRING == argOneType && RELARG_STRING == argTwoType) {
        pkbDispatch.get_string_set_argOne_from_string_argTwo =
                QueryEvaluator::pkbd_setup_get_1SS_From_2SS(
                        relRef->relType);
        pkbDispatch.relRef_eval =
                &QueryEvaluator::ev_rr_ss_string_string_01;
    } else if (RELARG_STRING == argOneType && RELARG_INT == argTwoType) {
        pkbDispatch.get_string_set_argOne_from_int_argTwo =
                QueryEvaluator::pkbd_setup_get_1SS_From_2IS(
                        relRef->relType);
        pkbDispatch.relRef_eval =
                &QueryEvaluator::ev_rr_ss_string_int_01;
    } else if (RELARG_INT == argOneType && RELARG_STRING == argTwoType) {
        pkbDispatch.get_int_set_argOne_from_string_argTwo =
                QueryEvaluator::pkbd_setup_get_1IS_From_2SS(
                        relRef->relType);
        pkbDispatch.relRef_eval =
                &QueryEvaluator::ev_rr_ss_int_string_01;
    } else if (RELARG_INT == argOneType && RELARG_INT == argTwoType) {
        pkbDispatch.get_int_set_argOne_from_int_argTwo =
                QueryEvaluator::pkbd_setup_get_1IS_From_2IS(
                        relRef->relType);
        pkbDispatch.relRef_eval =
                &QueryEvaluator::ev_rr_ss_int_int_01;
    }
}

void __cdecl QueryEvaluator::ev_relRef_syn_syn_10_setup(
        EvalPKBDispatch& pkbDispatch, const RelRef *relRef)
{
    RelRefArgType argOneType =
            designEnt_to_relRefArgType(relRef->argOneSyn);
    RelRefArgType argTwoType =
            designEnt_to_relRefArgType(relRef->argTwoSyn);
    assert(RELARG_INT == argOneType || RELARG_STRING == argOneType);
    assert(RELARG_INT == argTwoType || RELARG_STRING == argTwoType);
    if (RELARG_STRING == argOneType && RELARG_STRING == argTwoType) {
        pkbDispatch.get_string_set_argTwo_from_string_argOne =
                QueryEvaluator::pkbd_setup_get_2SS_From_1SS(
                        relRef->relType);
        pkbDispatch.relRef_eval =
                &QueryEvaluator::ev_rr_ss_string_string_10;
    } else if (RELARG_STRING == argOneType && RELARG_INT == argTwoType) {
        pkbDispatch.get_int_set_argTwo_from_string_argOne =
                QueryEvaluator::pkbd_setup_get_2IS_From_1SS(
                        relRef->relType);
        pkbDispatch.relRef_eval =
                &QueryEvaluator::ev_rr_ss_string_int_10;
    } else if (RELARG_INT == argOneType && RELARG_STRING == argTwoType) {
        pkbDispatch.get_string_set_argTwo_from_int_argOne =
                QueryEvaluator::pkbd_setup_get_2SS_From_1IS(
                        relRef->relType);
        pkbDispatch.relRef_eval =
                &QueryEvaluator::ev_rr_ss_int_string_10;
    } else if (RELARG_INT == argOneType && RELARG_INT == argTwoType) {
        pkbDispatch.get_int_set_argTwo_from_int_argOne =
                QueryEvaluator::pkbd_setup_get_2IS_From_1IS(
                        relRef->relType);
        pkbDispatch.relRef_eval =
                &QueryEvaluator::ev_rr_ss_int_int_10;
    }
}

void __cdecl QueryEvaluator::ev_relRef_syn_syn_11_22_setup(
        SynInGraph synInGraph, EvalPKBDispatch& pkbDispatch,
        const RelRef *relRef)
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
__cdecl QueryEvaluator::pkbd_setup_get_all_string_method(DesignEnt ent)
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
__cdecl QueryEvaluator::pkbd_setup_get_all_int_method(DesignEnt ent)
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
__cdecl QueryEvaluator::pkbd_setup_get_1SS_From_2SS(RelRefType relType)
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
__cdecl QueryEvaluator::pkbd_setup_get_1SS_From_2IS(RelRefType relType)
{
    // no relation has (string,int) arguments
    assert(false);
    return NULL;
}

QueryEvaluator::pkbGet_1IS_From_2SS
__cdecl QueryEvaluator::pkbd_setup_get_1IS_From_2SS(RelRefType relType)
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
__cdecl QueryEvaluator::pkbd_setup_get_1IS_From_2IS(RelRefType relType)
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
__cdecl QueryEvaluator::pkbd_setup_get_2SS_From_1SS(RelRefType relType)
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
__cdecl QueryEvaluator::pkbd_setup_get_2SS_From_1IS(RelRefType relType)
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
__cdecl QueryEvaluator::pkbd_setup_get_2IS_From_1SS(RelRefType relType)
{
    // no Rel with (string,int) as arguments
    assert(false);
    return NULL;
}

QueryEvaluator::pkbGet_2IS_From_1IS
__cdecl QueryEvaluator::pkbd_setup_get_2IS_From_1IS(RelRefType relType)
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

void __cdecl QueryEvaluator::ev_rr_ss_string_string_00_from_argOne(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
        const EvalPKBDispatch& disp)
{
    assert(disp.get_all_string_argOne != NULL);
    assert(disp.get_string_set_argTwo_from_string_argOne != NULL);
    set<string> argOneSet = (pkb->*(disp.get_all_string_argOne))();
    rTable.syn_00_transaction_begin(relRef->argOneString, RV_STRING,
            relRef->argTwoString, RV_STRING);
    for (set<string>::const_iterator it = argOneSet.begin();
            it != argOneSet.end(); it++) {
        set<string> argTwoSet =
                (pkb->*(disp.get_string_set_argTwo_from_string_argOne))
                    (relRef->argOneSyn, relRef->argTwoSyn, *it);
        for (set<string>::const_iterator kt = argTwoSet.begin();
                kt != argTwoSet.end(); kt++) {
            rTable.syn_00_add_row(*it, *kt);
        }
    }
    rTable.syn_00_transaction_end();
}

// Currently, nothing uses this and it does not seem it will be used
void __cdecl QueryEvaluator::ev_rr_ss_string_string_00_from_argTwo(
        ResultsTable &rTable, PKB *pkb, const RelRef *relRef,
        const EvalPKBDispatch& disp)
{
    assert(disp.get_all_string_argTwo != NULL);
    assert(disp.get_string_set_argOne_from_string_argTwo != NULL);
    set<string> argTwoSet = (pkb->*(disp.get_all_string_argTwo))();
    rTable.syn_00_transaction_begin(relRef->argOneString, RV_STRING,
            relRef->argTwoString, RV_STRING);
    for (set<string>::const_iterator it = argTwoSet.begin();
            it != argTwoSet.end(); it++) {
        set<string> argOneSet =
                (pkb->*
                    (disp.get_string_set_argOne_from_string_argTwo))
                        (relRef->argOneSyn, relRef->argTwoSyn, *it);
        for (set<string>::const_iterator kt = argOneSet.begin();
                kt != argOneSet.end(); kt++) {
            rTable.syn_00_add_row(*kt, *it);
        }
    }
    rTable.syn_00_transaction_end();
}

void __cdecl QueryEvaluator::ev_rr_ss_string_string_01(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
        const EvalPKBDispatch& disp)
{
    assert(disp.get_string_set_argOne_from_string_argTwo != NULL);
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
            (pkb->*(disp.get_string_set_argOne_from_string_argTwo))
                    (relRef->argOneSyn, relRef->argTwoSyn, argTwoVal);
        for (set<string>::const_iterator argOneIt = argOneSet.begin();
                argOneIt != argOneSet.end(); argOneIt++) {
            rTable.syn_01_augment_new_row(i, *argOneIt);
        }
    }
    rTable.syn_01_transaction_end();
}

void __cdecl QueryEvaluator::ev_rr_ss_string_string_10(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
        const EvalPKBDispatch& disp)
{
    assert(disp.get_string_set_argTwo_from_string_argOne != NULL);
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
                (pkb->*(disp.get_string_set_argTwo_from_string_argOne))
                        (relRef->argOneSyn, relRef->argTwoSyn, argOneVal);
        for (set<string>::const_iterator argTwoIt = argTwoSet.begin();
                argTwoIt != argTwoSet.end(); argTwoIt++) {
            rTable.syn_10_augment_new_row(i, *argTwoIt);
        }
    }
    rTable.syn_10_transaction_end();
}

void __cdecl QueryEvaluator::ev_rr_ss_string_string_11(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
        const EvalPKBDispatch& disp)
{
    assert(disp.f_string_argOne_string_argTwo != NULL);
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
        if ((pkb->*(disp.f_string_argOne_string_argTwo))
                        (relRef->argOneSyn, argOneVal,
                         relRef->argTwoSyn, argTwoVal)) {
            rTable.syn_11_mark_row_ok(i);
        }
    }
    rTable.syn_11_transaction_end();
}

void __cdecl QueryEvaluator::ev_rr_ss_string_string_22(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
        const EvalPKBDispatch& disp)
{
    assert(NULL != disp.f_string_argOne_string_argTwo);
    assert(NULL != disp.relRef_eval);
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
            if ((pkb->*(disp.f_string_argOne_string_argTwo))
                        (relRef->argOneSyn, argOneVal,
                         relRef->argTwoSyn, argTwoVal)) {
                rTable.syn_22_add_row(i, k);
            }
        }
    }
    rTable.syn_22_transaction_end();
}

// Currently, nothing uses this and it does not seem it will be used
void __cdecl QueryEvaluator::ev_rr_ss_string_int_00_from_argOne(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
        const EvalPKBDispatch& disp)
{
    // fail immediately
    assert(false);
    assert(disp.get_all_string_argOne != NULL);
    assert(disp.get_int_set_argTwo_from_string_argOne != NULL);
    rTable.syn_00_transaction_begin(relRef->argOneString, RV_STRING,
            relRef->argOneString, RV_INT);
    set<string> argOneSet = (pkb->*(disp.get_all_string_argOne))();
    for (set<string>::const_iterator it = argOneSet.begin();
            it != argOneSet.end(); it++) {
        set<int> argTwoSet =
            (pkb->*(disp.get_int_set_argTwo_from_string_argOne))
                    (relRef->argOneSyn, relRef->argTwoSyn, *it);
        for (set<int>::const_iterator kt = argTwoSet.begin();
                kt != argTwoSet.end(); kt++) {
            rTable.syn_00_add_row(*it, *kt);
        }
    }
    rTable.syn_00_transaction_end();
}

// Currently, nothing uses this and it does not seem it will be used
void __cdecl QueryEvaluator::ev_rr_ss_string_int_00_from_argTwo(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
        const EvalPKBDispatch& disp)
{
    // fail immediately
    assert(false);
    assert(disp.get_all_int_argTwo != NULL);
    assert(disp.get_string_set_argOne_from_int_argTwo != NULL);
    rTable.syn_00_transaction_begin(relRef->argOneString, RV_STRING,
            relRef->argOneString, RV_INT);
    set<int> argTwoSet = (pkb->*(disp.get_all_int_argTwo))();
    for (set<int>::const_iterator it = argTwoSet.begin();
            it != argTwoSet.end(); it++) {
        set<string> argOneSet =
            (pkb->*(disp.get_string_set_argOne_from_int_argTwo))
                    (relRef->argOneSyn, relRef->argTwoSyn, *it);
        for (set<string>::const_iterator kt = argOneSet.begin();
                kt != argOneSet.end(); kt++) {
            rTable.syn_00_add_row(*kt, *it);
        }
    }
    rTable.syn_00_transaction_end();
}

// Currently, nothing uses this and it does not seem it will be used
void __cdecl QueryEvaluator::ev_rr_ss_string_int_01(ResultsTable& rTable,
        PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp)
{
    // fail immediately
    assert(false);
}

// Currently, nothing uses this and it does not seem it will be used
void __cdecl QueryEvaluator::ev_rr_ss_string_int_10(ResultsTable& rTable,
        PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp)
{
    // fail immediately
    assert(false);
}

// Currently, nothing uses this and it does not seem it will be used
void __cdecl QueryEvaluator::ev_rr_ss_string_int_11(ResultsTable& rTable,
        PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp)
{
    // fail immediately
    assert(false);
}

// Currently, nothing uses this and it does not seem it will be used
void __cdecl QueryEvaluator::ev_rr_ss_string_int_22(ResultsTable& rTable,
        PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp)
{
    // fail immediately
    assert(false);
}

void __cdecl QueryEvaluator::ev_rr_ss_int_string_00_from_argOne(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
        const EvalPKBDispatch& disp)
{
    assert(disp.get_all_int_argOne != NULL);
    assert(disp.get_string_set_argTwo_from_int_argOne != NULL);
    rTable.syn_00_transaction_begin(relRef->argOneString, RV_INT,
            relRef->argTwoString, RV_STRING);
    set<int> argOneSet = (pkb->*(disp.get_all_int_argOne))();
    for (set<int>::const_iterator it = argOneSet.begin();
            it != argOneSet.end(); it++) {
        set<string> argTwoSet =
                (pkb->*(disp.get_string_set_argTwo_from_int_argOne))
                        (relRef->argOneSyn, relRef->argTwoSyn, *it);
        for (set<string>::const_iterator kt = argTwoSet.begin();
                kt != argTwoSet.end(); kt++) {
            rTable.syn_00_add_row(*it, *kt);
        }
    }
    rTable.syn_00_transaction_end();
}

// not used for now
void __cdecl QueryEvaluator::ev_rr_ss_int_string_00_from_argTwo(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
        const EvalPKBDispatch& disp)
{
    assert(disp.get_all_string_argTwo != NULL);
    assert(disp.get_int_set_argOne_from_string_argTwo != NULL);
    rTable.syn_00_transaction_begin(relRef->argOneString, RV_INT,
            relRef->argTwoString, RV_STRING);
    set<string> argTwoSet = (pkb->*(disp.get_all_string_argTwo))();
    for (set<string>::const_iterator it = argTwoSet.begin();
            it != argTwoSet.end(); it++) {
        set<int> argOneSet =
                (pkb->*(disp.get_int_set_argOne_from_string_argTwo))
                        (relRef->argOneSyn, relRef->argTwoSyn, *it);
        for (set<int>::const_iterator kt = argOneSet.begin();
                kt != argOneSet.end(); kt++) {
            rTable.syn_00_add_row(*kt, *it);
        }
    }
    rTable.syn_00_transaction_end();
}

void __cdecl QueryEvaluator::ev_rr_ss_int_string_01(ResultsTable& rTable,
        PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(disp.get_int_set_argOne_from_string_argTwo != NULL);
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
                (pkb->*(disp.get_int_set_argOne_from_string_argTwo))
                        (relRef->argOneSyn, relRef->argTwoSyn,
                                argTwoVal);
        for (set<int>::const_iterator argOneIt = argOneSet.begin();
                argOneIt != argOneSet.end(); argOneIt++){
            rTable.syn_01_augment_new_row(i, *argOneIt);
        }
    }
    rTable.syn_01_transaction_end();
}

void __cdecl QueryEvaluator::ev_rr_ss_int_string_10(ResultsTable& rTable,
        PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(disp.get_string_set_argTwo_from_int_argOne != NULL);
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
                (pkb->*(disp.get_string_set_argTwo_from_int_argOne))
                        (relRef->argOneSyn, relRef->argTwoSyn,
                         argOneVal);
        for (set<string>::const_iterator argTwoIt = argTwoSet.begin();
                argTwoIt != argTwoSet.end(); argTwoIt++) {
            rTable.syn_10_augment_new_row(i, *argTwoIt);
        }
    }
    rTable.syn_10_transaction_end();
}

void __cdecl QueryEvaluator::ev_rr_ss_int_string_11(ResultsTable& rTable,
        PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(disp.f_int_argOne_string_argTwo != NULL);
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
        if ((pkb->*(disp.f_int_argOne_string_argTwo))
                    (relRef->argOneSyn, argOneVal,
                        relRef->argTwoSyn, argTwoVal)) {
            rTable.syn_11_mark_row_ok(i);
        }
    }
    rTable.syn_11_transaction_end();
}

void __cdecl QueryEvaluator::ev_rr_ss_int_string_22(ResultsTable& rTable,
        PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(NULL != disp.f_int_argOne_string_argTwo);
    assert(NULL != disp.relRef_eval);
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
            if ((pkb->*(disp.f_int_argOne_string_argTwo))
                        (relRef->argOneSyn, argOneVal,
                         relRef->argTwoSyn, argTwoVal)) {
                rTable.syn_22_add_row(i, k);
            }
        }
    }
    rTable.syn_22_transaction_end();
}

void __cdecl QueryEvaluator::ev_rr_ss_int_int_00_from_argOne(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
        const EvalPKBDispatch& disp)
{
    assert(disp.get_all_int_argOne != NULL);
    assert(disp.get_int_set_argTwo_from_int_argOne != NULL);
    rTable.syn_00_transaction_begin(relRef->argOneString, RV_INT,
            relRef->argTwoString, RV_INT);
    set<int> argOneSet = (pkb->*(disp.get_all_int_argOne))();
    for (set<int>::const_iterator it = argOneSet.begin();
            it != argOneSet.end(); it++) {
        set<int> argTwoSet =
                (pkb->*(disp.get_int_set_argTwo_from_int_argOne))
                        (relRef->argOneSyn, relRef->argTwoSyn, *it);
        for (set<int>::const_iterator kt = argTwoSet.begin();
                kt != argTwoSet.end(); kt++) {
            rTable.syn_00_add_row(*it, *kt);
        }
    }
    rTable.syn_00_transaction_end();
}

void __cdecl QueryEvaluator::ev_rr_ss_int_int_00_from_argTwo(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
        const EvalPKBDispatch& disp)
{
    assert(disp.get_all_int_argTwo != NULL);
    assert(disp.get_int_set_argOne_from_int_argTwo != NULL);
    rTable.syn_00_transaction_begin(relRef->argOneString, RV_INT,
            relRef->argTwoString, RV_INT);
    set<int> argTwoSet = (pkb->*(disp.get_all_int_argTwo))();
    for (set<int>::const_iterator it = argTwoSet.begin();
            it != argTwoSet.end(); it++) {
        set<int> argOneSet =
                (pkb->*(disp.get_int_set_argOne_from_int_argTwo))
                        (relRef->argOneSyn, relRef->argTwoSyn, *it);
        for (set<int>::const_iterator kt = argOneSet.begin();
                kt != argOneSet.end(); kt++) {
            rTable.syn_00_add_row(*kt, *it);
        }
    }
    rTable.syn_00_transaction_end();
}

void __cdecl QueryEvaluator::ev_rr_ss_int_int_01(ResultsTable& rTable,
        PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(NULL != disp.get_int_set_argOne_from_int_argTwo);
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
                (pkb->*(disp.get_int_set_argOne_from_int_argTwo))
                        (relRef->argOneSyn, relRef->argTwoSyn,
                                argTwoVal);
        for (set<int>::const_iterator argOneIt = argOneSet.begin();
                argOneIt != argOneSet.end(); argOneIt++){
            rTable.syn_01_augment_new_row(i, *argOneIt);
        }
    }
    rTable.syn_01_transaction_end();
}

void __cdecl QueryEvaluator::ev_rr_ss_int_int_10(ResultsTable& rTable,
        PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(disp.get_int_set_argTwo_from_int_argOne != NULL);
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
                (pkb->*(disp.get_int_set_argTwo_from_int_argOne))
                        (relRef->argOneSyn, relRef->argTwoSyn,
                         argOneVal);
        for (set<int>::const_iterator argTwoIt = argTwoSet.begin();
                argTwoIt != argTwoSet.end(); argTwoIt++) {
            rTable.syn_10_augment_new_row(i, *argTwoIt);
        }
    }
    rTable.syn_10_transaction_end();
}

void __cdecl QueryEvaluator::ev_rr_ss_int_int_11(ResultsTable& rTable,
        PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(disp.f_int_argOne_int_argTwo != NULL);
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
        if ((pkb->*(disp.f_int_argOne_int_argTwo))
                    (relRef->argOneSyn, argOneVal,
                        relRef->argTwoSyn, argTwoVal)) {
            rTable.syn_11_mark_row_ok(i);
        }
    }
    rTable.syn_11_transaction_end();
}

void __cdecl QueryEvaluator::ev_rr_ss_int_int_22(ResultsTable& rTable,
        PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(NULL != disp.f_int_argOne_int_argTwo);
    assert(NULL != disp.relRef_eval);
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
            if ((pkb->*(disp.f_int_argOne_int_argTwo))
                        (relRef->argOneSyn, argOneVal,
                         relRef->argTwoSyn, argTwoVal)) {
                rTable.syn_22_add_row(i, k);
            }
        }
    }
    rTable.syn_22_transaction_end();
}

void __cdecl QueryEvaluator::ev_rr_ss_int_int_0(ResultsTable& rTable,
        PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(NULL != disp.get_all_int_argOne);
    assert(NULL != disp.f_int_argOne_int_argTwo);
    assert(NULL != disp.relRef_eval);
    rTable.syn_0_transaction_begin(relRef->argOneString, RV_INT);
    set<int> argSet = (pkb->*(disp.get_all_int_argOne))();
    for (set<int>::const_iterator argIt = argSet.begin();
            argIt != argSet.end(); argIt++) {
        int argVal = *argIt;
        if ((pkb->*(disp.f_int_argOne_int_argTwo))
                   (relRef->argOneSyn, argVal,
                    relRef->argOneSyn, argVal)) {
            rTable.syn_0_add_row(argVal);
        }
    }
    rTable.syn_0_transaction_end();
}

void __cdecl QueryEvaluator::ev_rr_ss_int_int_1(ResultsTable& rTable,
        PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(NULL != disp.f_int_argOne_int_argTwo);
    assert(NULL != disp.relRef_eval);
    pair<const vector<Record> *, int> viPair =
            rTable.syn_1_transaction_begin(relRef->argOneString);
    const vector<Record>& records = *(viPair.first);
    int nrRecords = records.size();
    int colIdx = viPair.second;
    for (int rowNum = 0; rowNum < nrRecords; rowNum++) {
        const Record& record = records[rowNum];
        const pair<string, int>& siPair = record.get_column(colIdx);
        int argVal = siPair.second;
        if ((pkb->*(disp.f_int_argOne_int_argTwo))
                    (relRef->argOneSyn, argVal,
                     relRef->argOneSyn, argVal)) {
            rTable.syn_1_mark_row_ok(rowNum);
        }
    }
    rTable.syn_1_transaction_end();
}

void __cdecl QueryEvaluator::ev_relRef_syn_X(ResultsTable& rTable,
        PKB *pkb, const RelRef *relRef)
{
    EvalPKBDispatch pkbDispatch;
    if (rTable.has_synonym(relRef->argOneString)) {
        switch (relRef->relType) {
        case REL_MODIFIES:
            if (ENT_PROC == relRef->argOneSyn) {
                if (RELARG_STRING == relRef->argTwoType) {
                    pkbDispatch.f_string_argOne_string_argTwo =
                            &PKB::modifies_query_string_X_string_Y;
                    QueryEvaluator::ev_rr_syn_X_string_string_1(rTable,
                            pkb, relRef, pkbDispatch, ENT_VAR,
                            relRef->argTwoString);
                } else if (RELARG_WILDCARD == relRef->argTwoType) {
                    pkbDispatch.f_string_argOne_smth =
                            &PKB::modifies_X_Y_string_X_smth;
                    QueryEvaluator::ev_rr_syn_X_string_wild_1(rTable,
                            pkb, relRef, pkbDispatch);
                } else {
                    assert(false);
                }
            } else {
                // stmt type
                if (RELARG_STRING == relRef->argTwoType) {
                    pkbDispatch.f_int_argOne_string_argTwo =
                            &PKB::modifies_query_int_X_string_Y;
                    QueryEvaluator::ev_rr_syn_X_int_string_1(rTable, pkb,
                            relRef, pkbDispatch, ENT_VAR, relRef->argTwoString);
                } else if (RELARG_WILDCARD == relRef->argTwoType) {
                    pkbDispatch.f_int_argOne_smth =
                            &PKB::modifies_X_Y_int_X_smth;
                    QueryEvaluator::ev_rr_syn_X_int_wild_1(rTable, pkb,
                            relRef, pkbDispatch);
                } else {
                    assert(false);
                }
            }
            break;
        case REL_USES:
            if (ENT_PROC == relRef->argOneSyn) {
                if (RELARG_STRING == relRef->argTwoType) {
                    pkbDispatch.f_string_argOne_string_argTwo =
                            &PKB::uses_query_string_X_string_Y;
                    QueryEvaluator::ev_rr_syn_X_string_string_1(rTable,
                            pkb, relRef, pkbDispatch, ENT_VAR,
                            relRef->argTwoString);
                } else if (RELARG_WILDCARD == relRef->argTwoType) {
                    pkbDispatch.f_string_argOne_smth =
                            &PKB::uses_X_Y_string_X_smth;
                    QueryEvaluator::ev_rr_syn_X_string_wild_1(rTable,
                            pkb, relRef, pkbDispatch);
                } else {
                    assert(false);
                }
            } else {
                // stmt type
                if (RELARG_STRING == relRef->argTwoType) {
                    pkbDispatch.f_int_argOne_string_argTwo =
                            &PKB::uses_query_int_X_string_Y;
                    QueryEvaluator::ev_rr_syn_X_int_string_1(rTable, pkb,
                            relRef, pkbDispatch, ENT_VAR,
                            relRef->argTwoString);
                } else if (RELARG_WILDCARD == relRef->argTwoType) {
                    pkbDispatch.f_int_argOne_smth =
                            &PKB::uses_X_Y_int_X_smth;
                    QueryEvaluator::ev_rr_syn_X_int_wild_1(rTable,
                            pkb, relRef, pkbDispatch);
                } else {
                    assert(false);
                }
            }
            break;
        case REL_CALLS:
            // arg one can only be procedure
            if (RELARG_STRING == relRef->argTwoType) {
                pkbDispatch.f_string_argOne_string_argTwo =
                        &PKB::calls_query_string_X_string_Y;
                QueryEvaluator::ev_rr_syn_X_string_string_1(rTable, pkb,
                        relRef, pkbDispatch, ENT_PROC,
                        relRef->argTwoString);
            } else {
                // wildcard
                pkbDispatch.f_string_argOne_smth =
                        &PKB::calls_X_Y_string_X_smth;
                QueryEvaluator::ev_rr_syn_X_string_wild_1(rTable, pkb,
                        relRef, pkbDispatch);
            }
            break;
        case REL_CALLS_STAR:
            // arg one can only be procedure
            if (RELARG_STRING == relRef->argTwoType) {
                pkbDispatch.f_string_argOne_string_argTwo =
                        &PKB::callsStar_query_string_X_string_Y;
                QueryEvaluator::ev_rr_syn_X_string_string_1(rTable, pkb,
                        relRef, pkbDispatch, ENT_PROC,
                        relRef->argTwoString);
            } else {
                // wildcard
                pkbDispatch.f_string_argOne_smth =
                        &PKB::callsStar_X_Y_string_X_smth;
                QueryEvaluator::ev_rr_syn_X_string_wild_1(rTable, pkb,
                        relRef, pkbDispatch);
            }
            break;
        case REL_PARENT:
            // arg one is all stmt type
            if (RELARG_INT == relRef->argTwoType) {
                pkbDispatch.f_int_argOne_int_argTwo =
                        &PKB::parent_query_int_X_int_Y;
                QueryEvaluator::ev_rr_syn_X_int_int_1(rTable, pkb,
                        relRef, pkbDispatch, ENT_STMT, relRef->argTwoInt);
            } else {
                // arg two is wildcard
                pkbDispatch.f_int_argOne_smth =
                        &PKB::parent_X_Y_int_X_smth;
                QueryEvaluator::ev_rr_syn_X_int_wild_1(rTable, pkb,
                        relRef, pkbDispatch);
            }
            break;
        case REL_PARENT_STAR:
            // arg one is all stmt type
            if (RELARG_INT == relRef->argTwoType) {
                pkbDispatch.f_int_argOne_int_argTwo =
                        &PKB::parentStar_query_int_X_int_Y;
                QueryEvaluator::ev_rr_syn_X_int_int_1(rTable, pkb, relRef,
                        pkbDispatch, ENT_STMT, relRef->argTwoInt);
            } else {
                // arg two is wildcard
                pkbDispatch.f_int_argOne_smth =
                        &PKB::parentStar_X_Y_int_X_smth;
                QueryEvaluator::ev_rr_syn_X_int_wild_1(rTable, pkb,
                        relRef, pkbDispatch);
            }
            break;
        case REL_FOLLOWS:
            // arg one is all stmt type
            if (RELARG_INT == relRef->argTwoType) {
                pkbDispatch.f_int_argOne_int_argTwo =
                        &PKB::follows_query_int_X_int_Y;
                QueryEvaluator::ev_rr_syn_X_int_int_1(rTable, pkb, relRef,
                        pkbDispatch, ENT_STMT, relRef->argTwoInt);
            } else {
                // arg two is wildcard
                pkbDispatch.f_int_argOne_smth =
                        &PKB::follows_X_Y_int_X_smth;
                QueryEvaluator::ev_rr_syn_X_int_wild_1(rTable, pkb,
                        relRef, pkbDispatch);
            }
            break;
        case REL_FOLLOWS_STAR:
            // arg one is all stmt type
            if (RELARG_INT == relRef->argTwoType) {
                pkbDispatch.f_int_argOne_int_argTwo =
                        &PKB::followsStar_query_int_X_int_Y;
                QueryEvaluator::ev_rr_syn_X_int_int_1(rTable, pkb,
                        relRef, pkbDispatch, ENT_STMT, relRef->argTwoInt);
            } else {
                // arg two is wildcard
                pkbDispatch.f_int_argOne_smth =
                        &PKB::followsStar_X_Y_int_X_smth;
                QueryEvaluator::ev_rr_syn_X_int_wild_1(rTable, pkb,
                        relRef, pkbDispatch);
            }
            break;
        case REL_NEXT:
            QueryEvaluator::ev_relRef_syn_X_1_nextAndStar(rTable, pkb,
                    relRef);
            break;
        case REL_NEXT_STAR:
            QueryEvaluator::ev_relRef_syn_X_1_nextAndStar(rTable, pkb,
                    relRef);
            break;
        case REL_AFFECTS:
            // arg one is all stmt type
            if (RELARG_INT == relRef->argTwoType) {
                pkbDispatch.f_int_argOne_int_argTwo =
                        &PKB::affects_query_int_X_int_Y;
                QueryEvaluator::ev_rr_syn_X_int_int_1(rTable, pkb, relRef,
                        pkbDispatch, ENT_ASSIGN, relRef->argTwoInt);
            } else {
                // arg two is wildcard
                pkbDispatch.f_int_argOne_smth =
                        &PKB::affects_X_Y_int_X_smth;
                QueryEvaluator::ev_rr_syn_X_int_wild_1(rTable, pkb,
                        relRef, pkbDispatch);
            }
            break;
        case REL_AFFECTS_STAR:
            // arg one is all stmt type
            if (RELARG_INT == relRef->argTwoType) {
                pkbDispatch.f_int_argOne_int_argTwo =
                        &PKB::affectsStar_query_int_X_int_Y;
                QueryEvaluator::ev_rr_syn_X_int_int_1(rTable, pkb,
                        relRef, pkbDispatch, ENT_ASSIGN,
                        relRef->argTwoInt);
            } else {
                // arg two is wildcard
                pkbDispatch.f_int_argOne_smth =
                        &PKB::affectsStar_X_Y_int_X_smth;
                QueryEvaluator::ev_rr_syn_X_int_wild_1(rTable, pkb,
                        relRef, pkbDispatch);
            }
            break;
        }
    } else {
        // have not seen syn
        switch (relRef->relType) {
        case REL_MODIFIES:
            if (ENT_PROC == relRef->argOneSyn) {
                if (RELARG_STRING == relRef->argTwoType) {
                    pkbDispatch.get_string_set_argOne_from_string_argTwo =
                            &PKB::modifies_X_Y_get_string_X_from_string_Y;
                    QueryEvaluator::ev_rr_syn_X_string_string_0(rTable,
                            pkb, relRef, pkbDispatch, ENT_VAR,
                            relRef->argTwoString);
                } else if (RELARG_WILDCARD == relRef->argTwoType) {
                    // TODO: Can we actually retrieve _all_ procedures
                    //       here? Since they must modify smth
                    pkbDispatch.get_all_string_argOne =
                            &PKB::get_all_procs;
                    pkbDispatch.f_string_argOne_smth =
                            &PKB::modifies_X_Y_string_X_smth;
                    QueryEvaluator::ev_rr_syn_X_string_wild_0(rTable, pkb,
                            relRef, pkbDispatch);
                } else {
                    assert(false);
                }
            } else {
                // stmt type
                if (RELARG_STRING == relRef->argTwoType) {
                    pkbDispatch.get_int_set_argOne_from_string_argTwo =
                            &PKB::modifies_X_Y_get_int_X_from_string_Y;
                    QueryEvaluator::ev_rr_syn_X_int_string_0(rTable, pkb,
                            relRef, pkbDispatch, ENT_VAR,
                            relRef->argTwoString);
                } else if (RELARG_WILDCARD == relRef->argTwoType) {
                    switch (relRef->argOneSyn) {
                    case ENT_ASSIGN:
                        pkbDispatch.get_all_int_argOne =
                                &PKB::get_all_assign;
                        break;
                    case ENT_CALL:
                        pkbDispatch.get_all_int_argOne =
                                &PKB::get_all_call;
                        break;
                    case ENT_IF:
                        pkbDispatch.get_all_int_argOne =
                                &PKB::get_all_if;
                        break;
                    case ENT_WHILE:
                        pkbDispatch.get_all_int_argOne =
                                &PKB::get_all_while;
                        break;
                    case ENT_STMT:
                    case ENT_PROGLINE:
                        pkbDispatch.get_all_int_argOne =
                                &PKB::get_all_stmt;
                        break;
                    default:
                        assert(false);
                    }
                    pkbDispatch.f_int_argOne_smth =
                            &PKB::modifies_X_Y_int_X_smth;
                    QueryEvaluator::ev_rr_syn_X_int_wild_0(rTable, pkb,
                            relRef, pkbDispatch);
                } else {
                    assert(false);
                }
            }
            break;
        case REL_USES:
            if (ENT_PROC == relRef->argOneSyn) {
                if (RELARG_STRING == relRef->argTwoType) {
                    pkbDispatch.get_string_set_argOne_from_string_argTwo =
                            &PKB::uses_X_Y_get_string_X_from_string_Y;
                    QueryEvaluator::ev_rr_syn_X_string_string_0(rTable,
                            pkb, relRef, pkbDispatch, ENT_VAR,
                            relRef->argTwoString);
                } else if (RELARG_WILDCARD == relRef->argTwoType) {
                    pkbDispatch.get_all_string_argOne =
                            &PKB::get_all_procs;
                    pkbDispatch.f_string_argOne_smth =
                            &PKB::uses_X_Y_string_X_smth;
                    QueryEvaluator::ev_rr_syn_X_string_wild_0(rTable, pkb,
                            relRef, pkbDispatch);
                } else {
                    assert(false);
                }
            } else {
                // arg one is stmt type
                if (RELARG_STRING == relRef->argTwoType) {
                    pkbDispatch.get_int_set_argOne_from_string_argTwo =
                            &PKB::uses_X_Y_get_int_X_from_string_Y;
                    QueryEvaluator::ev_rr_syn_X_int_string_0(rTable, pkb,
                            relRef, pkbDispatch, ENT_VAR,
                            relRef->argTwoString);
                } else if (RELARG_WILDCARD == relRef->argTwoType) {
                    switch (relRef->argOneSyn) {
                    case ENT_ASSIGN:
                        pkbDispatch.get_all_int_argOne =
                                &PKB::get_all_assign;
                        break;
                    case ENT_CALL:
                        pkbDispatch.get_all_int_argOne =
                                &PKB::get_all_call;
                        break;
                    case ENT_IF:
                        pkbDispatch.get_all_int_argOne =
                                &PKB::get_all_if;
                        break;
                    case ENT_WHILE:
                        pkbDispatch.get_all_int_argOne =
                                &PKB::get_all_while;
                        break;
                    case ENT_STMT:
                    case ENT_PROGLINE:
                        pkbDispatch.get_all_int_argOne =
                                &PKB::get_all_stmt;
                        break;
                    default:
                        assert(false);
                    }
                    pkbDispatch.f_int_argOne_smth =
                            &PKB::uses_X_Y_int_X_smth;
                    QueryEvaluator::ev_rr_syn_X_int_wild_0(rTable, pkb,
                            relRef, pkbDispatch);
                } else {
                    assert(false);
                }
            }
            break;
        case REL_CALLS:
            // syn one can only be procedure
            if (RELARG_STRING == relRef->argTwoType) {
                pkbDispatch.get_string_set_argOne_from_string_argTwo =
                        &PKB::calls_X_Y_get_string_X_from_string_Y;
                QueryEvaluator::ev_rr_syn_X_string_string_0(rTable, pkb,
                        relRef, pkbDispatch, ENT_PROC,
                        relRef->argTwoString);
            } else if (RELARG_WILDCARD == relRef->argTwoType) {
                pkbDispatch.get_all_string_argOne =
                        &PKB::get_all_procs;
                pkbDispatch.f_string_argOne_smth =
                        &PKB::calls_X_Y_string_X_smth;
                QueryEvaluator::ev_rr_syn_X_string_wild_0(rTable, pkb,
                        relRef, pkbDispatch);
            } else {
                assert(false);
            }
            break;
        case REL_CALLS_STAR:
            // syn one can only be procedure
            if (RELARG_STRING == relRef->argTwoType) {
                pkbDispatch.get_string_set_argOne_from_string_argTwo =
                        &PKB::callsStar_X_Y_get_string_X_from_string_Y;
                QueryEvaluator::ev_rr_syn_X_string_string_0(rTable, pkb,
                        relRef, pkbDispatch, ENT_PROC,
                        relRef->argTwoString);
            } else if (RELARG_WILDCARD == relRef->argTwoType) {
                pkbDispatch.get_all_string_argOne =
                        &PKB::get_all_procs;
                pkbDispatch.f_string_argOne_smth =
                        &PKB::callsStar_X_Y_string_X_smth;
                QueryEvaluator::ev_rr_syn_X_string_wild_0(rTable, pkb,
                        relRef, pkbDispatch);
            } else {
                assert(false);
            }
            break;
        case REL_PARENT:
            // syn one is stmt type
            if (RELARG_INT == relRef->argTwoType) {
                pkbDispatch.get_int_set_argOne_from_int_argTwo =
                        &PKB::parent_X_Y_get_int_X_from_int_Y;
                QueryEvaluator::ev_rr_syn_X_int_int_0(rTable, pkb, relRef,
                        pkbDispatch, ENT_STMT, relRef->argTwoInt);
            } else if (RELARG_WILDCARD == relRef->argTwoType) {
                switch (relRef->argOneSyn) {
                case ENT_IF:
                    pkbDispatch.get_all_int_argOne =
                            &PKB::get_all_if;
                    break;
                case ENT_WHILE:
                    pkbDispatch.get_all_int_argOne =
                            &PKB::get_all_while;
                    break;
                case ENT_STMT:
                case ENT_PROGLINE:
                    pkbDispatch.get_all_int_argOne =
                            &PKB::get_all_stmt;
                    break;
                default:
                    assert(false);
                }
                pkbDispatch.f_int_argOne_smth =
                        &PKB::parent_X_Y_int_X_smth;
                QueryEvaluator::ev_rr_syn_X_int_wild_0(rTable, pkb,
                        relRef, pkbDispatch);
            } else {
                assert(false);
            }
            break;
        case REL_PARENT_STAR:
            // syn one is stmt type
            if (RELARG_INT == relRef->argTwoType) {
                pkbDispatch.get_int_set_argOne_from_int_argTwo =
                        &PKB::parentStar_X_Y_get_int_X_from_int_Y;
                QueryEvaluator::ev_rr_syn_X_int_int_0(rTable, pkb, relRef,
                        pkbDispatch, ENT_STMT, relRef->argTwoInt);
            } else if (RELARG_WILDCARD == relRef->argTwoType) {
                switch (relRef->argOneSyn) {
                case ENT_IF:
                    pkbDispatch.get_all_int_argOne =
                            &PKB::get_all_if;
                    break;
                case ENT_WHILE:
                    pkbDispatch.get_all_int_argOne =
                            &PKB::get_all_while;
                    break;
                case ENT_STMT:
                case ENT_PROGLINE:
                    pkbDispatch.get_all_int_argOne =
                            &PKB::get_all_stmt;
                    break;
                default:
                    assert(false);
                }
                pkbDispatch.f_int_argOne_smth =
                        &PKB::parentStar_X_Y_int_X_smth;
                QueryEvaluator::ev_rr_syn_X_int_wild_0(rTable, pkb,
                        relRef, pkbDispatch);
            } else {
                assert(false);
            }
            break;
        case REL_FOLLOWS:
            // syn one is stmt type
            if (RELARG_INT == relRef->argTwoType) {
                pkbDispatch.get_int_set_argOne_from_int_argTwo =
                        &PKB::follows_X_Y_get_int_X_from_int_Y;
                QueryEvaluator::ev_rr_syn_X_int_int_0(rTable, pkb, relRef,
                        pkbDispatch, ENT_STMT, relRef->argTwoInt);
            } else if (RELARG_WILDCARD == relRef->argTwoType) {
                switch (relRef->argOneSyn) {
                case ENT_ASSIGN:
                    pkbDispatch.get_all_int_argOne =
                            &PKB::get_all_assign;
                    break;
                case ENT_CALL:
                    pkbDispatch.get_all_int_argOne =
                            &PKB::get_all_call;
                    break;
                case ENT_IF:
                    pkbDispatch.get_all_int_argOne =
                            &PKB::get_all_if;
                    break;
                case ENT_WHILE:
                    pkbDispatch.get_all_int_argOne =
                            &PKB::get_all_while;
                    break;
                case ENT_STMT:
                case ENT_PROGLINE:
                    pkbDispatch.get_all_int_argOne =
                            &PKB::get_all_stmt;
                    break;
                default:
                    assert(false);
                }
                pkbDispatch.f_int_argOne_smth =
                        &PKB::follows_X_Y_int_X_smth;
                QueryEvaluator::ev_rr_syn_X_int_wild_0(rTable, pkb,
                        relRef, pkbDispatch);
            } else {
                assert(false);
            }
            break;
        case REL_FOLLOWS_STAR:
            // syn one is stmt type
            if (RELARG_INT == relRef->argTwoType) {
                pkbDispatch.get_int_set_argOne_from_int_argTwo =
                        &PKB::followsStar_X_Y_get_int_X_from_int_Y;
                QueryEvaluator::ev_rr_syn_X_int_int_0(rTable, pkb, relRef,
                        pkbDispatch, ENT_STMT, relRef->argTwoInt);
            } else if (RELARG_WILDCARD == relRef->argTwoType) {
                switch (relRef->argOneSyn) {
                case ENT_ASSIGN:
                    pkbDispatch.get_all_int_argOne =
                            &PKB::get_all_assign;
                    break;
                case ENT_CALL:
                    pkbDispatch.get_all_int_argOne =
                            &PKB::get_all_call;
                    break;
                case ENT_IF:
                    pkbDispatch.get_all_int_argOne =
                            &PKB::get_all_if;
                    break;
                case ENT_WHILE:
                    pkbDispatch.get_all_int_argOne =
                            &PKB::get_all_while;
                    break;
                case ENT_STMT:
                case ENT_PROGLINE:
                    pkbDispatch.get_all_int_argOne =
                            &PKB::get_all_stmt;
                    break;
                default:
                    assert(false);
                }
                pkbDispatch.f_int_argOne_smth =
                        &PKB::followsStar_X_Y_int_X_smth;
                QueryEvaluator::ev_rr_syn_X_int_wild_0(rTable, pkb,
                        relRef, pkbDispatch);
            } else {
                assert(false);
            }
            break;
        case REL_NEXT:
            QueryEvaluator::ev_relRef_syn_X_0_nextAndStar(rTable, pkb,
                    relRef);
            break;
        case REL_NEXT_STAR:
            QueryEvaluator::ev_relRef_syn_X_0_nextAndStar(rTable, pkb,
                    relRef);
            break;
        case REL_AFFECTS:
            // syn one is assign
            if (RELARG_INT == relRef->argTwoType) {
                pkbDispatch.get_int_set_argOne_from_int_argTwo =
                        &PKB::affects_X_Y_get_int_X_from_int_Y;
                QueryEvaluator::ev_rr_syn_X_int_int_0(rTable, pkb, relRef,
                        pkbDispatch, ENT_ASSIGN, relRef->argTwoInt);
            } else if (RELARG_WILDCARD == relRef->argTwoType) {
                switch (relRef->argOneSyn) {
                case ENT_ASSIGN:
                    pkbDispatch.get_all_int_argOne =
                            &PKB::get_all_assign;
                    break;
                default:
                    assert(false);
                }
                pkbDispatch.f_int_argOne_smth =
                        &PKB::affects_X_Y_int_X_smth;
                QueryEvaluator::ev_rr_syn_X_int_wild_0(rTable, pkb,
                        relRef, pkbDispatch);
            } else {
                assert(false);
            }
            break;
        case REL_AFFECTS_STAR:
            // syn one is assign
            if (RELARG_INT == relRef->argTwoType) {
                pkbDispatch.get_int_set_argOne_from_int_argTwo =
                        &PKB::affectsStar_X_Y_get_int_X_from_int_Y;
                QueryEvaluator::ev_rr_syn_X_int_int_0(rTable, pkb, relRef,
                        pkbDispatch, ENT_ASSIGN, relRef->argTwoInt);
            } else if (RELARG_WILDCARD == relRef->argTwoType) {
                switch (relRef->argOneSyn) {
                case ENT_ASSIGN:
                    pkbDispatch.get_all_int_argOne =
                            &PKB::get_all_assign;
                    break;
                default:
                    assert(false);
                }
                pkbDispatch.f_int_argOne_smth =
                        &PKB::affectsStar_X_Y_int_X_smth;
                QueryEvaluator::ev_rr_syn_X_int_wild_0(rTable, pkb,
                        relRef, pkbDispatch);
            } else {
                assert(false);
            }
            break;
        }
    }
}

void __cdecl QueryEvaluator::ev_relRef_syn_X_0_nextAndStar(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef)
{
    EvalPKBDispatch pkbDispatch;
    switch (relRef->argTwoType) {
    case RELARG_INT:
        if (REL_NEXT == relRef->relType) {
            pkbDispatch.get_int_set_argOne_from_int_argTwo =
                    &PKB::next_X_Y_get_int_X_from_int_Y;
        } else if (REL_NEXT_STAR == relRef->relType) {
            pkbDispatch.get_int_set_argOne_from_int_argTwo =
                    &PKB::nextStar_X_Y_get_int_X_from_int_Y;
        } else {
            assert(false);
        }
        QueryEvaluator::ev_rr_syn_X_int_int_0(rTable, pkb, relRef,
                pkbDispatch, ENT_STMT, relRef->argTwoInt);
        break;
    case RELARG_WILDCARD:
        switch (relRef->argOneSyn) {
        case ENT_ASSIGN:
            pkbDispatch.get_all_int_argOne =
                    &PKB::get_all_assign;
            break;
        case ENT_CALL:
            pkbDispatch.get_all_int_argOne =
                    &PKB::get_all_call;
            break;
        case ENT_IF:
            pkbDispatch.get_all_int_argOne =
                    &PKB::get_all_if;
            break;
        case ENT_WHILE:
            pkbDispatch.get_all_int_argOne =
                    &PKB::get_all_while;
            break;
        case ENT_STMT:
        case ENT_PROGLINE:
            pkbDispatch.get_all_int_argOne =
                    &PKB::get_all_stmt;
            break;
        default:
            assert(false);
        }
        if (REL_NEXT == relRef->relType) {
            pkbDispatch.f_int_argOne_smth =
                    &PKB::next_X_Y_int_X_smth;
        } else if (REL_NEXT_STAR == relRef->relType) {
            pkbDispatch.f_int_argOne_smth =
                    &PKB::nextStar_X_Y_int_X_smth;
        } else {
            assert(false);
        }
        QueryEvaluator::ev_rr_syn_X_int_wild_0(rTable, pkb, relRef,
                pkbDispatch);
        break;
    default:
        assert(false);
    }
}

void __cdecl QueryEvaluator::ev_relRef_syn_X_1_nextAndStar(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef)
{
    EvalPKBDispatch pkbDispatch;
    switch (relRef->argTwoType) {
    case RELARG_INT:
        if (REL_NEXT == relRef->relType) {
            pkbDispatch.f_int_argOne_int_argTwo =
                    &PKB::next_query_int_X_int_Y;
        } else if (REL_NEXT_STAR == relRef->relType) {
            pkbDispatch.f_int_argOne_int_argTwo =
                    &PKB::nextStar_query_int_X_int_Y;
        } else {
            assert(false);
        }
        QueryEvaluator::ev_rr_syn_X_int_int_1(rTable, pkb, relRef,
                pkbDispatch, ENT_STMT, relRef->argTwoInt);
        break;
    case RELARG_WILDCARD:
        if (REL_NEXT == relRef->relType) {
            pkbDispatch.f_int_argOne_smth =
                    &PKB::next_X_Y_int_X_smth;
        } else if (REL_NEXT_STAR == relRef->relType) {
            pkbDispatch.f_int_argOne_smth =
                    &PKB::nextStar_X_Y_int_X_smth;
        } else {
            assert(false);
        }
        QueryEvaluator::ev_rr_syn_X_int_wild_1(rTable, pkb, relRef,
                pkbDispatch);
        break;
    default:
        assert(false);
    }
}

void __cdecl QueryEvaluator::ev_rr_syn_X_string_string_0(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
        const EvalPKBDispatch& disp, DesignEnt xType, const string& xVal)
{
    assert(NULL != disp.get_string_set_argOne_from_string_argTwo);
    rTable.syn_0_transaction_begin(relRef->argOneString, RV_STRING);
    const set<string>& synSet =
            (pkb->*(disp.get_string_set_argOne_from_string_argTwo))
                    (relRef->argOneSyn, xType, xVal);
    for (set<string>::const_iterator it = synSet.begin();
            it != synSet.end(); it++) {
        rTable.syn_0_add_row(*it);
    }
    rTable.syn_0_transaction_end();
}

void __cdecl QueryEvaluator::ev_rr_syn_X_string_wild_0(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
        const EvalPKBDispatch& disp)
{
    assert(NULL != disp.get_all_string_argOne);
    assert(NULL != disp.f_string_argOne_smth);
    rTable.syn_0_transaction_begin(relRef->argOneString, RV_STRING);
    const set<string>& synSet =
            (pkb->*(disp.get_all_string_argOne))();
    DesignEnt synEntType = relRef->argOneSyn;
    for (set<string>::const_iterator synIt = synSet.begin();
            synIt != synSet.end(); synIt++) {
        const string& synVal = *synIt;
        if ((pkb->*(disp.f_string_argOne_smth)) (synEntType, synVal)) {
            rTable.syn_0_add_row(synVal);
        }
    }
    rTable.syn_0_transaction_end();
}

void __cdecl QueryEvaluator::ev_rr_syn_X_int_string_0(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
        const EvalPKBDispatch& disp, DesignEnt xType, const string& xVal)
{
    assert(NULL != disp.get_int_set_argOne_from_string_argTwo);
    rTable.syn_0_transaction_begin(relRef->argOneString, RV_INT);
    const set<int>& synSet =
            (pkb->*(disp.get_int_set_argOne_from_string_argTwo))
                    (relRef->argOneSyn, xType, xVal);
    for (set<int>::const_iterator synIt = synSet.begin();
            synIt != synSet.end(); synIt++) {
        rTable.syn_0_add_row(*synIt);
    }
    rTable.syn_0_transaction_end();
}

void __cdecl QueryEvaluator::ev_rr_syn_X_int_int_0(ResultsTable& rTable,
        PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp,
        DesignEnt xType, int xVal)
{
    assert(NULL != disp.get_int_set_argOne_from_int_argTwo);
    rTable.syn_0_transaction_begin(relRef->argOneString, RV_INT);
    const set<int>& synSet =
            (pkb->*(disp.get_int_set_argOne_from_int_argTwo))
                    (relRef->argOneSyn, xType, xVal);
    for (set<int>::const_iterator synIt = synSet.begin();
            synIt != synSet.end(); synIt++ ) {
        rTable.syn_0_add_row(*synIt);
    }
    rTable.syn_0_transaction_end();
}

void __cdecl QueryEvaluator::ev_rr_syn_X_int_wild_0(ResultsTable& rTable,
        PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp)
{
    assert(NULL != disp.get_all_int_argOne);
    assert(NULL != disp.f_int_argOne_smth);
    rTable.syn_0_transaction_begin(relRef->argOneString, RV_INT);
    const set<int>& synSet = (pkb->*(disp.get_all_int_argOne))();
    DesignEnt synEntType = relRef->argOneSyn;
    for (set<int>::const_iterator synIt = synSet.begin();
            synIt != synSet.end(); synIt++) {
        int synVal = *synIt;
        if ((pkb->*(disp.f_int_argOne_smth)) (synEntType, synVal)) {
            rTable.syn_0_add_row(synVal);
        }
    }
    rTable.syn_0_transaction_end();
}

void __cdecl QueryEvaluator::ev_rr_syn_X_string_string_1(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
        const EvalPKBDispatch& disp, DesignEnt xType, const string& xVal)
{
    assert(NULL != disp.f_string_argOne_string_argTwo);
    pair<const vector<Record> *, int> viPair =
            rTable.syn_1_transaction_begin(relRef->argOneString);
    const vector<Record>& records = *(viPair.first);
    int nrRecords = records.size();
    int colIdx = viPair.second;
    DesignEnt synType = relRef->argOneSyn;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = records[i];
        const pair<string, int>& siPair = record.get_column(colIdx);
        const string& synVal = siPair.first;
        if ((pkb->*(disp.f_string_argOne_string_argTwo))
                    (synType, synVal, xType, xVal)) {
            rTable.syn_1_mark_row_ok(i);
        }
    }
    rTable.syn_1_transaction_end();
}

void __cdecl QueryEvaluator::ev_rr_syn_X_string_wild_1(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
        const EvalPKBDispatch& disp)
{
    assert(NULL != disp.f_string_argOne_smth);
    pair<const vector<Record> *, int> viPair =
            rTable.syn_1_transaction_begin(relRef->argOneString);
    const vector<Record>& records = *(viPair.first);
    int nrRecords = records.size();
    int colIdx = viPair.second;
    DesignEnt synEntType = relRef->argOneSyn;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = records[i];
        const pair<string, int>& siPair = record.get_column(colIdx);
        const string& synVal = siPair.first;
        if ((pkb->*(disp.f_string_argOne_smth)) (synEntType, synVal)) {
            rTable.syn_1_mark_row_ok(i);
        }
    }
    rTable.syn_1_transaction_end();
}

void __cdecl QueryEvaluator::ev_rr_syn_X_int_string_1(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
        const EvalPKBDispatch& disp, DesignEnt xType, const string& xVal)
{
    assert(NULL != disp.f_int_argOne_string_argTwo);
    pair<const vector<Record> *, int> viPair =
            rTable.syn_1_transaction_begin(relRef->argOneString);
    const vector<Record>& records = *(viPair.first);
    int nrRecords = records.size();
    int colIdx = viPair.second;
    DesignEnt synEntType = relRef->argOneSyn;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = records[i];
        const pair<string, int>& siPair = record.get_column(colIdx);
        int synVal = siPair.second;
        if ((pkb->*(disp.f_int_argOne_string_argTwo))
                (synEntType, synVal, xType, xVal)) {
            rTable.syn_1_mark_row_ok(i);
        }
    }
    rTable.syn_1_transaction_end();
}

void __cdecl QueryEvaluator::ev_rr_syn_X_int_int_1(ResultsTable& rTable,
        PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp,
        DesignEnt xType, int xVal)
{
    assert(NULL != disp.f_int_argOne_int_argTwo);
    pair<const vector<Record> *, int> viPair =
            rTable.syn_1_transaction_begin(relRef->argOneString);
    const vector<Record>& records = *(viPair.first);
    int nrRecords = records.size();
    int colIdx = viPair.second;
    DesignEnt synEntType = relRef->argOneSyn;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = records[i];
        const pair<string, int>& siPair = record.get_column(colIdx);
        int synVal = siPair.second;
        if ((pkb->*(disp.f_int_argOne_int_argTwo))
                (synEntType, synVal, xType, xVal)) {
            rTable.syn_1_mark_row_ok(i);
        }
    }
    rTable.syn_1_transaction_end();
}

void __cdecl QueryEvaluator::ev_rr_syn_X_int_wild_1(ResultsTable& rTable,
        PKB *pkb, const RelRef *relRef, const EvalPKBDispatch &disp)
{
    assert(NULL != disp.f_int_argOne_smth);
    pair<const vector<Record> *, int> viPair=
            rTable.syn_1_transaction_begin(relRef->argOneString);
    const vector<Record>& records = *(viPair.first);
    int nrRecords = records.size();
    int colIdx = viPair.second;
    DesignEnt synEntType = relRef->argOneSyn;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = records[i];
        const pair<string, int>& siPair = record.get_column(colIdx);
        int synVal = siPair.second;
        if ((pkb->*(disp.f_int_argOne_smth)) (synEntType, synVal)) {
            rTable.syn_1_mark_row_ok(i);
        }
    }
    rTable.syn_1_transaction_end();
}

void __cdecl QueryEvaluator::ev_relRef_X_syn(ResultsTable& rTable,
        PKB *pkb, const RelRef *relRef)
{
    if (rTable.has_synonym(relRef->argTwoString)) {
        switch (relRef->relType) {
        case REL_MODIFIES:
            QueryEvaluator::ev_relRef_X_syn_1_modifies(rTable, pkb,
                    relRef);
            break;
        case REL_USES:
            QueryEvaluator::ev_relRef_X_syn_1_uses(rTable, pkb, relRef);
            break;
        case REL_CALLS:
            QueryEvaluator::ev_relRef_X_syn_1_calls(rTable, pkb, relRef);
            break;
        case REL_CALLS_STAR:
            QueryEvaluator::ev_relRef_X_syn_1_callsStar(rTable, pkb,
                    relRef);
            break;
        case REL_PARENT:
            QueryEvaluator::ev_relRef_X_syn_1_parent(rTable, pkb,
                    relRef);
            break;
        case REL_PARENT_STAR:
            QueryEvaluator::ev_relRef_X_syn_1_parentStar(rTable, pkb,
                    relRef);
            break;
        case REL_FOLLOWS:
        case REL_FOLLOWS_STAR:
            QueryEvaluator::ev_relRef_X_syn_1_followsAndStar(rTable,
                    pkb, relRef);
            break;
        case REL_NEXT:
        case REL_NEXT_STAR:
            QueryEvaluator::ev_relRef_X_syn_1_nextAndStar(rTable,
                    pkb, relRef);
            break;
        case REL_AFFECTS:
        case REL_AFFECTS_STAR:
            QueryEvaluator::ev_relRef_X_syn_1_affectsAndStar(rTable,
                    pkb, relRef);
            break;
        }
    } else {
        switch (relRef->relType) {
        case REL_MODIFIES:
            QueryEvaluator::ev_relRef_X_syn_0_modifies(rTable, pkb,
                    relRef);
            break;
        case REL_USES:
            QueryEvaluator::ev_relRef_X_syn_0_uses(rTable, pkb,
                    relRef);
            break;
        case REL_CALLS:
            QueryEvaluator::ev_relRef_X_syn_0_calls(rTable, pkb, relRef);
            break;
        case REL_CALLS_STAR:
            QueryEvaluator::ev_relRef_X_syn_0_callsStar(rTable, pkb,
                    relRef);
            break;
        case REL_PARENT:
            QueryEvaluator::ev_relRef_X_syn_0_parent(rTable, pkb,
                    relRef);
            break;
        case REL_PARENT_STAR:
            QueryEvaluator::ev_relRef_X_syn_0_parentStar(rTable, pkb,
                    relRef);
            break;
        case REL_FOLLOWS:
        case REL_FOLLOWS_STAR:
            QueryEvaluator::ev_relRef_X_syn_0_followsAndStar(rTable,
                    pkb, relRef);
            break;
        case REL_NEXT:
        case REL_NEXT_STAR:
            QueryEvaluator::ev_relRef_X_syn_0_nextAndStar(rTable, pkb,
                    relRef);
            break;
        case REL_AFFECTS:
        case REL_AFFECTS_STAR:
            QueryEvaluator::ev_relRef_X_syn_0_affectsAndStar(rTable,
                    pkb, relRef);
            break;
        }
    }
}

void __cdecl QueryEvaluator::ev_relRef_X_syn_0_modifies(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef)
{
    EvalPKBDispatch pkbDispatch;
    switch (relRef->argOneType) {
    case RELARG_STRING:
        pkbDispatch.get_string_set_argTwo_from_string_argOne =
                &PKB::modifies_X_Y_get_string_Y_from_string_X;
        QueryEvaluator::ev_relRef_X_syn_string_string_0(rTable, pkb,
                relRef, pkbDispatch, ENT_PROC, relRef->argOneString);
        break;
    case RELARG_INT:
        pkbDispatch.get_string_set_argTwo_from_int_argOne =
                &PKB::modifies_X_Y_get_string_Y_from_int_X;
        QueryEvaluator::ev_relRef_X_syn_int_string_0(rTable, pkb, relRef,
                pkbDispatch, ENT_STMT, relRef->argOneInt);
        break;
    case RELARG_WILDCARD:
        pkbDispatch.get_all_string_argTwo =
                &PKB::get_all_vars;
        pkbDispatch.f_smth_string_argTwo =
                &PKB::modifies_X_Y_smth_string_Y;
        QueryEvaluator::ev_relRef_X_syn_wild_string_0(rTable, pkb, relRef,
                pkbDispatch);
        break;
    default:
        assert(false);
    }
}

void __cdecl QueryEvaluator::ev_relRef_X_syn_1_modifies(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef)
{
    EvalPKBDispatch pkbDispatch;
    switch (relRef->argOneType) {
    case RELARG_STRING:
        pkbDispatch.f_string_argOne_string_argTwo =
                &PKB::modifies_query_string_X_string_Y;
        QueryEvaluator::ev_relRef_X_syn_string_string_1(rTable, pkb,
                relRef, pkbDispatch, ENT_PROC, relRef->argOneString);
        break;
    case RELARG_INT:
        pkbDispatch.f_int_argOne_string_argTwo =
                &PKB::modifies_query_int_X_string_Y;
        QueryEvaluator::ev_relRef_X_syn_int_string_1(rTable, pkb, relRef,
                pkbDispatch, ENT_STMT, relRef->argOneInt);
        break;
    case RELARG_WILDCARD:
        pkbDispatch.f_smth_string_argTwo =
                &PKB::modifies_X_Y_smth_string_Y;
        QueryEvaluator::ev_relRef_X_syn_wild_string_1(rTable, pkb, relRef,
                pkbDispatch);
        break;
    default:
        assert(false);
    }
}

void __cdecl QueryEvaluator::ev_relRef_X_syn_0_uses(ResultsTable& rTable,
        PKB *pkb, const RelRef *relRef)
{
    EvalPKBDispatch pkbDispatch;
    switch (relRef->argOneType) {
    case RELARG_STRING:
        pkbDispatch.get_string_set_argTwo_from_string_argOne =
                &PKB::uses_X_Y_get_string_Y_from_string_X;
        QueryEvaluator::ev_relRef_X_syn_string_string_0(rTable, pkb,
                relRef, pkbDispatch, ENT_PROC, relRef->argOneString);
        break;
    case RELARG_INT:
        pkbDispatch.get_string_set_argTwo_from_int_argOne =
                &PKB::uses_X_Y_get_string_Y_from_int_X;
       QueryEvaluator::ev_relRef_X_syn_int_string_0(rTable, pkb, relRef,
                pkbDispatch, ENT_STMT, relRef->argOneInt);
        break;
    case RELARG_WILDCARD:
        pkbDispatch.get_all_string_argTwo =
                &PKB::get_all_vars;
        pkbDispatch.f_smth_string_argTwo =
                &PKB::uses_X_Y_smth_string_Y;
        QueryEvaluator::ev_relRef_X_syn_wild_string_0(rTable, pkb, relRef,
                pkbDispatch);
        break;
    default:
        assert(false);
    }
}

void __cdecl QueryEvaluator::ev_relRef_X_syn_1_uses(ResultsTable& rTable,
        PKB *pkb, const RelRef *relRef)
{
    EvalPKBDispatch pkbDispatch;
    switch (relRef->argOneType) {
    case RELARG_STRING:
        pkbDispatch.f_string_argOne_string_argTwo =
                &PKB::uses_query_string_X_string_Y;
        QueryEvaluator::ev_relRef_X_syn_string_string_1(rTable, pkb,
                relRef, pkbDispatch, ENT_PROC, relRef->argOneString);
        break;
    case RELARG_INT:
        pkbDispatch.f_int_argOne_string_argTwo =
                &PKB::uses_query_int_X_string_Y;
        QueryEvaluator::ev_relRef_X_syn_int_string_1(rTable, pkb, relRef,
                pkbDispatch, ENT_STMT, relRef->argOneInt);
        break;
    case RELARG_WILDCARD:
        pkbDispatch.f_smth_string_argTwo =
                &PKB::uses_X_Y_smth_string_Y;
        QueryEvaluator::ev_relRef_X_syn_wild_string_1(rTable, pkb, relRef,
                pkbDispatch);
        break;
    default:
        assert(false);
    }
}

void __cdecl QueryEvaluator::ev_relRef_X_syn_0_calls(ResultsTable& rTable,
        PKB *pkb, const RelRef *relRef)
{
    EvalPKBDispatch pkbDispatch;
    switch (relRef->argOneType) {
    case RELARG_STRING:
        pkbDispatch.get_string_set_argTwo_from_string_argOne =
                &PKB::calls_X_Y_get_string_Y_from_string_X;
        QueryEvaluator::ev_relRef_X_syn_string_string_0(rTable, pkb,
                relRef, pkbDispatch, ENT_PROC, relRef->argOneString);
        break;
    case RELARG_WILDCARD:
        pkbDispatch.get_all_string_argTwo =
                &PKB::get_all_procs;
        pkbDispatch.f_smth_string_argTwo =
                &PKB::calls_X_Y_smth_string_Y;
        QueryEvaluator::ev_relRef_X_syn_wild_string_0(rTable, pkb, relRef,
                pkbDispatch);
        break;
    default:
        assert(false);
    }
}

void __cdecl QueryEvaluator::ev_relRef_X_syn_1_calls(ResultsTable& rTable,
        PKB *pkb, const RelRef *relRef)
{
    EvalPKBDispatch pkbDispatch;
    switch (relRef->argOneType) {
    case RELARG_STRING:
        pkbDispatch.f_string_argOne_string_argTwo =
                &PKB::calls_query_string_X_string_Y;
        QueryEvaluator::ev_relRef_X_syn_string_string_1(rTable, pkb,
                relRef, pkbDispatch, ENT_PROC, relRef->argOneString);
        break;
    case RELARG_WILDCARD:
        pkbDispatch.f_smth_string_argTwo =
                &PKB::calls_X_Y_smth_string_Y;
        QueryEvaluator::ev_relRef_X_syn_wild_string_1(rTable, pkb, relRef,
                pkbDispatch);
        break;
    default:
        assert(false);
    }
}

void __cdecl QueryEvaluator::ev_relRef_X_syn_0_callsStar(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef)
{
    EvalPKBDispatch pkbDispatch;
    switch (relRef->argOneType) {
    case RELARG_STRING:
        pkbDispatch.get_string_set_argTwo_from_string_argOne =
                &PKB::callsStar_X_Y_get_string_Y_from_string_X;
        QueryEvaluator::ev_relRef_X_syn_string_string_0(rTable, pkb,
                relRef, pkbDispatch, ENT_PROC, relRef->argOneString);
        break;
    case RELARG_WILDCARD:
        pkbDispatch.get_all_string_argTwo =
                &PKB::get_all_procs;
        pkbDispatch.f_smth_string_argTwo =
                &PKB::callsStar_X_Y_smth_string_Y;
        QueryEvaluator::ev_relRef_X_syn_wild_string_0(rTable, pkb, relRef,
                pkbDispatch);
        break;
    default:
        assert(false);
    }
}

void __cdecl QueryEvaluator::ev_relRef_X_syn_1_callsStar(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef)
{
    EvalPKBDispatch pkbDispatch;
    switch (relRef->argOneType) {
    case RELARG_STRING:
        pkbDispatch.f_string_argOne_string_argTwo =
                &PKB::callsStar_query_string_X_string_Y;
        QueryEvaluator::ev_relRef_X_syn_string_string_1(rTable, pkb,
                relRef, pkbDispatch, ENT_PROC, relRef->argOneString);
        break;
    case RELARG_WILDCARD:
        pkbDispatch.f_smth_string_argTwo =
                &PKB::callsStar_X_Y_smth_string_Y;
        QueryEvaluator::ev_relRef_X_syn_wild_string_1(rTable, pkb, relRef,
                pkbDispatch);
        break;
    default:
        assert(false);
    }
}

void __cdecl QueryEvaluator::ev_relRef_X_syn_0_parent(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef)
{
    EvalPKBDispatch pkbDispatch;
    switch (relRef->argOneType) {
    case RELARG_INT:
        pkbDispatch.get_int_set_argTwo_from_int_argOne =
                &PKB::parent_X_Y_get_int_Y_from_int_X;
        QueryEvaluator::ev_relRef_X_syn_int_int_0(rTable, pkb, relRef,
                pkbDispatch, ENT_STMT, relRef->argOneInt);
        break;
    case RELARG_WILDCARD:
        switch (relRef->argTwoSyn) {
        case ENT_ASSIGN:
            pkbDispatch.get_all_int_argTwo =
                    &PKB::get_all_assign;
            break;
        case ENT_CALL:
            pkbDispatch.get_all_int_argTwo =
                    &PKB::get_all_call;
            break;
        case ENT_IF:
            pkbDispatch.get_all_int_argTwo =
                    &PKB::get_all_if;
            break;
        case ENT_WHILE:
            pkbDispatch.get_all_int_argTwo =
                    &PKB::get_all_while;
            break;
        case ENT_STMT:
        case ENT_PROGLINE:
            pkbDispatch.get_all_int_argTwo =
                    &PKB::get_all_stmt;
            break;
        default:
            assert(false);
        }
        pkbDispatch.f_smth_int_argTwo =
                &PKB::parent_X_Y_smth_int_Y;
        QueryEvaluator::ev_relRef_X_syn_wild_int_0(rTable, pkb, relRef,
                pkbDispatch);
        break;
    default:
        assert(false);
    }
}

void __cdecl QueryEvaluator::ev_relRef_X_syn_1_parent(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef)
{
    EvalPKBDispatch pkbDispatch;
    switch (relRef->argOneType) {
    case RELARG_INT:
        pkbDispatch.f_int_argOne_int_argTwo =
                &PKB::parent_query_int_X_int_Y;
        QueryEvaluator::ev_relRef_X_syn_int_int_1(rTable, pkb, relRef,
                pkbDispatch, ENT_STMT, relRef->argOneInt);
        break;
    case RELARG_WILDCARD:
        pkbDispatch.f_smth_int_argTwo =
                &PKB::parent_X_Y_smth_int_Y;
        QueryEvaluator::ev_relRef_X_syn_wild_int_1(rTable, pkb, relRef,
                pkbDispatch);
        break;
    default:
        assert(false);
    }
}

void __cdecl QueryEvaluator::ev_relRef_X_syn_0_parentStar(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef)
{
    EvalPKBDispatch pkbDispatch;
    switch (relRef->argOneType) {
    case RELARG_INT:
        pkbDispatch.get_int_set_argTwo_from_int_argOne =
                &PKB::parentStar_X_Y_get_int_Y_from_int_X;
        QueryEvaluator::ev_relRef_X_syn_int_int_0(rTable, pkb, relRef,
                pkbDispatch, ENT_STMT, relRef->argOneInt);
        break;
    case RELARG_WILDCARD:
        switch (relRef->argTwoSyn) {
        case ENT_ASSIGN:
            pkbDispatch.get_all_int_argTwo =
                    &PKB::get_all_assign;
            break;
        case ENT_CALL:
            pkbDispatch.get_all_int_argTwo =
                    &PKB::get_all_call;
            break;
        case ENT_IF:
            pkbDispatch.get_all_int_argTwo =
                    &PKB::get_all_if;
            break;
        case ENT_WHILE:
            pkbDispatch.get_all_int_argTwo =
                    &PKB::get_all_while;
            break;
        case ENT_STMT:
        case ENT_PROGLINE:
            pkbDispatch.get_all_int_argTwo =
                    &PKB::get_all_stmt;
            break;
        default:
            assert(false);
        }
        pkbDispatch.f_smth_int_argTwo =
                &PKB::parentStar_X_Y_smth_int_Y;
        QueryEvaluator::ev_relRef_X_syn_wild_int_0(rTable, pkb, relRef,
                pkbDispatch);
        break;
    default:
        assert(false);
    }
}

void __cdecl QueryEvaluator::ev_relRef_X_syn_1_parentStar(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef)
{
    EvalPKBDispatch pkbDispatch;
    switch (relRef->argOneType) {
    case RELARG_INT:
        pkbDispatch.f_int_argOne_int_argTwo =
                &PKB::parentStar_query_int_X_int_Y;
        QueryEvaluator::ev_relRef_X_syn_int_int_1(rTable, pkb, relRef,
                pkbDispatch, ENT_STMT, relRef->argOneInt);
        break;
    case RELARG_WILDCARD:
        pkbDispatch.f_smth_int_argTwo =
                &PKB::parentStar_X_Y_smth_int_Y;
        QueryEvaluator::ev_relRef_X_syn_wild_int_1(rTable, pkb, relRef,
                pkbDispatch);
        break;
    default:
        assert(false);
    }
}

void __cdecl QueryEvaluator::ev_relRef_X_syn_0_followsAndStar(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef)
{
    EvalPKBDispatch pkbDispatch;
    switch (relRef->argOneType) {
    case RELARG_INT:
        if (REL_FOLLOWS == relRef->relType) {
            pkbDispatch.get_int_set_argTwo_from_int_argOne =
                    &PKB::follows_X_Y_get_int_Y_from_int_X;
        } else if (REL_FOLLOWS_STAR == relRef->relType) {
            pkbDispatch.get_int_set_argTwo_from_int_argOne =
                    &PKB::followsStar_X_Y_get_int_Y_from_int_X;
        } else {
            assert(false);
        }
        QueryEvaluator::ev_relRef_X_syn_int_int_0(rTable, pkb, relRef,
                pkbDispatch, ENT_STMT, relRef->argOneInt);
        break;
    case RELARG_WILDCARD:
        switch (relRef->argTwoSyn) {
        case ENT_ASSIGN:
            pkbDispatch.get_all_int_argTwo =
                    &PKB::get_all_assign;
            break;
        case ENT_CALL:
            pkbDispatch.get_all_int_argTwo =
                    &PKB::get_all_call;
            break;
        case ENT_IF:
            pkbDispatch.get_all_int_argTwo =
                    &PKB::get_all_if;
            break;
        case ENT_WHILE:
            pkbDispatch.get_all_int_argTwo =
                    &PKB::get_all_while;
            break;
        case ENT_STMT:
        case ENT_PROGLINE:
            pkbDispatch.get_all_int_argTwo =
                    &PKB::get_all_stmt;
            break;
        default:
            assert(false);
        }
        if (REL_FOLLOWS == relRef->relType) {
            pkbDispatch.f_smth_int_argTwo =
                    &PKB::follows_X_Y_smth_int_Y;
        } else if (REL_FOLLOWS_STAR == relRef->relType) {
            pkbDispatch.f_smth_int_argTwo =
                    &PKB::followsStar_X_Y_smth_int_Y;
        } else {
            assert(false);
        }
        QueryEvaluator::ev_relRef_X_syn_wild_int_0(rTable, pkb,
                relRef, pkbDispatch);
        break;
    default:
        assert(false);
    }
}

void __cdecl QueryEvaluator::ev_relRef_X_syn_1_followsAndStar(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef)
{
    EvalPKBDispatch pkbDispatch;
    switch (relRef->argOneType) {
    case RELARG_INT:
        if (REL_FOLLOWS == relRef->relType) {
            pkbDispatch.f_int_argOne_int_argTwo =
                    &PKB::follows_query_int_X_int_Y;
        } else if (REL_FOLLOWS_STAR == relRef->relType) {
            pkbDispatch.f_int_argOne_int_argTwo =
                    &PKB::followsStar_query_int_X_int_Y;
        } else {
            assert(false);
        }
        QueryEvaluator::ev_relRef_X_syn_int_int_1(rTable, pkb, relRef,
                pkbDispatch, ENT_STMT, relRef->argOneInt);
        break;
    case RELARG_WILDCARD:
        if (REL_FOLLOWS == relRef->relType) {
            pkbDispatch.f_smth_int_argTwo =
                    &PKB::follows_X_Y_smth_int_Y;
        } else if (REL_FOLLOWS_STAR == relRef->relType) {
            pkbDispatch.f_smth_int_argTwo =
                    &PKB::followsStar_X_Y_smth_int_Y;
        } else {
            assert(false);
        }
        QueryEvaluator::ev_relRef_X_syn_wild_int_1(rTable, pkb, relRef,
                pkbDispatch);
        break;
    default:
        assert(false);
    }
}

void __cdecl QueryEvaluator::ev_relRef_X_syn_0_nextAndStar(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef)
{
    EvalPKBDispatch pkbDispatch;
    switch (relRef->argOneType) {
    case RELARG_INT:
        if (REL_NEXT == relRef->relType) {
            pkbDispatch.get_int_set_argTwo_from_int_argOne =
                    &PKB::next_X_Y_get_int_Y_from_int_X;
        } else if (REL_NEXT_STAR == relRef->relType) {
            pkbDispatch.get_int_set_argTwo_from_int_argOne =
                    &PKB::nextStar_X_Y_get_int_Y_from_int_X;
        } else {
            assert(false);
        }
        QueryEvaluator::ev_relRef_X_syn_int_int_0(rTable, pkb, relRef,
                pkbDispatch, ENT_STMT, relRef->argOneInt);
        break;
    case RELARG_WILDCARD:
        switch (relRef->argTwoSyn) {
        case ENT_ASSIGN:
            pkbDispatch.get_all_int_argTwo =
                    &PKB::get_all_assign;
            break;
        case ENT_CALL:
            pkbDispatch.get_all_int_argTwo =
                    &PKB::get_all_call;
            break;
        case ENT_IF:
            pkbDispatch.get_all_int_argTwo =
                    &PKB::get_all_if;
            break;
        case ENT_WHILE:
            pkbDispatch.get_all_int_argTwo =
                    &PKB::get_all_while;
            break;
        case ENT_STMT:
        case ENT_PROGLINE:
            pkbDispatch.get_all_int_argTwo =
                    &PKB::get_all_stmt;
            break;
        default:
            assert(false);
        }
        if (REL_NEXT == relRef->relType) {
            pkbDispatch.f_smth_int_argTwo =
                    &PKB::next_X_Y_smth_int_Y;
        } else {
            pkbDispatch.f_smth_int_argTwo =
                    &PKB::nextStar_X_Y_smth_int_Y;
        }
        QueryEvaluator::ev_relRef_X_syn_wild_int_0(rTable, pkb, relRef,
                pkbDispatch);
        break;
    default:
        assert(false);
    }
}

void __cdecl QueryEvaluator::ev_relRef_X_syn_1_nextAndStar(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef)
{
    EvalPKBDispatch pkbDispatch;
    switch (relRef->argOneType) {
    case RELARG_INT:
        if (REL_NEXT == relRef->relType) {
            pkbDispatch.f_int_argOne_int_argTwo =
                    &PKB::next_query_int_X_int_Y;
        } else if (REL_NEXT_STAR == relRef->relType) {
            pkbDispatch.f_int_argOne_int_argTwo =
                    &PKB::nextStar_query_int_X_int_Y;
        } else {
            assert(false);
        }
        QueryEvaluator::ev_relRef_X_syn_int_int_1(rTable, pkb, relRef,
                pkbDispatch, ENT_STMT, relRef->argOneInt);
        break;
    case RELARG_WILDCARD:
        if (REL_NEXT == relRef->relType) {
            pkbDispatch.f_smth_int_argTwo =
                    &PKB::next_X_Y_smth_int_Y;
        } else if (REL_NEXT_STAR == relRef->relType) {
            pkbDispatch.f_smth_int_argTwo =
                    &PKB::nextStar_X_Y_smth_int_Y;
        } else {
            assert(false);
        }
        QueryEvaluator::ev_relRef_X_syn_wild_int_1(rTable, pkb, relRef,
                pkbDispatch);
        break;
    default:
        assert(false);
    }
}

void __cdecl QueryEvaluator::ev_relRef_X_syn_0_affectsAndStar(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef)
{
    EvalPKBDispatch pkbDispatch;
    switch (relRef->argOneType) {
    case RELARG_INT:
        if (REL_AFFECTS == relRef->relType) {
            pkbDispatch.get_int_set_argTwo_from_int_argOne =
                    &PKB::affects_X_Y_get_int_Y_from_int_X;
        } else if (REL_AFFECTS_STAR == relRef->relType) {
            pkbDispatch.get_int_set_argTwo_from_int_argOne =
                    &PKB::affectsStar_X_Y_get_int_Y_from_int_X;
        } else {
            assert(false);
        }
        QueryEvaluator::ev_relRef_X_syn_int_int_0(rTable, pkb, relRef,
                pkbDispatch, ENT_ASSIGN, relRef->argOneInt);
        break;
    case RELARG_WILDCARD:
        switch (relRef->argTwoSyn) {
        case ENT_ASSIGN:
            pkbDispatch.get_all_int_argTwo =
                    &PKB::get_all_assign;
            break;
        default:
            assert(false);
        }
        if (REL_AFFECTS == relRef->relType) {
            pkbDispatch.f_smth_int_argTwo =
                    &PKB::affects_X_Y_smth_int_Y;
        } else if (REL_AFFECTS_STAR == relRef->relType) {
            pkbDispatch.f_smth_int_argTwo =
                    &PKB::affectsStar_X_Y_smth_int_Y;
        } else {
            assert(false);
        }
        QueryEvaluator::ev_relRef_X_syn_wild_int_0(rTable, pkb, relRef,
                pkbDispatch);
        break;
    default:
        assert(false);
    }
}

void __cdecl QueryEvaluator::ev_relRef_X_syn_1_affectsAndStar(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef)
{
    EvalPKBDispatch pkbDispatch;
    switch (relRef->argOneType) {
    case RELARG_INT:
        if (REL_AFFECTS == relRef->relType) {
            pkbDispatch.f_int_argOne_int_argTwo =
                    &PKB::affects_query_int_X_int_Y;
        } else if (REL_AFFECTS_STAR == relRef->relType) {
            pkbDispatch.f_int_argOne_int_argTwo =
                    &PKB::affectsStar_query_int_X_int_Y;
        } else {
            assert(false);
        }
        QueryEvaluator::ev_relRef_X_syn_int_int_1(rTable, pkb, relRef,
                pkbDispatch, ENT_ASSIGN, relRef->argOneInt);
        break;
    case RELARG_WILDCARD:
        if (REL_AFFECTS == relRef->relType) {
            pkbDispatch.f_smth_int_argTwo =
                    &PKB::affects_X_Y_smth_int_Y;
        } else if (REL_AFFECTS_STAR == relRef->relType) {
            pkbDispatch.f_smth_int_argTwo =
                    &PKB::affectsStar_X_Y_smth_int_Y;
        } else {
            assert(false);
        }
        QueryEvaluator::ev_relRef_X_syn_wild_int_1(rTable, pkb, relRef,
                pkbDispatch);
        break;
    default:
        assert(false);
    }
}

void __cdecl QueryEvaluator::ev_relRef_X_syn_string_string_0(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
        const EvalPKBDispatch& disp, DesignEnt xType, const string& xVal)
{
    assert(NULL != disp.get_string_set_argTwo_from_string_argOne);
    rTable.syn_0_transaction_begin(relRef->argTwoString, RV_STRING);
    const set<string> synSet =
            (pkb->*(disp.get_string_set_argTwo_from_string_argOne))
                    (xType, relRef->argTwoSyn, xVal);
    for (set<string>::const_iterator synIt = synSet.begin();
            synIt != synSet.end(); synIt++) {
        const string& synVal = *synIt;
        rTable.syn_0_add_row(synVal);
    }
    rTable.syn_0_transaction_end();
}

void __cdecl QueryEvaluator::ev_relRef_X_syn_string_string_1(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
        const EvalPKBDispatch& disp, DesignEnt xType, const string& xVal)
{
    assert(NULL != disp.f_string_argOne_string_argTwo);
    pair<const vector<Record> *, int> viPair =
            rTable.syn_1_transaction_begin(relRef->argTwoString);
    const vector<Record>& records = *(viPair.first);
    int nrRecords = records.size();
    int colIdx = viPair.second;
    DesignEnt synEntType = relRef->argTwoSyn;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = records[i];
        const pair<string, int> siPair = record.get_column(colIdx);
        const string& synVal = siPair.first;
        if ((pkb->*(disp.f_string_argOne_string_argTwo))
                (xType, xVal, synEntType, synVal)) {
            rTable.syn_1_mark_row_ok(i);
        }
    }
    rTable.syn_1_transaction_end();
}

void __cdecl QueryEvaluator::ev_relRef_X_syn_int_string_0(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
        const EvalPKBDispatch& disp, DesignEnt xType, int xVal)
{
    assert(NULL != disp.get_string_set_argTwo_from_int_argOne);
    rTable.syn_0_transaction_begin(relRef->argTwoString, RV_STRING);
    const set<string>& synSet =
            (pkb->*(disp.get_string_set_argTwo_from_int_argOne))
                    (xType, relRef->argTwoSyn, xVal);
    for (set<string>::const_iterator synIt = synSet.begin();
            synIt != synSet.end(); synIt++) {
        const string& synVal = *synIt;
        rTable.syn_0_add_row(synVal);
    }
    rTable.syn_0_transaction_end();
}

void __cdecl QueryEvaluator::ev_relRef_X_syn_int_string_1(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
        const EvalPKBDispatch& disp, DesignEnt xType, int xVal)
{
    assert(NULL != disp.f_int_argOne_string_argTwo);
    pair<const vector<Record> *, int> viPair =
            rTable.syn_1_transaction_begin(relRef->argTwoString);
    const vector<Record>& records = *(viPair.first);
    int nrRecords = records.size();
    int colIdx = viPair.second;
    DesignEnt synEntType = relRef->argTwoSyn;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = records[i];
        const pair<string, int> siPair = record.get_column(colIdx);
        const string& synVal = siPair.first;
        if ((pkb->*(disp.f_int_argOne_string_argTwo))
                (xType, xVal, synEntType, synVal)) {
            rTable.syn_1_mark_row_ok(i);
        }
    }
    rTable.syn_1_transaction_end();
}

void __cdecl QueryEvaluator::ev_relRef_X_syn_wild_string_0(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
        const EvalPKBDispatch& disp)
{
    assert(NULL != disp.get_all_string_argTwo);
    assert(NULL != disp.f_smth_string_argTwo);
    rTable.syn_0_transaction_begin(relRef->argTwoString, RV_STRING);
    const set<string>& synSet =
            (pkb->*(disp.get_all_string_argTwo))();
    DesignEnt synEntType = relRef->argTwoSyn;
    for (set<string>::const_iterator synIt = synSet.begin();
            synIt != synSet.end(); synIt++) {
        const string& synVal = *synIt;
        if ((pkb->*(disp.f_smth_string_argTwo)) (synEntType, synVal)) {
            rTable.syn_0_add_row(synVal);
        }
    }
    rTable.syn_0_transaction_end();
}

void __cdecl QueryEvaluator::ev_relRef_X_syn_wild_string_1(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
        const EvalPKBDispatch& disp)
{
    assert(NULL != disp.f_smth_string_argTwo);
    pair<const vector<Record> *, int> viPair =
            rTable.syn_1_transaction_begin(relRef->argTwoString);
    const vector<Record>& records = *(viPair.first);
    int nrRecords = records.size();
    int colIdx = viPair.second;
    DesignEnt synEntType = relRef->argTwoSyn;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = records[i];
        const pair<string, int> siPair =
                record.get_column(colIdx);
        const string& synVal = siPair.first;
        if ((pkb->*(disp.f_smth_string_argTwo)) (synEntType, synVal)) {
            rTable.syn_1_mark_row_ok(i);
        }
    }
    rTable.syn_1_transaction_end();
}

void __cdecl QueryEvaluator::ev_relRef_X_syn_int_int_0(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
        const EvalPKBDispatch& disp, DesignEnt xType, int xVal)
{
    assert(NULL != disp.get_int_set_argTwo_from_int_argOne);
    rTable.syn_0_transaction_begin(relRef->argTwoString, RV_INT);
    const set<int>& synSet =
            (pkb->*(disp.get_int_set_argTwo_from_int_argOne))
                    (xType, relRef->argTwoSyn, xVal);
    for (set<int>::const_iterator synIt = synSet.begin();
            synIt != synSet.end(); synIt++) {
        rTable.syn_0_add_row(*synIt);
    }
    rTable.syn_0_transaction_end();
}

void __cdecl QueryEvaluator::ev_relRef_X_syn_int_int_1(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
        const EvalPKBDispatch& disp, DesignEnt xType, int xVal)
{
    assert(NULL != disp.f_int_argOne_int_argTwo);
    pair<const vector<Record> *, int> viPair =
            rTable.syn_1_transaction_begin(relRef->argTwoString);
    const vector<Record>& records = *(viPair.first);
    int nrRecords = records.size();
    int colIdx = viPair.second;
    DesignEnt synEntType = relRef->argTwoSyn;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = records[i];
        const pair<string, int>& siPair = record.get_column(colIdx);
        int synVal = siPair.second;
        if ((pkb->*(disp.f_int_argOne_int_argTwo))
                (xType, xVal, synEntType, synVal)) {
            rTable.syn_1_mark_row_ok(i);
        }
    }
    rTable.syn_1_transaction_end();
}

void __cdecl QueryEvaluator::ev_relRef_X_syn_wild_int_0(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
        const EvalPKBDispatch& disp)
{
    assert(NULL != disp.get_all_int_argTwo);
    assert(NULL != disp.f_smth_int_argTwo);
    rTable.syn_0_transaction_begin(relRef->argTwoString, RV_INT);
    const set<int>& synSet =
            (pkb->*(disp.get_all_int_argTwo))();
    DesignEnt synEntType = relRef->argTwoSyn;
    for (set<int>::const_iterator synIt = synSet.begin();
            synIt != synSet.end(); synIt++) {
        int synVal = *synIt;
        if ((pkb->*(disp.f_smth_int_argTwo)) (synEntType, synVal)) {
            rTable.syn_0_add_row(synVal);
        }
    }
    rTable.syn_0_transaction_end();
}

void __cdecl QueryEvaluator::ev_relRef_X_syn_wild_int_1(
        ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
        const EvalPKBDispatch& disp)
{
    assert(NULL != disp.f_smth_int_argTwo);
    pair<const vector<Record> *, int> viPair =
            rTable.syn_1_transaction_begin(relRef->argTwoString);
    const vector<Record>& records = *(viPair.first);
    int nrRecords = records.size();
    int colIdx = viPair.second;
    DesignEnt synEntType = relRef->argTwoSyn;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = records[i];
        const pair<string, int>& siPair = record.get_column(colIdx);
        int synVal = siPair.second;
        if ((pkb->*(disp.f_smth_int_argTwo)) (synEntType, synVal)) {
            rTable.syn_1_mark_row_ok(i);
        }
    }
    rTable.syn_1_transaction_end();
}

void QueryEvaluator::evaluate_withClause(int rTableIdx,
        const GenericRef *genRef)
{
    const WithClause *withClausePtr =
        dynamic_cast<const WithClause *>(genRef);
    assert(NULL != withClausePtr);
    const WithClause& withClause = *withClausePtr;
    if (REF_ATTRREF == withClause.leftRef.refType &&
            REF_ATTRREF == withClause.rightRef.refType) {
        this->ev_withClause_attrRef_attrRef(rTableIdx, withClause);
    } else if (REF_ATTRREF == withClause.leftRef.refType) {
        this->ev_withClause_attrRef_X(rTableIdx, withClause);
    } else {
        // Either both are attrRef or lhs is attrRef
        // it cannot be any other case
        assert(false);
    }
}

void QueryEvaluator::ev_withClause_attrRef_attrRef(int rTableIdx,
        const WithClause& withClause)
{
    using std::swap;
    BaseType leftRefType =
            refSynType_to_BaseType(withClause.leftRef.refSynType);
    BaseType rightRefType =
            refSynType_to_BaseType(withClause.rightRef.refSynType);
    assert(BASETYPE_INT == leftRefType ||
            BASETYPE_STRING == leftRefType);
    assert(leftRefType == rightRefType);
    const ResultsTable& rTable = this->resultsTable[rTableIdx];
    EvalPKBDispatch pkbDispatch;
    if (BASETYPE_INT == leftRefType) {
        bool seenLeftSyn =
                rTable.has_synonym(withClause.leftRef.refStringVal);
        bool seenRightSyn =
                rTable.has_synonym(withClause.rightRef.refStringVal);
        if (seenLeftSyn && seenRightSyn) {
            if (rTable.syn_in_same_table(withClause.leftRef.refStringVal,
                    withClause.rightRef.refStringVal)) {
                this->ev_withClause_ii_11(rTableIdx, withClause);
            } else {
                this->ev_withClause_ii_22(rTableIdx, withClause);
            }
        } else if (seenLeftSyn) {
            this->ev_withClause_attrRef_attrRef_ii_10_setup(rTableIdx,
                    withClause, pkbDispatch);
            this->ev_withClause_ii_10(rTableIdx, withClause, pkbDispatch);
        } else if (seenRightSyn) {
            this->ev_withClause_attrRef_attrRef_ii_01_setup(rTableIdx,
                    withClause, pkbDispatch);
            this->ev_withClause_ii_01(rTableIdx, withClause, pkbDispatch);
        } else {
            this->ev_withClause_attrRef_attrRef_ii_00_setup(rTableIdx,
                    withClause, pkbDispatch);
            this->ev_withClause_ii_00(rTableIdx, withClause, pkbDispatch);
        }
    } else if (BASETYPE_STRING == leftRefType) {
        bool seenLeftSyn =
                rTable.has_synonym(withClause.leftRef.refStringVal);
        bool seenRightSyn =
                rTable.has_synonym(withClause.rightRef.refStringVal);
        RefSynType leftRefSynType = withClause.leftRef.refSynType;
        RefSynType rightRefSynType = withClause.rightRef.refSynType;
        if (seenLeftSyn && seenRightSyn) {
            if (rTable.syn_in_same_table(withClause.leftRef.refStringVal,
                    withClause.rightRef.refStringVal)) {
                if (REFSYN_CALL_PROCNAME == leftRefSynType &&
                        REFSYN_CALL_PROCNAME == rightRefSynType) {
                    this->ev_withClause_ss_cpn_cpn_11(rTableIdx,
                            withClause);
                } else if (REFSYN_CALL_PROCNAME == leftRefSynType) {
                    this->ev_withClause_ss_cpn_X_11(rTableIdx,
                            withClause);
                } else if (REFSYN_CALL_PROCNAME == rightRefSynType) {
                    WithClause tmpWithClause(withClause);
                    swap(tmpWithClause.leftRef, tmpWithClause.rightRef);
                    this->ev_withClause_ss_cpn_X_11(rTableIdx,
                            tmpWithClause);
                } else {
                    this->ev_withClause_ss_11(rTableIdx, withClause);
                }
            } else {
                if (REFSYN_CALL_PROCNAME == leftRefSynType &&
                        REFSYN_CALL_PROCNAME == rightRefSynType) {
                    this->ev_withClause_ss_cpn_cpn_22(rTableIdx,
                            withClause);
                } else if (REFSYN_CALL_PROCNAME == leftRefSynType) {
                    this->ev_withClause_ss_cpn_X_22(rTableIdx,
                            withClause);
                } else if (REFSYN_CALL_PROCNAME == rightRefSynType) {
                    WithClause tmpWithClause(withClause);
                    swap(tmpWithClause.leftRef, tmpWithClause.rightRef);
                    this->ev_withClause_ss_cpn_X_22(rTableIdx,
                            tmpWithClause);
                } else {
                    this->ev_withClause_ss_22(rTableIdx, withClause);
                }
            }
        } else if (seenLeftSyn) {
            if (REFSYN_CALL_PROCNAME == leftRefSynType &&
                    REFSYN_CALL_PROCNAME == rightRefSynType) {
                WithClause tmpWithClause(withClause);
                swap(tmpWithClause.leftRef, tmpWithClause.rightRef);
                // convert 10 case to 01 case
                this->ev_withClause_ss_cpn_cpn_01(rTableIdx,
                        tmpWithClause);
            } else if (REFSYN_CALL_PROCNAME == leftRefSynType) {
                this->ev_withClause_attrRef_attrRef_ss_10_setup(rTableIdx,
                        withClause, pkbDispatch);
                this->ev_withClause_ss_cpn_X_10(rTableIdx,
                        withClause, pkbDispatch);
            } else if (REFSYN_CALL_PROCNAME == rightRefSynType) {
                // 10 X_cpn case.
                // X = cpn is impossible case due to lexicographical
                // ordering of RefSynType (after withClause.normalize()),
                // since call.procName is before procedure.procName and
                // variable.varName
                // convert 10 X_cpn case to 01 cpn_X case
                assert(false);
            } else {
                // convert to 01 case
                WithClause tmpWithClause(withClause);
                swap(tmpWithClause.leftRef, tmpWithClause.rightRef);
                this->ev_withClause_attrRef_attrRef_ii_01_setup(rTableIdx,
                        tmpWithClause, pkbDispatch);
                this->ev_withClause_ss_01(rTableIdx, tmpWithClause,
                        pkbDispatch);
            }
        } else if (seenRightSyn) {
            this->ev_withClause_attrRef_attrRef_ss_01_setup(rTableIdx,
                    withClause, pkbDispatch);
            if (REFSYN_CALL_PROCNAME == leftRefSynType &&
                    REFSYN_CALL_PROCNAME == rightRefSynType) {
                this->ev_withClause_ss_cpn_cpn_01(rTableIdx, withClause);
            } else if (REFSYN_CALL_PROCNAME == leftRefSynType) {
                this->ev_withClause_ss_cpn_X_01(rTableIdx, withClause);
            } else if (REFSYN_CALL_PROCNAME == rightRefSynType) {
                // 01 X_cpn case.
                // X = cpn is impossible case due to lexicographical
                // ordering of RefSynType (after withClause.normalize()),
                // since call.procName is before procedure.procName and
                // variable.varName
                // convert 10 X_cpn case to 01 cpn_X case
                assert(false);
            } else {
                this->ev_withClause_ss_01(rTableIdx, withClause,
                        pkbDispatch);
            }
        } else {
            this->ev_withClause_attrRef_attrRef_ss_00_setup(rTableIdx,
                    withClause, pkbDispatch);
            if (REFSYN_CALL_PROCNAME == leftRefSynType &&
                    REFSYN_CALL_PROCNAME == rightRefSynType) {
                this->ev_withClause_ss_cpn_cpn_00(rTableIdx, withClause);
            } else if (REFSYN_CALL_PROCNAME == leftRefSynType) {
                this->ev_withClause_ss_cpn_X_00(rTableIdx, withClause,
                        pkbDispatch);
            } else if (REFSYN_CALL_PROCNAME == rightRefSynType) {
                // convert 00 X_cpn case to 00 cpn_X case
                WithClause tmpWithClause(withClause);
                swap(tmpWithClause.leftRef, tmpWithClause.rightRef);
                pkbDispatch.reset();
                this->ev_withClause_attrRef_attrRef_ss_00_setup(rTableIdx,
                        tmpWithClause, pkbDispatch);
                this->ev_withClause_ss_cpn_X_00(rTableIdx, tmpWithClause,
                        pkbDispatch);
            } else {
                this->ev_withClause_ss_00(rTableIdx, withClause,
                        pkbDispatch);
            }
        }
    } else {
        assert(false);
    }
}

QueryEvaluator::pkbGetAllIntFn
QueryEvaluator::get_all_int_pkb_method_from_RefSynType(
        RefSynType refSynType)
{
    switch (refSynType) {
    case REFSYN_ASSIGN:
        return &PKB::get_all_assign;
        break;
    case REFSYN_CALL:
        return &PKB::get_all_call;
        break;
    case REFSYN_IF:
        return &PKB::get_all_if;
        break;
    case REFSYN_WHILE:
        return &PKB::get_all_while;
        break;
    case REFSYN_STMT:
    case REFSYN_PROGLINE:
    case REFSYN_PROGLINE_PROGLINE_NO:
        return &PKB::get_all_stmt;
        break;
    case REFSYN_STMTLST:
        return &PKB::get_all_stmtLst;
        break;
    case REFSYN_CONST:
        return &PKB::get_all_const;
        break;
    default:
        assert(false);
    }
}

QueryEvaluator::pkbGetAllStringFn
QueryEvaluator::get_all_string_pkb_method_from_RefSynType(
        RefSynType refSynType)
{
    switch (refSynType) {
    case REFSYN_PROC:
        return &PKB::get_all_procs;
        break;
    case REFSYN_VAR:
        return &PKB::get_all_vars;
        break;
    case REFSYN_CALL_PROCNAME:
        // special case, deal with this in the ss methods
        return NULL;
        break;
    default:
        assert(false);
    }
}

QueryEvaluator::pkbHasAnyIntFn
QueryEvaluator::get_hasAnyInt_pkb_method_from_RefSynType(
        RefSynType refSynType)
{
    switch (refSynType) {
    case REFSYN_ASSIGN:
        return &PKB::has_assign;
        break;
    case REFSYN_CALL:
        return &PKB::has_call;
        break;
    case REFSYN_IF:
        return &PKB::has_if;
        break;
    case REFSYN_WHILE:
        return &PKB::has_while;
        break;
    case REFSYN_STMT:
    case REFSYN_PROGLINE:
    case REFSYN_PROGLINE_PROGLINE_NO:
        return &PKB::has_stmt;
        break;
    case REFSYN_STMTLST:
        return &PKB::has_stmtLst;
        break;
    case REFSYN_CONST:
        return &PKB::has_const;
        break;
    default:
        assert(false);
    }
}

QueryEvaluator::pkbHasAnyStringFn
QueryEvaluator::get_hasAnyString_pkb_method_from_RefSynType(
        RefSynType refSynType)
{
    switch (refSynType) {
    case REFSYN_PROC:
        return &PKB::has_procedure;
        break;
    case REFSYN_VAR:
        return &PKB::has_variable;
        break;
    case REFSYN_CALL_PROCNAME:
        return &PKB::has_call_procName;
        break;
    default:
        assert(false);
    }
}

void QueryEvaluator::ev_withClause_attrRef_attrRef_ii_00_setup(
        int rTableIdx, const WithClause& withClause,
        EvalPKBDispatch& pkbDispatch) const
{
    pkbDispatch.get_all_int_argOne =
            QueryEvaluator::get_all_int_pkb_method_from_RefSynType(
                    withClause.leftRef.refSynType);
    pkbDispatch.has_any_int =
            QueryEvaluator::get_hasAnyInt_pkb_method_from_RefSynType(
                    withClause.rightRef.refSynType);
}

void QueryEvaluator::ev_withClause_attrRef_attrRef_ii_01_setup(
        int rTableIdx, const WithClause& withClause,
        EvalPKBDispatch& pkbDispatch) const
{
    pkbDispatch.has_any_int =
            QueryEvaluator::get_hasAnyInt_pkb_method_from_RefSynType(
                    withClause.leftRef.refSynType);
}

void QueryEvaluator::ev_withClause_attrRef_attrRef_ii_10_setup(
        int rTableIdx, const WithClause& withClause,
        EvalPKBDispatch& pkbDispatch) const
{
    pkbDispatch.has_any_int =
            QueryEvaluator::get_hasAnyInt_pkb_method_from_RefSynType(
                    withClause.rightRef.refSynType);
}

void QueryEvaluator::ev_withClause_attrRef_attrRef_ss_00_setup(
        int rTableIdx, const WithClause& withClause,
        EvalPKBDispatch& pkbDispatch) const
{
    pkbDispatch.get_all_string_argOne =
            QueryEvaluator::get_all_string_pkb_method_from_RefSynType(
                    withClause.leftRef.refSynType);
    pkbDispatch.has_any_string =
            QueryEvaluator::get_hasAnyString_pkb_method_from_RefSynType(
                    withClause.rightRef.refSynType);
}

void QueryEvaluator::ev_withClause_attrRef_attrRef_ss_01_setup(
        int rTableIdx, const WithClause& withClause,
        EvalPKBDispatch& pkbDispatch) const
{
    pkbDispatch.has_any_string =
            QueryEvaluator::get_hasAnyString_pkb_method_from_RefSynType(
                    withClause.leftRef.refSynType);
}

void QueryEvaluator::ev_withClause_attrRef_attrRef_ss_10_setup(
        int rTableIdx, const WithClause& withClause,
        EvalPKBDispatch& pkbDispatch) const
{
    pkbDispatch.has_any_string =
            QueryEvaluator::get_hasAnyString_pkb_method_from_RefSynType(
                    withClause.rightRef.refSynType);
}

void QueryEvaluator::ev_withClause_ii_00(int rTableIdx,
        const WithClause& withClause,
        const EvalPKBDispatch& disp)
{
    assert(NULL != disp.get_all_int_argOne);
    assert(NULL != disp.has_any_int);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    rTable.syn_00_transaction_begin(withClause.leftRef.refStringVal,
            RV_INT, withClause.rightRef.refStringVal, RV_INT);
    const set<int>& argOneSet =
            (this->pkb->*(disp.get_all_int_argOne))();
    for (set<int>::const_iterator argOneIt = argOneSet.begin();
            argOneIt != argOneSet.end(); argOneIt++) {
        int argOneVal = *argOneIt;
        if ((this->pkb->*(disp.has_any_int))(argOneVal)) {
            rTable.syn_00_add_row(argOneVal, argOneVal);
        }
    }
    rTable.syn_00_transaction_end();
}

void QueryEvaluator::ev_withClause_ii_01(int rTableIdx,
        const WithClause& withClause,
        const EvalPKBDispatch& disp)
{
    assert(NULL != disp.has_any_int);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    pair<const vector<Record> *, int> viPair =
            rTable.syn_01_transaction_begin(
                    withClause.leftRef.refStringVal,
                    withClause.rightRef.refStringVal,
                    RV_INT);
    const vector<Record>& records = *(viPair.first);
    int nrRecords = records.size();
    int colIdx = viPair.second;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = records[i];
        const pair<string, int>& siPair = record.get_column(colIdx);
        int argTwoVal = siPair.second;
        if ((this->pkb->*(disp.has_any_int))(argTwoVal)) {
            rTable.syn_01_augment_new_row(i, argTwoVal);
        }
    }
    rTable.syn_01_transaction_end();
}

void QueryEvaluator::ev_withClause_ii_10(int rTableIdx,
        const WithClause& withClause,
        const EvalPKBDispatch& disp)
{
    assert(NULL != disp.has_any_int);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    pair<const vector<Record> *, int> viPair =
            rTable.syn_10_transaction_begin(
                    withClause.leftRef.refStringVal,
                    withClause.rightRef.refStringVal,
                    RV_INT);
    const vector<Record>& records = *(viPair.first);
    int nrRecords = records.size();
    int colIdx = viPair.second;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = records[i];
        const pair<string, int>& siPair = record.get_column(colIdx);
        int argTwoVal = siPair.second;
        if ((this->pkb->*(disp.has_any_int))(argTwoVal)) {
            rTable.syn_10_augment_new_row(i, argTwoVal);
        }
    }
    rTable.syn_10_transaction_end();
}

void QueryEvaluator::ev_withClause_ii_11(int rTableIdx,
        const WithClause& withClause)
{
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    pair<const vector<Record> *, pair<int, int> > viiPair =
            rTable.syn_11_transaction_begin(
                    withClause.leftRef.refStringVal,
                    withClause.rightRef.refStringVal);
    const vector<Record>& records = *(viiPair.first);
    int nrRecords = records.size();
    int colOne = viiPair.second.first;
    int colTwo = viiPair.second.second;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = records[i];
        const pair<string, int>& pOne = record.get_column(colOne);
        const int argOneVal = pOne.second;
        const pair<string, int>& pTwo = record.get_column(colTwo);
        const int argTwoVal = pTwo.second;
        if (argOneVal == argTwoVal) {
            rTable.syn_11_mark_row_ok(i);
        }
    }
    rTable.syn_11_transaction_end();
}

void QueryEvaluator::ev_withClause_ii_22(int rTableIdx,
        const WithClause& withClause)
{
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    pair<pair<const vector<Record> *, int>,
         pair<const vector<Record> *, int> > vipPair =
            rTable.syn_22_transaction_begin(
                    withClause.leftRef.refStringVal,
                    withClause.rightRef.refStringVal);
    const vector<Record>& recordsOne = *(vipPair.first.first);
    int nrRecordsOne = recordsOne.size();
    int colOne = vipPair.first.second;
    vector<int> argOneVec;
    for (int i = 0; i < nrRecordsOne; i++) {
        const Record& record = recordsOne[i];
        const pair<string, int>& siPair = record.get_column(colOne);
        int argOneVal = siPair.second;
        argOneVec.push_back(argOneVal);
    }
    const vector<Record>& recordsTwo = *(vipPair.second.first);
    int nrRecordsTwo = recordsTwo.size();
    int colTwo = vipPair.second.second;
    vector<int> argTwoVec;
    for (int i = 0; i < nrRecordsTwo; i++) {
        const Record& record = recordsTwo[i];
        const pair<string, int>& siPair = record.get_column(colTwo);
        int argTwoVal = siPair.second;
        argTwoVec.push_back(argTwoVal);
    }
    for (int rowOne = 0; rowOne < nrRecordsOne; rowOne++) {
        const int argOneVal = argOneVec[rowOne];
        for (int rowTwo = 0; rowTwo < nrRecordsTwo; rowTwo++) {
            const int argTwoVal = argTwoVec[rowTwo];
            if (argOneVal == argTwoVal) {
                rTable.syn_22_add_row(rowOne, rowTwo);
            }
        }
    }
    rTable.syn_22_transaction_end();
}

void QueryEvaluator::ev_withClause_ss_00(int rTableIdx,
        const WithClause& withClause,
        const EvalPKBDispatch& disp)
{
    assert(NULL != disp.get_all_string_argOne);
    assert(NULL != disp.has_any_string);
    assert(REFSYN_CALL_PROCNAME != withClause.leftRef.refSynType);
    assert(REFSYN_CALL_PROCNAME != withClause.rightRef.refSynType);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    rTable.syn_00_transaction_begin(withClause.leftRef.refStringVal,
            RV_STRING, withClause.rightRef.refStringVal, RV_STRING);
    const set<string>& argOneSet =
            (this->pkb->*(disp.get_all_string_argOne))();
    for (set<string>::const_iterator argOneIt = argOneSet.begin();
            argOneIt != argOneSet.end(); argOneIt++) {
        const string& argOneVal = *argOneIt;
        if ((this->pkb->*(disp.has_any_string))(argOneVal)) {
            rTable.syn_00_add_row(argOneVal, argOneVal);
        }
    }
    rTable.syn_00_transaction_end();
}

void QueryEvaluator::ev_withClause_ss_cpn_cpn_00(int rTableIdx,
        const WithClause& withClause)
{
    // Both are call.procName and not seen
    assert(REFSYN_CALL_PROCNAME == withClause.leftRef.refSynType);
    assert(REFSYN_CALL_PROCNAME == withClause.rightRef.refSynType);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    rTable.syn_00_transaction_begin(withClause.leftRef.refStringVal,
            RV_INT, withClause.rightRef.refStringVal, RV_INT);
    const set<int>& argOneSet = this->pkb->get_all_call();
    for (set<int>::const_iterator argOneIt = argOneSet.begin();
            argOneIt != argOneSet.end(); argOneIt++) {
        int argOneVal = *argOneIt;
        const string& procCalled = this->pkb->get_call_procName(argOneVal);
        const set<int>& callStmtCallingProc =
                this->pkb->get_call_stmt_calling(procCalled);
        for (set<int>::const_iterator argTwoIt =
                callStmtCallingProc.begin();
                argTwoIt != callStmtCallingProc.end(); argTwoIt++) {
            rTable.syn_00_add_row(argOneVal, *argTwoIt);
        }
    }
    rTable.syn_00_transaction_end();
}

void QueryEvaluator::ev_withClause_ss_cpn_X_00(int rTableIdx,
        const WithClause& withClause, const EvalPKBDispatch& disp)
{
    assert(REFSYN_CALL_PROCNAME == withClause.leftRef.refSynType);
    assert(REFSYN_CALL_PROCNAME != withClause.rightRef.refSynType);
    assert(NULL != disp.has_any_string);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    rTable.syn_00_transaction_begin(withClause.leftRef.refStringVal,
            RV_INT, withClause.rightRef.refStringVal, RV_STRING);
    const set<int>& argOneSet = this->pkb->get_all_call();
    for (set<int>::const_iterator argOneIt = argOneSet.begin();
            argOneIt != argOneSet.end(); argOneIt++) {
        int argOneVal = *argOneIt;
        const string& procCalled =
                this->pkb->get_call_procName(argOneVal);
        if ((this->pkb->*(disp.has_any_string))(procCalled)) {
            rTable.syn_00_add_row(argOneVal, procCalled);
        }
    }
    rTable.syn_00_transaction_end();
}

void QueryEvaluator::ev_withClause_ss_01(int rTableIdx,
        const WithClause& withClause,
        const EvalPKBDispatch& disp)
{
    assert(REFSYN_CALL_PROCNAME != withClause.leftRef.refSynType);
    assert(REFSYN_CALL_PROCNAME != withClause.rightRef.refSynType);
    assert(NULL != disp.has_any_string);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    pair<const vector<Record> *, int> viPair =
            rTable.syn_01_transaction_begin(
                    withClause.leftRef.refStringVal,
                    withClause.rightRef.refStringVal, RV_STRING);
    const vector<Record>& records = *(viPair.first);
    int nrRecords = records.size();
    int colIdx = viPair.second;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = records[i];
        const pair<string, int>& siPair = record.get_column(colIdx);
        const string& argTwoVal = siPair.first;
        if ((this->pkb->*(disp.has_any_string))(argTwoVal)) {
            rTable.syn_01_augment_new_row(i, argTwoVal);
        }
    }
    rTable.syn_01_transaction_end();
}

void QueryEvaluator::ev_withClause_ss_cpn_cpn_01(int rTableIdx,
        const WithClause& withClause)
{
    assert(REFSYN_CALL_PROCNAME == withClause.leftRef.refSynType);
    assert(REFSYN_CALL_PROCNAME == withClause.rightRef.refSynType);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    pair<const vector<Record> *, int> viPair =
            rTable.syn_01_transaction_begin(
                    withClause.leftRef.refStringVal,
                    withClause.rightRef.refStringVal, RV_INT);
    const vector<Record>& records = *(viPair.first);
    int nrRecords = records.size();
    int colIdx = viPair.second;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = records[i];
        const pair<string, int>& siPair = record.get_column(colIdx);
        int argTwoVal = siPair.second;
        const string& procCalled =
                this->pkb->get_call_procName(argTwoVal);
        const set<int>& callStmtCallingProc =
                this->pkb->get_call_stmt_calling(procCalled);
        for (set<int>::const_iterator argOneIt =
                callStmtCallingProc.begin();
                argOneIt != callStmtCallingProc.end(); argOneIt++) {
            int argOneVal = *argOneIt;
            rTable.syn_01_augment_new_row(i, argOneVal);
        }
    }
    rTable.syn_01_transaction_end();
}

void QueryEvaluator::ev_withClause_ss_cpn_X_01(int rTableIdx,
        const WithClause& withClause)
{
    assert(REFSYN_CALL_PROCNAME == withClause.leftRef.refSynType);
    assert(REFSYN_CALL_PROCNAME != withClause.rightRef.refSynType);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    pair<const vector<Record> *, int> viPair =
            rTable.syn_01_transaction_begin(
                    withClause.leftRef.refStringVal,
                    withClause.rightRef.refStringVal, RV_INT);
    const vector<Record>& records = *(viPair.first);
    int nrRecords = records.size();
    int colIdx = viPair.second;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = records[i];
        const pair<string, int> siPair = record.get_column(colIdx);
        const string& procCalled = siPair.first;
        const set<int>& argOneSet =
                this->pkb->get_call_stmt_calling(procCalled);
        for (set<int>::const_iterator argOneIt = argOneSet.begin();
                argOneIt != argOneSet.end(); argOneIt++) {
            rTable.syn_01_augment_new_row(i, *argOneIt);
        }
    }
    rTable.syn_01_transaction_end();
}

void QueryEvaluator::ev_withClause_ss_cpn_X_10(int rTableIdx,
        const WithClause& withClause, const EvalPKBDispatch& disp)
{
    assert(REFSYN_CALL_PROCNAME == withClause.leftRef.refSynType);
    assert(REFSYN_CALL_PROCNAME != withClause.rightRef.refSynType);
    assert(NULL != disp.has_any_string);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    pair<const vector<Record> *, int> viPair =
            rTable.syn_10_transaction_begin(
                    withClause.leftRef.refStringVal,
                    withClause.rightRef.refStringVal, RV_STRING);
    const vector<Record>& records = *(viPair.first);
    int nrRecords = records.size();
    int colIdx = viPair.second;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = records[i];
        const pair<string, int>& siPair = record.get_column(colIdx);
        int callStmt = siPair.second;
        const string& procCalled =
                this->pkb->get_call_procName(callStmt);
        if ((this->pkb->*(disp.has_any_string))(procCalled)) {
            rTable.syn_10_augment_new_row(i, procCalled);
        }
    }
    rTable.syn_10_transaction_end();
}

void QueryEvaluator::ev_withClause_ss_11(int rTableIdx,
        const WithClause& withClause)
{
    assert(REFSYN_CALL_PROCNAME != withClause.leftRef.refSynType);
    assert(REFSYN_CALL_PROCNAME != withClause.rightRef.refSynType);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    pair<const vector<Record> *, pair<int, int> > viiPair =
            rTable.syn_11_transaction_begin(
                    withClause.leftRef.refStringVal,
                    withClause.rightRef.refStringVal);
    const vector<Record>& records = *(viiPair.first);
    int nrRecords = records.size();
    int colOne = viiPair.second.first;
    int colTwo = viiPair.second.second;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = records[i];
        const pair<string, int>& pOne = record.get_column(colOne);
        const string& argOneVal = pOne.first;
        const pair<string, int>& pTwo = record.get_column(colTwo);
        const string& argTwoVal = pTwo.first;
        if (0 == argOneVal.compare(argTwoVal)) {
            rTable.syn_11_mark_row_ok(i);
        }
    }
    rTable.syn_11_transaction_end();
}

void QueryEvaluator::ev_withClause_ss_cpn_cpn_11(int rTableIdx,
        const WithClause& withClause)
{
    assert(REFSYN_CALL_PROCNAME == withClause.leftRef.refSynType);
    assert(REFSYN_CALL_PROCNAME == withClause.rightRef.refSynType);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    pair<const vector<Record> *, pair<int, int> > viiPair =
            rTable.syn_11_transaction_begin(
                    withClause.leftRef.refStringVal,
                    withClause.rightRef.refStringVal);
    const vector<Record>& records = *(viiPair.first);
    int nrRecords = records.size();
    int colOne = viiPair.second.first;
    int colTwo = viiPair.second.second;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = records[i];
        const pair<string, int>& pOne = record.get_column(colOne);
        int argOneVal = pOne.second;
        const string& procOneName =
                this->pkb->get_call_procName(argOneVal);
        const pair<string, int>& pTwo = record.get_column(colTwo);
        int argTwoVal = pTwo.second;
        const string& procTwoName =
                this->pkb->get_call_procName(argTwoVal);
        if (0 == procOneName.compare(procTwoName)) {
            rTable.syn_11_mark_row_ok(i);
        }
    }
    rTable.syn_11_transaction_end();
}

void QueryEvaluator::ev_withClause_ss_cpn_X_11(int rTableIdx,
        const WithClause& withClause)
{
    assert(REFSYN_CALL_PROCNAME == withClause.leftRef.refSynType);
    assert(REFSYN_CALL_PROCNAME != withClause.rightRef.refSynType);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    pair<const vector<Record> *, pair<int, int> > viiPair =
            rTable.syn_11_transaction_begin(
                    withClause.leftRef.refStringVal,
                    withClause.rightRef.refStringVal);
    const vector<Record>& records = *(viiPair.first);
    int nrRecords = records.size();
    int colOne = viiPair.second.first;
    int colTwo = viiPair.second.second;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = records[i];
        const pair<string, int>& pOne = record.get_column(colOne);
        int argOneVal = pOne.second;
        const string& procName = this->pkb->get_call_procName(argOneVal);
        const pair<string, int>& pTwo = record.get_column(colTwo);
        const string& argTwoVal = pTwo.first;
        if (0 == procName.compare(argTwoVal)) {
            rTable.syn_11_mark_row_ok(i);
        }
    }
    rTable.syn_11_transaction_end();
}

void QueryEvaluator::ev_withClause_ss_22(int rTableIdx,
        const WithClause& withClause)
{
    assert(REFSYN_CALL_PROCNAME != withClause.leftRef.refSynType);
    assert(REFSYN_CALL_PROCNAME != withClause.rightRef.refSynType);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    pair<pair<const vector<Record> *, int>,
         pair<const vector<Record> *, int> > vipPair =
                rTable.syn_22_transaction_begin(
                        withClause.leftRef.refStringVal,
                        withClause.rightRef.refStringVal);
    const vector<Record>& recordsOne = *(vipPair.first.first);
    int nrRecordOne = recordsOne.size();
    int colOne = vipPair.first.second;
    vector<string> argOneVec;
    for (int i = 0; i < nrRecordOne; i++) {
        const Record& record = recordsOne[i];
        const pair<string, int>& siPair = record.get_column(colOne);
        const string& str = siPair.first;
        argOneVec.push_back(str);
    }
    const vector<Record>& recordsTwo = *(vipPair.second.first);
    int nrRecordTwo = recordsTwo.size();
    int colTwo = vipPair.second.second;
    vector<string> argTwoVec;
    for (int i = 0; i < nrRecordTwo; i++) {
        const Record& record = recordsTwo[i];
        const pair<string, int>& siPair = record.get_column(colTwo);
        const string& str = siPair.first;
        argTwoVec.push_back(str);
    }
    for (int rowOne = 0; rowOne < nrRecordOne; rowOne++) {
        const string& argOneVal = argOneVec[rowOne];
        for (int rowTwo = 0; rowTwo < nrRecordTwo; rowTwo++) {
            const string& argTwoVal = argTwoVec[rowTwo];
            if (0 == argOneVal.compare(argTwoVal)) {
                rTable.syn_22_add_row(rowOne, rowTwo);
            }
        }
    }
    rTable.syn_22_transaction_end();
}

void QueryEvaluator::ev_withClause_ss_cpn_cpn_22(int rTableIdx,
        const WithClause& withClause)
{
    assert(REFSYN_CALL_PROCNAME == withClause.leftRef.refSynType);
    assert(REFSYN_CALL_PROCNAME == withClause.rightRef.refSynType);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    pair<pair<const vector<Record> *, int>,
         pair<const vector<Record> *, int> > vipPair =
                rTable.syn_22_transaction_begin(
                        withClause.leftRef.refStringVal,
                        withClause.rightRef.refStringVal);
    const vector<Record>& recordOne = *(vipPair.first.first);
    int nrRecordOne = recordOne.size();
    int colOne = vipPair.first.second;
    vector<string> argOneVec;
    for (int i = 0; i < nrRecordOne; i++) {
        const Record& record = recordOne[i];
        const pair<string, int>& siPair = record.get_column(colOne);
        int callStmt = siPair.second;
        const string& procName = this->pkb->get_call_procName(callStmt);
        argOneVec.push_back(procName);
    }
    const vector<Record>& recordTwo = *(vipPair.second.first);
    int nrRecordTwo = recordTwo.size();
    int colTwo = vipPair.second.second;
    vector<string> argTwoVec;
    for (int i = 0; i < nrRecordTwo; i++) {
        const Record& record = recordTwo[i];
        const pair<string, int>& siPair = record.get_column(colTwo);
        int callStmt = siPair.second;
        const string& procName = this->pkb->get_call_procName(callStmt);
        argTwoVec.push_back(procName);
    }
    for (int rowOne = 0; rowOne < nrRecordOne; rowOne++) {
        const string& argOneVal = argOneVec[rowOne];
        for (int rowTwo = 0; rowTwo < nrRecordTwo; rowTwo++) {
            const string& argTwoVal = argTwoVec[rowTwo];
            if (0 == argOneVal.compare(argTwoVal)) {
                rTable.syn_22_add_row(rowOne, rowTwo);
            }
        }
    }
    rTable.syn_22_transaction_end();
}

void QueryEvaluator::ev_withClause_ss_cpn_X_22(int rTableIdx,
        const WithClause& withClause)
{
    assert(REFSYN_CALL_PROCNAME == withClause.leftRef.refSynType);
    assert(REFSYN_CALL_PROCNAME != withClause.rightRef.refSynType);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    pair<pair<const vector<Record> *, int>,
         pair<const vector<Record> *, int> > vipPair =
            rTable.syn_22_transaction_begin(
                    withClause.leftRef.refStringVal,
                    withClause.rightRef.refStringVal);
    const vector<Record>& recordOne = *(vipPair.first.first);
    int nrRecordOne = recordOne.size();
    int colOne = vipPair.first.second;
    vector<string> argOneVec;
    for (int i = 0; i < nrRecordOne; i++) {
        const Record& record = recordOne[i];
        const pair<string, int>& siPair = record.get_column(colOne);
        int callStmt = siPair.second;
        const string& procName = this->pkb->get_call_procName(callStmt);
        argOneVec.push_back(procName);
    }
    const vector<Record>& recordTwo = *(vipPair.second.first);
    int nrRecordTwo = recordTwo.size();
    int colTwo = vipPair.second.second;
    vector<string> argTwoVec;
    for (int i = 0; i < nrRecordTwo; i++) {
        const Record& record = recordTwo[i];
        const pair<string, int>& siPair = record.get_column(colTwo);
        const string& argTwoVal = siPair.first;
        argTwoVec.push_back(argTwoVal);
    }
    for (int rowOne = 0; rowOne < nrRecordOne; rowOne++) {
        const string& argOneVal = argOneVec[rowOne];
        for (int rowTwo = 0; rowTwo < nrRecordTwo; rowTwo++) {
            const string& argTwoVal = argTwoVec[rowTwo];
            if (0 == argOneVal.compare(argTwoVal)) {
                rTable.syn_22_add_row(rowOne, rowTwo);
            }
        }
    }
    rTable.syn_22_transaction_end();
}

void QueryEvaluator::ev_withClause_attrRef_X(int rTableIdx,
        const WithClause& withClause)
{
    BaseType leftRefType =
            refSynType_to_BaseType(withClause.leftRef.refSynType);
    assert(BASETYPE_INVALID != leftRefType);
    if (BASETYPE_INT == leftRefType) {
        assert(REF_INT == withClause.rightRef.refType);
        this->ev_withClause_attrRef_X_int(rTableIdx, withClause);
    } else if (BASETYPE_STRING == leftRefType) {
        assert(REF_STRING == withClause.rightRef.refType);
        this->ev_withClause_attrRef_X_string(rTableIdx, withClause);
    } else {
        assert(false);
    }
}

void QueryEvaluator::ev_withClause_attrRef_X_int(int rTableIdx,
        const WithClause& withClause)
{
    EvalPKBDispatch pkbDispatch;
    const ResultsTable& rTable = this->resultsTable[rTableIdx];
    if (rTable.has_synonym(withClause.leftRef.refStringVal)) {
        this->ev_withClause_i_1(rTableIdx, withClause);
    } else {
        pkbDispatch.get_all_int_argOne =
                QueryEvaluator::get_all_int_pkb_method_from_RefSynType(
                        withClause.leftRef.refSynType);
        this->ev_withClause_i_0(rTableIdx, withClause, pkbDispatch);
    }
}

void QueryEvaluator::ev_withClause_attrRef_X_string(int rTableIdx,
        const WithClause& withClause)
{
    EvalPKBDispatch pkbDispatch;
    const ResultsTable& rTable = this->resultsTable[rTableIdx];
    if (rTable.has_synonym(withClause.leftRef.refStringVal)) {
        if (REFSYN_CALL_PROCNAME == withClause.leftRef.refSynType) {
            this->ev_withClause_cpn_1(rTableIdx, withClause);
        } else {
            this->ev_withClause_s_1(rTableIdx, withClause);
        }
    } else {
        if (REFSYN_CALL_PROCNAME == withClause.leftRef.refSynType) {
            this->ev_withClause_cpn_0(rTableIdx, withClause);
        } else {
            pkbDispatch.get_all_string_argOne =
                    QueryEvaluator::
                        get_all_string_pkb_method_from_RefSynType(
                                withClause.leftRef.refSynType);
            this->ev_withClause_s_0(rTableIdx, withClause, pkbDispatch);
        }
    }
}

void QueryEvaluator::ev_withClause_i_0(int rTableIdx,
        const WithClause& withClause, const EvalPKBDispatch& disp)
{
    assert(NULL != disp.get_all_int_argOne);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    rTable.syn_0_transaction_begin(withClause.leftRef.refStringVal,
            RV_INT);
    const set<int>& argOneSet =
            (this->pkb->*(disp.get_all_int_argOne))();
    const int concreteVal = withClause.rightRef.refIntVal;
    if (argOneSet.end() != argOneSet.find(concreteVal)) {
        rTable.syn_0_add_row(concreteVal);
    }
    rTable.syn_0_transaction_end();
}

void QueryEvaluator::ev_withClause_i_1(int rTableIdx,
        const WithClause& withClause)
{
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    pair<const vector<Record> *, int> viPair =
            rTable.syn_1_transaction_begin(
                    withClause.leftRef.refStringVal);
    const vector<Record>& records = *(viPair.first);
    int nrRecords = records.size();
    int colIdx = viPair.second;
    const int concreteVal = withClause.rightRef.refIntVal;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = records[i];
        const pair<string, int>& siPair = record.get_column(colIdx);
        int argOneVal = siPair.second;
        if (concreteVal == argOneVal) {
            rTable.syn_1_mark_row_ok(i);
        }
    }
    rTable.syn_1_transaction_end();
}

void QueryEvaluator::ev_withClause_s_0(int rTableIdx,
        const WithClause& withClause, const EvalPKBDispatch& disp)
{
    assert(REFSYN_CALL_PROCNAME != withClause.leftRef.refSynType);
    assert(NULL != disp.get_all_string_argOne);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    rTable.syn_0_transaction_begin(withClause.leftRef.refStringVal,
            RV_STRING);
    const set<string>& argOneSet =
            (this->pkb->*(disp.get_all_string_argOne))();
    const string& concreteVal = withClause.rightRef.refStringVal;
    if (argOneSet.end() != argOneSet.find(concreteVal)) {
        rTable.syn_0_add_row(concreteVal);
    }
    rTable.syn_0_transaction_end();
}

void QueryEvaluator::ev_withClause_cpn_0(int rTableIdx,
        const WithClause& withClause)
{
    assert(REFSYN_CALL_PROCNAME == withClause.leftRef.refSynType);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    rTable.syn_0_transaction_begin(withClause.leftRef.refStringVal,
            RV_INT);
    const set<int>& argOneSet = this->pkb->get_all_call();
    const string& concreteVal = withClause.rightRef.refStringVal;
    for (set<int>::const_iterator argOneIt = argOneSet.begin();
            argOneIt != argOneSet.end(); argOneIt++) {
        int callStmt = *argOneIt;
        const string& procCalled =
                this->pkb->get_call_procName(callStmt);
        if (0 == procCalled.compare(concreteVal)) {
            rTable.syn_0_add_row(callStmt);
        }
    }
    rTable.syn_0_transaction_end();
}

void QueryEvaluator::ev_withClause_s_1(int rTableIdx,
        const WithClause& withClause)
{
    assert(REFSYN_CALL_PROCNAME != withClause.leftRef.refSynType);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    pair<const vector<Record> *, int> viPair =
            rTable.syn_1_transaction_begin(
                    withClause.leftRef.refStringVal);
    const vector<Record>& records = *(viPair.first);
    int nrRecords = records.size();
    int colIdx = viPair.second;
    const string& concreteVal = withClause.rightRef.refStringVal;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = records[i];
        const pair<string, int>& siPair = record.get_column(colIdx);
        const string& argOneVal = siPair.first;
        if (0 == argOneVal.compare(concreteVal)) {
            rTable.syn_1_mark_row_ok(i);
        }
    }
    rTable.syn_1_transaction_end();
}

void QueryEvaluator::ev_withClause_cpn_1(int rTableIdx,
        const WithClause& withClause)
{
    assert(REFSYN_CALL_PROCNAME == withClause.leftRef.refSynType);
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    pair<const vector<Record> *, int> viPair =
            rTable.syn_1_transaction_begin(
                    withClause.leftRef.refStringVal);
    const vector<Record>& records = *(viPair.first);
    int nrRecords = records.size();
    int colIdx = viPair.second;
    const string& concreteVal = withClause.rightRef.refStringVal;
    for (int i = 0; i < nrRecords; i++) {
        const Record& record = records[i];
        const pair<string, int>& siPair = record.get_column(colIdx);
        int callStmt = siPair.second;
        const string& procCalled =
                this->pkb->get_call_procName(callStmt);
        if (0 == procCalled.compare(concreteVal)) {
            rTable.syn_1_mark_row_ok(i);
        }
    }
    rTable.syn_1_transaction_end();
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
    assert(patCl->varRefType == PATVARREF_SYN ||
        patCl->varRefType == PATVARREF_STRING ||
        patCl->varRefType == PATVARREF_WILDCARD);
    assert(patCl->exprType != PATEXPR_INVALID);
    if (patCl->varRefType == PATVARREF_SYN) {
        if (patCl->exprType == PATEXPR_EXPR) {
            this->evaluate_patCl_assign_syn_expr(rTableIdx, patCl);
        } else if (patCl->exprType == PATEXPR_EXPR_WILDCARD) {
            this->evaluate_patCl_assign_syn_exprwild(rTableIdx, patCl);
        } else if (patCl->exprType == PATEXPR_WILDCARD) {
            this->evaluate_patCl_assign_syn_wildcard(rTableIdx, patCl);
        }
    }
    if (patCl->varRefType == PATVARREF_STRING) {
        if (patCl->exprType == PATEXPR_EXPR) {
            this->evaluate_patCl_assign_string_expr(rTableIdx, patCl);
        } else if (patCl->exprType == PATEXPR_EXPR_WILDCARD) {
            this->evaluate_patCl_assign_string_exprwild(rTableIdx, patCl);
        } else if (patCl->exprType == PATEXPR_WILDCARD) {
            this->evaluate_patCl_assign_string_wildcard(rTableIdx, patCl);
        }
    }
    if (patCl->varRefType == PATVARREF_WILDCARD) {
        if (patCl->exprType == PATEXPR_EXPR) {
            this->evaluate_patCl_assign_wildcard_expr(rTableIdx, patCl);
        } else if (patCl->exprType == PATEXPR_EXPR_WILDCARD) {
            this->evaluate_patCl_assign_wildcard_exprwild(rTableIdx,
                    patCl);
        } else if (patCl->exprType == PATEXPR_WILDCARD) {
            this->evaluate_patCl_assign_wildcard_wildcard(rTableIdx,
                    patCl);
        }
    }
}

void QueryEvaluator::evaluate_patCl_assign_string_expr(int rTableIdx,
        const PatCl *patCl) {
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    bool hasAssgnSyn = rTable.has_synonym(patCl->syn);
    Node *rootExprTree = Parser(patCl->exprString, FROMSTRING).yard();

    if (hasAssgnSyn) {
        pair<const vector<Record> *, int> viPair =
            rTable.syn_1_transaction_begin(patCl->syn);
        int assignCol = viPair.second;
        const vector<Record>& records = *(viPair.first);
        int recordsSize = records.size();
        for (int i = 0; i < recordsSize; i++) {
            const Record& rec = records[i];
            pair<string, int> assignPair = rec.get_column(assignCol);
            int assignStmt = assignPair.second;
            Node *assignNode =
                    this->pkb->get_stmtBank()->get_node(assignStmt);
            string modifiedVar = assignNode->get_leaves()[0]->get_name();
            if (modifiedVar == patCl->varRefString) {
                if (this->evaluate_matching_tree(
                        assignNode->get_leaves()[1], rootExprTree)) {
                    rTable.syn_1_mark_row_ok(i);
                }
            }
        }
        rTable.syn_1_transaction_end();
    } else {
        rTable.syn_0_transaction_begin(patCl->syn, RV_INT);
        set<int> allAssignStmts = this->pkb->get_all_assign();
        for (set<int>::iterator k=allAssignStmts.begin();
                k!=allAssignStmts.end(); k++) {
            int assignStmt = *k;
            Node* assignStmtNode =
                    this->pkb->get_stmtBank()->get_node(assignStmt);
            string modifiedVar;
            const set<string>& get_modifies =
                    assignStmtNode->get_modifies();
            for (set<string>::iterator j = get_modifies.begin();
                    j != get_modifies.end(); j++) {
                modifiedVar= *j;
            }
            if (modifiedVar == patCl->varRefString) {
                const vector<Node*> leaves = assignStmtNode->get_leaves();
                if (this->evaluate_matching_tree(leaves[1],
                        rootExprTree)) {
                    rTable.syn_0_add_row(assignStmt);
                }
            }
        }
        rTable.syn_0_transaction_end();
    }
}

void QueryEvaluator::evaluate_patCl_assign_string_exprwild(int rTableIdx,
        const PatCl *patCl)
{
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    bool hasAsgnSyn = rTable.has_synonym(patCl->syn);
    Node *rootExprTree = Parser(patCl->exprString, FROMSTRING).yard();
    if (hasAsgnSyn) {
        pair<const vector<Record> *, int> viPair =
                rTable.syn_1_transaction_begin(patCl->syn);
        int assignCol = viPair.second;
        const vector<Record>& records = *(viPair.first);
        int recordsSize = records.size();
        for (int i = 0; i < recordsSize; i++) {
            const Record& rec = records[i];
            pair<string, int> assignPair = rec.get_column(assignCol);
            int assignStmt = assignPair.second;
            Node *assignNode = this->pkb->
                    get_stmtBank()->get_node(assignStmt);
            string modifiedVar = assignNode->get_leaves()[0]->get_name();
            std::queue<Node *> nodeQueue;
            nodeQueue.push(assignNode);
            ///NEED TEST
            while (!nodeQueue.empty()) {
                Node *frontNode = nodeQueue.front();
                nodeQueue.pop();
                vector<Node *> leaves = frontNode->get_leaves();
                int nrLeaves = leaves.size();
                for (int k = 0; k < nrLeaves; k++) {
                    nodeQueue.push(leaves[k]);
                    if (leaves[k]->get_name() ==
                            rootExprTree->get_name()) {
                        if (this->evaluate_matching_tree(leaves[k],
                                rootExprTree)) {
                            rTable.syn_1_mark_row_ok(i);
                        }
                    }
                }
            }
        }
        rTable.syn_1_transaction_end();
    } else {
        rTable.syn_0_transaction_begin(patCl->syn, RV_INT);
        set<int> allAssignStmts = this->pkb->get_all_assign();
        for (set<int>::iterator i = allAssignStmts.begin();
                i != allAssignStmts.end(); i++) {
            int assignStmt = *i;
            Node *assignNode =
                    this->pkb->get_stmtBank()->get_node(assignStmt);
            std::queue<Node *> nodeQueue;
            nodeQueue.push(assignNode->get_leaves()[1]); /*MODIFIED*/
            while (!nodeQueue.empty()) {
                Node *frontNode = nodeQueue.front();
                nodeQueue.pop();
                vector<Node *> leaves = frontNode->get_leaves();
                int nrLeaves = leaves.size();
                for (int k = 0; k < nrLeaves; k++) {
                    nodeQueue.push(leaves[k]);
                    /*if (leaves[k]->get_name() == rootExprTree->get_name()) {
                        if (this->evaluate_matching_tree(leaves[k], rootExprTree)) {
                            rTable.syn_0_add_row(assignStmt);
                        }
                    }*/
                }
                if (frontNode->get_name() == rootExprTree->get_name()) {
                    if (this->evaluate_matching_tree(frontNode,
                            rootExprTree)) {
                        rTable.syn_0_add_row(assignStmt);
                    }
                }
            }
        }
        rTable.syn_0_transaction_end();
    }
}

void QueryEvaluator::evaluate_patCl_assign_string_wildcard(int rTableIdx,
        const PatCl *patCl)
{
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    bool hasAgnSyn = rTable.has_synonym(patCl->syn);
    if (hasAgnSyn) {
        //or 1
        pair<const vector<Record> *, int> viPair =
            rTable.syn_1_transaction_begin(patCl->syn);
        int synCol = viPair.second;
        const vector<Record>& records = *(viPair.first);
        int recordsSize = records.size();
        for (int i = 0; i < recordsSize; i++) {
            const Record& rec = records[i];
            pair<string, int> assignPair = rec.get_column(synCol);
            int assignStmt = assignPair.second;
            Node *assignStmtNode =
                    this->pkb->get_stmtBank()->get_node(assignStmt);
            const set<string>& modifies_set =
                    assignStmtNode->get_modifies();
            for (set<string>::iterator k = modifies_set.begin();
                    k != modifies_set.end(); k++) {
                string modifies_variable = *k;
                if (modifies_variable == patCl->varRefString) {
                    rTable.syn_1_mark_row_ok(i);
                }
            }
            //set<Node*> assignNodeChild = assignStmtNode.get_child();
        }
        rTable.syn_1_transaction_end();
    } else {
        //0
        rTable.syn_0_transaction_begin(patCl->syn, RV_INT);
        set<int> allAssignStmts = this->pkb->get_all_assign();
        /*set<int> allModifiedStmts = this->pkb->get_stmt_modifies(patCl->varRefString);
        for (set<int>::iterator i=allModifiedStmts.begin(); i!=allModifiedStmts.end(); i++) {
            int modifiedStmt = *i;
            rTable.syn_0_add_row(modifiedStmt);
        }*/
        for (set<int>::iterator i = allAssignStmts.begin();
                i != allAssignStmts.end(); i++) {
            int assignStmt = *i;
            Node *assignStmtNode =
                    this->pkb->get_stmtBank()->get_node(assignStmt);
            const set<string>& modifies_set =
                    assignStmtNode->get_modifies();
            for (set<string>::iterator k = modifies_set.begin();
                    k != modifies_set.end(); k++) {
                string modifies_variable = *k;
                if (modifies_variable == patCl->varRefString) {
                    rTable.syn_0_add_row(assignStmt);
                }
            }
        }
        rTable.syn_0_transaction_end();
    }
}

bool QueryEvaluator::is_operation(const string& operation)
{
    return (operation == "+" || operation == "-" || operation == "/" ||
            operation == "*");
}

bool QueryEvaluator::evaluate_matching_tree(Node* ASTNode, Node* assignNode)
{
    bool result = true;
    if (ASTNode->get_name() != assignNode->get_name()) {
        return false;
    }
    vector<Node *> astLeaves = ASTNode->get_leaves();
    vector<Node *> assignLeaves = assignNode->get_leaves();
    if (assignLeaves.size() != assignLeaves.size()) {
        return false;
    } else if ((astLeaves.size() == 0 && assignLeaves.size() != 0) ||
            (astLeaves.size() != 0 && assignLeaves.size() == 0)) {
        return false;
    }
    int nrAstLeaves = astLeaves.size();
    for (int i = 0; i < nrAstLeaves; i++) {
        Node *astChild = astLeaves[i];
        Node *assignChild = assignLeaves[i];
        if (astChild->get_name() != assignChild->get_name()) {
            return false;
        } else {
            if (is_operation(astChild->get_name())) {
                result = this->evaluate_matching_tree(astChild,
                        assignChild);
                if (result == false) {
                    return false;
                }
            }
        }
    }
    return result;
}

void QueryEvaluator::evaluate_patCl_assign_syn_expr(int rTableIdx,
        const PatCl *patCl)
{
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    bool hasAssignSyn = rTable.has_synonym(patCl->syn);
    bool hasVarSyn = rTable.has_synonym(patCl->varRefString);
    if (hasAssignSyn && hasVarSyn) {
        if (rTable.syn_in_same_table(patCl->syn, patCl->varRefString)) {
            this->evaluate_patCl_assign_syn_expr_11(rTable, patCl);
        } else {
            this->evaluate_patCl_assign_syn_expr_22(rTable, patCl);
        }
    } else if (hasAssignSyn) {
        //syn_10 transaction
        pair<const vector<Record> *, int> viPair =
                rTable.syn_10_transaction_begin(patCl->syn,
                        patCl->varRefString, RV_STRING);
        int assignCol = viPair.second;
        const vector<Record>& records = *(viPair.first);
        int recordsSize = records.size();
        string variable;
        for (int i = 0; i < recordsSize; i++) {
            const Record& rec = records[i];
            pair<string, int> assignPair = rec.get_column(assignCol);
            int assignStmt = assignPair.second;
            Node *assignNode =
                    this->pkb->get_stmtBank()->get_node(assignStmt);
            Node *exprNode = Parser(patCl->exprString, FROMSTRING).yard();
            if (exprNode != NULL) {
                set<string> get_modifies =
                        this->pkb->get_var_stmt_modifies(assignStmt);
                for (set<string>::iterator j = get_modifies.begin();
                        j != get_modifies.end(); j++) {
                    variable = *j;
                }
                if (this->evaluate_matching_tree(
                        assignNode->get_leaves()[1], exprNode)) {
                    rTable.syn_10_augment_new_row(i, variable);
                }
            }
        }
        rTable.syn_10_transaction_end();
    } else if (hasVarSyn) {
        //01
        pair<const vector<Record> *, int> viPair =
                rTable.syn_01_transaction_begin(patCl->syn,
                        patCl->varRefString, RV_INT);
        int varCol = viPair.second;
        const vector<Record>& records = *(viPair.first);
        int recordsSize = records.size();
        for (int j = 0; j < recordsSize; j++) {
            const Record& rec = records[j];
            pair<string, int> varPair = rec.get_column(varCol);
            string variable = varPair.first;
            set<int> allAssignStmts =
                    this->pkb->get_stmt_modifies(variable);
            Node *exprNode = Parser(patCl->exprString, FROMSTRING).yard();
            for (set<int>::iterator i = allAssignStmts.begin();
                    i != allAssignStmts.end(); i++) {
                int assignStmt = *i;
                Node *assignNode =
                        this->pkb->get_stmtBank()->get_node(assignStmt);
                if (assignNode->get_name() == "=") {
                    if (this->evaluate_matching_tree(
                            assignNode->get_leaves()[1], exprNode)) {
                        rTable.syn_01_augment_new_row(j, assignStmt);
                    }
                }
            }
        }
        rTable.syn_01_transaction_end();
    } else {
        rTable.syn_00_transaction_begin(patCl->syn, RV_INT,
                patCl->varRefString, RV_STRING);
        set<int> allAssignStmts = this->pkb->get_all_assign();
        for (set<int>::iterator i = allAssignStmts.begin();
                i != allAssignStmts.end(); i++) {
            int assignStmt = *i;
            string modifiedVar;
            Node *assignNode =
                    this->pkb->get_stmtBank()->get_node(assignStmt);
            Node *exprNode = Parser(patCl->exprString, FROMSTRING).yard();
            set<string> get_modifies =
                    this->pkb->get_var_stmt_modifies(assignStmt);
            for (set<string>::iterator i = get_modifies.begin();
                    i != get_modifies.end(); i++) {
                modifiedVar = *i;
            }
            if (this->evaluate_matching_tree(assignNode->get_leaves()[1],
                    exprNode)) {
                rTable.syn_00_add_row(assignStmt, modifiedVar);
            }
        }
        rTable.syn_00_transaction_end();
    }
}

void QueryEvaluator::evaluate_patCl_assign_syn_expr_11(
        ResultsTable& rTable, const PatCl* patCl)
{
    pair<const vector<Record> *, pair<int, int> > viiPair =
            rTable.syn_11_transaction_begin(patCl->syn,
                    patCl->varRefString);
    const vector<Record>& records = *(viiPair.first);
    int nrRecords = records.size();
    int assignCol = viiPair.second.first;
    int varCol = viiPair.second.second;
    Node *rootExprTree = Parser(patCl->exprString, FROMSTRING).yard();
    for (int i = 0; i < nrRecords; i++) {
        const Record& rec = records[i];
        pair<string, int> assignPair = rec.get_column(assignCol);
        pair<string, int> varPair = rec.get_column(varCol);
        int assignStmt = assignPair.second;
        Node *assignNode =
                this->pkb->get_stmtBank()->get_node(assignStmt);
        string var = varPair.first;
        string modifiedVar;
        set<string> modifiedVarSet =
                this->pkb->get_var_stmt_modifies(assignStmt);
        for (set<string>::iterator k = modifiedVarSet.begin();
                k != modifiedVarSet.end(); k++) {
            modifiedVar = *k;
        }
        if (modifiedVar == var) {
            if (this->evaluate_matching_tree(
                    assignNode->get_leaves()[1],rootExprTree)) {
                rTable.syn_11_mark_row_ok(i);
            }
        }
    }
    rTable.syn_11_transaction_end();
}

void QueryEvaluator::evaluate_patCl_assign_syn_expr_22(
        ResultsTable& rTable, const PatCl* patCl)
{
    pair<pair<const vector<Record> *, int>,
         pair<const vector<Record> *, int> > vipPair =
            rTable.syn_22_transaction_begin(patCl->syn,
                    patCl->varRefString);
    const vector<Record>& assignRecords = *(vipPair.first.first);
    int nrAssignRecords = assignRecords.size();
    int assignCol = vipPair.first.second;

    const vector<Record>& varRecords = *(vipPair.second.first);
    int nrVarRecords = varRecords.size();
    int varCol = vipPair.second.second;

    Node *rootExprNode = Parser(patCl->exprString, FROMSTRING).yard();
    for (int i = 0; i < nrAssignRecords; i++) {
        const Record& assignRec = assignRecords[i];
        pair<string, int> assignPair = assignRec.get_column(assignCol);
        int assignStmt = assignPair.second;
        Node* assignNode =
                this->pkb->get_stmtBank()->get_node(assignStmt);
        string modifiedVar;
        set<string> get_modifies = this->pkb->
            get_var_stmt_modifies(assignStmt);
        for (set<string>::iterator k = get_modifies.begin();
                k!= get_modifies.end(); k++) {
            modifiedVar = *k;
        }
        for (int j = 0; j < nrVarRecords; j++) {
            const Record& varRec = varRecords[j];
            pair<string, int> varPair = varRec.get_column(varCol);
            string var = varPair.first;
            if (modifiedVar == var) {
                if (this->evaluate_matching_tree(rootExprNode,
                        assignNode->get_leaves()[1])) {
                    rTable.syn_22_add_row(i, j);
                }
            }
        }
    }
    rTable.syn_22_transaction_end();
}

void QueryEvaluator::evaluate_patCl_assign_syn_exprwild(int rTableIdx,
        const PatCl *patCl)
{
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    bool hasAsgnSyn = rTable.has_synonym(patCl->syn);
    bool hasVarSyn = rTable.has_synonym(patCl->varRefString);
    Node *rootExprTree = Parser(patCl->exprString, FROMSTRING).yard();

    if (hasAsgnSyn && hasVarSyn) {
        if (rTable.syn_in_same_table(patCl->syn, patCl->varRefString)) {
            this->evaluate_patCl_assign_syn_exprwild_11(rTable, patCl);
        } else {
            this->evaluate_patCl_assign_syn_exprwild_22(rTable, patCl);
        }
    } else if (hasAsgnSyn) {
        pair<const vector<Record> *, int> viPair =
                rTable.syn_10_transaction_begin(patCl->syn,
                        patCl->varRefString, RV_STRING);
        int assignCol = viPair.second;
        const vector<Record>& records = *(viPair.first);
        int recordsSize = records.size();
        for (int k = 0; k < recordsSize; k++) {
            const Record& rec = records[k];
            pair<string, int> assignPair = rec.get_column(assignCol);
            int assignStmt = assignPair.second;
            Node* assignNode =
                    this->pkb->get_stmtBank()->get_node(assignStmt);
            string modifiedVar = assignNode->get_leaves()[0]->get_name();
            std::queue<Node *> nodeQueue;
            nodeQueue.push(assignNode->get_leaves()[1]);
            while (!nodeQueue.empty()) {
                Node *frontNode = nodeQueue.front();
                nodeQueue.pop();
                vector<Node *> leaves = frontNode->get_leaves();
                int nrLeaves = leaves.size();
                for (int i = 0; i < nrLeaves; i++) {
                    nodeQueue.push(leaves[i]);
                }  /*change for testing*/
                if (frontNode->get_name() == rootExprTree->get_name()) {
                    if (this->evaluate_matching_tree(frontNode,
                            rootExprTree)) {
                        rTable.syn_10_augment_new_row(k, modifiedVar);
                    }
                }
            }
        }
        rTable.syn_10_transaction_end();
    } else if (hasVarSyn) {
        pair<const vector<Record> *, int> viPair =
                rTable.syn_01_transaction_begin(patCl->syn,
                        patCl->varRefString, RV_INT);
        int varCol = viPair.second;
        const vector<Record>& records = *(viPair.first);
        int recordsSize = records.size();
        for (int k = 0; k < recordsSize; k++) {
            const Record& rec = records[k];
            pair<string, int> varPair = rec.get_column(varCol);
            string var = varPair.first;
            set<int> allConsideringStmts =
                    this->pkb->get_stmt_modifies(var);
            for (set<int>::iterator i = allConsideringStmts.begin();
                    i != allConsideringStmts.end(); i++) {
                int assignStmt = *i;
                Node *assignNode =
                        this->pkb->get_stmtBank()->get_node(assignStmt);
                if (assignNode->get_name() != "=") {
                    continue;
                }
                std::queue<Node *> nodeQueue;
                nodeQueue.push(assignNode->get_leaves()[1]);
                while (!nodeQueue.empty()) {
                    Node *frontNode = nodeQueue.front();
                    nodeQueue.pop();
                    vector<Node *> leaves = frontNode->get_leaves();
                    int nrLeaves = leaves.size();
                    for (int i = 0; i < nrLeaves; i++) {
                        nodeQueue.push(leaves[i]); /*CHANGED FOR TESTING*/
                    }
                    if (frontNode->get_name() ==
                            rootExprTree->get_name()) {
                        if (this->evaluate_matching_tree(frontNode,
                                rootExprTree)) {
                            rTable.syn_01_augment_new_row(k, assignStmt);
                        }
                    }
                }
            }
        }
        rTable.syn_01_transaction_end();
    } else {
        rTable.syn_00_transaction_begin(patCl->syn, RV_INT,
                patCl->varRefString, RV_STRING);
        set<int> allAssignStmts = this->pkb->get_all_assign();
        for (set<int>::iterator i = allAssignStmts.begin();
                i != allAssignStmts.end(); i++) {
            int assignStmt = *i;
            Node *assignNode =
                    this->pkb->get_stmtBank()->get_node(assignStmt);
            string modifiedVar = assignNode->get_leaves()[0]->get_name();
            //---------------------------
            std::queue<Node *> nodeQueue;
            nodeQueue.push(assignNode->get_leaves()[1]);
            while (!nodeQueue.empty()) {
                Node *frontNode = nodeQueue.front();
                nodeQueue.pop();
                vector<Node *> leaves = frontNode->get_leaves();
                int nrLeaves = leaves.size();
                for (int i = 0; i < nrLeaves; i++) {
                    nodeQueue.push(leaves[i]);
                } /*TESTING*/
                if (frontNode->get_name() == rootExprTree->get_name()) {
                    if (this->evaluate_matching_tree(frontNode,
                            rootExprTree)) {
                        rTable.syn_00_add_row(assignStmt, modifiedVar);
                    }
                }
            }
        }
        rTable.syn_00_transaction_end();
    }
}

//===================================NEED TEST===========================
void QueryEvaluator::evaluate_patCl_assign_syn_exprwild_11(
        ResultsTable& rTable, const PatCl* patCl)
{
    pair<const vector<Record> *, pair<int, int> > viiPair =
            rTable.syn_11_transaction_begin(patCl->syn,
                    patCl->varRefString);
    const vector<Record>& records = *(viiPair.first);
    int nrRecords = records.size();
    int assignCol = viiPair.second.first;
    int varCol = viiPair.second.second;
    Node *rootExprTree = Parser(patCl->exprString, FROMSTRING).yard();

    for (int i = 0; i < nrRecords; i++) {
        const Record& rec = records[i];
        pair<string, int> assignPair = rec.get_column(assignCol);
        int assignStmt = assignPair.second;
        Node *assignNode =
                this->pkb->get_stmtBank()->get_node(assignStmt);
        pair<string, int> varPair = rec.get_column(varCol);
        string var = varPair.first;
        set<string> modifiedVarSet =
                this->pkb->get_var_stmt_modifies(assignStmt);
        string modifiedVar;
        for (set<string>::iterator k = modifiedVarSet.begin();
                k != modifiedVarSet.end(); k++) {
            modifiedVar = *k;
        }
        if (modifiedVar == var) {
            std::queue<Node *> nodeQueue;
            nodeQueue.push(assignNode);
            while (!(nodeQueue.empty())) {
                Node *frontNode = nodeQueue.front();
                nodeQueue.pop();
                vector<Node *> leaves = frontNode->get_leaves();
                int nrLeaves = leaves.size();
                for (int k = 0; k < nrLeaves; k++) {
                    Node *child = leaves[k];
                    if (child->get_name() == rootExprTree->get_name()) {
                        if (this->evaluate_matching_tree(child,
                                rootExprTree)) {
                            rTable.syn_11_mark_row_ok(i);
                        }
                    }
                }
            }
        }
    }
    rTable.syn_11_transaction_end();
}

//====================================NEED TEST=============================
void QueryEvaluator::evaluate_patCl_assign_syn_exprwild_22(
        ResultsTable& rTable, const PatCl* patCl)
{
    pair<pair<const vector<Record> *, int>,
         pair<const vector<Record> *, int>> vipPair =
            rTable.syn_22_transaction_begin(patCl->syn,
                    patCl->varRefString);
    const vector<Record>& assignRecords = *(vipPair.first.first);
    int nrAssignRecords = assignRecords.size();
    int assignCol = vipPair.first.second;

    const vector<Record>& varRecords = *(vipPair.second.first);
    int nrVarRecords = varRecords.size();
    int varCol = vipPair.second.second;

    Node *exprNode = Parser(patCl->exprString, FROMSTRING).yard();
    for (int i = 0; i < nrAssignRecords; i++) {
        const Record& assignRec = assignRecords[i];
        pair<string, int> assignPair = assignRec.get_column(assignCol);
        int assignStmt = assignPair.second;
        Node *assignNode =
                this->pkb->get_stmtBank()->get_node(assignStmt);
        string modifiedVar = assignNode->get_leaves()[0]->get_name();
        for (int j = 0; j < nrVarRecords; j++) {
            const Record& varRec = varRecords[j];
            pair<string, int> varPair = varRec.get_column(varCol);
            string var = varPair.first;
            if (var == modifiedVar) {
                std::queue<Node *> nodeQueue;
                nodeQueue.push(assignNode);
                while (!(nodeQueue.empty())) {
                    Node *frontNode = nodeQueue.front();
                    nodeQueue.pop();
                    vector<Node *> leaves = frontNode->get_leaves();
                    int nrLeaves = leaves.size();
                    for (int k = 0; k < nrLeaves; k++) {
                        nodeQueue.push(leaves[k]);
                        Node *child = leaves[k];
                        if (child->get_name() == exprNode->get_name()) {
                            if (this->evaluate_matching_tree(child,
                                    exprNode)) {
                                rTable.syn_22_add_row(i,j);
                            }
                        }
                    }
                }
            }
        }
    }
    rTable.syn_22_transaction_end();
}

void QueryEvaluator::evaluate_patCl_assign_syn_wildcard(int rTableIdx,
        const PatCl *patCl)
{
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    bool hasAgnSyn = rTable.has_synonym(patCl->syn);
    bool hasVarSyn = rTable.has_synonym(patCl->varRefString);

    if (hasAgnSyn && hasVarSyn) {
        if (rTable.syn_in_same_table(patCl->syn, patCl->varRefString)) {
            this->evaluate_patCl_assign_syn_wildcard_11(rTable, patCl);
        } else {
            this->evaluate_patCl_assign_syn_wildcard_22(rTable, patCl);
        }
    } else if (hasAgnSyn) {
        //Agn synonym has been seen, 
        //get all assignment stmts, augment with its ctrl var
        //10
        pair<const vector<Record> *, int> viPair =
                rTable.syn_10_transaction_begin(patCl->syn,
                        patCl->varRefString, RV_STRING);
        const vector<Record>& records = *(viPair.first);
        int assignCol = viPair.second;
        int assignSize = records.size();
        for (int i = 0; i < assignSize; i++) {
            const Record& rec = records[i];
            const pair<string, int>& assignPair =
                    rec.get_column(assignCol);
            int assignStmt = assignPair.second;
            set<string> get_modifies =
                    this->pkb->get_var_stmt_modifies(assignStmt);
            for (set<string>::iterator k = get_modifies.begin();
                    k != get_modifies.end(); k++) {
                string var = *k;
                rTable.syn_10_augment_new_row(i, var);
            }
        }
        rTable.syn_10_transaction_end();
    } else if (hasVarSyn) {
        //01
        pair<const vector<Record> *, int> viPair =
                rTable.syn_01_transaction_begin(patCl->syn,
                        patCl->varRefString, RV_INT);
        const vector<Record>& records = *(viPair.first);
        int varCol = viPair.second;
        int noRecords = records.size();
        for (int i = 0; i < noRecords; i++) {
            const Record& rec = records[i];
            const pair<string, int>& varPair = rec.get_column(varCol);
            string var = varPair.first;
            set<int> stmtModifies = this->pkb->get_stmt_modifies(var);
            for (set<int>::iterator k = stmtModifies.begin();
                    k != stmtModifies.end(); k++) {
                int stmt = *k;
                rTable.syn_01_augment_new_row(i, stmt);
            }
        }
        rTable.syn_01_transaction_end();
    } else {
        //00
        rTable.syn_00_transaction_begin(patCl->syn, RV_INT,
                patCl->varRefString, RV_STRING);
        set<int> allAssignStmts = this->pkb->get_all_assign();
        for (set<int>::iterator i = allAssignStmts.begin();
                i != allAssignStmts.end(); i++) {
            int assignStmt = *i;
            set<string> get_modifies =
                    this->pkb->get_var_stmt_modifies(assignStmt);
            for (set<string>::iterator k = get_modifies.begin();
                    k != get_modifies.end(); k++) {
                string var = *k;
                rTable.syn_00_add_row(assignStmt, var);
            }
        }
        rTable.syn_00_transaction_end();
    }
}

void QueryEvaluator::evaluate_patCl_assign_syn_wildcard_11(
        ResultsTable& rTable, const PatCl *patCl)
{
    pair<const vector<Record> *, pair<int, int>> viiPair =
            rTable.syn_11_transaction_begin(patCl->syn,
                    patCl->varRefString);
    int assignCol = viiPair.second.first;
    int varCol = viiPair.second.second;
    const vector<Record>& records = *(viiPair.first);
    int recordsSize = records.size();
    Node *rootExprTree = Parser(patCl->exprString, FROMSTRING).yard();
    for (int i = 0; i < recordsSize; i++) {
        const Record& rec = records[i];
        pair<string, int> assignPair = rec.get_column(assignCol);
        pair<string, int> varPair = rec.get_column(varCol);
        int assignStmt = assignPair.second;
        string var = varPair.first;
        Node *assignNode =
                this->pkb->get_stmtBank()->get_node(assignStmt);
        string modifiedVar;
        set<string> get_modifies =
                this->pkb->get_var_stmt_modifies(assignStmt);
        for (set<string>::iterator k = get_modifies.begin();
                k != get_modifies.end(); k++) {
            modifiedVar = *k;
        }
        if (modifiedVar == var) {
            if (this->evaluate_matching_tree(
                    assignNode->get_leaves()[1], rootExprTree)) {
                rTable.syn_11_mark_row_ok(i);
            }
        }
    }
    rTable.syn_11_transaction_end();
}

void QueryEvaluator::evaluate_patCl_assign_syn_wildcard_22(
        ResultsTable& rTable, const PatCl *patCl)
{
    pair<pair<const vector<Record> *, int>,
         pair<const vector<Record> *, int>> vipPair =
            rTable.syn_22_transaction_begin(patCl->syn,
                    patCl->varRefString);

    const vector<Record>& assignRecords = *(vipPair.first.first);
    int assignCol = vipPair.first.second;
    int assignRecordsSize = assignRecords.size();

    const vector<Record>& varRecords = *(vipPair.second.first);
    int varCol = vipPair.second.second;
    int varRecordsSize = varRecords.size();

    for (int i = 0; i < assignRecordsSize; i++) {
        const Record& rec = assignRecords[i];
        const pair<string, int>& assignPair = rec.get_column(assignCol);
        int assignStmt = assignPair.second;
        string modifiedVar;
        set<string> modifiedVarSet =
                this->pkb->get_var_stmt_modifies(assignStmt);
        for (set<string>::iterator k = modifiedVarSet.begin();
                k != modifiedVarSet.end(); k++) {
            modifiedVar = *k;
        }
        for (int j = 0; j < varRecordsSize; j++) {
            const Record& rec = varRecords[j];
            const pair<string, int>& varPair = rec.get_column(varCol);
            string var = varPair.first;
            if (var == modifiedVar) {
                //rTable.syn_22_add_row(assignStmt, j);
                rTable.syn_22_add_row(i, j);
            }
        }
    }
    rTable.syn_22_transaction_end();
}

void QueryEvaluator::evaluate_patCl_assign_wildcard_expr(int rTableIdx,
        const PatCl *patCl)
{
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    bool hasAssignSyn = rTable.has_synonym(patCl->syn);
    Node *rootExprTree = Parser(patCl->exprString, FROMSTRING).yard();
    if (hasAssignSyn) {
        pair<const vector<Record> *, int> viPair =
                rTable.syn_1_transaction_begin(patCl->syn);
        int assignCol = viPair.second;
        const vector<Record>& records = *(viPair.first);
        int recordsNo = records.size();
        for (int i = 0; i < recordsNo; i++) {
            const Record& rec = records[i];
            pair<string, int> assignPair = rec.get_column(assignCol);
            int assignStmt = assignPair.second;
            Node *assignNode =
                    this->pkb->get_stmtBank()->get_node(assignStmt);
            if (this->evaluate_matching_tree(
                    assignNode->get_leaves()[1], rootExprTree)) {
                rTable.syn_1_mark_row_ok(i);
            }
        }
        rTable.syn_1_transaction_end();
    } else {
        rTable.syn_0_transaction_begin(patCl->syn, RV_INT);
        set<int> allAssignStmts = this->pkb->get_all_assign();
        for (set<int>::iterator i = allAssignStmts.begin();
                i != allAssignStmts.end(); i++) {
            int assignStmt = *i;
            Node *assignNode =
                    this->pkb->get_stmtBank()->get_node(assignStmt);
            std::queue<Node *> nodeQueue;
            //---------------------------------------------
            /*nodeQueue.push(assignNode);
            while (!nodeQueue.empty()) {
                Node* frontNode = nodeQueue.front();
                nodeQueue.pop();
                vector<Node*> leaves = frontNode->get_leaves();
                for (int i=0; i<leaves.size(); i++) {
                    nodeQueue.push(leaves[i]);
                    if (leaves[i]->get_name() == rootExprTree->get_name()) {
                        if (this->evaluate_matching_tree(leaves[i], rootExprTree)) {
                            rTable.syn_0_add_row(assignStmt);
                        }
                    }
                }*/
            if (this->evaluate_matching_tree(
                    assignNode->get_leaves()[1], rootExprTree)) {
                rTable.syn_0_add_row(assignStmt);
            }
        }
        rTable.syn_0_transaction_end();
    }
}

void QueryEvaluator::evaluate_patCl_assign_wildcard_exprwild(int rTableIdx,
        const PatCl *patCl)
{
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    bool hasAssignSyn = rTable.has_synonym(patCl->syn);
    Node *rootExprTree = Parser(patCl->exprString, FROMSTRING).yard();

    if (hasAssignSyn) {
        pair<const vector<Record> *, int> viPair =
            rTable.syn_1_transaction_begin(patCl->syn);
        int assignCol = viPair.second;
        const vector<Record>& records = *(viPair.first);
        int recordsSize = records.size();
        for (int i = 0; i < recordsSize; i++) {
            const Record& rec = records[i];
            pair<string, int> assignPair = rec.get_column(assignCol);
            int assignStmt = assignPair.second;
            Node *assignNode =
                    this->pkb->get_stmtBank()->get_node(assignStmt);
            std::queue<Node *> nodeQueue;
            nodeQueue.push(assignNode);
            while (!nodeQueue.empty()) {
                Node *frontNode = nodeQueue.front();
                nodeQueue.pop();
                vector<Node *> leaves = frontNode->get_leaves();
                int nrLeaves = leaves.size();
                for (int k = 0; k < nrLeaves; k++) {
                    nodeQueue.push(leaves[k]);
                    if (leaves[k]->get_name() ==
                            rootExprTree->get_name()) {
                        if (this->evaluate_matching_tree(leaves[k],
                                rootExprTree)) {
                            rTable.syn_1_mark_row_ok(i);
                        }
                    }
                }
            }
        }
        rTable.syn_1_transaction_end();
    } else {
        rTable.syn_0_transaction_begin(patCl->syn, RV_INT);
        set<int> allAssignStmts = this->pkb->get_all_assign();
        for (set<int>::iterator i = allAssignStmts.begin();
                i != allAssignStmts.end(); i++) {
            int assignStmt = *i;
            Node *assignNode =
                    this->pkb->get_stmtBank()->get_node(assignStmt);
            std::queue<Node *> nodeQueue;
            nodeQueue.push(assignNode);
            while (!nodeQueue.empty()) {
                Node *frontNode = nodeQueue.front();
                nodeQueue.pop();
                vector<Node *> leaves = frontNode->get_leaves();
                int nrLeaves = leaves.size();
                for (int i = 0; i < nrLeaves; i++) {
                    nodeQueue.push(leaves[i]);
                    if (leaves[i]->get_name() ==
                            rootExprTree->get_name()) {
                        if (this->evaluate_matching_tree(
                                leaves[i], rootExprTree)) {
                            rTable.syn_0_add_row(assignStmt);
                        }
                    }
                }
            }
       }
        rTable.syn_0_transaction_end();
    }
}

void QueryEvaluator::evaluate_patCl_assign_wildcard_wildcard(
        int rTableIdx, const PatCl *patCl)
{
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    bool hasSyn = rTable.has_synonym(patCl->syn);
    if (hasSyn) {
        //nothing to do here
    } else {
        rTable.syn_0_transaction_begin(patCl->syn, RV_INT);
        set<int> allAssignStmts = this->pkb->get_all_assign();
        for (set<int>::iterator i = allAssignStmts.begin();
                i != allAssignStmts.end(); i++) {
            int assignStmt = *i;
            rTable.syn_0_add_row(assignStmt);
        }
        rTable.syn_0_transaction_end();
    }
    
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
    //queryStr = "while w; if i; variable v;";
    //queryStr += "Select a such that Modifies(w, i) and pattern i(v, _)";
    //i = syn, v = varRefType, _ = exprType
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
        // Make this a 10 transaction using augment_new_row
        std::pair<const std::vector<Record> *, int> viPair =
                rTable.syn_10_transaction_begin(patCl->syn,
                        patCl->varRefString, RV_STRING);
        const vector<Record>& record = *(viPair.first);
        int noRecords = record.size();
        int synColNo = viPair.second;
        for (int i = 0; i < noRecords; i++) {
            const Record& rec = record[i];
            const pair<string, int>& ifPair = rec.get_column(synColNo);
            int ifStmt = ifPair.second;
            const string& controlVariable =
                    this->pkb->get_control_variable(ENT_IF, ifStmt);
            rTable.syn_10_augment_new_row(i, controlVariable);
        }
        rTable.syn_10_transaction_end();
    } else if (hasVarSyn) {
        // pattern ifSyn(varSyn,_,_)
        // ifSyn is not seen
        // for each varSyn, get the if statement it is a control
        // variable (if any) and augment the row.
        // Make this a 01 transaction using augment_new_row
        std::pair<const std::vector<Record> *, int> viPair =
                rTable.syn_01_transaction_begin(patCl->syn,
                        patCl->varRefString, RV_STRING);
        const vector<Record>& record = *(viPair.first);
        int noRecords = record.size();
        int varColNo = viPair.second;
        for (int i = 0; i < noRecords; i++) {
            const Record& rec = record[i];
            const pair<string, int>& varPair = rec.get_column(varColNo);
            string var = varPair.first;
            const std::set<int> allIfStmts = this->pkb->get_all_if();
            for (set<int>::iterator m = allIfStmts.begin();
                    m != allIfStmts.end(); i++) {
                int ifStmt = *m;
                if (this->pkb->has_control_variable(ENT_IF,
                        ifStmt, var)) {
                    rTable.syn_01_augment_new_row(i, *m);
                }
            }
        }
        rTable.syn_01_transaction_end();
    } else {
        // pattern ifSyn(varSyn,_,_)
        // both not seen. This is a 00 transaction, but it is
        // advised to get all if stmts, then get their control
        // variable, and add the new row.
        rTable.syn_00_transaction_begin(patCl->syn, RV_INT,
                patCl->varRefString, RV_STRING);
        set<int> allIfStmts = this->pkb->get_all_if();
        for (set<int>::iterator m = allIfStmts.begin();
                m != allIfStmts.end(); m++) {
            int ifStmt = *m;
            const string& controlVariable =
                this->pkb->get_control_variable(ENT_IF, *m);
            rTable.syn_00_add_row(*m, controlVariable);
        }
        rTable.syn_00_transaction_end();
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
            if (this->pkb->has_control_variable(
                    ENT_IF, ifSynVal, controlVarName)) {
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
        pair<const vector<Record>*, int> viPair =
            rTable.syn_1_transaction_begin(patCl->syn);
        int ifSynCol = viPair.second;
        const vector<Record>& ifPair = *(viPair.first);
        int nrIfPair = ifPair.size();
        for (int i = 0; i < nrIfPair; i++) {
            const Record& rec = ifPair[i];
            const pair<string, int>& ifSynPair = rec.get_column(ifSynCol);
            int ifSynStmt = ifSynPair.second;
            if (this->pkb->has_control_variable(
                    ENT_IF, ifSynStmt, patCl->varRefString)) {
                rTable.syn_1_mark_row_ok(i);
            }
        }
        rTable.syn_1_transaction_end();
    } else {
        // ifSyn("someVarString",_,_)
        // ifSyn is NOT seen. Use ResultsTable::syn_0_transaction
        // Retrieve all if stmt. Loop and only syn_0_add_row
        // those with "someVarString" as control variable
        rTable.syn_0_transaction_begin(patCl->syn, RV_INT);
        set<int> allIfStmts = this->pkb->get_all_if();
        for (set<int>::iterator i = allIfStmts.begin();
                i != allIfStmts.end(); i++) {
            int ifStmt = *i;
            if (this->pkb->has_control_variable(
                    ENT_IF, ifStmt, patCl->varRefString)) {
                rTable.syn_0_add_row(ifStmt);
            }
        }
        rTable.syn_0_transaction_end();
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
        rTable.syn_0_transaction_begin(patCl->syn, RV_INT);
        set<int> allIfStmts = this->pkb->get_all_if();
        for (set<int>::iterator i = allIfStmts.begin();
                i != allIfStmts.end(); i++) {
            int ifStmt = *i;
            rTable.syn_0_add_row(ifStmt);
        }
        rTable.syn_0_transaction_end();
    }
}

void QueryEvaluator::evaluate_patCl_while(int rTableIdx,
        const PatCl *patCl)
{
    assert(patCl->varRefType == PATVARREF_SYN ||
        patCl->varRefType == PATVARREF_STRING ||
        patCl->varRefType == PATVARREF_WILDCARD);
    if (patCl->varRefType == PATVARREF_SYN) {
        this->evaluate_patCl_while_var_syn(rTableIdx, patCl);
    } else if (patCl->varRefType == PATVARREF_STRING) {
        this->evaluate_patCl_while_var_string(rTableIdx, patCl);
    } else if (patCl->varRefType == PATVARREF_WILDCARD) {
        this->evaluate_patCl_while_var_wildcard(rTableIdx, patCl);
    }
}

void QueryEvaluator::evaluate_patCl_while_var_syn(int rTableIdx, 
        const PatCl *patCl) 
{
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    bool hasWhileSyn = rTable.has_synonym(patCl->syn);
    bool hasVarSyn = rTable.has_synonym(patCl->varRefString);
    if (hasWhileSyn && hasVarSyn) {
        //whileSynand varSyn have been seen
        if (rTable.syn_in_same_table(patCl->syn, patCl->varRefString)) {
            this->evaluate_patCl_while_var_syn_11(rTable, patCl);
        } else {
            this->evaluate_patCl_while_var_syn_22(rTable, patCl);
        }
    } else if (hasWhileSyn) {
        //whileSyn seen, varSyn not seen
        //10 transaction
        pair<const vector<Record> *, int> viPair = rTable.
            syn_10_transaction_begin(patCl->syn, patCl->varRefString,
                    RV_INT);
        const vector<Record>& records = *(viPair.first);
        int nrRecords = records.size();
        int whileCol = viPair.second;
        for (int i = 0; i < nrRecords; i++) {
            const pair<string, int> &whileStmt =
                    records[i].get_column(whileCol);
            int whileStmtNo = whileStmt.second;
            string varString =
                    this->pkb->get_control_variable(ENT_WHILE,
                            whileStmtNo);
            rTable.syn_10_augment_new_row(i, varString);
        }
        rTable.syn_10_transaction_end();
    } else if (hasVarSyn) {
        //whileSyn not seen, varSyn seen
        //01 transaction
        pair<const vector<Record>*, int> viPair = rTable.
            syn_01_transaction_begin(patCl->syn, patCl->varRefString,
                    RV_INT);
        const vector<Record>& records = *(viPair.first);
        //vector<Record> records = *(viPair.first);
        int varCol = viPair.second;
        int noRecords = records.size();

        for (int i = 0; i < noRecords; i++) {
            const Record& rec = records[i];
            const pair<string, int>& varPair = rec.get_column(varCol);
            string var = varPair.first;
            const set<int> allWhileStmts = this->pkb->get_all_while();
            for (set<int>::iterator k = allWhileStmts.begin();
                    k != allWhileStmts.end(); k++) {
                int whileStmt = *k;
                if (this->pkb->has_control_variable(ENT_WHILE,
                        whileStmt, var)) {
                    rTable.syn_01_augment_new_row(i, whileStmt);
                }
            }
        }
        rTable.syn_01_transaction_end();
        /*set<int> allWhileStmts = this->pkb->get_all_while();
        for (set<int>::iterator i = allWhileStmts.begin(); i!=allWhileStmts.end(); i++) {
            int whileStmt = *i;
            if (this->pkb->has_control_variable(ENT_WHILE, whileStmt, patCl->varRefString)) {
                rTable.syn_01_augment_new_row();
            }
        }*/
    }
}
void QueryEvaluator::evaluate_patCl_while_var_string(int rTableIdx, 
        const PatCl *patCl) 
{
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    if (rTable.has_synonym(patCl->syn)) {
        //whileSyn has been seen
        pair<const vector<Record>*, int> viPair =
                rTable.syn_1_transaction_begin(patCl->syn);
        int whileCol = viPair.second;
        const vector<Record>& records = *(viPair.first);
        int noRecords = records.size();
        for (int i = 0; i < noRecords; i++) {
            const Record& rec = records[i];
            const pair<string, int>& whilePair = rec.get_column(whileCol);
            int whileStmt = whilePair.second;
            if (this->pkb->has_control_variable(
                    ENT_WHILE, whileStmt, patCl->varRefString)) {
                rTable.syn_1_mark_row_ok(i);
            }
        }
        rTable.syn_1_transaction_end();
    } else {
        //whileSyn has not been seen
        rTable.syn_0_transaction_begin(patCl->syn, RV_INT);
        set<int> allWhileStmts = this->pkb->get_all_while();
        for (set<int>::iterator i = allWhileStmts.begin();
                i != allWhileStmts.end(); i++) {
            int whileStmt = *i;
            if (this->pkb->has_control_variable(
                    ENT_WHILE, whileStmt, patCl->varRefString)) {
                rTable.syn_0_add_row(whileStmt);
            }
        }
        rTable.syn_0_transaction_end();
    }
}
void QueryEvaluator::evaluate_patCl_while_var_wildcard(int rTableIdx, 
        const PatCl *patCl)
{
    //pattern while(_, _)
    ResultsTable& rTable = this->resultsTable[rTableIdx];
    if (rTable.has_synonym(patCl->syn)) {
        //rTable has whileSyn, nothing to do
    } else {
        //syn_0
        rTable.syn_0_transaction_begin(patCl->syn, RV_INT);
        set<int> allWhileStmts = this->pkb->get_all_while();
        for (set<int>::iterator i = allWhileStmts.begin();
                i != allWhileStmts.end(); i++) {
            int whileStmt = *i;
            rTable.syn_0_add_row(whileStmt);
        }
        rTable.syn_0_transaction_end();
    }
}
void QueryEvaluator::evaluate_patCl_while_var_syn_11(ResultsTable& rTable,
        const PatCl *patCl)
{
    pair<const vector<Record>*, pair<int, int>> viiPair =
            rTable.syn_11_transaction_begin(patCl->syn,
                    patCl->varRefString);
    const vector<Record>& records = *(viiPair.first);
    int whileSynCol = viiPair.second.first;
    int varSynCol = viiPair.second.second;
    int noRecords = records.size();
    for (int i = 0; i < noRecords; i++) {
        const Record& rec = records[i];
        const pair<string, int>& whilePair = rec.get_column(whileSynCol);
        const pair<string, int>& varPair = rec.get_column(varSynCol);
        int whileStmt = whilePair.second;
        const string& controlVar = varPair.first;
        if (this->pkb->has_control_variable(ENT_WHILE, whileStmt,
                controlVar)) {
            rTable.syn_11_mark_row_ok(i);
        }
    }
    rTable.syn_11_transaction_end();
}
void QueryEvaluator::evaluate_patCl_while_var_syn_22(ResultsTable& rTable,
        const PatCl *patCl)
{
    pair<pair<const vector<Record> *, int>,
        pair<const vector<Record> *, int> > vipPair =
            rTable.syn_22_transaction_begin(patCl->syn,
                    patCl->varRefString);
    const vector<Record>& whileSynVec = *(vipPair.first.first);
    int whileCol = vipPair.first.second;
    int whileSynSize = whileSynVec.size();

    const vector<Record>& varSynVec = *(vipPair.second.first);
    int controlVarCol = vipPair.second.second;
    int varSynSize = varSynVec.size();

    vector<const string *> cVarVec;
    for (int i = 0; i < varSynSize; i++) {
        const Record& controlVarRecord = varSynVec[i];
        const pair<string, int>& controlVarPair = 
            controlVarRecord.get_column(controlVarCol);
        cVarVec.push_back(&(controlVarPair.first));
    }

    for (int i = 0; i < whileSynSize; i++) {
        const Record& whileSynRecord = whileSynVec[i];
        const pair<string, int>& whileSynPair =
            whileSynRecord.get_column(whileCol);
        int whileStmt = whileSynPair.second;
        for (int k=0; k<varSynSize; k++) {
            const string& controlVarName = *(cVarVec[k]);
            if (this->pkb->has_control_variable(ENT_IF, whileStmt,
                    controlVarName)) {
                rTable.syn_22_add_row(i, k);
            }
        }
    }
    rTable.syn_22_transaction_end();
}