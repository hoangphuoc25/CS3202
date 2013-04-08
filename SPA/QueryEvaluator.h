#ifndef T11_QUERY_EVALUATOR_H
#define T11_QUERY_EVALUATOR_H

#include <list>
#include <set>
#include <string>
#include <pthread.h>
#include "PKB.h"
#include "PQLParser.h"
#include "ResultsTable.h"
#include "ResultsProjector.h"

#define SPACONFIG_FNAME      "spaconfig.txt"
#define TEMP_SPACONFIG_FNAME "tempspaconfig.txt"
#define QE_MAXTHREADS_STR    "MaxThreads"
#define QE_THREADSON_STR     "ThreadsOn"
/// Default number of threads for multithreaded config
#define QE_DEFAULT_NR_THREADS 4
/// Minimum number of threads for multithreaded config
#define QE_MIN_THREADS 2
/// Maximum number of threads for multithreaded config
#define QE_MAX_THREADS 8

/// Represents whether synonym argument(s) to a clause have been seen
enum SynInGraph {
    SYN_SYN_00, //< both args syn, both not in graph
    SYN_SYN_01, //< both args syn, 1st arg not in graph, 2nd arg in graph
    SYN_SYN_10, //< both args syn, 1st arg in graph, 2nd arg not in graph
    SYN_SYN_11, //< both args syn, both in graph and in same table
    SYN_SYN_22, //< both args syn, both in graph but in diff tables
    SYN_X_0,    //< 1st arg = syn, 2nd arg = not syn, syn not in graph
    SYN_X_1,    //< 1st arg = syn, 2nd arg = not syn, syn in graph
    X_SYN_0,    //< 1st arg = not syn, 2nd arg = syn, syn not in graph
    X_SYN_1,    //< 1st arg = not syn, 2nd arg = syn, syn in graph
    SYN_ARGS_INVALID //< invalid arguments
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

/// Contains PKB methods to be called during evaluation of clauses
struct EvalPKBDispatch {
    /// Relation's arguments are (string,string); Retrieves a set of
    /// string synonym (2nd arg) satisfying a known string synonym
    /// (1st arg) based on the Relation
    std::set<std::string> (PKB::*get_string_set_argTwo_from_string_argOne)
        (DesignEnt typeOne, DesignEnt typeTwo, const std::string&) const;
    /// Relation's arguments are (int,string); Retrieves a set of string
    /// synonym (2nd arg) satisfying a known int synonym (1st arg)
    /// based on the Relation
    std::set<std::string> (PKB::*get_string_set_argTwo_from_int_argOne)
        (DesignEnt typeOne, DesignEnt typeTwo, int) const;
    /// Relation's arguments are (string,int); Retrieves a set of int
    /// synonym (2nd arg) satisfying a known string synonym (1st arg) based
    /// on the Relation
    std::set<int> (PKB::*get_int_set_argTwo_from_string_argOne)
        (DesignEnt typeOne, DesignEnt typeTwo, const std::string&) const;
    /// Relation's arguments are (int,int); Retrieves a set of int
    /// synonym (2nd arg) satisfying a known int synonym (1st arg) based
    /// on the Relation
    std::set<int> (PKB::*get_int_set_argTwo_from_int_argOne)
        (DesignEnt typeOne, DesignEnt typeTwo, int) const;
    /// Relation's arguments are (string,string); Retrieves a set of
    /// string synonym (1st arg) satisfying a known string synonym
    /// (2nd arg) based on the Relation
    std::set<std::string> (PKB::*get_string_set_argOne_from_string_argTwo)
        (DesignEnt typeOne, DesignEnt typeTwo, const std::string&) const;
    /// Relation's arguments are (string,int); Retrieves a set of
    /// string synonym (1st arg) satisfying a known int synonym
    /// (2nd arg) based on the Relation
    std::set<std::string> (PKB::*get_string_set_argOne_from_int_argTwo)
        (DesignEnt typeOne, DesignEnt typeTwo, int) const;
    /// Relation's arguments are (int,string); Retrieves a set of
    /// int synonym (1st arg) satisfying a known string synonym
    /// (2nd arg) based on the Relation
    std::set<int> (PKB::*get_int_set_argOne_from_string_argTwo)
        (DesignEnt typeOne, DesignEnt typeTwo, const std::string&) const;
    /// Relation's arguments are (int,int); Retrieves a set of
    /// int synonym (1st arg) satisfying a known int synonym
    /// (2nd arg) based on the Relation
    std::set<int> (PKB::*get_int_set_argOne_from_int_argTwo)
        (DesignEnt typeOne, DesignEnt typeTwo, int) const;
    /// Relation's arguments are (string,_); Retrieves the set of all
    /// string synonym for the 1st argument
    std::set<std::string> (PKB::*get_all_string_argOne)() const;
    /// Relation's arguments are (int,_); Retrieves the set of all
    /// int synonym for the 1st argument
    std::set<int> (PKB::*get_all_int_argOne)() const;
    /// Relation's arguments are (_,string); Retrieves the set of all
    /// string synonym for the 2nd argument
    std::set<std::string> (PKB::*get_all_string_argTwo)() const;
    /// Relation's arguments are (_,int); Retrieves the set of all
    /// int synonym for the 2nd argument
    std::set<int> (PKB::*get_all_int_argTwo)() const;

    // Predicates
    /// Relation R's arguments are (string,string); Determines whether
    /// R(x,y) is true based on concrete values of x and y
    bool (PKB::*f_string_argOne_string_argTwo)
            (DesignEnt argOneType, const std::string&,
             DesignEnt argTwoType, const std::string&) const;
    /// Relation R's arguments are (string,int); Determines whether
    /// R(x,y) is true based on concrete values of x and y
    bool (PKB::*f_string_argOne_int_argTwo)(DesignEnt argOneType,
             const std::string&, DesignEnt argTwType, int) const;
    /// Relation R's arguments are (string,_); Determines whether
    /// R(x,_) is true based on concrete value of x
    bool (PKB::*f_string_argOne_smth)(DesignEnt argOneType,
            const std::string&) const;
    /// Relation R's arguments are (int,string); Determines whether
    /// R(x,y) is true based on concrete values of x and y
    bool (PKB::*f_int_argOne_string_argTwo)(DesignEnt argOneType,
             int, DesignEnt argTwoType, const std::string&) const;
    /// Relation R's arguments are (int,int); Determines whether
    /// R(x,y) is true based on concrete values of x and y
    bool (PKB::*f_int_argOne_int_argTwo)(DesignEnt argOneType,
             int, DesignEnt argTwoType, int) const;
    /// Relation R's arguments are (int,_); Determines whether
    /// R(x,y) is true based on concrete value of x
    bool (PKB::*f_int_argOne_smth)(DesignEnt argOneType,
            int argOneVal) const;
    /// Relation R's arguments are (_,string); Determines whether
    /// R(_,y) is true based on concrete value of y
    bool (PKB::*f_smth_string_argTwo)(DesignEnt argTwoType,
            const std::string& argTwoVal) const;
    /// Relation R's arguments are (_,int); Determines whether
    /// R(_,y) is true based on concrete values of x and y
    bool (PKB::*f_smth_int_argTwo)(DesignEnt argTwoType, int argTwoVal)
            const;
    /// PKB method for checking if a concrete int synonym exists
    bool (PKB::*has_any_int)(int synVal) const;
    /// PKB method for checking if a concrete string synonym exists
    bool (PKB::*has_any_string)(const std::string& synVal) const;

