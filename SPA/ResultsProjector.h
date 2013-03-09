#ifndef T11_RESULTS_PROJECTOR_H
#define T11_RESULTS_PROJECTOR_H

#include <vector>
#include <list>
#include <string>
#include <map>
#include <set>
#include "PKB.h"
#include "PQL.h"
#include "ResultsTable.h"

class ResultsProjector {
public:
    ResultsProjector();
    void get_results(ResultsTable& resultsTable, QueryInfo *qinfo,
            PKB *pkb, std::list<std::string>& results);

    static const std::string TRUE_STR;
    static const std::string FALSE_STR;
private:
    void reset();
    void recursive_generate(int n, QueryInfo *qinfo, PKB *pkb);
    void create_table_from_syn_set(ResultsTable& resultsTable,
            const AttrRef& attrRef, PKB *pkb);
    /// Creates a Table from a set&gt;int&lt; and absorbs it into
    /// a given ResultsTable
    /// @param resultsTable the ResultsTable which should absorb the
    ///                     Table
    /// @param attrRef data structure of the synonym we are creating
    ///                the Table. This synonym should not exist in
    ///                the ResultsTable, ie.
    ///                ResultsTable.has_synonym(attrRef.syn) == false,
    ///                otherwise this will cause an assertion failure
    /// @param pkb PKB to retrieve the set of synonyms from
    /// @param pkbRetrievalFn PKB method to retrieve the set of
    ///                       integer synonyms
    /// @return true if the ResultsTable is alive after the absorption,
    ///         false otherwise. The ResultsTable will be dead if the
    ///         set of synonyms retrieved is empty (eg. trying to
    ///         retrieve call statements in a program without any
    ///         call statements)
    bool create_table_from_int_syn_set(ResultsTable& resultsTable,
            const AttrRef &attrRef, PKB *pkb,
            std::set<int> (PKB::*pkbRetrievalFn)() const);
    /// Creates a Table from a set&gt;string&lt; and absorbs it into
    /// a given ResultsTable
    /// @param resultsTable the ResultsTable which should absorb the
    ///                     Table
    /// @param attrRef data structure of the synonym we are creating
    ///                the Table. This synonym should not exist in
    ///                the ResultsTable, ie.
    ///                ResultsTable.has_synonym(attrRef.syn) == false,
    ///                otherwise this will cause an assertion failure
    /// @param pkb PKB to retrieve the set of synonyms from
    /// @param pkbRetrievalFn PKB method to retrieve the set of
    ///                       string synonyms
    /// @return true if the ResultsTable is alive after the absorption,
    ///         false otherwise. The ResultsTable will be dead if the
    ///         set of synonyms retrieved is empty (eg. trying to
    ///         retrieve call statements in a program without any
    ///         call statements)
    bool create_table_from_string_syn_set(ResultsTable& resultsTable,
            const AttrRef &attrRef, PKB *pkb,
            std::set<std::string> (PKB::*pkbRetrievalFn)() const);

    int nrSelect;
    StringBuffer sb;
    std::vector<Table *> tablesUsed;
    std::map<Table *, int> tablesUsedMap;
    std::map<int, std::string> columnToSyn;
    std::map<std::string, int> synToColumn;
    int columnCount;
    std::vector<std::pair<int, int> > tableColToChoose;
    std::vector<int> recGenRowChosen;
    std::set<std::string> sortedResults;

    std::map<std::string, std::string> synValues;
    std::map<std::string, int> synToSetIndex;
    std::vector<std::set<std::pair<int, std::string> > > synValuesSet;
    std::vector<int> synIndices;
    std::vector<bool> synRepeated;
};

#endif