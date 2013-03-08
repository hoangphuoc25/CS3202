#ifndef T11_QUERY_EVALUATOR_H
#define T11_QUERY_EVALUATOR_H

#include <list>
#include <set>
#include <string>
#include "PKB.h"
#include "PQLParser.h"
#include "ResultsTable.h"
#include "ResultsProjector.h"

// Used when one/both RelRef arguments are synonyms.
enum SynInGraph {
    SYN_SYN_00, // both args syn, both not in graph
    SYN_SYN_01, // both args syn, 1st arg not in graph, 2nd arg in graph
    SYN_SYN_10, // both args syn, 1st arg in graph, 2nd arg not in graph
    SYN_SYN_11, // both args syn, both in graph and in same table
    SYN_SYN_22, // both args syn, both in graph but in diff tables
    SYN_X_0,    // 1st arg = syn, 2nd arg = not syn, syn not in graph
    SYN_X_1,    // 1st arg = syn, 2nd arg = not syn, syn in graph
    X_SYN_0,    // 1st arg = not syn, 2nd arg = syn, syn not in graph
    X_SYN_1,    // 1st arg = not syn, 2nd arg = syn, syn in graph
    SYN_ARGS_INVALID
};

// Used by EvalSyn to dispatch to actual methods for evaluating RelRef
// This contains sufficient information about the RelRef to allow us
// to dispatch to the proper function
struct EvalSynArgDesc {
    enum RelRefType relRefType;
    enum SynInGraph synInGraph;
    enum DesignEnt argOneSynType;
    enum DesignEnt argTwoSynType;
    enum RelRefArgType argOneOtherType;
    enum RelRefArgType argTwoOtherType;

    EvalSynArgDesc();
    EvalSynArgDesc(enum RelRefType, enum SynInGraph, enum DesignEnt,
            enum DesignEnt, enum RelRefArgType, enum RelRefArgType);
};

// Used to compare EvalSynArgDesc
struct EvalSynArgDescCmp {
    bool operator()(const EvalSynArgDesc &a, const EvalSynArgDesc &b) const;
};

// Forward declaration
class QueryEvaluator;

// Used as a lookup table to PKB
struct EvalPKBDispatch {
    // Retrieve all arg two satisfying a given arg one
    std::set<std::string> (PKB::*get_string_set_argTwo_from_string_argOne)
        (DesignEnt typeOne, DesignEnt typeTwo, const std::string&) const;
    std::set<std::string> (PKB::*get_string_set_argTwo_from_int_argOne)
        (DesignEnt typeOne, DesignEnt typeTwo, int) const;
    std::set<int> (PKB::*get_int_set_argTwo_from_string_argOne)
        (DesignEnt typeOne, DesignEnt typeTwo, const std::string&) const;
    std::set<int> (PKB::*get_int_set_argTwo_from_int_argOne)
        (DesignEnt typeOne, DesignEnt typeTwo, int) const;
    // Retrieve all arg one satisfying a given arg two
    std::set<std::string> (PKB::*get_string_set_argOne_from_string_argTwo)
        (DesignEnt typeOne, DesignEnt typeTwo, const std::string&) const;
    std::set<std::string> (PKB::*get_string_set_argOne_from_int_argTwo)
        (DesignEnt typeOne, DesignEnt typeTwo, int) const;
    std::set<int> (PKB::*get_int_set_argOne_from_string_argTwo)
        (DesignEnt typeOne, DesignEnt typeTwo, const std::string&) const;
    std::set<int> (PKB::*get_int_set_argOne_from_int_argTwo)
        (DesignEnt typeOne, DesignEnt typeTwo, int) const;
    // Retrieve all arg one / arg two
    std::set<std::string> (PKB::*get_all_string_argOne)() const;
    std::set<int> (PKB::*get_all_int_argOne)() const;
    std::set<std::string> (PKB::*get_all_string_argTwo)() const;
    std::set<int> (PKB::*get_all_int_argTwo)() const;

    // Predicates
    bool (PKB::*f_string_argOne_string_argTwo)
            (DesignEnt argOneType, const std::string&,
             DesignEnt argTwoType, const std::string&) const;
    bool (PKB::*f_string_argOne_int_argTwo)(DesignEnt argOneType,
             const std::string&, DesignEnt argTwType, int) const;
    bool (PKB::*f_int_argOne_string_argTwo)(DesignEnt argOneType,
             int, DesignEnt argTwoType, const std::string&) const;
    bool (PKB::*f_int_argOne_int_argTwo)(DesignEnt argOneType,
             int, DesignEnt argTwoType, int) const;

    // Generic QueryEvaluator evaluation function
    void (QueryEvaluator::*relRef_eval)
             (int rTableIdx, const RelRef *relRef, const EvalPKBDispatch&);

    EvalPKBDispatch();
    void reset();
};

