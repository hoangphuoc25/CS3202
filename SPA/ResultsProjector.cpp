#include <cassert>
#include <vector>
#include "ResultsProjector.h"
#include "StringBuffer.h"

using std::list;
using std::string;
using std::vector;
using std::set;
using std::map;
using std::pair;

// internal method
string int_to_string(int x)
{
    vector<char> vec;
    StringBuffer sb;
    if (x == 0) {
        return "0";
    }
    int d;
    while (x > 0) {
        d = x % 10;
        vec.push_back(d + '0');
        x /= 10;
    }
    for (int i = vec.size()-1; i >= 0; i--) {
        sb.append(vec[i]);
    }
    return sb.toString();
}

ResultsProjector::ResultsProjector()
    : nrSelect(0), sb() {}

void ResultsProjector::reset()
{
    this->nrSelect = 0;
    this->synValues.clear();
    this->synToSetIndex.clear();
    this->synValuesSet.clear();
    this->synIndices.clear();
    this->synRepeated.clear();
}

void ResultsProjector::add_syn_to_graph(ResultsGraph &resultsGraph,
        const AttrRef &attrRef, PKB *pkb)
{
    // TODO: Implement PKB methods for those left empty
    assert(attrRef.entType != ENT_INVALID);
    switch (attrRef.entType) {
    case ENT_PROC:
        break;
    case ENT_STMTLST:
        break;
    case ENT_STMT:
        break;
    case ENT_ASSIGN:
        this->add_int_syn_to_graph(resultsGraph, attrRef, pkb,
                &PKB::get_all_assign);
        break;
    case ENT_CALL:
        this->add_int_syn_to_graph(resultsGraph, attrRef, pkb,
                &PKB::get_all_call);
        break;
    case ENT_WHILE:
        this->add_int_syn_to_graph(resultsGraph, attrRef, pkb,
                    &PKB::get_all_while);
        break;
    case ENT_IF:
        this->add_int_syn_to_graph(resultsGraph, attrRef, pkb,
                &PKB::get_all_if);
        break;
    case ENT_VAR:
        break;
    case ENT_CONST:
        break;
    case ENT_PROGLINE:
        break;
    }
}

void ResultsProjector::add_int_syn_to_graph(ResultsGraph &resultsGraph,
        const AttrRef &attrRef, PKB *pkb,
        set<int> (PKB::*retrieve_int_set)() const)
{
    DesignEnt entType = attrRef.entType;
    const string& synName = attrRef.syn;
    set<int> synSet = (pkb->*retrieve_int_set)();
    for (set<int>::const_iterator it = synSet.begin(); it != synSet.end();
            it++) {
        resultsGraph.add_vertex(entType, synName, *it);
    }
}

void ResultsProjector::get_results(
        ResultsGraph& resultsGraph,
        QueryInfo *qinfo, PKB *pkb, list<string>& results)
{
    this->reset();
    results.clear();
    SelectType selectType = qinfo->get_selectType();
    if (selectType == SEL_BOOLEAN) {
        if (resultsGraph.is_alive()) {
            results.push_back("True");
        } else {
            results.push_back("False");
        }
    }
    if (!resultsGraph.is_alive()) {
        return;
    }
    const vector<AttrRef>& selectTuple = qinfo->get_selectTuple();
    this->nrSelect = selectTuple.size();
    for (int i = 0; i < this->nrSelect; i++) {
        const AttrRef& attrRef = selectTuple[i];
        // synonym is new, add everything into graph
        if (!resultsGraph.has_syn(attrRef.syn)) {
            this->add_syn_to_graph(resultsGraph, attrRef, pkb);
        }
        if (this->synToSetIndex.find(attrRef.syn) ==
                this->synToSetIndex.end()) {
            set<pair<int, string> > synValuesSet =
                resultsGraph.get_synonym(attrRef.syn);
            if (synValuesSet.size() <= 0) {
                return;
            }
            int synId = (int)this->synToSetIndex.size();
            this->synToSetIndex[attrRef.syn] = synId;
            this->synValuesSet.push_back(synValuesSet);
            this->synRepeated.push_back(false);
        } else {
            this->synRepeated.push_back(true);
        }
        int synId = this->synToSetIndex[attrRef.syn];
        this->synIndices.push_back(synId);
    }
    this->recursive_generate(0, selectTuple, qinfo, results);
}

void ResultsProjector::recursive_generate(int n,
        const vector<AttrRef>& selectTuple,
        QueryInfo *qinfo, list<string>& results)
{
    if (n >= this->nrSelect) {
        // generate results
        this->sb.clear();
        for (int i = 0; i < this->nrSelect; i++) {
            if (i > 0) {
                this->sb.append(',');
            }
            const AttrRef& attrRef = selectTuple[i];
            map<string, string>::const_iterator
                it = this->synValues.find(attrRef.syn);
            assert(it != this->synValues.end());
            this->sb.append(it->second);
        }
        results.push_back(this->sb.toString());
        return;
    }
    const AttrRef& attrRef = selectTuple[n];
    if (this->synRepeated[n]) {
        this->recursive_generate(n+1, selectTuple, qinfo, results);
    } else {
        bool useInt;
        switch (attrRef.entType) {
        case ENT_PROC:
        case ENT_VAR:
            useInt = false;
            break;
        default:
            useInt = true;
        }
        for (set<pair<int, string> >::const_iterator
                it = this->synValuesSet[n].begin();
                it != this->synValuesSet[n].end(); it++) {
            if (useInt) {
                this->synValues[attrRef.syn] =
                        int_to_string(it->first);
            } else {
                this->synValues[attrRef.syn] = it->second;
            }
            this->recursive_generate(n+1, selectTuple, qinfo, results);
        }
    }
}