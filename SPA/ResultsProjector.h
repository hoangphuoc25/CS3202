#ifndef T11_RESULTS_PROJECTOR_H
#define T11_RESULTS_PROJECTOR_H

#include <vector>
#include <list>
#include <string>
#include <map>
#include <set>
#include "PKB.h"
#include "PQLParser.h"
#include "ResultsGraph.h"

class ResultsProjector {
public:
    ResultsProjector();
    void get_results(ResultsGraph &resultsGraph,
            QueryInfo *qinfo, PKB *pkb, std::list<std::string>& results);
private:
    void reset();
    void recursive_generate(int n,
            const std::vector<AttrRef>& selectTuple,
            QueryInfo *qinfo, std::list<std::string>& results);
    void add_syn_to_graph(ResultsGraph &resultsGraph, const AttrRef &attrRef,
            PKB *pkb);
    void add_int_syn_to_graph(ResultsGraph &resultsGraph,
            const AttrRef &attrRef, PKB *pkb,
            std::set<int> (PKB::*)() const);
    void add_string_syn_to_graph(ResultsGraph &resultsGraph,
            const AttrRef &attrRef, PKB *pkb,
            std::set<std::string> (PKB::*)() const);

    int nrSelect;
    StringBuffer sb;
    std::map<std::string, std::string> synValues;
    std::map<std::string, int> synToSetIndex;
    std::vector<std::set<std::pair<int, std::string> > > synValuesSet;
    std::vector<int> synIndices;
    std::vector<bool> synRepeated;
};

#endif