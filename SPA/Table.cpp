#include <cassert>
#include "Table.h"

using std::map;
using std::set;
using std::string;
using std::vector;

TableState Table::VALID_ADD_ROW_STATES_ARR[13] = {
    TS_ADD_ROW, TS_ADD_ROW_S, TS_ADD_ROW_I,
    TS_ADD_ROW_SS, TS_ADD_ROW_SI, TS_ADD_ROW_IS, TS_ADD_ROW_II,
    TS_ADD_ROW_R_S, TS_ADD_ROW_R_I,
    TS_ADD_ROW_R_SS, TS_ADD_ROW_R_SI, TS_ADD_ROW_R_IS, TS_ADD_ROW_R_II
};

const set<TableState> Table::VALID_ADD_ROW_STATES(
        Table::VALID_ADD_ROW_STATES_ARR,
        Table::VALID_ADD_ROW_STATES_ARR+13);

Table::Table()
    : tableState(TS_START), alive(true), RECORDS(), SYNTOCOLS(),
      COLTOSYN()
{
    this->curRecords = &(this->RECORDS[0]);
    this->auxRecords = &(this->RECORDS[1]);
    this->curSynToCol = &(this->SYNTOCOLS[0]);
    this->auxSynToCol = &(this->SYNTOCOLS[1]);
    this->curColToSyn = &(this->COLTOSYN[0]);
    this->auxColToSyn = &(this->COLTOSYN[1]);
}

Table::~Table() {}

bool Table::is_alive() const
{
    return this->alive;
}

bool Table::has_synonym(const string& syn) const
{
    return (this->curSynToCol->find(syn) !=
            this->curSynToCol->end());
}

int Table::get_synonym_column(const string& syn) const
{
    map<string, int>::const_iterator it =
            this->curSynToCol->find(syn);
    if (it == this->curSynToCol->end()) {
        return -1;
    } else {
        return it->second;
    }
}

const vector<Record>& Table::get_records() const
{
    return *(this->curRecords);
}

const map<int, string>& Table::get_col_to_synonym() const
{
    return *(this->curColToSyn);
}

const map<string, int>& Table::get_synonym_to_col() const
{
    return *(this->curSynToCol);
}

void Table::add_rows_transaction_begin()
{
    assert(this->tableState == TS_START);
    this->tableState = TS_ADD_ROW;
    this->auxRecords->clear();
    this->auxSynToCol->clear();
    this->auxColToSyn->clear();
}

void Table::add_rows_transaction_end()
{
    using std::swap;
    assert(Table::VALID_ADD_ROW_STATES.find(this->tableState) !=
            Table::VALID_ADD_ROW_STATES.end());
    swap(this->curRecords, this->auxRecords);
    swap(this->curSynToCol, this->auxSynToCol);
    swap(this->curColToSyn, this->auxColToSyn);
    this->alive = ((int)this->curRecords->size() > 0);
    this->tableState = TS_START;
}

void Table::add_row(const string& syn, const string& val)
{
    this->add_row_syn_preamble(TS_ADD_ROW_S, syn);
    Record row;
    row.add_synonym(val);
    this->auxRecords->push_back(row);
}

void Table::add_row(const string& syn, int val)
{
    this->add_row_syn_preamble(TS_ADD_ROW_I, syn);
    Record row;
    row.add_synonym(val);
    this->auxRecords->push_back(row);
}

void Table::add_row(const string& synOne, const string& valOne,
        const string& synTwo, const string& valTwo)
{
    this->add_row_syn_syn_preamble(TS_ADD_ROW_SS, synOne, synTwo);
    Record row;
    row.add_synonym(valOne);
    row.add_synonym(valTwo);
    this->auxRecords->push_back(row);
}

void Table::add_row(const string& synOne, const string& valOne,
        const string& synTwo, int valTwo)
{
    this->add_row_syn_syn_preamble(TS_ADD_ROW_SI, synOne, synTwo);
    Record row;
    row.add_synonym(valOne);
    row.add_synonym(valTwo);
    this->auxRecords->push_back(row);
}

void Table::add_row(const string& synOne, int valOne,
        const string& synTwo, const string& valTwo)
{
    this->add_row_syn_syn_preamble(TS_ADD_ROW_IS, synOne, synTwo);
    Record row;
    row.add_synonym(valOne);
    row.add_synonym(valTwo);
    this->auxRecords->push_back(row);
}

void Table::add_row(const string& synOne, int valOne,
        const string& synTwo, int valTwo)
{
    this->add_row_syn_syn_preamble(TS_ADD_ROW_II, synOne, synTwo);
    Record row;
    row.add_synonym(valOne);
    row.add_synonym(valTwo);
    this->auxRecords->push_back(row);
}

void Table::add_row(const Table& table, const Record& rec,
        const string& syn, const string& val)
{
    this->add_row_record_syn_preamble(TS_ADD_ROW_R_S, table, syn);
    Record row(rec);
    row.add_synonym(val);
    this->auxRecords->push_back(row);
}

void Table::add_row(const Table& table, const Record& rec,
        const string& syn, int val)
{
    this->add_row_record_syn_preamble(TS_ADD_ROW_R_I, table, syn);
    Record row;
    row.add_synonym(val);
    this->auxRecords->push_back(row);
}