    /// Generic QueryEvaluator evaluation function used for evaluating
    /// Relation clauses
    void (*relRef_eval)
             (ResultsTable &rTable, PKB *pkb, const RelRef *relRef,
              const EvalPKBDispatch&);
    /// Default constructor
    EvalPKBDispatch();
    /// Sets all the PKB method fields in the object to NULL
    void reset();
};

/// QueryEvaluator, the brains of the SPA.
/// Configuration of QueryEvaluator settings can be done through
/// supplying a map of string -> int flags in one of its constructors.
/// The flags currently include:
/// 1. multithreaded - If set, will fork up to the specified number
///                    of threads (minimum 1 thread) to evaluate the
///                    queries
class QueryEvaluator {
public:
    /// Default constructor
    QueryEvaluator();
    /// Constructor taking in a a map of settings
    /// @param flags Query Evaluator settings. Refer to the summary
    ///              documentation for QueryEvaluator for more details
    QueryEvaluator(const std::map<std::string, std::string>& flags);
    /// Initializes QueryEvaluator from a configuration file.
    /// The default configuration file is named 'spaconfig' and housed
    /// in the same directory as the executable.
    QueryEvaluator(const std::string& configFile);
    /// Parses a SIMPLE program; must be called before evaluate
    /// @param simple the SIMPLE source code in C++ std::string format
    void parseSimple(const std::string& simple);
    /// Parses a SIMPLE program in a given file
    /// @fname name of the file containing the SIMPLE program
    void parseSimple_from_file(const std::string& fname);
    /// Resets the QueryEvaluator with different settings
    /// @param settings read the class documentation for QueryEvaluator
    ///        for more information
    void reset(const std::map<std::string, std::string>& settings);
    /// Evaluates a PQL query; must be called after one of
    /// parseSimple or parseSimple_from_file
    /// @param queryStr the query string
    /// @param resultList results of query evaluation placed here
    void evaluate(const std::string& queryStr,
            std::list<std::string>& resultList);
    /// Checks if multithreading is enabled
    /// @return true if multithreading is enabled, false otherwise
    bool is_multithreaded() const;
    /// Gets the maximum number of threads to spawn if multithreading
    /// is enabled
    /// @return the maximum number of threads to spawn if multithreading
    ///         is enabled
    int get_maxThreads() const;

    /// typedef for get_all_[string synonym] PKB methods
    typedef std::set<std::string> (PKB::*pkbGetAllStringFn) () const;
    /// typedef for get_all_[int synonym] PKB methods
    typedef std::set<int> (PKB::*pkbGetAllIntFn) () const;
    /// Retrieves the appropriate PKB method for retrieving all
    /// synonym based on a given RefSynType of BASETYPE_INT
    /// @param refSynType the RefSynType of the synonym
    /// @return the PKB retrieval function to retrieve all synonyms
    ///         of that RefSynType
    static pkbGetAllIntFn
        get_all_int_pkb_method_from_RefSynType(
            RefSynType refSynType);
    /// Retrieves the appropriate PKB method for retrieving all
    /// synonym based on a given RefSynType of BASETYPE_STRING
    /// @param refSynType the RefSynType of the synonym
    /// @return the PKB retrieval function to retrieve all synonyms
    ///         of that RefSynType
    static pkbGetAllStringFn
        get_all_string_pkb_method_from_RefSynType(
            RefSynType refSynType);
    /// typedef for has_any_[int synonym] PKB methods
    typedef bool (PKB::*pkbHasAnyIntFn)(int) const;
    /// typedef for has_any_[string synonym] PKB methods
    typedef bool (PKB::*pkbHasAnyStringFn)(const std::string&) const;
    /// Retrieves the PKB method for has_any_X based on the RefSynType
    /// of X, where X is of BASETYPE_INT
    /// @param refSynType the RefSynType of the synonym X
    /// @return the appropriate PKB method for has_any_X
    static pkbHasAnyIntFn
        get_hasAnyInt_pkb_method_from_RefSynType(
            RefSynType refSynType);
    /// Retrieves the PKB method for has_any_X based on the RefSynType
    /// of X, where X is of BASETYPE_STRING
    /// @param refSynType the RefSynType of the synonym X
    /// @return the appropriate PKB method for has_any_X
    static pkbHasAnyStringFn
        get_hasAnyString_pkb_method_from_RefSynType(
            RefSynType refSynType);

    /// Evaluates a Relation clause
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param genRef the Relation clause
    static void __cdecl evaluate_relRef(ResultsTable& rTable, PKB *pkb,
            const GenericRef *genRef);
    /// Evaluates a Relation clause where both arguments are synonyms
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause
    static void __cdecl ev_relRef_syn_syn(ResultsTable& rTable, PKB *pkb,
            const RelRef *relRef);
    /// Sets up the PKB Dispatch Table for a Relation clause with
    /// 1 synonym argument which is not seen
    /// @param pkbDispatch the PKB Dispatch Table to set up
    /// @param relRef the Relation clause to evaluate
    static void __cdecl ev_relRef_syn_syn_0_setup(
            EvalPKBDispatch& pkbDispatch, const RelRef *relRef);
    /// Sets up the PKB Dispatch Table for a Relation clause with
    /// 1 synonym argument which has been seen
    /// @param pkbDispatch the PKB Dispatch Table to set up
    /// @param relRef the Relation clause to evaluate
    static void __cdecl ev_relRef_syn_syn_1_setup(
            EvalPKBDispatch& pkbDispatch, const RelRef *relRef);
    /// Sets up the PKB Dispatch Table for a Relation clause with
    /// 2 synonym arguments which are not seen
    /// @param pkbDispatch the PKB Dispatch Table to set up
    /// @param relRef the Relation clause to evaluate
    static void __cdecl ev_relRef_syn_syn_00_setup(
            EvalPKBDispatch& pkbDispatch, const RelRef *relRef);
    /// Sets up the PKB Dispatch Table for a Relation clause with
    /// 2 synonym arguments, where the 1st argument has not been seen
    /// and the 2nd argument has been seen
    /// @param pkbDispatch the PKB Dispatch Table to set up
    /// @param relRef the Relation clause to evaluate
    static void __cdecl ev_relRef_syn_syn_01_setup(
            EvalPKBDispatch& pkbDispatch, const RelRef *relRef);
    /// Sets up the PKB Dispatch Table for a Relation clause with
    /// 2 synonym arguments where the 1st argument has been seen
    /// and the 2nd argument has not been seen
    /// @param pkbDispatch the PKB Dispatch Table to set up
    /// @param relRef the Relation clause to evaluate
    static void __cdecl ev_relRef_syn_syn_10_setup(
            EvalPKBDispatch& pkbDispatch, const RelRef *relRef);
    /// Sets up the PKB Dispatch Table for a Relation clause with
    /// 2 synonym arguments and the 2 arguments have been seen,
    /// including 11 and 22 case
    /// @param pkbDispatch the PKB Dispatch Table to set up
    /// @param relRef the Relation clause to evaluate
    static void __cdecl ev_relRef_syn_syn_11_22_setup(SynInGraph sig,
            EvalPKBDispatch& pkbDispatch, const RelRef *relRef);

