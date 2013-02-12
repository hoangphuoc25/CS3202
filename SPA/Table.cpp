#include <cassert>
#include "Table.h"

using std::map;
using std::set;
using std::string;
using std::vector;

TableState Table::VALID_ADD_ROW_STATES_ARR[14] = {
    TS_ADD_ROW, TS_ADD_ROW_S, TS_ADD_ROW_I,
    TS_ADD_ROW_SS, TS_ADD_ROW_SI, TS_ADD_ROW_IS, TS_ADD_ROW_II,
    TS_ADD_ROW_R_S, TS_ADD_ROW_R_I,
    TS_ADD_ROW_R_SS, TS_ADD_ROW_R_SI, TS_ADD_ROW_R_IS, TS_ADD_ROW_R_II,
    TS_ADD_ROW_R_R
};

const set<TableState> Table::VALID_ADD_ROW_STATES(
        Table::VALID_ADD_ROW_STATES_ARR,
        Table::VALID_ADD_ROW_STATES_ARR+14);

TableState Table::VALID_AUGMENT_EXISTING_ROW_STATES_ARR[3] = {
    TS_AUGMENT_EXISTING_ROW, TS_AUGMENT_EXISTING_ROW_S,
    TS_AUGMENT_EXISTING_ROW_I
};

const set<TableState> Table::VALID_AUGMENT_EXISTING_ROW_STATES(
        Table::VALID_AUGMENT_EXISTING_ROW_STATES_ARR,
        Table::VALID_AUGMENT_EXISTING_ROW_STATES_ARR+3);

TableState Table::VALID_AUGMENT_NEW_ROW_STATES_ARR[3] = {
    TS_AUGMENT_NEW_ROW, TS_AUGMENT_NEW_ROW_S, TS_AUGMENT_NEW_ROW_I
};

const set<TableState> Table::VALID_AUGMENT_NEW_ROW_STATES(
        Table::VALID_AUGMENT_NEW_ROW_STATES_ARR,
        Table::VALID_AUGMENT_NEW_ROW_STATES_ARR+3);

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
    row.add_value(val);
    this->auxRecords->push_back(row);
}

void Table::add_row(const string& syn, int val)
{
    this->add_row_syn_preamble(TS_ADD_ROW_I, syn);
    Record row;
    row.add_value(val);
    this->auxRecords->push_back(row);
}

void Table::add_row(const string& synOne, const string& valOne,
        const string& synTwo, const string& valTwo)
{
    this->add_row_syn_syn_preamble(TS_ADD_ROW_SS, synOne, synTwo);
    Record row;
    row.add_value(valOne);
    row.add_value(valTwo);
    this->auxRecords->push_back(row);
}

void Table::add_row(const string& synOne, const string& valOne,
        const string& synTwo, int valTwo)
{
    this->add_row_syn_syn_preamble(TS_ADD_ROW_SI, synOne, synTwo);
    Record row;
    row.add_value(valOne);
    row.add_value(valTwo);
    this->auxRecords->push_back(row);
}

void Table::add_row(const string& synOne, int valOne,
        const string& synTwo, const string& valTwo)
{
    this->add_row_syn_syn_preamble(TS_ADD_ROW_IS, synOne, synTwo);
    Record row;
    row.add_value(valOne);
    row.add_value(valTwo);
    this->auxRecords->push_back(row);
}

void Table::add_row(const string& synOne, int valOne,
        const string& synTwo, int valTwo)
{
    this->add_row_syn_syn_preamble(TS_ADD_ROW_II, synOne, synTwo);
    Record row;
    row.add_value(valOne);
    row.add_value(valTwo);
    this->auxRecords->push_back(row);
}

void Table::add_row(const map<int, string>& colToSyn, const Record& rec,
        const string& syn, const string& val)
{
    this->add_row_record_syn_preamble(TS_ADD_ROW_R_S, colToSyn, syn);
    Record row(rec);
    row.add_value(val);
    this->auxRecords->push_back(row);
}

void Table::add_row(const map<int, string>& colToSynM,
        const Record& rec,
        const string& syn, int val)
{
    this->add_row_record_syn_preamble(TS_ADD_ROW_R_I, colToSynM, syn);
    Record row(rec);
    row.add_value(val);
    this->auxRecords->push_back(row);
}

void Table::add_row(const map<int, string>& colToSynM,
        const Record& rec,
        const string& synOne, const string& valOne,
        const string& synTwo, const string& valTwo)
{
    this->add_row_record_syn_syn_preamble(TS_ADD_ROW_R_SS, colToSynM,
            synOne, synTwo);
    Record row(rec);
    row.add_value(valOne);
    row.add_value(valTwo);
    this->auxRecords->push_back(row);
}

