#include <cassert>
#include <utility>
#include "ResultsTable.h"

using std::make_pair;
using std::map;
using std::pair;
using std::set;
using std::string;
using std::vector;

ResultsTable::ResultsTable()
    : state(RTS_START), tablesCheckedOut(),
      tableCheckedOutA(NULL), tableCheckedOutB(NULL),
      tableAIdx(-1), tableBIdx(-1), tableASyn(), tableBSyn(),
      synAType(RV_INVALID), synBType(RV_INVALID),
      alive(true), synMap(), tables(),
      nextTable(0) {}

ResultsTable::ResultsTable(const ResultsTable& o)
{
    assert(o.is_alive());
    assert(RTS_START == o.state);
    this->state = RTS_START;
    this->tablesCheckedOut = set<Table *>();
    this->tableCheckedOutA = this->tableCheckedOutB = NULL;
    this->tableAIdx = this->tableBIdx = -1;
    this->tableASyn = string();
    this->tableBSyn = string();
    this->synAType = this->synBType = RV_INVALID;
    this->alive = true;
    this->synMap = o.synMap;
    this->tables = o.tables;
    this->nextTable = o.nextTable;
}

ResultsTable& ResultsTable::operator=(const ResultsTable& o)
{
    ResultsTable tmp(o);
    swap(*this, tmp);
    return *this;
}

void swap(ResultsTable& one, ResultsTable& two)
{
    assert(one.is_alive());
    assert(RTS_START == one.state);
    assert(two.is_alive());
    assert(RTS_START == two.state);
    using std::swap;
    swap(one.synMap, two.synMap);
    swap(one.tables, two.tables);
    swap(one.nextTable, two.nextTable);
}

ResultsTable::~ResultsTable()
{
    for (map<int, Table *>::const_iterator it = this->tables.begin();
            it != this->tables.end(); it++) {
        delete it->second;
    }
}

bool ResultsTable::has_synonym(const string& syn) const
{
    map<string, int>::const_iterator it = this->synMap.find(syn);
    return (it != this->synMap.end());
}

bool ResultsTable::is_alive() const
{
    return this->alive;
}

void ResultsTable::checkout_transaction_begin()
{
    assert(RTS_START == this->state);
    this->state = RTS_CHECKOUT;
}

void ResultsTable::checkout_transaction_end()
{
    assert(RTS_CHECKOUT == this->state);
    for (set<Table *>::iterator it =
            this->tablesCheckedOut.begin();
            it != this->tablesCheckedOut.end(); it++) {
        (*it)->unfreeze();
    }
    this->tablesCheckedOut.clear();
    this->state = RTS_START;
}

Table* ResultsTable::checkout_table(const string& syn)
{
    assert(RTS_CHECKOUT == this->state);
    map<string, int>::const_iterator it = this->synMap.find(syn);
    assert(it != this->synMap.end());
    Table *tab = this->tables[it->second];
    if (this->tablesCheckedOut.find(tab) ==
            this->tablesCheckedOut.end()) {
        this->tablesCheckedOut.insert(tab);
        tab->freeze();
    }
    return tab;
}

void ResultsTable::syn_0_transaction_begin(const string& syn,
        RecordValType rvType)
{
    assert(RTS_START == this->state);
    assert(!this->has_synonym(syn));
    assert(rvType != RV_INVALID);
    int tableLabel = this->nextTable;
    this->nextTable++;
    this->synMap[syn] = tableLabel;
    this->tableCheckedOutA = this->tables[tableLabel] = new Table();
    this->tableCheckedOutA->add_rows_transaction_begin();
    this->tableAIdx = tableLabel;
    this->tableASyn = syn;
    this->synAType = rvType;
    this->state = RTS_0_TRANSACT;
}

