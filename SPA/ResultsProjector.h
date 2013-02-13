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
private:
    void reset();
    void recursive_generate(int n, QueryInfo *qinfo, PKB *pkb);
    void create_table_from_syn_set(ResultsTable& resultsTable,
            const AttrRef& attrRef, PKB *pkb);
    void create_table_from_int_syn_set(ResultsTable& resultsTable,
            const AttrRef &attrRef, PKB *pkb,
            std::set<int> (PKB::*)() const);
    void create_table_from_string_syn_set(ResultsTable& resultsTable,
            const AttrRef &attrRef, PKB *pkb,
            std::set<std::string> (PKB::*)() const);

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