    /// typedef for Relation argument types are (string,string),
    /// retrieves the 1st string synonym based on a concrete 2nd string
    /// synonym
    typedef std::set<std::string> (PKB::*pkbGet_1SS_From_2SS)
                    (DesignEnt, DesignEnt, const std::string&) const;
    /// typedef for Relation argument types are (string,int),
    /// retrieves the 1st string synonym based on a concrete 2nd int
    /// synonym
    typedef std::set<std::string> (PKB::*pkbGet_1SS_From_2IS)
                    (DesignEnt, DesignEnt, int) const;
    /// typedef for Relation argument types are (int,string),
    /// retrieves the 1st int synonym based on a concrete 2nd string
    /// synonym
    typedef std::set<int> (PKB::*pkbGet_1IS_From_2SS)
                    (DesignEnt, DesignEnt, const std::string&) const;
    /// typedef for Relation argument types are (int,int),
    /// retrieves the 1st int synonym based on a concrete 2nd int
    /// synonym
    typedef std::set<int> (PKB::*pkbGet_1IS_From_2IS)
                    (DesignEnt, DesignEnt, int) const;
    /// typedef for Relation argument types are (string,string),
    /// retrieves the 2nd string synonym based on a concrete 1st string
    /// synonym
    typedef std::set<std::string> (PKB::*pkbGet_2SS_From_1SS)
                    (DesignEnt, DesignEnt, const std::string&) const;
    /// typedef for Relation argument types are (int,string),
    /// retrieves the 2nd string synonym based on a concrete 1st int
    /// synonym
    typedef std::set<std::string> (PKB::*pkbGet_2SS_From_1IS)
                    (DesignEnt, DesignEnt, int) const;
    /// typedef for Relation argument types are (string,int),
    /// retrieves the 2nd int synonym based on a concrete 1st string
    /// synonym
    typedef std::set<int> (PKB::*pkbGet_2IS_From_1SS)
                    (DesignEnt, DesignEnt, const std::string&) const;
    /// typedef for Relation argument types are (int,int),
    /// retrieves the 2nd int synonym based on a concrete 1st int
    /// synonym
    typedef std::set<int> (PKB::*pkbGet_2IS_From_1IS)
                    (DesignEnt, DesignEnt, int) const;
    /// Retrieves the appropriate PKB method for retrieving all string
    /// synonyms of a given type
    /// @param ent the synonym design entity type
    /// @return the PKB method for retrieving all string synonyms of
    /// the given type
    static pkbGetAllStringFn __cdecl pkbd_setup_get_all_string_method(
            DesignEnt ent);
    /// Retrieves the appropriate PKB method for retrieving all int
    /// synonyms of a given type
    /// @param ent the synonym design entity type
    /// @return the PKB method for retrieving all int synonyms of the
    ///         given type
    static pkbGetAllIntFn __cdecl pkbd_setup_get_all_int_method
            (DesignEnt ent);
    /// Relation args are (string,string); gets the PKB method used for
    /// retrieving all 1st string synonym based on a concrete 2nd string
    /// synonym, depending on the Relation type
    /// @param r the Relation type
    /// @return the appropriate PKB method retrieving all 1st string
    ///         synonym based on a concrete 2nd string synonym
    static pkbGet_1SS_From_2SS
            __cdecl pkbd_setup_get_1SS_From_2SS(RelRefType r);
    /// This is not used and will cause an assertion failure if called
    static pkbGet_1SS_From_2IS
            __cdecl pkbd_setup_get_1SS_From_2IS(RelRefType r);
    /// Relation args are (int,string); gets the PKB method used for
    /// retrieving all 1st int synonym based on a concrete 2nd string
    /// synonym, depending on the Relation type
    /// @param r the Relation type
    /// @return the appropriate PKB method retrieving all 1st int
    ///         synonym based on a concrete 2nd string synonym
    static pkbGet_1IS_From_2SS
            __cdecl pkbd_setup_get_1IS_From_2SS(RelRefType r);
    /// Relation args are (int,int); gets the PKB method used for
    /// retrieving all 1st int synonym based on a concrete 2nd int
    /// synonym, depending on the Relation type
    /// @param r the Relation type
    /// @return the appropriate PKB method retrieving all 1st int
    ///         synonym based on a concrete 2nd int synonym
    static pkbGet_1IS_From_2IS
            __cdecl pkbd_setup_get_1IS_From_2IS(RelRefType r);
    /// Relation args are (string,string); gets the PKB method used for
    /// retrieving all 2nd string synonym based on a concrete 1st string
    /// synonym, depending on the Relation type
    /// @param r the Relation type
    /// @return the appropriate PKB method retrieving all 2nd string
    ///         synonym based on a concrete 1st string synonym
    static pkbGet_2SS_From_1SS
            __cdecl pkbd_setup_get_2SS_From_1SS(RelRefType r);
    /// Relation args are (int,string); gets the PKB method used for
    /// retrieving all 2nd string synonym based on a concrete 1st int
    /// synonym, depending on the Relation type
    /// @param r the Relation type
    /// @return the appropriate PKB method retrieving all 2nd string
    ///         synonym based on a concrete 1st int synonym
    static pkbGet_2SS_From_1IS
            __cdecl pkbd_setup_get_2SS_From_1IS(RelRefType r);
    /// This is not used and will cause an assertion failure if called
    static pkbGet_2IS_From_1SS
            __cdecl pkbd_setup_get_2IS_From_1SS(RelRefType r);
    /// Relation args are (int,int); gets the PKB method used for
    /// retrieving all 2nd int synonym based on a concrete 1st int
    /// synonym, depending on the Relation type
    /// @param r the Relation type
    /// @return the appropriate PKB method retrieving all 2nd int
    ///         synonym based on a concrete 1st int synonym
    static pkbGet_2IS_From_1IS
            __cdecl pkbd_setup_get_2IS_From_1IS(RelRefType r);

    // How to read these functions
    // eg. ev_rr_ss_string_string_00_from_argOne
    //     ev = evaluate, rr = relRef, ss = syn syn (both args are syn)
    //     string_string = arg 1 is string, arg 2 is string
    //     00 = arg 1 is not in results, arg 2 is not in results
    //     from_argOne = since both arg 1 and arg 2 are not in results,
    //                   we can choose to get either all arg 1 or all arg 2
    //                   from the PKB. In this case, we choose to get all
    //                   all arg 1. Hence from_argOne

