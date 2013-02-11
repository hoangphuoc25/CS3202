#ifndef T11_RESULTS_TABLE_H
#define T11_RESULTS_TABLE_H

#include <map>
#include <string>
#include <vector>
#include "PQL.h"
#include "Table.h"

enum ResultsTableState {
    RTS_START, RTS_0_TRANSACT, RTS_1_TRANSACT,
    RTS_11_TRANSACT, RTS_22_TRANSACT
};

enum ResultsTab22Transact {
    USE_TABLE_A, USE_TABLE_B, USE_NEW_TABLE
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
    Table* retrieve_table_for_synonym(const std::string& syn);
    void absorb_resultsTable(const ResultsTable &o);

    Table* syn_0_transaction_begin(const std::string& syn);
    void syn_0_transaction_end();
    Table* syn_1_transaction_begin(const std::string& syn);
    void syn_1_transaction_end();
    Table* syn_11_transaction_begin(const std::string& synOne,
            const std::string& synTwo);
    void syn_11_transaction_end();
    std::pair<Table *, Table *> syn_22_transaction_begin(
            const std::string& synOne, const std::string& synTwo);
    void syn_22_transaction_end(Table *endTable,
            ResultsTab22Transact which,
            const std::string& synOne, const std::string& synTwo);
    void syn_22_transaction_end_redirect_synonyms(int dest, int src);

private:
    ResultsTableState state;
    int tableCheckedOutA;
    int tableCheckedOutB;
    bool alive;
    std::map<std::string, int> synMap;
    std::map<int, Table *> tables;
    int nextTable;
};

#endif