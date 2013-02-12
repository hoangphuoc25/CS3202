#ifndef T11_RESULTS_TABLE_H
#define T11_RESULTS_TABLE_H

#include <map>
#include <set>
#include <string>
#include <vector>
#include "PQL.h"
#include "Table.h"

enum ResultsTableState {
    RTS_START, RTS_0_TRANSACT, RTS_1_TRANSACT,
    RTS_11_TRANSACT, RTS_22_TRANSACT,
    RTS_CHECKOUT
};

enum ResultsTab22Transact {
    USE_TABLE_A, USE_TABLE_B, USE_NEW_TABLE
};

enum RecordValType {
    RV_INVALID, RV_STRING, RV_INT
};

class ResultsTable {
public:
    ResultsTable();
    ResultsTable(const ResultsTable& o);
    ResultsTable& operator=(const ResultsTable& o);
    friend void swap(ResultsTable& one, ResultsTable& two);
    ~ResultsTable();

    bool has_synonym(const std::string& syn) const;
    bool is_alive() const;
    void absorb_resultsTable(const ResultsTable &o);

    void checkout_transaction_begin();
    void checkout_transaction_end();
    Table *checkout_table(const std::string& syn);

    void syn_0_transaction_begin(const std::string& syn,
            RecordValType rvType);
    void syn_0_transaction_end();
    void syn_0_add_row(const std::string& val);
    void syn_0_add_row(int val);
    const std::vector<Record>& syn_1_transaction_begin
            (const std::string& syn);
    void syn_1_transaction_end();
    void syn_1_mark_row_ok(int row);
    const std::vector<Record>& syn_11_transaction_begin(
            const std::string& synOne,
            const std::string& synTwo);
    void syn_11_transaction_end();
    std::pair<Table *, Table *>
        syn_22_transaction_begin(
            const std::string& synOne, const std::string& synTwo);
    void syn_22_transaction_end();
    void syn_22_add_row(const Table& tableOne, const Record& recOne,
            const Table& tableTwo, const Record& recTwo);

private:
    ResultsTableState state;
    std::set<Table *> tablesCheckedOut;
    Table *tableCheckedOutA;
    Table *tableCheckedOutB;
    int tableAIdx;
    int tableBIdx;
    std::string tableASyn;
    std::string tableBSyn;
    RecordValType synAType;
    RecordValType synBType;
    bool alive;
    std::map<std::string, int> synMap;
    std::map<int, Table *> tables;
    int nextTable;
};

#endif