class QueryEvaluator {
public:
    QueryEvaluator();
    // used to parse a SIMPLE program. Must be called before evaluate
    void parseSimple(const std::string& simple);
    // Called after parseSimple. Evaluates a query based on the SIMPLE program
    // Results are returned in resultsSet
    void evaluate(const std::string& queryStr,
            std::list<std::string>& resultSet);
private:
    void reset();
    void partition_evaluation(QueryInfo *qinfo);
    void partition_process_relRef(int idx, const GenericRef *genRef);
    void partition_process_patCl(int idx, const GenericRef *genRef);
    int partition_add_vertex(int idx, const std::string& syn);
    void partition_add_edge(int idx, const std::string& synOne,
            const std::string& synTwo);
    void partition_evaluation_cc();
    void partition_evaluation_cc_bfs(int v);
    void partition_evaluation_partition(int nrClauses);

    bool relRef_arg_use_string(DesignEnt entType) const;
    void evaluate_relRef(int rTableIdx, const GenericRef *genRef);
    void ev_relRef_syn_syn(int rTableIdx, const RelRef *relRef);
    void ev_relRef_syn_syn_00_setup(EvalPKBDispatch& pkbDispatch,
            const RelRef *relRef) const;
    void ev_relRef_syn_syn_01_setup(EvalPKBDispatch& pkbDispatch,
            const RelRef *relRef) const;
    void ev_relRef_syn_syn_10_setup(EvalPKBDispatch& pkbDispatch,
            const RelRef *relRef) const;
    void ev_relRef_syn_syn_11_22_setup(SynInGraph sig,
            EvalPKBDispatch& pkbDispatch, const RelRef *relRef) const;
    typedef std::set<std::string> (PKB::*pkbGetAllStringFn) () const;
    typedef std::set<int> (PKB::*pkbGetAllIntFn) () const;
    typedef std::set<std::string> (PKB::*pkbGet_1SS_From_2SS)
                    (DesignEnt, DesignEnt, const std::string&) const;
    typedef std::set<std::string> (PKB::*pkbGet_1SS_From_2IS)
                    (DesignEnt, DesignEnt, int) const;
    typedef std::set<int> (PKB::*pkbGet_1IS_From_2SS)
                    (DesignEnt, DesignEnt, const std::string&) const;
    typedef std::set<int> (PKB::*pkbGet_1IS_From_2IS)
                    (DesignEnt, DesignEnt, int) const;
    typedef std::set<std::string> (PKB::*pkbGet_2SS_From_1SS)
                    (DesignEnt, DesignEnt, const std::string&) const;
    typedef std::set<std::string> (PKB::*pkbGet_2SS_From_1IS)
                    (DesignEnt, DesignEnt, int) const;
    typedef std::set<int> (PKB::*pkbGet_2IS_From_1SS)
                    (DesignEnt, DesignEnt, const std::string&) const;
    typedef std::set<int> (PKB::*pkbGet_2IS_From_1IS)
                    (DesignEnt, DesignEnt, int) const;
    pkbGetAllStringFn pkbd_setup_get_all_string_method(
            DesignEnt ent) const;
    pkbGetAllIntFn pkbd_setup_get_all_int_method(DesignEnt ent) const;
    pkbGet_1SS_From_2SS pkbd_setup_get_1SS_From_2SS(RelRefType r) const;
    pkbGet_1SS_From_2IS pkbd_setup_get_1SS_From_2IS(RelRefType r) const;
    pkbGet_1IS_From_2SS pkbd_setup_get_1IS_From_2SS(RelRefType r) const;
    pkbGet_1IS_From_2IS pkbd_setup_get_1IS_From_2IS(RelRefType r) const;
    pkbGet_2SS_From_1SS pkbd_setup_get_2SS_From_1SS(RelRefType r) const;
    pkbGet_2SS_From_1IS pkbd_setup_get_2SS_From_1IS(RelRefType r) const;
    pkbGet_2IS_From_1SS pkbd_setup_get_2IS_From_1SS(RelRefType r) const;
    pkbGet_2IS_From_1IS pkbd_setup_get_2IS_From_1IS(RelRefType r) const;