void ResultsTable::syn_0_transaction_end()
{
    assert(RTS_0_TRANSACT == this->state);
    assert(this->tableCheckedOutA != NULL);
    this->tableCheckedOutA->add_rows_transaction_end();
    this->alive = (this->alive && this->tableCheckedOutA->is_alive());
    this->tableCheckedOutA = NULL;
    this->tableAIdx = -1;
    this->tableASyn = string();
    this->synAType = RV_INVALID;
    this->state = RTS_START;
}

void ResultsTable::syn_0_add_row(const string& val)
{
    assert(RTS_0_TRANSACT == this->state);
    assert(tableCheckedOutA != NULL);
    assert(RV_STRING == this->synAType);
    this->tableCheckedOutA->add_row(this->tableASyn, val);
}

void ResultsTable::syn_0_add_row(int val)
{
    assert(RTS_0_TRANSACT == this->state);
    assert(tableCheckedOutA != NULL);
    assert(RV_INT == this->synAType);
    this->tableCheckedOutA->add_row(this->tableASyn, val);
}

const vector<Record>& ResultsTable::syn_1_transaction_begin(
        const string& syn)
{
    assert(RTS_START == this->state);
    assert(this->has_synonym(syn));
    map<string, int>::const_iterator it = this->synMap.find(syn);
    assert(it != this->synMap.end());
    map<int, Table *>::const_iterator tableIt =
            this->tables.find(it->second);
    assert(tableIt != this->tables.end());
    this->tableAIdx = tableIt->first;
    this->tableASyn = syn;
    this->tableCheckedOutA = tableIt->second;
    this->tableCheckedOutA->mark_rows_transaction_begin();
    this->state = RTS_1_TRANSACT;
    return this->tableCheckedOutA->get_records();
}

void ResultsTable::syn_1_transaction_end()
{
    assert(RTS_1_TRANSACT == this->state);
    assert(this->tableCheckedOutA != NULL);
    this->tableCheckedOutA->mark_rows_transaction_end();
    this->alive = (this->alive && this->tableCheckedOutA->is_alive());
    this->tableCheckedOutA = NULL;
    this->tableAIdx = -1;
    this->tableASyn = string();
    this->state = RTS_START;
}

void ResultsTable::syn_1_mark_row_ok(int row)
{
    assert(RTS_1_TRANSACT == this->state);
    this->tableCheckedOutA->mark_row_ok(row);
}

void ResultsTable::syn_00_transaction_begin(const string& synA,
        RecordValType rvAType, const string& synB,
        RecordValType rvBType)
{
    assert(RTS_START == this->state);
    assert(!this->has_synonym(synA));
    assert(!this->has_synonym(synB));
    assert(synA.compare(synB) != 0);
    assert(RV_INVALID != rvAType);
    assert(RV_INVALID != rvBType);
    int tableLabel = this->nextTable;
    this->nextTable++;
    this->synMap[synA] = this->synMap[synB] = tableLabel;
    this->tableCheckedOutA = this->tables[tableLabel] = new Table();
    this->tableCheckedOutA->add_rows_transaction_begin();
    this->tableAIdx = tableLabel;
    this->tableASyn = synA;
    this->tableBSyn = synB;
    this->synAType = rvAType;
    this->synBType = rvBType;
    this->state = RTS_00_TRANSACT;
}

void ResultsTable::syn_00_transaction_end()
{
    assert(RTS_00_TRANSACT == this->state);
    this->tableCheckedOutA->add_rows_transaction_end();
    this->alive = (this->alive && this->tableCheckedOutA->is_alive());
    this->tableCheckedOutA = NULL;
    this->tableAIdx = -1;
    this->tableASyn = string();
    this->tableBSyn = string();
    this->synAType = this->synBType = RV_INVALID;
    this->state = RTS_START;
}

void ResultsTable::syn_00_add_row(const string& valA, const string& valB)
{
    assert(RTS_00_TRANSACT == this->state);
    assert(RV_STRING == this->synAType);
    assert(RV_STRING == this->synBType);
    this->tableCheckedOutA->add_row(this->tableASyn, valA,
            this->tableBSyn, valB);
}

