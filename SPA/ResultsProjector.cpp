#include <cassert>
#include <algorithm>
#include <vector>
#include "ResultsProjector.h"
#include "StringBuffer.h"

using std::list;
using std::string;
using std::vector;
using std::set;
using std::make_pair;
using std::map;
using std::pair;
using std::sort;

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

const string ResultsProjector::TRUE_STR = "True";
const string ResultsProjector::FALSE_STR = "False";

ResultsProjector::ResultsProjector()
    : nrSelect(0), sb(), tablesUsed(), tablesUsedMap(), columnToSyn(),
      synToColumn(), columnCount(0), tableColToChoose(),
      recGenRowChosen(), sortedResults()
      {}

void ResultsProjector::reset()
{
    this->nrSelect = 0;
    this->tablesUsed.clear();
    this->tablesUsedMap.clear();
    this->columnToSyn.clear();
    this->synToColumn.clear();
    this->columnCount = 0;
    this->tableColToChoose.clear();
    this->sortedResults.clear();
    this->synValues.clear();
    this->synToSetIndex.clear();
    this->synValuesSet.clear();
    this->synIndices.clear();
    this->synRepeated.clear();
}

void ResultsProjector::create_table_from_syn_set(
        ResultsTable& resultsTable, const AttrRef& attrRef, PKB *pkb)
{
    // TODO: Implement PKB methods for those left empty
    assert(attrRef.entType != ENT_INVALID);
    switch (attrRef.entType) {
    case ENT_PROC:
        this->create_table_from_string_syn_set(resultsTable, attrRef,
                pkb, &PKB::get_all_procs);
        break;
    case ENT_STMTLST:
        this->create_table_from_int_syn_set(resultsTable, attrRef, pkb,
                &PKB::get_all_stmtLst);
        break;
    case ENT_STMT:
        this->create_table_from_int_syn_set(resultsTable, attrRef, pkb,
                &PKB::get_all_stmt);
        break;
    case ENT_ASSIGN:
        this->create_table_from_int_syn_set(resultsTable, attrRef, pkb,
                &PKB::get_all_assign);
        break;
    case ENT_CALL:
        this->create_table_from_int_syn_set(resultsTable, attrRef, pkb,
                &PKB::get_all_call);
        break;
    case ENT_WHILE:
        this->create_table_from_int_syn_set(resultsTable, attrRef, pkb,
                    &PKB::get_all_while);
        break;
    case ENT_IF:
        this->create_table_from_int_syn_set(resultsTable, attrRef, pkb,
                &PKB::get_all_if);
        break;
    case ENT_VAR:
        this->create_table_from_string_syn_set(resultsTable, attrRef,
                pkb, &PKB::get_all_vars);
        break;
    case ENT_CONST:
        this->create_table_from_int_syn_set(resultsTable, attrRef, pkb,
                &PKB::get_all_const);
        break;
    case ENT_PROGLINE:
        this->create_table_from_int_syn_set(resultsTable, attrRef, pkb,
                &PKB::get_all_progline);
        break;
    }
}

bool ResultsProjector::create_table_from_int_syn_set(
        ResultsTable& resultsTable, const AttrRef &attrRef, PKB *pkb,
        set<int> (PKB::*retrieve_int_set)() const)
{
    DesignEnt entType = attrRef.entType;
    const string& synName = attrRef.syn;
    Table *table = Table::create_from_set(synName,
            (pkb->*retrieve_int_set)());
    return resultsTable.absorb_table(table);
}

bool ResultsProjector::create_table_from_string_syn_set(
        ResultsTable& resultsTable, const AttrRef &attrRef, PKB *pkb,
        set<string> (PKB::*retrieve_string_set)() const)
{
    DesignEnt entType = attrRef.entType;
    const string& synName = attrRef.syn;
    Table *table = Table::create_from_set(synName,
            (pkb->*retrieve_string_set)());
    return resultsTable.absorb_table(table);
}

