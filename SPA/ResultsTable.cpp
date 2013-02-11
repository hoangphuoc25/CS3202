#include <cassert>
#include <utility>
#include "ResultsTable.h"

using std::make_pair;
using std::map;
using std::pair;
using std::string;
using std::vector;

ResultsTable::ResultsTable()
    : state(RTS_START), tableCheckedOutA(-1), tableCheckedOutB(-1),
      alive(true), synMap(), tables(), nextTable(0) {}

ResultsTable::ResultsTable(const ResultsTable& o)
    : state(o.state), tableCheckedOutA(o.tableCheckedOutA),
      tableCheckedOutB(o.tableCheckedOutB),
      alive(o.alive), synMap(o.synMap), tables(o.tables),
      nextTable(o.nextTable) {}

ResultsTable& ResultsTable::operator=(const ResultsTable& o)
{
    ResultsTable tmp(o);
    swap(*this, tmp);
    return *this;
}

void swap(ResultsTable& one, ResultsTable& two)
{
    using std::swap;
    swap(one.state, two.state);
    swap(one.tableCheckedOutA, two.tableCheckedOutA);
    swap(one.tableCheckedOutB, two.tableCheckedOutB);
    swap(one.alive, two.alive);
    swap(one.synMap, two.synMap);
    swap(one.tables, two.tables);
    swap(one.nextTable, two.nextTable);
}

ResultsTable::~ResultsTable() {}

bool ResultsTable::has_synonym(const string& syn) const
{
    map<string, int>::const_iterator it = this->synMap.find(syn);
    return (it != this->synMap.end());
}

bool ResultsTable::is_alive() const
{
    return this->alive;
}

Table* ResultsTable::retrieve_table_for_synonym(const string& syn)
{
    map<string, int>::const_iterator it = this->synMap.find(syn);
    assert(it != this->synMap.end());
    return this->tables[it->second];
}

void ResultsTable::absorb_resultsTable(const ResultsTable &o)
{
    assert(o.alive);
    for (map<string, int>::const_iterator it = o.synMap.begin();
            it != o.synMap.end(); it++) {
        assert(this->synMap.find(it->first) == this->synMap.end());
        this->synMap[it->first] = this->nextTable;
        map<int, Table *>::const_iterator tableIt =
                o.tables.find(it->second);
        assert(tableIt != o.tables.end());
        this->tables[this->nextTable] = tableIt->second;
        this->nextTable++;
    }
}

Table* ResultsTable::syn_0_transaction_begin(const string& syn)
{
    assert(RTS_START == this->state);
    assert(!this->has_synonym(syn));
    int tableLabel = this->nextTable;
    this->nextTable++;
    this->synMap[syn] = tableLabel;
    Table *tab = this->tables[tableLabel] = new Table();
    this->state = RTS_0_TRANSACT;
    this->tableCheckedOutA = tableLabel;
    return tab;
}

void ResultsTable::syn_0_transaction_end()
{
    assert(RTS_0_TRANSACT == this->state);
    assert(this->tableCheckedOutA != -1);
    map<int, Table *>::const_iterator it =
            this->tables.find(this->tableCheckedOutA);
    assert(it != this->tables.end());
    this->alive = (this->alive && it->second->is_alive());
    this->tableCheckedOutA = -1;
    this->state = RTS_START;
}

Table* ResultsTable::syn_1_transaction_begin(const string& syn)
{
    assert(RTS_START == this->state);
    assert(this->has_synonym(syn));
    map<string, int>::const_iterator it = this->synMap.find(syn);
    assert(it != this->synMap.end());
    map<int, Table *>::const_iterator tableIt =
            this->tables.find(it->second);
    assert(tableIt != this->tables.end());
    this->state = RTS_1_TRANSACT;
    return tableIt->second;
}

void ResultsTable::syn_1_transaction_end()
{
    assert(RTS_1_TRANSACT == this->state);
    assert(this->tableCheckedOutA != -1);
    map<int, Table *>::const_iterator it =
            this->tables.find(this->tableCheckedOutA);
    assert(it != this->tables.end());
    this->alive = (this->alive && it->second->is_alive());
    this->tableCheckedOutA = -1;
    this->state = RTS_START;
}

Table* ResultsTable::syn_11_transaction_begin(const string& synOne,
        const string& synTwo)
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
    Table *tab = tableIt->second;
    this->state = RTS_11_TRANSACT;
    this->tableCheckedOutA = tableIt->first;
    return tab;
}

void ResultsTable::syn_11_transaction_end()
{
    assert(RTS_11_TRANSACT == this->state);
    assert(this->tableCheckedOutA != -1);
    map<int, Table *>::const_iterator it =
            this->tables.find(this->tableCheckedOutA);
    Table *tab = it->second;
    this->alive = (this->alive && tab->is_alive());
    this->tableCheckedOutA = -1;
    this->state = RTS_START;
}

pair<Table *, Table *> ResultsTable::syn_22_transaction_begin(
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
    this->tableCheckedOutA = tableA->first;
    this->tableCheckedOutB = tableB->first;
    pair<Table *, Table *> tabPair =
            make_pair(tableA->second, tableB->second);
    this->state = RTS_22_TRANSACT;
    return tabPair;
}

void ResultsTable::syn_22_transaction_end(Table *endTable,
        ResultsTab22Transact which,
        const string& argOne, const string& argTwo)
{
    assert(RTS_22_TRANSACT == this->state);
    assert(-1 != this->tableCheckedOutA);
    assert(-1 != this->tableCheckedOutB);
    if (which == USE_TABLE_A) {
        // endTable == Table A. Direct B's synonyms to A
        this->syn_22_transaction_end_redirect_synonyms(
                this->tableCheckedOutA, this->tableCheckedOutB);
    } else if (which == USE_TABLE_B) {
        // endTable == Table B. Direct A's synonyms to B
        this->syn_22_transaction_end_redirect_synonyms(
                this->tableCheckedOutB, this->tableCheckedOutA);
    } else {
        // endTable is a new table. Direct A and B's synonyms to it
        int newTableLabel = this->nextTable;
        this->nextTable++;
        assert(this->tables.find(newTableLabel) == this->tables.end());
        this->tables[newTableLabel] = endTable;
        this->syn_22_transaction_end_redirect_synonyms(
                newTableLabel, this->tableCheckedOutA);
        this->syn_22_transaction_end_redirect_synonyms(
                newTableLabel, this->tableCheckedOutB);
    }
    this->tableCheckedOutA = this->tableCheckedOutB = -1;
    this->alive = (this->alive && endTable->is_alive());
    this->state = RTS_START;
}

void ResultsTable::syn_22_transaction_end_redirect_synonyms(
        int dest, int src)
{
    assert(dest != src);
    // Redirect synonyms from src to dest
    map<int, Table *>::const_iterator tabIt =
            this->tables.find(src);
    assert(this->tables.end() != tabIt);
    Table *tab = tabIt->second;
    const map<string, int>& synM = tab->get_synonym_to_col();
    for (map<string, int>::const_iterator it = synM.begin();
            it != synM.end(); it++) {
        this->synMap[it->first] = dest;
    }
    // destroy src table
    this->tables.erase(src);
    delete tab;
}