    /// Evaluates a (string,string) Relation clause where both arguments
    /// have not been seen and we start from retrieving all 1st synonym
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    /// @param disp the PKB Dispatch Table
    static void __cdecl ev_rr_ss_string_string_00_from_argOne(
            ResultsTable &rTable, PKB *pkb, const RelRef *relRef,
            const EvalPKBDispatch& disp);
    /// Evaluates a (string,string) Relation clause where both arguments
    /// have not been seen and we start from retrieving all 2nd synonym
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    /// @param disp the PKB Dispatch Table
    static void __cdecl ev_rr_ss_string_string_00_from_argTwo(
            ResultsTable &rTable, PKB *pkb, const RelRef *relRef,
            const EvalPKBDispatch& disp);
    /// Evaluates a (string,string) Relation clause where arg 1 has not
    /// been seen and arg 2 has been seen
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    /// @param disp the PKB Dispatch Table
    static void __cdecl ev_rr_ss_string_string_01(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp);
    /// Evaluates a (string,string) Relation clause where arg 1 has been
    /// seen and arg 2 has not been seen
    /// @param rTable the ResultsTable for this relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    /// @param disp the PKB Dispatch Table
    static void __cdecl ev_rr_ss_string_string_10(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp);
    /// Evaluates a (string,string) Relation clause where both arguments
    /// have been seen and are in the same Table
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    /// @param disp the PKB Dispatch Table
    static void __cdecl ev_rr_ss_string_string_11(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp);
    /// Evaluates a (string,string) Relation clause where both arguments
    /// have been seen and but are not in the same Table.
    /// NOTE: This should be deprecated in future patches
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    /// @param disp the PKB Dispatch Table
    static void __cdecl ev_rr_ss_string_string_22(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp);
    /// Not supposed to be used; this fails immediately upon call
    static void __cdecl ev_rr_ss_string_int_00_from_argOne(
            ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
            const EvalPKBDispatch& disp);
    /// Not supposed to be used; this fails immediately upon call
    static void __cdecl ev_rr_ss_string_int_00_from_argTwo(
            ResultsTable &rTable, PKB *pkb, const RelRef *relRef,
            const EvalPKBDispatch& disp);
    /// Not supposed to be used; this fails immediately upon call
    static void __cdecl ev_rr_ss_string_int_01(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp);
    /// Not supposed to be used; this fails immediately upon call
    static void __cdecl ev_rr_ss_string_int_10(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp);
    /// Not supposed to be used; this fails immediately upon call
    static void __cdecl ev_rr_ss_string_int_11(ResultsTable &rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp);
    /// Not supposed to be used; this fails immediately upon call
    static void __cdecl ev_rr_ss_string_int_22(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp);
    /// Evaluates a (int,string) Relation clause where both arguments
    /// have not been seen and we start from retrieving all 1st synonym
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    /// @param disp the PKB Dispatch Table
    static void __cdecl ev_rr_ss_int_string_00_from_argOne(
            ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
            const EvalPKBDispatch& disp);
    /// Evaluates a (int,string) Relation clause where both arguments
    /// have not been seen and we start from retrieving all 2nd synonym
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    /// @param disp the PKB Dispatch Table
    static void __cdecl ev_rr_ss_int_string_00_from_argTwo(
            ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
            const EvalPKBDispatch& disp);
    /// Evaluates a (int,string) Relation clause where the 1st arg has
    /// not been seen and the 2nd arg has been seen
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    /// @param disp the PKB Dispatch Table
    static void __cdecl ev_rr_ss_int_string_01(ResultsTable &rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp);
    /// Evaluates a (int,string) Relation clause where the 1st arg has
    /// been seen and the 2nd arg has not been seen
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    /// @param disp the PKB Dispatch Table
    static void __cdecl ev_rr_ss_int_string_10(ResultsTable &rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp);
    /// Evaluates a (int,string) Relation clause where the both args
    /// have been seen and are in the same Table
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    /// @param disp the PKB Dispatch Table
    static void __cdecl ev_rr_ss_int_string_11(ResultsTable &rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp);
    /// Evaluates a (int,string) Relation clause where the both args
    /// have been seen and but are in different Table.
    /// NOTE: This should be deprecated in future patches
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    /// @param disp the PKB Dispatch Table
    static void __cdecl ev_rr_ss_int_string_22(ResultsTable &rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp);
    /// Evaluates a (int,int) Relation clause where the both args
    /// have not been seen and we start from retrieving all 1st synonym
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    /// @param disp the PKB Dispatch Table
    static void __cdecl ev_rr_ss_int_int_00_from_argOne(
            ResultsTable &rTable, PKB *pkb, const RelRef *relRef,
            const EvalPKBDispatch& disp);
    /// Evaluates a (int,int) Relation clause where the both args
    /// have not been seen and we start from retrieving all 2nd synonym
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    /// @param disp the PKB Dispatch Table
    static void __cdecl ev_rr_ss_int_int_00_from_argTwo(
            ResultsTable &rTable, PKB *pkb, const RelRef *relRef,
            const EvalPKBDispatch& disp);
    /// Evaluates a (int,int) Relation clause where arg 1 has not been
    /// seen and arg 2 has been seen
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    /// @param disp the PKB Dispatch Table
    static void __cdecl ev_rr_ss_int_int_01(ResultsTable &rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp);
    /// Evaluates a (int,int) Relation clause where arg 1 has been
    /// seen and arg 2 has not been seen
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    /// @param disp the PKB Dispatch Table
    static void __cdecl ev_rr_ss_int_int_10(ResultsTable &rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp);
    /// Evaluates a (int,int) Relation clause where both args have been
    /// seen and are in the same Table
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    /// @param disp the PKB Dispatch Table
    static void __cdecl ev_rr_ss_int_int_11(ResultsTable &rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp);
    /// Evaluates a (int,int) Relation clause where both args have been
    /// seen but are in different Table.
    /// NOTE: This should be deprecated by future patches
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    /// @param disp the PKB Dispatch Table
    static void __cdecl ev_rr_ss_int_int_22(ResultsTable &rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp);

    /// Evaluating of Relation where synonym arguments are both of
    /// type int, both synonym arguments are the same and unseen
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef a pointer to the RelRef describing the Relation
    ///               and its parameters
    /// @param disp A dispatch table into PKB and QueryEvaluator methods
    ///             for query evaluation purposes
    static void __cdecl ev_rr_ss_int_int_0(ResultsTable &rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp);
    /// Evaluating of Relation where synonym arguments are both of
    /// type int, both synonym arguments are the same and seen
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef a pointer to the RelRef describing the Relation
    ///               and its parameters
    /// @param disp A dispatch table into PKB and QueryEvaluator methods
    ///             for query evaluation purposes
    static void __cdecl ev_rr_ss_int_int_1(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp);

    /// Evaluate a Relation clause, where the first argument is a
    /// synonym and the second argument is not a synonym
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause
    static void __cdecl ev_relRef_syn_X(ResultsTable& rTable, PKB *pkb,
            const RelRef *relRef);
    /// Evaluates Next(X,syn) and Next*(X,syn), where syn has not
    /// been seen.
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    static void __cdecl ev_relRef_syn_X_0_nextAndStar(
            ResultsTable& rTable, PKB *pkb, const RelRef *relRef);
    /// Evaluates Next(X,syn) and Next*(X,syn), where syn has not been
    /// seen.
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    static void __cdecl ev_relRef_syn_X_1_nextAndStar(
            ResultsTable& rTable, PKB *pkb, const RelRef *relRef);
    /// Evaluates a Relation clause where args are (string,string),
    /// the first synonym has not been seen and the second arg
    /// is a concrete string
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    /// @param disp the PKB Dispatch Table
    /// @param xType the synonym type of 2nd argument (a concrete
    ///              string value)
    /// @param xVal the concrete string value for the 2nd argument
    static void __cdecl ev_rr_syn_X_string_string_0(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp,
            DesignEnt xType, const std::string& xVal);
    /// Evaluates a Relation clause where args are (string,_),
    /// the first synonym has not been seen and the second argument
    /// is an underscore
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    /// @param disp the PKB Dispatch Table
    static void __cdecl ev_rr_syn_X_string_wild_0(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp);
    /// Evaluates a Relation clause where args are (int,string),
    /// the first synonym has not been seen and the second argument
    /// is a concrete string
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    /// @param disp the PKB Dispatch Table
    /// @param xType the synonym type of the 2nd argument (a concrete
    ///              string value)
    /// @param xVal the concrete string value for the 2nd argument
    static void __cdecl ev_rr_syn_X_int_string_0(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp,
            DesignEnt xType, const std::string& xVal);
    /// Evaluates a Relation clause where args are (int,int),
    /// the first synonym has not been seen and the second argument
    /// is a concrete int
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    /// @param disp the PKB Dispatch Table
    /// @param xType the synonym type of the 2nd argument (a concrete
    ///              integer value)
    /// @param xVal the concrete integer value for the 2nd argument
    static void __cdecl ev_rr_syn_X_int_int_0(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp,
            DesignEnt xType, int xVal);
    /// Evaluates a Relation clause where args are (int,_),
    /// the first synonym has not been seen and the second argument
    /// is an underscore
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    /// @param disp the PKB Dispatch Table
    static void __cdecl ev_rr_syn_X_int_wild_0(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp);
    /// Evaluates a Relation clause where args are (string,string),
    /// the first synonym has been seen and the second argument
    /// is a concrete string
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    /// @param disp the PKB Dispatch Table
    /// @param xType the synonym type of the second argument (a concrete
    ///              string value)
    /// @param xVal the concrete string value for the second argument
    static void __cdecl ev_rr_syn_X_string_string_1(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp,
            DesignEnt xType, const std::string& xVal);
    /// Evaluates a Relation clause where args are (string,_),
    /// the first synonym has been seen and the second argument
    /// is an underscore
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    /// @param disp the PKB Dispatch Table
    static void __cdecl ev_rr_syn_X_string_wild_1(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp);
    /// Evaluates a Relation clause where args are (int,string),
    /// the first synonym hasbeen seen and the second argument
    /// is a concrete string
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    /// @param disp the PKB Dispatch Table
    /// @param xType the synonym type of the 2nd argument (a concrete
    ///              string value)
    /// @param xVal the concrete string value for the 2nd argument
    static void __cdecl ev_rr_syn_X_int_string_1(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp,
            DesignEnt xType, const std::string& xVal);
    /// Evaluates a Relation clause where args are (int,int),
    /// the first synonym has been seen and the second argument
    /// is a concrete integer
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    /// @param disp the PKB Dispatch Table
    /// @param xType the synonym type of the 2nd argument (a concrete
    ///              integer value)
    /// @param xVal the concrete integer value for the 2nd argument
    static void __cdecl ev_rr_syn_X_int_int_1(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp,
            DesignEnt xType, int xVal);
    /// Evaluates a Relation clause where args are (int,_),
    /// the first synonym has been seen and the second argument
    /// is an undersscore
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    /// @param disp the PKB Dispatch Table
    static void __cdecl ev_rr_syn_X_int_wild_1(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp);