void Table::add_row(const Table& table, const Record& rec,
        const string& synOne, const string& valOne,
        const string& synTwo, const string& valTwo)
{
    this->add_row_record_syn_syn_preamble(TS_ADD_ROW_R_SS, table,
            synOne, synTwo);
    Record row;
    row.add_synonym(valOne);
    row.add_synonym(valTwo);
    this->auxRecords->push_back(row);
}

void Table::add_row(const Table& table, const Record& rec,
        const string& synOne, const string& valOne,
        const string& synTwo, int valTwo)
{
    this->add_row_record_syn_syn_preamble(TS_ADD_ROW_R_SI, table,
            synOne, synTwo);
    Record row;
    row.add_synonym(valOne);
    row.add_synonym(valTwo);
    this->auxRecords->push_back(row);
}

void Table::add_row(const Table& table, const Record& rec,
        const string& synOne, int valOne,
        const string& synTwo, const string& valTwo)
{
    this->add_row_record_syn_syn_preamble(TS_ADD_ROW_R_IS, table,
            synOne, synTwo);
    Record row;
    row.add_synonym(valOne);
    row.add_synonym(valTwo);
    this->auxRecords->push_back(row);
}

void Table::add_row(const Table& table, const Record& rec,
        const string& synOne, int valOne,
        const string& synTwo, int valTwo)
{
    this->add_row_record_syn_syn_preamble(TS_ADD_ROW_R_II, table,
            synOne, synTwo);
    Record row;
    row.add_synonym(valOne);
    row.add_synonym(valTwo);
    this->auxRecords->push_back(row);
}

void Table::add_row_syn_preamble(const TableState idealState,
        const string& syn)
{
    assert(TS_ADD_ROW == this->tableState ||
            idealState == this->tableState);
    if (TS_ADD_ROW == this->tableState) {
        assert(this->auxSynToCol->empty());
        assert(this->auxColToSyn->empty());
        this->add_synonym(syn);
        this->tableState = idealState;
    }
}

void Table::add_row_syn_syn_preamble(const TableState idealState,
        const string& synOne, const string& synTwo)
{
    assert(TS_ADD_ROW == this->tableState ||
            idealState == this->tableState);
    if (TS_ADD_ROW == this->tableState) {
        assert(this->auxSynToCol->empty());
        assert(this->auxColToSyn->empty());
        this->add_synonym(synOne);
        this->add_synonym(synTwo);
        this->tableState = idealState;
    }
}

void Table::add_row_record_syn_preamble(const TableState idealState,
        const Table& table, const string& syn)
{
    assert(TS_ADD_ROW == this->tableState ||
            idealState == this->tableState);
    if (TS_ADD_ROW == this->tableState) {
        assert(this->auxSynToCol->empty());
        assert(this->auxColToSyn->empty());
        this->add_synonyms_in_table(table);
        this->add_synonym(syn);
        this->tableState = idealState;
    }
}

void Table::add_row_record_syn_syn_preamble(const TableState idealState,
        const Table& table, const string& synOne, const string& synTwo)
{
    assert(TS_ADD_ROW == this->tableState ||
            idealState == this->tableState);
    if (TS_ADD_ROW == this->tableState) {
        assert(this->auxSynToCol->empty());
        assert(this->auxColToSyn->empty());
        this->add_synonyms_in_table(table);
        this->add_synonym(synOne);
        this->add_synonym(synTwo);
        this->tableState = idealState;
    }
}

void Table::add_synonym(const string& syn)
{
    assert(this->auxSynToCol->find(syn) == this->auxSynToCol->end());
    int nextCol = (int)this->auxSynToCol->size();
    assert(this->auxColToSyn->find(nextCol) == this->auxColToSyn->end());
    (*(this->auxSynToCol))[syn] = nextCol;
    (*(this->auxColToSyn))[nextCol] = syn;
}

void Table::add_synonyms_in_table(const Table& o)
{
    assert(o.curSynToCol != this->auxSynToCol);
    assert(o.curColToSyn != this->auxColToSyn);
    int nextCol = this->auxSynToCol->size();
    for (map<int, string>::const_iterator it = o.curColToSyn->begin();
            it != o.curColToSyn->end(); it++) {
        assert(this->auxSynToCol->find(it->second) ==
                this->auxSynToCol->end());
        (*(this->auxSynToCol))[it->second] = nextCol;
        (*(this->auxColToSyn))[nextCol] = it->second;
        nextCol++;
    }
}

void Table::mark_rows_transaction_begin()
{
    assert(TS_START == this->tableState);
    this->preserveRow = vector<int>((int)this->curRecords->size() + 5,
            0);
    this->tableState = TS_MARK_ROW;
}

void Table::mark_rows_transaction_end()
{
    using std::swap;
    assert(TS_MARK_ROW == this->tableState);
    this->auxRecords->clear();
    int nrPreserved = 0;
    int len = this->curRecords->size();
    for (int i = 0; i < len; i++) {
        if (preserveRow[i]) {
            this->auxRecords->push_back((*(this->curRecords))[i]);
            nrPreserved++;
        }
    }
    swap(this->curRecords, this->auxRecords);
    this->alive = (nrPreserved > 0);
    this->tableState = TS_START;
}

void Table::mark_row_ok(int row)
{
    assert(TS_MARK_ROW == this->tableState);
    this->preserveRow[row] = 1;
}