void ResultsProjector::get_results(ResultsTable& resultsTable,
        QueryInfo *qinfo, PKB *pkb, list<string>& results)
{
    this->reset();
    results.clear();
    SelectType selectType = qinfo->get_selectType();
    if (selectType == SEL_BOOLEAN) {
        if (resultsTable.is_alive()) {
            results.push_back(ResultsProjector::TRUE_STR);
        } else {
            results.push_back(ResultsProjector::FALSE_STR);
        }
        return;
    }
    if (!resultsTable.is_alive()) {
        return;
    }
    const vector<AttrRef>& selectTuple = qinfo->get_selectTuple();
    this->nrSelect = selectTuple.size();
    // create new tables for synonyms not in any clauses
    for (int i = 0; i < this->nrSelect && resultsTable.is_alive();
            i++) {
        const AttrRef& attrRef = selectTuple[i];
        if (!resultsTable.has_synonym(attrRef.syn)) {
            this->create_table_from_syn_set(resultsTable, attrRef, pkb);
        }
    }
    // ResultsTable might be dead after absorption. Check
    if (!resultsTable.is_alive()) {
        return;
    }
    resultsTable.checkout_transaction_begin();
    // get the set of tables required and construct table,column info
    for (int i = 0; i < this->nrSelect; i++) {
        const AttrRef& attrRef = selectTuple[i];
        Table *table = resultsTable.checkout_table(attrRef.syn);
        const map<string, int>& synToCol = table->get_synonym_to_col();
        int tableLabel = -1;
        int tableCol = -1;
        map<Table *, int>::const_iterator tableIdxIt =
                this->tablesUsedMap.find(table);
        if (tableIdxIt == this->tablesUsedMap.end()) {
            tableLabel = (int)this->tablesUsed.size();
            this->tablesUsedMap[table] = tableLabel;
            this->tablesUsed.push_back(table);
        } else {
            tableLabel = tableIdxIt->second;
        }
        map<string, int>::const_iterator siIt =
                synToCol.find(attrRef.syn);
        assert(siIt != synToCol.end());
        tableCol = siIt->second;
        assert(tableLabel != -1 && tableCol != -1);
        this->tableColToChoose.push_back(
                    make_pair(tableLabel, tableCol));
    }
    this->recGenRowChosen =
            vector<int>((int)this->tablesUsed.size() + 5, -1);
    this->recursive_generate(0, qinfo, pkb);
    resultsTable.checkout_transaction_end();
    results = list<string>(this->sortedResults.begin(),
            this->sortedResults.end());
}

void ResultsProjector::recursive_generate(int n,
        QueryInfo *qinfo, PKB *pkb)
{
    if (n >= this->tablesUsed.size()) {
        // generate results
        const vector<AttrRef>& selectTuple = qinfo->get_selectTuple();
        this->sb.clear();
        for (int i = 0; i < this->nrSelect; i++) {
            if (i > 0) {
                this->sb.append(',');
            }
            const AttrRef& attrRef = selectTuple[i];
            const pair<int, int>& tableColPair =
                    this->tableColToChoose[i];
            int tableIdx = tableColPair.first;
            int colIdx = tableColPair.second;
            Table *table = this->tablesUsed[tableIdx];
            const vector<Record>& records = table->get_records();
            int rowChosen = this->recGenRowChosen[tableIdx];
            const Record& record = records[rowChosen];
            const pair<string, int>& recordField =
                    record.get_column(colIdx);
            // handle call.procName
            if (attrRef.entType == ENT_CALL &&
                    attrRef.attr == ATTR_PROCNAME) {
                string callProcName =
                        pkb->get_call_procName(recordField.second);
                assert(callProcName != StmtBank::EMPTY_NAME);
                this->sb.append(callProcName);
            } else {
                switch (attrRef.entType) {
                case ENT_ASSIGN:
                case ENT_CALL:
                case ENT_IF:
                case ENT_WHILE:
                case ENT_STMTLST:
                case ENT_STMT:
                case ENT_PROGLINE:
                case ENT_CONST:
                    this->sb.append(int_to_string(recordField.second));
                    break;
                case ENT_PROC:
                case ENT_VAR:
                    this->sb.append(recordField.first);
                    break;
                }
            }
        }
        this->sortedResults.insert(this->sb.toString());
        return;
    } else {
        const vector<Record>& records =
                this->tablesUsed[n]->get_records();
        int nrRecords = records.size();
        for (int i = 0; i < nrRecords; i++) {
            this->recGenRowChosen[n] = i;
            this->recursive_generate(n+1, qinfo, pkb);
        }
    }
}