void Table::add_row(const map<int, string>& colToSynM,
        const Record& rec,
        const string& synOne, const string& valOne,
        const string& synTwo, int valTwo)
{
    this->add_row_record_syn_syn_preamble(TS_ADD_ROW_R_SI, colToSynM,
            synOne, synTwo);
    Record row(rec);
    row.add_value(valOne);
    row.add_value(valTwo);
    this->auxRecords->push_back(row);
}

void Table::add_row(const map<int, string>& colToSynM,
        const Record& rec,
        const string& synOne, int valOne,
        const string& synTwo, const string& valTwo)
{
    this->add_row_record_syn_syn_preamble(TS_ADD_ROW_R_IS, colToSynM,
            synOne, synTwo);
    Record row(rec);
    row.add_value(valOne);
    row.add_value(valTwo);
    this->auxRecords->push_back(row);
}

void Table::add_row(const map<int, string>& colToSynM,
        const Record& rec,
        const string& synOne, int valOne,
        const string& synTwo, int valTwo)
{
    this->add_row_record_syn_syn_preamble(TS_ADD_ROW_R_II, colToSynM,
            synOne, synTwo);
    Record row(rec);
    row.add_value(valOne);
    row.add_value(valTwo);
    this->auxRecords->push_back(row);
}

void Table::add_row(const map<int, string>& colToSynOne,
        const Record& recOne,
        const map<int, string>& colToSynTwo, const Record& recTwo)
{
    assert(TS_ADD_ROW == this->tableState ||
            TS_ADD_ROW_R_R == this->tableState);
    if (TS_ADD_ROW == this->tableState) {
        assert(this->auxSynToCol->empty());
        assert(this->auxColToSyn->empty());
        this->add_synonyms_in_map(colToSynOne);
        this->add_synonyms_in_map(colToSynTwo);
        this->tableState = TS_ADD_ROW_R_R;
    }
    Record record(recOne);
    record.add_record(recTwo);
    this->auxRecords->push_back(record);
}

void Table::add_row_syn_preamble(const TableState idealState,
        const string& syn)
{
    assert(TS_ADD_ROW == this->tableState ||
            idealState == this->tableState);
    if (TS_ADD_ROW == this->tableState) {
        assert(this->auxSynToCol->empty());
        assert(this->auxColToSyn->empty());
        this->add_synonym_to_aux(syn);
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
        this->add_synonym_to_aux(synOne);
        this->add_synonym_to_aux(synTwo);
        this->tableState = idealState;
    }
}

void Table::add_row_record_syn_preamble(const TableState idealState,
        const map<int, string>& colToSynM, const string& syn)
{
    assert(TS_ADD_ROW == this->tableState ||
            idealState == this->tableState);
    if (TS_ADD_ROW == this->tableState) {
        assert(this->auxSynToCol->empty());
        assert(this->auxColToSyn->empty());
        this->add_synonyms_in_map(colToSynM);
        this->add_synonym_to_aux(syn);
        this->tableState = idealState;
    }
}

void Table::add_row_record_syn_syn_preamble(const TableState idealState,
        const map<int, string>& colToSynM,
        const string& synOne, const string& synTwo)
{
    assert(TS_ADD_ROW == this->tableState ||
            idealState == this->tableState);
    if (TS_ADD_ROW == this->tableState) {
        assert(this->auxSynToCol->empty());
        assert(this->auxColToSyn->empty());
        this->add_synonyms_in_map(colToSynM);
        this->add_synonym_to_aux(synOne);
        this->add_synonym_to_aux(synTwo);
        this->tableState = idealState;
    }
}

void Table::add_synonym_to_aux(const string& syn)
{
    assert(this->auxSynToCol->find(syn) == this->auxSynToCol->end());
    int nextCol = (int)this->auxSynToCol->size();
    assert(this->auxColToSyn->find(nextCol) == this->auxColToSyn->end());
    (*(this->auxSynToCol))[syn] = nextCol;
    (*(this->auxColToSyn))[nextCol] = syn;
}

void Table::add_synonym_to_cur(const string& syn)
{
    assert(this->curSynToCol->find(syn) == this->curSynToCol->end());
    int nextCol = (int)this->curSynToCol->size();
    assert(this->curColToSyn->find(nextCol) == this->curColToSyn->end());
    (*(this->curSynToCol))[syn] = nextCol;
    (*(this->curColToSyn))[nextCol] = syn;
}