    /// Evaluates a Relation clause where the first argument is not
    /// a synonym and the second argument is a synonym
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef the Relation clause to evaluate
    static void __cdecl ev_relRef_X_syn(ResultsTable& rTable, PKB *pkb,
            const RelRef *relRef);
    /// Evaluates Modifies(X,syn) where syn has not been seen.
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    static void __cdecl ev_relRef_X_syn_0_modifies(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef);
    /// Evaluates Modifies(X,syn) where syn has been seen.
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    static void __cdecl ev_relRef_X_syn_1_modifies(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef);
    /// Evaluates Uses(X,syn) where syn has not been seen.
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    static void __cdecl ev_relRef_X_syn_0_uses(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef);
    /// Evaluates Uses(X,syn) where syn has been seen.
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    static void __cdecl ev_relRef_X_syn_1_uses(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef);
    /// Evaluates Calls(X,syn) where syn has not been seen
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    static void __cdecl ev_relRef_X_syn_0_calls(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef);
    /// Evaluates Calls(X,syn) where syn has been seen.
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    static void __cdecl ev_relRef_X_syn_1_calls(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef);
    /// Evaluates Calls*(X,syn) where syn has not been seen
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    static void __cdecl ev_relRef_X_syn_0_callsStar(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef);
    /// Evaluates Calls*(X,syn) where syn has been seen.
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    static void __cdecl ev_relRef_X_syn_1_callsStar(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef);
    /// Evaluates Parent(X,syn) where syn has not been seen.
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    static void __cdecl ev_relRef_X_syn_0_parent(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef);
    /// Evaluates Parent(X,syn) where syn has been seen.
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    static void __cdecl ev_relRef_X_syn_1_parent(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef);
    /// Evaluates Parent*(X,syn) where syn has not been seen.
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    static void __cdecl ev_relRef_X_syn_0_parentStar(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef);
    /// Evaluates Parent*(X,syn) where syn has been seen.
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    static void __cdecl ev_relRef_X_syn_1_parentStar(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef);
    /// Evaluates Follows(X,syn) and Follows*(X,syn) where syn
    /// has not been seen.
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    static void __cdecl ev_relRef_X_syn_0_followsAndStar(
            ResultsTable& rTable, PKB *pkb, const RelRef *relRef);
    /// Evaluates Follows(X,syn) and Follows*(X,syn) where syn
    /// has been seen.
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    static void __cdecl ev_relRef_X_syn_1_followsAndStar(
            ResultsTable& rTable, PKB *pkb, const RelRef *relRef);
    /// Evaluates Next(X,syn) and Next*(X,syn) where syn
    /// has not been seen.
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    static void __cdecl ev_relRef_X_syn_0_nextAndStar(
            ResultsTable& rTable, PKB *pkb, const RelRef *relRef);
    /// Evaluates Next(X,syn) and Next*(X,syn) where syn
    /// has been seen.
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    static void __cdecl ev_relRef_X_syn_1_nextAndStar(
            ResultsTable& rTable, PKB *pkb, const RelRef *relRef);
    /// Evaluates Affects(X,syn) and Affects*(X,syn) where syn
    /// has not been seen.
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    static void __cdecl ev_relRef_X_syn_0_affectsAndStar(
            ResultsTable& rTable, PKB *pkb, const RelRef *relRef);
    /// Evaluates Affects(X,syn) and Affects*(X,syn) where syn
    /// has been seen.
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    static void __cdecl ev_relRef_X_syn_1_affectsAndStar(
            ResultsTable& rTable, PKB *pkb, const RelRef *relRef);
    /// Evaluates Rel(X,syn), where both arguments are strings and syn
    /// has not been seen.
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    /// @param disp PKB dispatch table
    /// @param xType design entity type of X
    /// @param xVal value of X
    static void __cdecl ev_relRef_X_syn_string_string_0(
            ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
            const EvalPKBDispatch& disp, DesignEnt xType, const string& xVal);
    /// Evaluates Rel(X,syn), where both arguments are strings and syn
    /// has been seen.
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    /// @param disp PKB dispatch table
    /// @param xType design entity type of X
    /// @param xVal value of X
    static void __cdecl ev_relRef_X_syn_string_string_1(
            ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
            const EvalPKBDispatch& disp, DesignEnt xType,
            const string& xVal);
    /// Evaluates Rel(X,syn), where arguments are (int,string) and syn
    /// has not been seen.
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    /// @param disp PKB dispatch table
    /// @param xType design entity type of X
    /// @param xVal value of X
    static void __cdecl ev_relRef_X_syn_int_string_0(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp,
            DesignEnt xType, int xVal);
    /// Evaluates Rel(X,syn), where arguments are (int,string) and syn
    /// has been seen.
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    /// @param disp PKB dispatch table
    /// @param xType design entity type of X
    /// @param xVal value of X
    static void __cdecl ev_relRef_X_syn_int_string_1(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp,
            DesignEnt xType, int xVal);
    /// Evaluates Rel(X,syn), where arguments are (_,string) and syn
    /// has not been seen.
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    /// @param disp PKB dispatch table
    static void __cdecl ev_relRef_X_syn_wild_string_0(
            ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
            const EvalPKBDispatch& disp);
    /// Evaluates Rel(X,syn), where arguments are (_,string) and syn
    /// has been seen.
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    /// @param disp PKB dispatch table
    static void __cdecl ev_relRef_X_syn_wild_string_1(
            ResultsTable& rTable, PKB *pkb, const RelRef *relRef,
            const EvalPKBDispatch& disp);
    /// Evaluates Rel(X,syn), where arguments are (int,int) and syn
    /// has not been seen.
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    /// @param disp PKB dispatch table
    static void __cdecl ev_relRef_X_syn_int_int_0(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp,
            DesignEnt xType, int xVal);
    /// Evaluates Rel(X,syn), where arguments are (int,int) and syn
    /// has been seen.
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    /// @param disp PKB dispatch table
    static void __cdecl ev_relRef_X_syn_int_int_1(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp,
            DesignEnt xType, int xVal);
    /// Evaluates Rel(X,syn), where arguments are (_,int) and syn
    /// has not been seen.
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    /// @param disp PKB dispatch table
    static void __cdecl ev_relRef_X_syn_wild_int_0(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp);
    /// Evaluates Rel(X,syn), where arguments are (_,int) and syn
    /// has been seen.
    /// @param rTable the ResultsTable for this Relation
    /// @param pkb PKB
    /// @param relRef info on this Relation clause
    /// @param disp PKB dispatch table
    static void __cdecl ev_relRef_X_syn_wild_int_1(ResultsTable& rTable,
            PKB *pkb, const RelRef *relRef, const EvalPKBDispatch& disp);
private:
    /// Private copy constructor to prevent copying
    QueryEvaluator(const QueryEvaluator& o);
    /// Private copy assign operator to prevent assignment
    QueryEvaluator& operator=(const QueryEvaluator& o);
    /// Resets the QueryEvaluator so it is ready for evaluating another
    /// PQL query
    void reset_for_pql_query();
    void read_config_from_map(
            const std::map<std::string, std::string>& settings);
    /// Reads configuration settings from the given file
    /// @param configFile name of the configuration file
    void read_config(const std::string& configFile);
    /// Partitions the clauses into connected components by building an
    /// undirected graph, with synonyms as vertices. Each vertex v has
    /// an edge with vertex w if and only if v and w are distinct and
    /// v and w are seen in the same clause
    void partition_evaluation(const QueryInfo *qinfo);
    /// Adds vertices/edges based on synonym(s) in a Relation clause
    /// @param idx the index of the Relation clause
    /// @param genRef the Relation Clause
    void partition_process_relRef(int idx, const GenericRef *genRef);
    /// Adds vertices/edges based on synonym(s) in a WithClause
    /// @param idx the index of the WithClause
    /// @param genRef the WithClause
    void partition_process_withClause(int idx, const GenericRef *genRef);
   /// Adds vertices/edges based on synonym(s) in a Pattern clause
    /// @param idx the index of the Pattern clause
    /// @param genRef the Pattern clause
    void partition_process_patCl(int idx, const GenericRef *genRef);
    /// Adds a vertex to the component graph during the partitioning
    /// process
    /// @param idx index of the clause
    /// @param syn the synonym being added as a vertex
    int partition_add_vertex(int idx, const std::string& syn);
    /// Adds an edge between 2 distinct synonyms v and w
    /// @param idx the index of the clause
    /// @param synOne the first synonym argument to the clause
    /// @param synTwo the second synonym argument to the clause
    void partition_add_edge(int idx, const std::string& synOne,
            const std::string& synTwo);
    /// Computes the connected components in the graph built by the
    /// partitioning process
    void partition_evaluation_cc();
    /// Used by partition_evaluation_cc for computing connected
    /// components. We make use of a breadth first search algorithm
    /// @param v vertex to start the breadth first search from
    void partition_evaluation_cc_bfs(int v);
    /// Creates the ResultsTable objects based on the connected
    /// components computed in the query partitioning process
    void partition_evaluation_partition(int nrClauses);

