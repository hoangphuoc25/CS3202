#ifndef T11_TABLE_H
#define T11_TABLE_H

#include <map>
#include <set>
#include <string>
#include <vector>
#include "Record.h"

enum TableState {
    TS_START,
    TS_ADD_ROW, TS_ADD_ROW_S, TS_ADD_ROW_I,
    TS_ADD_ROW_SS, TS_ADD_ROW_SI, TS_ADD_ROW_IS, TS_ADD_ROW_II,
    TS_ADD_ROW_R_S, TS_ADD_ROW_R_I,
    TS_ADD_ROW_R_SS, TS_ADD_ROW_R_SI, TS_ADD_ROW_R_IS, TS_ADD_ROW_R_II,
    TS_MARK_ROW,
    TS_AUGMENT_ROW, TS_AUGMENT_ROW_S, TS_AUGMENT_ROW_I
};

class Table {
public:
    Table();
    ~Table();
    bool is_alive() const;
    bool has_synonym(const std::string& syn) const;
    int get_synonym_column(const std::string& syn) const;
    const std::vector<Record>& get_records() const;
    const std::map<int, std::string>& get_col_to_synonym() const;
    const std::map<std::string, int>& get_synonym_to_col() const;
    void add_rows_transaction_begin();
    void add_rows_transaction_end();
    void add_row(const std::string& syn, const std::string& val);
    void add_row(const std::string& syn, int val);
    void add_row(const std::string& synOne, const std::string& valOne,
            const std::string& synTwo, const std::string& valTwo);
    void add_row(const std::string& synOne, const std::string& valOne,
            const std::string& synTwo, int valTwo);
    void add_row(const std::string& synOne, int valOne,
            const std::string& synTwo, const std::string& valTwo);
    void add_row(const std::string& synOne, int valOne,
            const std::string& synTwo, int valTwo);
    void add_row(const Table& table, const Record& rec,
            const std::string& syn, const std::string& val);
    void add_row(const Table& table, const Record& rec,
            const std::string& syn, int val);
    void add_row(const Table& table, const Record& rec,
            const std::string& synOne, const std::string& valOne,
            const std::string& synTwo, const std::string& valTwo);
    void add_row(const Table& table, const Record& rec,
            const std::string& synOne, const std::string& valOne,
            const std::string& synTwo, int valTwo);
    void add_row(const Table& table, const Record& rec,
            const std::string& synOne, int valOne,
            const std::string& synTwo, const std::string& valTwo);
    void add_row(const Table& table, const Record& rec,
            const std::string& synOne, int valOne,
            const std::string& synTwo, int valTwo);

    void mark_rows_transaction_begin();
    void mark_rows_transaction_end();
    void mark_row_ok(int row);

    void augment_rows_transaction_begin();
    void augment_rows_transaction_end();
    void augment_row(int row, const std::string& syn,
            const std::string& val);
    void augment_row(int row, const std::string& syn, int val);

private:
    static TableState VALID_ADD_ROW_STATES_ARR[13];
    static const std::set<TableState> VALID_ADD_ROW_STATES;
    static TableState VALID_AUGMENT_ROW_STATES_ARR[3];
    static const std::set<TableState> VALID_AUGMENT_ROW_STATES;

    void add_row_syn_preamble(const TableState idealState,
            const std::string& syn);
    void add_row_syn_syn_preamble(const TableState idealState,
            const std::string& synOne, const std::string& synTwo);
    void add_row_record_syn_preamble(const TableState idealState,
            const Table& table, const std::string& syn);
    void add_row_record_syn_syn_preamble(const TableState idealState,
            const Table& table, const std::string& synOne,
            const std::string& synTwo);
    void add_synonym_to_aux(const std::string& syn);
    void add_synonym_to_cur(const std::string& syn);
    void add_synonyms_in_table(const Table& table);

    enum TableState tableState;
    bool alive;
    std::vector<Record> *curRecords;
    std::vector<Record> *auxRecords;
    std::vector<Record> RECORDS[2];
    std::map<std::string, int> *curSynToCol;
    std::map<std::string, int> *auxSynToCol;
    std::map<std::string, int> SYNTOCOLS[2];
    std::map<int, std::string> *curColToSyn;
    std::map<int, std::string> *auxColToSyn;
    std::map<int, std::string> COLTOSYN[2];
    std::vector<int> preserveRow;
};

#endif