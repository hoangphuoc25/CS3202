#ifndef T11_QUERY_EVALUATOR_H
#define T11_QUERY_EVALUATOR_H

#include <list>
#include <string>
#include "PKB.h"
#include "PQLParser.h"
#include "ResultsGraph.h"
#include "ResultsProjector.h"

// Used when one/both RelRef arguments are synonyms.
enum SynInGraph {
    SYN_SYN_00, // both args syn, both not in graph
    SYN_SYN_01, // both args syn, 1st arg not in graph, 2nd arg in graph
    SYN_SYN_10, // both args syn, 1st arg in graph, 2nd arg not in graph
    SYN_SYN_11, // both args syn, both args in graph
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
                              (const std::string&) const;
    std::set<std::string> (PKB::*get_string_set_argTwo_from_int_argOne)
                              (int) const;
    std::set<int> (PKB::*get_int_set_argTwo_from_string_argOne)
                      (const std::string&) const;
    std::set<int> (PKB::*get_int_set_argTwo_from_int_argOne)
                      (int) const;
    // Retrieve all arg one satisfying a given arg two
    std::set<std::string> (PKB::*get_string_set_argOne_from_string_argTwo)
                              (const std::string&) const;
    std::set<std::string> (PKB::*get_string_set_argOne_from_int_argTwo)
                              (int) const;
    std::set<int> (PKB::*get_int_set_argOne_from_string_argTwo)
                      (const std::string&) const;
    std::set<int> (PKB::*get_int_set_argOne_from_int_argTwo)
                      (int) const;
    // Retrieve all arg one / arg two
    std::set<std::string> (PKB::*get_all_string_argOne)() const;
    std::set<int> (PKB::*get_all_int_argOne)() const;
    std::set<std::string> (PKB::*get_all_string_argTwo)() const;
    std::set<int> (PKB::*get_all_int_argTwo)() const;

    // Predicates
    bool (PKB::*f_string_argOne_string_argTwo)
            (const std::string&, const std::string&) const;
    bool (PKB::*f_string_argOne_int_argTwo)(const std::string&, int) const;
    bool (PKB::*f_int_argOne_string_argTwo)(int, const std::string&) const;
    bool (PKB::*f_int_argOne_int_argTwo)(int, int) const;

    // Generic QueryEvaluator evaluation function
    void (QueryEvaluator::*relRef_eval)
             (RelRef *relRef, const EvalPKBDispatch&);

    EvalPKBDispatch();
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
    bool relRef_arg_use_string(DesignEnt entType) const;
    void evaluate_relRef(RelRef *relRef);
    void ev_relRef_syn_syn(RelRef *relRef);
    // How to read these functions
    // eg. ev_rr_ss_string_string_00_from_argOne
    //     ev = evaluate, rr = relRef, ss = syn syn (both args are syn)
    //     string_string = arg 1 is string, arg 2 is string
    //     00 = arg 1 is not in results, arg 2 is not in results
    //     from_argOne = since both arg 1 and arg 2 are not in results,
    //                   we can choose to get either all arg 1 or all arg 2
    //                   from the PKB. In this case, we choose to get all
    //                   all arg 1. Hence from_argOne
    void ev_rr_ss_string_string_00_from_argOne(RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_string_string_00_from_argTwo(RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_string_string_01(RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_string_string_10(RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_string_string_11(RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_string_int_00_from_argOne(RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_string_int_00_from_argTwo(RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_string_int_01(RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_string_int_10(RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_string_int_11(RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_int_string_00_from_argOne(RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_int_string_00_from_argTwo(RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_int_string_01(RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_int_string_10(RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_int_string_11(RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_int_int_00_from_argOne(RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_int_int_00_from_argTwo(RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_int_int_01(RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_int_int_10(RelRef *relRef,
            const EvalPKBDispatch& disp);
    void ev_rr_ss_int_int_11(RelRef *relRef,
            const EvalPKBDispatch& disp);

    // evaluate relRef, one of the arguments is a synonym
    void ev_relRef_syn_X(RelRef *relRef);
    void ev_relRef_X_syn(RelRef *relRef);
    // evaluate relRef, none of the arguments is a synonym
    void ev_relRef_X_X(RelRef *relRef);

    void evaluate_patCl(PatCl *patCl);

    PQLParser pqlParser;
    PKB *pkb;
    ResultsGraph results;
    ResultsProjector resultsProjector;
    std::map<EvalSynArgDesc, EvalPKBDispatch,
             EvalSynArgDescCmp> dispatchTable;
};

#endif