    /// Evaluates queries component wise in parallel
    void evaluate_parallel(const QueryInfo *qinfo);

    /// Evaluates an isolated clause and returns the evaluation
    /// result (either true / false)
    /// @param qinfo the QueryInfo data structure for this PQL query
    /// @param clauseIdx the index of the clause inside the
    /// @return true if the isolated clause evaluates to true,
    ///         false otherwise
    bool ev_isolated_clause(const QueryInfo *qinfo, int clauseIdx) const;
    /// Evaluates an isolated Relation clause and returns the
    /// evaluation result
    /// @param genRef the Relation clause
    /// @return true if the Relation clause evaluates to true, false
    ///         otherwise
    bool ev_isolated_relation_clause(const GenericRef *genRef) const;
    /// Evaluates an isolated Relation clause with (string,string) args
    /// @param relRef the Relation clause
    /// @return true if the Relation clause evaluates to true, false
    ///         otherwise
    bool ev_isolated_relation_string_string(const RelRef *relRef) const;
    /// Evaluates an isolated Relation clause with (string,int) args
    /// @param relRef the Relation clause
    /// @return true if the Relation clause evaluates to true, false
    ///         otherwise
    bool ev_isolated_relation_string_int(const RelRef *relRef) const;
    /// Evaluates an isolated Relation clause with (string,_) args
    /// @param relRef the Relation clause
    /// @return true if the Relation clause evaluates to true, false
    ///         otherwise
    bool ev_isolated_relation_string_wild(const RelRef *relRef) const;
    /// Evaluates an isolated Relation clause with (int,string) args
    /// @param relRef the Relation clause
    /// @return true if the Relation clause evaluates to true, false
    ///         otherwise
    bool ev_isolated_relation_int_string(const RelRef *relRef) const;
    /// Evaluates an isolated Relation clause with (int,int) args
    /// @param relRef the Relation clause
    /// @return true if the Relation clause evaluates to true, false
    ///         otherwise
    bool ev_isolated_relation_int_int(const RelRef *relRef) const;
    /// Evaluates an isolated Relation clause with (int,_) args
    /// @param relRef the Relation clause
    /// @return true if the Relation clause evaluates to true, false
    ///         otherwise
    bool ev_isolated_relation_int_wild(const RelRef *relRef) const;
    /// Evaluates an isolated Relation clause with (_,string) args
    /// @param relRef the Relation clause
    /// @return true if the Relation clause evaluates to true, false
    ///         otherwise
    bool ev_isolated_relation_wild_string(const RelRef *relRef) const;
    /// Evaluates an isolated Relation clause with (_,int) args
    /// @param relRef the Relation clause
    /// @return true if the Relation clause evaluates to true, false
    ///         otherwise
    bool ev_isolated_relation_wild_int(const RelRef *relRef) const;
    /// Evaluates an isolated Relation clause with (_,_) args
    /// @param relRef the Relation clause
    /// @return true if the Relation clause evaluates to true, false
    ///         otherwise
    bool ev_isolated_relation_wild_wild(const RelRef *relRef) const;