void ResultsTable::syn_00_add_row(const string& valA, int valB)
{
    assert(RTS_00_TRANSACT == this->state);
    assert(RV_STRING == this->synAType);
    assert(RV_INT == this->synBType);
    this->tableCheckedOutA->add_row(this->tableASyn, valA,
            this->tableBSyn, valB);
}

void ResultsTable::syn_00_add_row(int valA, const string& valB)
{
    assert(RTS_00_TRANSACT == this->state);
    assert(RV_INT == this->synAType);
    assert(RV_STRING == this->synBType);
    this->tableCheckedOutA->add_row(this->tableASyn, valA,
            this->tableBSyn, valB);
}

void ResultsTable::syn_00_add_row(int valA, int valB)
{
    assert(RTS_00_TRANSACT == this->state);
    assert(RV_INT == this->synAType);
    assert(RV_INT == this->synBType);
    this->tableCheckedOutA->add_row(this->tableASyn, valA,
            this->tableBSyn, valB);
}

const vector<Record>& ResultsTable::syn_01_transaction_begin(
        const string& synNew, const string& synOld, RecordValType rvType)
{
    assert(RTS_START == this->state);
    assert(!this->has_synonym(synNew));
    assert(this->has_synonym(synOld));
    assert(rvType != RV_INVALID);
    map<string, int>::const_iterator synIt =
            this->synMap.find(synOld);
    assert(synIt != this->synMap.end());
    int tableIdx = synIt->second;
    synMap[synNew] = tableIdx;
    map<int, Table *>::const_iterator tableIt =
            this->tables.find(tableIdx);
    assert(tableIt != this->tables.end());
    Table *table = tableIt->second;
    this->tableCheckedOutA = table;
    this->tableCheckedOutA->augment_new_rows_transaction_begin();
    this->tableAIdx = tableIdx;
    this->tableASyn = synNew;
    this->synAType = rvType;
    this->state = RTS_01_TRANSACT;
    return this->tableCheckedOutA->get_records();
}

void ResultsTable::syn_01_transaction_end()
{
    assert(RTS_01_TRANSACT == this->state);
    this->tableCheckedOutA->augment_new_rows_transaction_end();
    this->alive = (this->alive && this->tableCheckedOutA->is_alive());
    this->tableCheckedOutA = NULL;
    this->tableAIdx = -1;
    this->tableASyn = string();
    this->synAType = RV_INVALID;
    this->state = RTS_START;
}

void ResultsTable::syn_01_augment_new_row(int row, const string& val)
{
    assert(RTS_01_TRANSACT == this->state);
    assert(RV_STRING == this->synAType);
    this->tableCheckedOutA->augment_new_row(row, this->tableASyn, val);
}

void ResultsTable::syn_01_augment_new_row(int row, int val)
{
    assert(RTS_01_TRANSACT == this->state);
    assert(RV_INT == this->synAType);
    this->tableCheckedOutA->augment_new_row(row, this->tableASyn, val);
}

const vector<Record>& ResultsTable::syn_11_transaction_begin(
        const string& synOne, const string& synTwo)
{
    assert(RTS_START == this->state);
    assert(this->has_synonym(synOne));
    assert(this->has_synonym(synTwo));
    map<string, int>::const_iterator it, kt;
    it = this->synMap.find(synOne);
    kt = this->synMap.find(synTwo);
    assert(it != this->synMap.end());
    assert(kt != this->synMap.end());
    assert(it->second == kt->second);
    map<int, Table *>::const_iterator tableIt =
            this->tables.find(it->second);
    assert(tableIt != this->tables.end());
    this->tableAIdx = this->tableBIdx = tableIt->first;
    this->tableASyn = synOne;
    this->tableBSyn = synTwo;
    this->tableCheckedOutA = tableIt->second;
    this->tableCheckedOutA->mark_rows_transaction_begin();
    this->state = RTS_11_TRANSACT;
    return this->tableCheckedOutA->get_records();
}