    // How to read these functions
    // eg. ev_rr_ss_string_string_00_from_argOne
    //     ev = evaluate, rr = relRef, ss = syn syn (both args are syn)
    //     string_string = arg 1 is string, arg 2 is string
    //     00 = arg 1 is not in results, arg 2 is not in results
    //     from_argOne = since both arg 1 and arg 2 are not in results,
    //                   we can choose to get either all arg 1 or all arg 2
    //                   from the PKB. In this case, we choose to get all
    //                   all arg 1. Hence from_argOne
    void ev_rr_ss_string_string_00_from_argOne(int rTableIdx,
            const RelRef *relRef, const EvalPKBDispatch& disp);
    // Currently, nothing uses this and it does not seem it will be used
    void ev_rr_ss_string_string_00_from_argTwo(int rTableIdx,
            const RelRef *relRef, const EvalPKBDispatch& disp);
    void ev_rr_ss_string_string_01(int rTableIdx, const RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_string_string_10(int rTableIdx, const RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_string_string_11(int rTableIdx, const RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_string_string_22(int rTableIdx, const RelRef *relRef,
            const EvalPKBDispatch& disp);
    // Currently, nothing uses this and it does not seem it will be used
    void ev_rr_ss_string_int_00_from_argOne(int rTableIdx,
            const RelRef *relRef, const EvalPKBDispatch& disp);
    // Currently, nothing uses this and it does not seem it will be used
    void ev_rr_ss_string_int_00_from_argTwo(int rTableIdx,
            const RelRef *relRef, const EvalPKBDispatch& disp);
    // Currently, nothing uses this and it does not seem it will be used
    void ev_rr_ss_string_int_01(int rTableIdx, const RelRef *relRef,
            const EvalPKBDispatch& disp);
    // Currently, nothing uses this and it does not seem it will be used
    void ev_rr_ss_string_int_10(int rTableIdx, const RelRef *relRef,
            const EvalPKBDispatch& disp);
    // Currently, nothing uses this and it does not seem it will be used
    void ev_rr_ss_string_int_11(int rTableIdx, const RelRef *relRef,
            const EvalPKBDispatch& disp);
    // Currently, nothing uses this and it does not seem it will be used
    void ev_rr_ss_string_int_22(int rTableIdx, const RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_int_string_00_from_argOne(int rTableIdx,
            const RelRef *relRef, const EvalPKBDispatch& disp);
    // not used for now
    void ev_rr_ss_int_string_00_from_argTwo(int rTableIdx,
            const RelRef *relRef, const EvalPKBDispatch& disp);
    /*
     * Evaluates RelRef where both arguments are synonyms; the
     * first synonym has values of type integer and was not previously
     * in any RelRef, the second synonym has values of type string and
     *  was in at least one previous RelRef.
     *
     * Current evaluation strategy is to:
     * 1. Get the set of valid values for 2nd synonym from the graph,
     *    call this set Y.
     * 2. For each element in Y, retrieve the set of X such that
     *    RelRef(X,Y).
     * 3. Add edge(X,Y) to the graph.
     */
    void ev_rr_ss_int_string_01(int rTableIdx, const RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_int_string_10(int rTableIdx, const RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_int_string_11(int rTableIdx, const RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_int_string_22(int rTableIdx, const RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_int_int_00_from_argOne(int rTableIdx,
            const RelRef *relRef, const EvalPKBDispatch& disp);
    void ev_rr_ss_int_int_00_from_argTwo(int rTableIdx,
            const RelRef *relRef, const EvalPKBDispatch& disp);
    void ev_rr_ss_int_int_01(int rTableIdx, const RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_int_int_10(int rTableIdx, const RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_int_int_11(int rTableIdx, const RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_int_int_22(int rTableIdx, const RelRef *relRef,
            const EvalPKBDispatch& disp);

    // evaluate relRef, one of the arguments is a synonym
    void ev_relRef_syn_X(int rTableIdx, const RelRef *relRef);
    void ev_relRef_X_syn(int rTableIdx, const RelRef *relRef);
    // evaluate relRef, none of the arguments is a synonym
    void ev_relRef_X_X(int rTableIdx, const RelRef *relRef);

    void evaluate_patCl(int rTableIdx, const GenericRef *genRef);
    void evaluate_patCl_assign(int rTableIdx, const PatCl *patCl);
    void evaluate_patCl_if(int rTableIdx, const PatCl *patCl);
    void evaluate_patCl_if_var_syn(int rTableIdx, const PatCl *patCl);
    void evaluate_patCl_if_var_syn_11(ResultsTable& rTable,
            const PatCl *patCl);
    void evaluate_patCl_if_var_syn_22(ResultsTable& rTable,
            const PatCl *patCl);
    void evaluate_patCl_if_var_string(int rTableIdx,
            const PatCl *patCl);
    void evaluate_patCl_if_var_wildcard(int rTableIdx,
            const PatCl *patCl);
    void evaluate_patCl_while(int rTableIdx, const PatCl *patCl);

    PQLParser pqlParser;
    PKB *pkb;
    ResultsProjector resultsProjector;
    std::map<EvalSynArgDesc, EvalPKBDispatch,
             EvalSynArgDescCmp> dispatchTable;
    bool isAlive;

    // evaluating Rel(syn,syn)

    // graph construction purposes
    std::map<std::string, int> graph_synMap;
    std::vector<std::set<int> > graph_adjList;
    std::vector<int> graph_refToVertex;
    std::vector<int> graph_vertexCC;
    int graph_nrVertexCC;
    std::set<int> graph_isolatedClauses;
    std::vector<std::vector<int> > partitionedClauses;
    std::vector<ResultsTable> resultsTable;
};

#endif