void Table::add_synonyms_in_map(const map<int, string>& colToSynM)
{
    int nextCol = this->auxSynToCol->size();
    for (map<int, string>::const_iterator it = colToSynM.begin();
            it != colToSynM.end(); it++) {
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
    if (row >= 0 && row < this->curRecords->size()) {
        this->preserveRow[row] = 1;
    }
}

void Table::augment_existing_rows_transaction_begin()
{
    assert(TS_START == this->tableState);
    this->auxSynToCol->clear();
    this->auxColToSyn->clear();
    this->preserveRow = vector<int>((int)this->curRecords->size() + 5, 0);
    this->tableState = TS_AUGMENT_EXISTING_ROW;
}

void Table::augment_existing_rows_transaction_end()
{
    using std::swap;
    assert(Table::VALID_AUGMENT_EXISTING_ROW_STATES.find(this->tableState)
            != Table::VALID_AUGMENT_EXISTING_ROW_STATES.end());
    this->auxRecords->clear();
    int nrRecords = this->curRecords->size();
    for (int i = 0; i < nrRecords; i++) {
        if (this->preserveRow[i]) {
            this->auxRecords->push_back((*(this->curRecords))[i]);
        }
    }
    swap(this->curRecords, this->auxRecords);
    this->alive = (this->curRecords->size() > 0);
    this->tableState = TS_START;
}

void Table::augment_existing_row(int row, const string& syn,
        const string& val)
{
    assert(TS_AUGMENT_EXISTING_ROW == this->tableState ||
            TS_AUGMENT_EXISTING_ROW_S == this->tableState);
    if (TS_AUGMENT_EXISTING_ROW == this->tableState) {
        assert(!this->has_synonym(syn));
        this->add_synonym_to_cur(syn);
        this->tableState = TS_AUGMENT_EXISTING_ROW_S;
    }
    int nrRecords = this->curRecords->size();
    if (row >= 0 && row < nrRecords) {
        (*(this->curRecords))[row].add_value(val);
        this->preserveRow[row] = 1;
    }
}

void Table::augment_existing_row(int row, const string& syn, int val)
{
    assert(TS_AUGMENT_EXISTING_ROW == this->tableState ||
            TS_AUGMENT_EXISTING_ROW_I == this->tableState);
    if (TS_AUGMENT_EXISTING_ROW == this->tableState) {
        assert(!this->has_synonym(syn));
        this->add_synonym_to_cur(syn);
        this->tableState = TS_AUGMENT_EXISTING_ROW_I;
    }
    int nrRecords = this->curRecords->size();
    if (row >= 0 && row < nrRecords) {
        (*(this->curRecords))[row].add_value(val);
        this->preserveRow[row] = 1;
    }
}

void Table::augment_new_rows_transaction_begin()
{
    assert(TS_START == this->tableState);
    this->auxRecords->clear();
    this->tableState = TS_AUGMENT_NEW_ROW;
}

void Table::augment_new_rows_transaction_end()
{
    assert(Table::VALID_AUGMENT_NEW_ROW_STATES.find(this->tableState) !=
            Table::VALID_AUGMENT_NEW_ROW_STATES.end());
    using std::swap;
    swap(this->curRecords, this->auxRecords);
    this->alive = (this->alive && this->curRecords->size() > 0);
    this->tableState = TS_START;
}

void Table::augment_new_row(int row, const string& syn,
        const string& val)
{
    assert(TS_AUGMENT_NEW_ROW == this->tableState ||
            TS_AUGMENT_NEW_ROW_S == this->tableState);
    if (TS_AUGMENT_NEW_ROW == this->tableState) {
        assert(!this->has_synonym(syn));
        this->add_synonym_to_cur(syn);
        this->tableState = TS_AUGMENT_NEW_ROW_S;
    }
    int nrRecords = this->curRecords->size();
    if (row >= 0 && row < nrRecords) {
        Record record((*(this->curRecords))[row]);
        record.add_value(val);
        this->auxRecords->push_back(record);
    }
}

void Table::augment_new_row(int row, const string& syn, int val)
{
    assert(TS_AUGMENT_NEW_ROW == this->tableState ||
            TS_AUGMENT_NEW_ROW_I == this->tableState);
    if (TS_AUGMENT_NEW_ROW == this->tableState) {
        assert(!this->has_synonym(syn));
        this->add_synonym_to_cur(syn);
        this->tableState = TS_AUGMENT_NEW_ROW_I;
    }
    int nrRecords = this->curRecords->size();
    if (row >= 0 && row < nrRecords) {
        Record record((*(this->curRecords))[row]);
        record.add_value(val);
        this->auxRecords->push_back(record);
    }
}

void Table::freeze()
{
    assert(TS_START == this->tableState);
    this->tableState = TS_FROZEN;
}

void Table::unfreeze()
{
    assert(TS_FROZEN == this->tableState);
    this->tableState = TS_START;
}