    /// Evaluates a WithClause
    /// @param rTableIdx ResultsTable index
    /// @param genRef the GenericRef representing the WithClause
    void evaluate_withClause(int rTableIdx, const GenericRef *genRef);
    /// Evaluates a WithClause where both arguments are AttrRef
    /// @param rTableIdx ResultsTable index
    /// @param withClause the WithClause to evaluate
    void ev_withClause_attrRef_attrRef(int rTableIdx,
            const WithClause& withClause);
    /// Setup the pkbDispatch for WithClause where both arguments
    /// are AttrRef int and not seen
    /// @param rTableIdx ResultsTable index
    /// @param withClause information on the WithClause
    /// @param pkbDispatch the PKB Dispatch Table to fill up
    void ev_withClause_attrRef_attrRef_ii_00_setup(int rTableIdx,
            const WithClause& withClause, EvalPKBDispatch& pkbDispatch)
                const;
    /// Setup the pkbDispatch for WithClause where both arguments
    /// are AttrRef int and arg 2 has been seen
    /// @param rTableIdx ResultsTable index
    /// @param withClause information on the WithClause
    /// @param pkbDispatch the PKB Dispatch Table to fill up
    void ev_withClause_attrRef_attrRef_ii_01_setup(int rTableIdx,
            const WithClause& withClause, EvalPKBDispatch& pkbDispatch)
                const;
    /// Setup the pkbDispatch for WithClause where both arguments
    /// are AttrRef int and arg 1 has been seen
    /// @param rTableIdx ResultsTable index
    /// @param withClause information on the WithClause
    /// @param pkbDispatch the PKB Dispatch Table to fill up
    void ev_withClause_attrRef_attrRef_ii_10_setup(int rTableIdx,
            const WithClause& withClause, EvalPKBDispatch& pkbDispatch)
                const;
    /// Setup the pkbDispatch for WithClause where both arguments
    /// are AttrRef string and not seen
    /// @param rTableIdx ResultsTable index
    /// @param withClause information on the WithClause
    /// @param pkbDispatch the PKB Dispatch Table to fill up
    void ev_withClause_attrRef_attrRef_ss_00_setup(int rTableIdx,
            const WithClause& withClause, EvalPKBDispatch& pkbDispatch)
                const;
    /// Setup the pkbDispatch for WithClause where both arguments
    /// are AttrRef string and arg 2 has been seen
    /// @param rTableIdx ResultsTable index
    /// @param withClause information on the WithClause
    /// @param pkbDispatch the PKB Dispatch Table to fill up
    void ev_withClause_attrRef_attrRef_ss_01_setup(int rTableIdx,
            const WithClause& withClause, EvalPKBDispatch& pkbDispatch)
                const;
    /// Setup the pkbDispatch for WithClause where both arguments
    /// are AttrRef string and arg 1 has been seen
    /// @param rTableIdx ResultsTable index
    /// @param withClause information on the WithClause
    /// @param pkbDispatch the PKB Dispatch Table to fill up
    void ev_withClause_attrRef_attrRef_ss_10_setup(int rTableIdx,
            const WithClause& withClause, EvalPKBDispatch& pkbDispatch)
                const;
    /// Evaluates a WithClause where both arguments are AttrRef of
    /// type int and none of them have been seen
    /// @param rTableIdx ResultsTable index
    /// @param withClause the WithClause to evaluate
    /// @param disp the PKB Dispatch Table
    void ev_withClause_ii_00(int rTableIdx,
            const WithClause& withClause, const EvalPKBDispatch& disp);
    /// Evaluates a WithClause where both arguments are AttrRef of
    /// type int and arg 2 has  been seen
    /// @param rTableIdx ResultsTable index
    /// @param withClause the WithClause to evaluate
    /// @param disp the PKB Dispatch Table
    void ev_withClause_ii_01(int rTableIdx,
            const WithClause& withClause, const EvalPKBDispatch& disp);
    /// Evaluates a WithClause where both arguments are AttrRef of
    /// type int and arg 1 has been seen
    /// @param rTableIdx ResultsTable index
    /// @param withClause the WithClause to evaluate
    /// @param disp the PKB Dispatch Table
    void ev_withClause_ii_10(int rTableIdx,
            const WithClause& withClause, const EvalPKBDispatch& disp);
    /// Evaluates a WithClause where both arguments are AttrRef of
    /// type int and have been seen in same Table
    /// @param rTableIdx ResultsTable index
    /// @param withClause the WithClause to evaluate
    void ev_withClause_ii_11(int rTableIdx,
            const WithClause& withClause);
    /// Evaluates a WithClause where both arguments are AttrRef of
    /// type int and have been seen, but in same Table
    /// @param rTableIdx ResultsTable index
    /// @param withClause the WithClause to evaluate
    void ev_withClause_ii_22(int rTableIdx,
            const WithClause& withClause);
    /// Evaluates a WithClause where both arguments are AttrRef of
    /// type string and none of them have been seen
    /// @param rTableIdx ResultsTable index
    /// @param withClause the WithClause to evaluate
    /// @param disp the PKB Dispatch Table
    void ev_withClause_ss_00(int rTableIdx,
            const WithClause& withClause, const EvalPKBDispatch& disp);
    /// Evaluates a WithClause where both arguments are call.procName
    /// and have not been seen
    /// @param rTableIdx ResultsTable index
    /// @param withClause the WithClause to evaluate
    void ev_withClause_ss_cpn_cpn_00(int rTableIdx,
            const WithClause& withClause);
    /// Evaluates a WithClause where arg 1 is call.procName,
    /// arg 2 is a string RefSynType (other than call.procName)
    /// and both args have not been seen
    /// @param rTableIdx ResultsTable index
    /// @param withClause the WithClause to evaluate
    /// @param disp PKB Dispatch Table
    void ev_withClause_ss_cpn_X_00(int rTableIdx,
            const WithClause& withClause,
            const EvalPKBDispatch& disp);
    /// Evaluates a WithClause where both arguments are AttrRef of
    /// type string and arg 2 has been seen
    /// @param rTableIdx ResultsTable index
    /// @param withClause the WithClause to evaluate
    /// @param disp the PKB Dispatch Table
    void ev_withClause_ss_01(int rTableIdx,
            const WithClause& withClause, const EvalPKBDispatch& disp);
    /// Evaluates a WithClause where both arguments are call.procName
    /// and arg 2 has been seen
    /// @param rTableIdx ResultsTable index
    /// @param withClause the WithClause to evaluate
    void ev_withClause_ss_cpn_cpn_01(int rTableIdx,
            const WithClause& withClause);
    /// Evaluates a WithClause where arg 1 is call.procName,
    /// arg 2 is a string RefSynType (not call.procName) and
    /// arg 2 has been seen
    /// @param rTableIdx ResultsTable index
    /// @param withClause the WithClause to evaluate
    void ev_withClause_ss_cpn_X_01(int rTableIdx,
            const WithClause& withClause);
    /// Evaluates a WithClause where arg 1 is a string RefSynType
    /// (not call.procName), arg 2 is call.procName, and arg 2
    /// has been seen
    /// @param rTableIdx ResultsTable index
    /// @param withClause the WithClause to evaluate
    /// @param disp PKB Dispatch Table
    void ev_withClause_ss_cpn_X_10(int rTableIdx,
            const WithClause& withClause,
            const EvalPKBDispatch& disp);
    /// Evaluates a WithClause where both arguments are AttrRef of
    /// type string and arg 1 has been seen
    /// @param rTableIdx ResultsTable index
    /// @param withClause the WithClause to evaluate
    void ev_withClause_ss_11(int rTableIdx,
            const WithClause& withClause);
    /// Evaluates a WithClause where both args are call.procName
    /// and have been seen in the same Table
    /// @param rTableIdx ResultsTable index
    /// @param withClause the WithClause to evaluate
    void ev_withClause_ss_cpn_cpn_11(int rTableIdx,
            const WithClause& withClause);
    /// Evaluates a WithClause where arg 1 is call.procName,
    /// arg 2 is a string RefSynType (not call.procName) and both args
    /// have been seen in the same Table
    /// @param rTableIdx ResultsTable index
    /// @param withClause the WithClause to evaluate
    void ev_withClause_ss_cpn_X_11(int rTableIdx,
            const WithClause& withClause);
    /// Evaluates a WithClause where both arguments are AttrRef of
    /// type string and have been seen, but in same Table
    /// @param rTableIdx ResultsTable index
    /// @param withClause the WithClause to evaluate
    void ev_withClause_ss_22(int rTableIdx,
            const WithClause& withClause);
    /// Evaluates a WithClause where both args are call.procName
    /// and have been seen but in different Table
    /// @param rTableIdx ResultsTable index
    /// @param withClause the WithClause to evaluate
    void ev_withClause_ss_cpn_cpn_22(int rTableIdx,
            const WithClause& withClause);
    /// Evaluates a WithClause where arg 1 is call.procName,
    /// arg 2 is a string RefSynType (not call.procName) and both args
    /// have been seen but in different Table
    /// @param rTableIdx ResultsTable index
    /// @param withClause the WithClause to evaluate
    void ev_withClause_ss_cpn_X_22(int rTableIdx,
            const WithClause& withClause);
    /// Evaluates a WithClause where the LHS is an AttrRef and
    /// the RHS is a concrete value
    /// @param rTableIdx ResultsTable index
    /// @param withClause the WithClause to evaluate
    void ev_withClause_attrRef_X(int rTableIdx,
            const WithClause& withClause);
    /// Evaluates a WithClause where both arguments are of BASETYPE_INT,
    /// the LHS is an AttrRef and the RHS is a concrete integer value
    /// @param rTableIdx ResultsTable index
    /// @param withClause the WithClause to evaluate
    void ev_withClause_attrRef_X_int(int rTableIdx,
            const WithClause& withClause);
    /// Evaluates a WithClause where both arguments are of
    /// BASETYPE_STRING, the LHS is an AttrRef and the RHS is a
    /// concrete string value
    /// @param rTableIdx ResultsTable index
    /// @param withClause the WithClause to evaluate
    void ev_withClause_attrRef_X_string(int rTableIdx,
            const WithClause& withClause);
    /// Evaluates a WithClause where both arguments are of BASETYPE_INT,
    /// the LHS is an unseen AttrRef and RHS is a concrete integer value
    /// @param rTableIdx ResultsTable index
    /// @param withClause the WithClause to evaluate
    /// @param disp PKB Dispatch Table
    void ev_withClause_i_0(int rTableIdx, const WithClause& withClause,
            const EvalPKBDispatch& disp);
    /// Evaluates a WithClause where both arguments are of BASETYPE_INT,
    /// the LHS is a seen AttrRef and RHS is a concrete integer value
    /// @param rTableIdx ResultsTable index
    /// @param withClause the WithClause to evaluate
    /// @param disp PKB Dispatch Table
    void ev_withClause_i_1(int rTableIdx, const WithClause& withClause);
    /// Evaluates a WithClause where both arguments are of
    /// BASETYPE_STRING, the LHS is an unseen string AttrRef
    /// (not call.procName) and RHS is a concrete string value
    /// @param rTableIdx ResultsTable index
    /// @param withClause the WithClause to evaluate
    /// @param disp PKB Dispatch Table
    void ev_withClause_s_0(int rTableIdx, const WithClause& withClause,
            const EvalPKBDispatch& disp);
    /// Evaluates a WithClause where both arguments are of
    /// BASETYPE_STRING, the LHS is an unseen call.procName and RHS is
    /// a concrete string value
    /// @param rTableIdx ResultsTable index
    /// @param withClause the WithClause to evaluate
    void ev_withClause_cpn_0(int rTableIdx, const WithClause& withClause);
    /// Evaluates a WithClause where both arguments are of
    /// BASETYPE_STRING, the LHS is a seen string AttrRef
    /// (not call.procName) and RHS is a concrete string value
    /// @param rTableIdx ResultsTable index
    /// @param withClause the WithClause to evaluate
    void ev_withClause_s_1(int rTableIdx, const WithClause& withClause);
    /// Evaluates a WithClause where both arguments are of
    /// BASETYPE_STRING, the LHS is a seen call.procName and RHS is
    /// a concrete string value
    /// @param rTableIdx ResultsTable index
    /// @param withClause the WithClause to evaluate
    void ev_withClause_cpn_1(int rTableIdx, const WithClause& withClause);