void ResultsTable::syn_11_transaction_end()
{
    assert(RTS_11_TRANSACT == this->state);
    assert(this->tableCheckedOutA != NULL);
    this->tableCheckedOutA->mark_rows_transaction_end();
    this->alive = (this->alive && this->tableCheckedOutA->is_alive());
    this->tableAIdx = this->tableBIdx = -1;
    this->tableASyn = string();
    this->tableBSyn = string();
    this->tableCheckedOutA = NULL;
    this->state = RTS_START;
}

void ResultsTable::syn_11_mark_row_ok(int row)
{
    assert(RTS_11_TRANSACT == this->state);
    this->tableCheckedOutA->mark_row_ok(row);
}

pair<const vector<Record> *, const vector<Record> * >
        ResultsTable::syn_22_transaction_begin(
            const string& synOne, const string& synTwo)
{
    assert(RTS_START == this->state);
    map<string, int>::const_iterator it, kt;
    it = this->synMap.find(synOne);
    kt = this->synMap.find(synTwo);
    assert(this->synMap.end() != it);
    assert(this->synMap.end() != kt);
    assert(it->second != kt->second);
    map<int, Table *>::const_iterator tableA, tableB;
    tableA = this->tables.find(it->second);
    tableB = this->tables.find(kt->second);
    assert(this->tables.end() != tableA);
    assert(this->tables.end() != tableB);
    assert(tableA->second != tableB->second);
    this->tableCheckedOutA = tableA->second;
    this->tableCheckedOutB = tableB->second;
    this->tableAIdx = tableA->first;
    this->tableBIdx = tableB->first;
    this->tableASyn = synOne;
    this->tableBSyn = synTwo;
    this->tableCheckedOutA->add_rows_transaction_begin();
    this->state = RTS_22_TRANSACT;
    return make_pair(&(this->tableCheckedOutA->get_records()),
                     &(this->tableCheckedOutB->get_records()));
}

void ResultsTable::syn_22_transaction_end()
{
    assert(RTS_22_TRANSACT == this->state);
    assert(NULL != this->tableCheckedOutA);
    assert(NULL != this->tableCheckedOutB);
    // use table A
    this->tableCheckedOutA->add_rows_transaction_end();
    // Redirect synonyms from table B to table A
    const map<string, int>& synM =
            this->tableCheckedOutB->get_synonym_to_col();
    for (map<string, int>::const_iterator it = synM.begin();
            it != synM.end(); it++) {
        this->synMap[it->first] = this->tableAIdx;
    }
    // destroy src table
    this->tables.erase(this->tableBIdx);
    delete this->tableCheckedOutB;
    this->alive = (this->alive && this->tableCheckedOutA->is_alive());
    this->tableCheckedOutA = this->tableCheckedOutB = NULL;
    this->tableAIdx = this->tableBIdx = -1;
    this->tableASyn = string();
    this->tableBSyn = string();
    this->state = RTS_START;
}

void ResultsTable::syn_22_add_row(const Record& recOne,
        const Record& recTwo)
{
    assert(RTS_22_TRANSACT == this->state);
    this->tableCheckedOutA->add_row(
            this->tableCheckedOutA->get_col_to_synonym(), recOne,
            this->tableCheckedOutB->get_col_to_synonym(), recTwo);
}

void ResultsTable::syn_22_add_row(int rowOne, int rowTwo)
{
    assert(RTS_22_TRANSACT == this->state);
    const vector<Record>& tableARows =
            this->tableCheckedOutA->get_records();
    const vector<Record>& tableBRows =
            this->tableCheckedOutB->get_records();
    int tableAnrRows = tableARows.size();
    int tableBnrRows = tableBRows.size();
    if (rowOne >= 0 && rowOne < tableAnrRows && rowTwo >= 0 &&
            rowTwo < tableBnrRows) {
        this->tableCheckedOutA->add_row(
                this->tableCheckedOutA->get_col_to_synonym(),
                tableARows[rowOne],
                this->tableCheckedOutB->get_col_to_synonym(),
                tableBRows[rowTwo]);
    }
}