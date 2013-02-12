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
    TS_ADD_ROW_R_R,
    TS_MARK_ROW,
    TS_AUGMENT_EXISTING_ROW, TS_AUGMENT_EXISTING_ROW_S,
    TS_AUGMENT_EXISTING_ROW_I,
    TS_AUGMENT_NEW_ROW, TS_AUGMENT_NEW_ROW_S, TS_AUGMENT_NEW_ROW_I,
    TS_FROZEN
};

class Table {
public:
    Table();
    ~Table();

    static Table* create_from_set(const std::string& syn,
            const std::set<std::string>& stringSet);
    static Table* create_from_set(const std::string& syn,
            const std::set<int>& intSet);

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
    void add_row(const std::map<int, std::string>& colToSyn,
            const Record& rec, const std::string& syn,
            const std::string& val);
    void add_row(const std::map<int, std::string>& colToSyn,
            const Record& rec, const std::string& syn, int val);
    void add_row(const std::map<int, std::string>& colToSyn,
            const Record& rec,
            const std::string& synOne, const std::string& valOne,
            const std::string& synTwo, const std::string& valTwo);
    void add_row(const std::map<int, std::string>& colToSyn,
            const Record& rec,
            const std::string& synOne, const std::string& valOne,
            const std::string& synTwo, int valTwo);
    void add_row(const std::map<int, std::string>& colToSyn,
            const Record& rec,
            const std::string& synOne, int valOne,
            const std::string& synTwo, const std::string& valTwo);
    void add_row(const std::map<int, std::string>& colToSyn,
            const Record& rec,
            const std::string& synOne, int valOne,
            const std::string& synTwo, int valTwo);
    void add_row(const std::map<int, std::string>& colToSynOne,
            const Record& recOne,
            const std::map<int, std::string>& colToSynTwo,
            const Record& recTwo);

    void mark_rows_transaction_begin();
    void mark_rows_transaction_end();
    void mark_row_ok(int row);

    void augment_existing_rows_transaction_begin();
    void augment_existing_rows_transaction_end();
    void augment_existing_row(int row, const std::string& syn,
            const std::string& val);
    void augment_existing_row(int row, const std::string& syn, int val);

    void augment_new_rows_transaction_begin();
    void augment_new_row(int row, const std::string& syn,
            const std::string& val);
    void augment_new_row(int row, const std::string& syn, int val);
    void augment_new_rows_transaction_end();

    void freeze();
    void unfreeze();

private:
    static TableState VALID_ADD_ROW_STATES_ARR[14];
    static const std::set<TableState> VALID_ADD_ROW_STATES;
    static TableState VALID_AUGMENT_EXISTING_ROW_STATES_ARR[3];
    static const std::set<TableState> VALID_AUGMENT_EXISTING_ROW_STATES;
    static TableState VALID_AUGMENT_NEW_ROW_STATES_ARR[3];
    static const std::set<TableState> VALID_AUGMENT_NEW_ROW_STATES;

    void add_row_syn_preamble(const TableState idealState,
            const std::string& syn);
    void add_row_syn_syn_preamble(const TableState idealState,
            const std::string& synOne, const std::string& synTwo);
    void add_row_record_syn_preamble(const TableState idealState,
            const std::map<int, std::string>& colToSynM,
            const std::string& syn);
    void add_row_record_syn_syn_preamble(const TableState idealState,
            const std::map<int, std::string>& colToSynM,
            const std::string& synOne, const std::string& synTwo);
    void add_synonym_to_aux(const std::string& syn);
    void add_synonym_to_cur(const std::string& syn);
    void add_synonyms_in_map(const std::map<int, std::string>& colToSynM);

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