    void evaluate_patCl(int rTableIdx, const GenericRef *genRef);
    void evaluate_patCl_if(int rTableIdx, const PatCl *patCl);
    void evaluate_patCl_if_var_syn(int rTableIdx, const PatCl *patCl);

    void evaluate_patCl_assign(int rTableIdx, const PatCl *patCl);
    void evaluate_patCl_assign_string_expr(int rTableIdx,
            const PatCl *patCl);
    void evaluate_patCl_assign_string_exprwild(int rTableIdx,
            const PatCl *patCl);
    void evaluate_patCl_assign_string_wildcard(int rTableIdx,
            const PatCl *patCl);
    void evaluate_patCl_assign_syn_expr(int rTableIdx,
            const PatCl *patCl);
    void evaluate_patCl_assign_syn_expr_11(ResultsTable& rTable,
            const PatCl* patCl);
    void evaluate_patCl_assign_syn_expr_22(ResultsTable& rTable,
            const PatCl* patCl);
    void evaluate_patCl_assign_syn_exprwild(int rTableIdx,
            const PatCl *patCl);
    void evaluate_patCl_assign_syn_exprwild_11(ResultsTable& rTable,
            const PatCl* patCl);
    void evaluate_patCl_assign_syn_exprwild_22(ResultsTable& rTable,
            const PatCl* patCl);
    void evaluate_patCl_assign_syn_wildcard(int rTableIdx,
            const PatCl *patCl);
    void evaluate_patCl_assign_syn_wildcard_11(ResultsTable& rTable,
            const PatCl *patCl);
    void evaluate_patCl_assign_syn_wildcard_22(ResultsTable& rTable,
            const PatCl *patCl);
    void evaluate_patCl_assign_wildcard_expr(int rTableIdx,
            const PatCl *patCl);
    void evaluate_patCl_assign_wildcard_exprwild(int rTableIdx,
            const PatCl *patCl);
    void evaluate_patCl_assign_wildcard_wildcard(int rTableIdx,
            const PatCl *patCl);

    void evaluate_patCl_if_var_syn_11(ResultsTable& rTable,
            const PatCl *patCl);
    void evaluate_patCl_if_var_syn_22(ResultsTable& rTable,
            const PatCl *patCl);
    void evaluate_patCl_if_var_string(int rTableIdx,
            const PatCl *patCl);
    void evaluate_patCl_if_var_wildcard(int rTableIdx,
            const PatCl *patCl);
    
    void evaluate_patCl_while(int rTableIdx, const PatCl *patCl);
    void evaluate_patCl_while_var_syn(int rTableIdx, const PatCl *patCl);
    void evaluate_patCl_while_var_syn_11(ResultsTable& rTable,
            const PatCl *patCl);
    void evaluate_patCl_while_var_syn_22(ResultsTable& rTable,
            const PatCl *patCl);
    void evaluate_patCl_while_var_string(int rTableIdx,
            const PatCl *patCl);
    void evaluate_patCl_while_var_wildcard(int rTableIdx,
            const PatCl *patCl);

    bool evaluate_matching_tree(Node*, Node*);
    bool is_operation(const string& operation);

    /// Internal PQLParser used to parse PQL queries
    PQLParser pqlParser;
    /// Internal PKB used for obtaining knowledge about the input
    /// SIMPLE Program
    PKB *pkb;
    /// Internal ResultsProjector used to compute the final results
    ResultsProjector resultsProjector;
    std::map<EvalSynArgDesc, EvalPKBDispatch,
             EvalSynArgDescCmp> dispatchTable;
    /// Indicates whether the query evaluator is alive
    bool isAlive;
    /// If true, the query evaluator will evaluate components
    /// in parallel by forking an appropriate number of threads
    bool optMultithreaded_;
    /// Specifies the maximum number of threads to spawn if
    /// multithreading is enabled (defaults to QE_DEFAULT_NR_THREADS)
    int maxThreads_;

    // graph construction purposes

    /// maps a synonym to a vertex id
    std::map<std::string, int> graph_synMap;
    /// Adjacency List of the graph
    std::vector<std::set<int> > graph_adjList;
    /// maps clause idx to a vertex involved in it. This allows us to
    /// identify a clause with a vertex
    std::vector<int> graph_refToVertex;
    /// Gives the index of the connected component a vertex belongs to
    std::vector<int> graph_vertexCC;
    /// number of connected components in the graph
    int graph_nrVertexCC;
    /// contains clause indices of isolated clauses, ie. clauses without
    /// any synonym arguments
    std::set<int> graph_isolatedClauses;
    /// Clauses for each component.
    /// index = the component index
    /// Each element in the outer vector is a vector of cluase indices
    /// for that component
    std::vector<std::vector<int> > partitionedClauses;
    /// vector of ResultsTable, one for each component
    std::vector<ResultsTable> resultsTable;

    #define EV_SAME_SYN_RELATION_ARR_SZ 4
    /// Contains all the possible Relation types where we can have
    /// the exact same synonym argument as both the arguments
    static const RelRefType EV_SAME_SYN_RELATION_ARR[
                         EV_SAME_SYN_RELATION_ARR_SZ];
    /// The set of all possible Relation types where we can have the
    /// exact same synonym argument as both the arguments
    static const std::set<RelRefType> EV_SAME_SYN_RELATION;
};

/// Entry function for a single thread to evaluate queries
/// @param qetInfo cast this to struct QEThreadInfo *
/// @return NULL
void * __cdecl thread_evaluate(void *qetinfo);

#endif