#ifndef T11_TABLE_H
#define T11_TABLE_H

#include <map>
#include <set>
#include <string>
#include <vector>
#include "Record.h"

/**
 * An internally used enumeration representing the state of a Table.
 */
enum TableState {
    TS_START,
    TS_ADD_ROW,
    TS_ADD_ROW_S,
    TS_ADD_ROW_I,
    TS_ADD_ROW_SS,
    TS_ADD_ROW_SI,
    TS_ADD_ROW_IS,
    TS_ADD_ROW_II,
    TS_ADD_ROW_R_S,
    TS_ADD_ROW_R_I,
    TS_ADD_ROW_R_SS,
    TS_ADD_ROW_R_SI,
    TS_ADD_ROW_R_IS,
    TS_ADD_ROW_R_II,
    TS_ADD_ROW_R_R,
    TS_MARK_ROW,
    TS_AUGMENT_EXISTING_ROW,
    TS_AUGMENT_EXISTING_ROW_S,
    TS_AUGMENT_EXISTING_ROW_I,
    TS_AUGMENT_NEW_ROW,
    TS_AUGMENT_NEW_ROW_S,
    TS_AUGMENT_NEW_ROW_I,
    TS_FROZEN
};

/**
 * A collection of Record objects, with each Record representing a
 * row in the Table. All Record objects in the same Table have the
 * same columns (and hence same number of values).
 */
class Table {
public:
    /**
     * Constructor
     */
    Table();

    /**
     * Destructor
     */
    ~Table();

    /**
     * Creates a Table for a string synonym.
     * This is used by the ResultsProjector when it encounters
     * an unseen string synonym.
     * @param syn the synonym of type string
     * @param stringSet a set of strings containing the values of
     *                  the synonym
     * @return a Table* containing solely the values of the
     *         string synonym
     */
    static Table* create_from_set(const std::string& syn,
            const std::set<std::string>& stringSet);

    /**
     * Creates a Table for an integer synonym.
     * This is used by the ResultsProjector when it encounters
     * an unseen integer synonym.
     * @param syn the synonym of type int
     * @param intSet a set of integers containing the values of
     *               the synonym
     * @return a Table* containing solely the values of the
     *         integer synonym
     */
    static Table* create_from_set(const std::string& syn,
            const std::set<int>& intSet);

    /**
     * Checks if the Table is alive.
     * @return true if the Table is alive, false otherwise
     */
    bool is_alive() const;

    /**
     * Checks if the Table contains the synonym
     * @param syn the name of the synonym
     * @return true if the Table contains the synonym, false
     *         otherwise
     */
    bool has_synonym(const std::string& syn) const;

    /**
     * Retrieves the 0-indexed column a given synonym
     * @param syn the name of the synonym
     * @return the column of the synonym if it is inside the
     *         Table, -1 otherwise
     */
    int get_synonym_column(const std::string& syn) const;

    /**
     * Retrieves all the Record objects in the Table
     * @return a reference to a const vector containing all the
     *          Record objects in the Table
     */
    const std::vector<Record>& get_records() const;

    /**
     * Retrieves the column to synonym map for the Table.
     * The columns are 0-indexed.
     * @return a reference to const map<int, string> representing
     *          the column number to synonym mapping of the Table
     */
    const std::map<int, std::string>& get_col_to_synonym() const;

    /**
     * Retrieves the synonym to column number map for the Table.
     * The columns are 0-indexed.
     * @return a reference to const map<string,int> representing
     *          the synonym to column mapping of the Table
     */
    const std::map<std::string, int>& get_synonym_to_col() const;

    /**
     * Initiates a transaction to add new rows to the Table.
     * This should only be used by the ResultsTable, otherwise it
     * is assumed that you know what you are doing.
     * The methods enabled by this transaction are the various
     * overloaded add_row methods. However, you should ensure that
     * you use the same add_row method throughout the entire
     * transaction, and use the same synonym(s).
     */
    void add_rows_transaction_begin();

    /**
     * Ends a transaction started by add_rows_transaction_begin
     */
    void add_rows_transaction_end();

    /**
     * Adds a row containing a single string value to the Table.
     * @param syn the name of the synonym
     * @param val the string value of the synonym
     */
    void add_row(const std::string& syn, const std::string& val);

    /**
     * Adds a row containing a single integer value to the Table.
     * @param syn the name of the synonym
     * @param val the integer value of the synonym
     */
    void add_row(const std::string& syn, int val);

    /**
     * Adds a row containing two string values to the Table.
     * NOTE: synOne and synTwo must be different; otherwise this will
     *       result in an assertion failure.
     * @param synOne name of the first synonym
     * @param valOne string value of the first synonym
     * @param synTwo name of the second synonym
     * @param valTwo string value of the second synonym
     */
    void add_row(const std::string& synOne, const std::string& valOne,
            const std::string& synTwo, const std::string& valTwo);

    /**
     * Adds a row containing one string and one integer to the Table.
     * NOTE: synOne and synTwo must be different; otherwise this will
     *       result in an assertion failure.
     * @param synOne name of the first synonym
     * @param valOne string value of the first synonym
     * @param synTwo name of the second synonym
     * @param valTwo integer value of the second synonym
     */
    void add_row(const std::string& synOne, const std::string& valOne,
            const std::string& synTwo, int valTwo);

    /**
     * Adds a row containing one integer and one string to the Table.
     * NOTE: synOne and synTwo must be different; otherwise this will
     *       result in an assertion failure.
     * @param synOne name of the first synonym
     * @param valOne integer value of the first synonym
     * @param synTwo name of the second synonym
     * @param valTwo string value of the second synonym
     */
    void add_row(const std::string& synOne, int valOne,
            const std::string& synTwo, const std::string& valTwo);

    /**
     * Adds a row containing two integer values to the Table.
     * NOTE: synOne and synTwo must be different; otherwise this will
     *       result in an assertion failure.
     * @param synOne name of the first synonym
     * @param valOne integer value of the first synonym
     * @param synTwo name of the second synonym
     * @param valTwo integer value of the second synonym
     */
    void add_row(const std::string& synOne, int valOne,
            const std::string& synTwo, int valTwo);

    /**
     * Adds the values of a Record and a new string value to the
     * Table. For instance, if you have a Record with 2 synonym
     * values "a1" and "v1", and the other synonym supplied to
     * this method is named "w1", then your Table should be used
     * to represent Record objects with 3 columns: "a1", "v1" and
     * "w1".
     * NOTE: The synonyms in the Record object and the argument
     *       "syn" must all be different synonyms. Otherwise, this
     *       will result in an assertion failure.
     * @param colToSyn the column to synonym mapping for the
     *        Record
     * @param rec the Record to be added
     * @param syn the name of the synonym
     * @param val the string value of the synonym
     */
    void add_row(const std::map<int, std::string>& colToSyn,
            const Record& rec, const std::string& syn,
            const std::string& val);

    /**
     * Adds the values of a Record and a new integer value to the
     * Table. For instance, if you have a Record with 2 synonym
     * values "a1" and "v1", and the other synonym supplied to
     * this method is named "w1", then your Table should be used
     * to represent Record objects with 3 columns: "a1", "v1" and
     * "w1".
     * NOTE: The synonyms in the Record object and the argument
     *       "syn" must all be different synonyms. Otherwise, this
     *       will result in an assertion failure.
     * @param colToSyn the column to synonym mapping for the
     *        Record
     * @param rec the Record to be added
     * @param syn the name of the synonym
     * @param val the integer value of the synonym
     */
    void add_row(const std::map<int, std::string>& colToSyn,
            const Record& rec, const std::string& syn, int val);

    /**
     * Adds the values of a Record and two new string values to the
     * Table. For instance, if you have a Record with 2 synonym
     * values "a1" and "v1", and the other two synonyms supplied to
     * this method are named "c1" and "w1", then your Table should
     * be used to represent Record objects with 4 columns: "a1",
     * "v1" , "c1" and "w1".
     * NOTE: The synonyms in the Record object and the arguments
     *       "synOne", "synTwo" must all be different synonyms.
     *       Otherwise, this will result in an assertion failure.
     * @param colToSyn the column to synonym mapping for the
     *        Record
     * @param rec the Record to be first added
     * @param synOne the name of the first new synonym
     * @param valOne the string value of the first new synonym
     * @param synTwo the name of the second new synonym
     * @param valTwo the string value of the second new synonym
     */
    void add_row(const std::map<int, std::string>& colToSyn,
            const Record& rec,
            const std::string& synOne, const std::string& valOne,
            const std::string& synTwo, const std::string& valTwo);

    /**
     * Adds the values of a Record and two new values (the first a
     * string, the second an integer) to the Table.
     * For instance, if you have a Record with 2 synonym
     * values "a1" and "v1", and the other two synonyms supplied to
     * this method are named "c1" and "w1", then your Table should
     * be used to represent Record objects with 4 columns: "a1",
     * "v1" , "c1" and "w1".
     * NOTE: The synonyms in the Record object and the arguments
     *       "synOne", "synTwo" must all be different synonyms.
     *       Otherwise, this will result in an assertion failure.
     * @param colToSyn the column to synonym mapping for the
     *        Record
     * @param rec the Record to be first added
     * @param synOne the name of the first new synonym
     * @param valOne the string value of the first new synonym
     * @param synTwo the name of the second new synonym
     * @param valTwo the integer value of the second new synonym
     */
    void add_row(const std::map<int, std::string>& colToSyn,
            const Record& rec,
            const std::string& synOne, const std::string& valOne,
            const std::string& synTwo, int valTwo);

    /**
     * Adds the values of a Record and two new values (the first a
     * string, the second an integer) to the Table.
     * For instance, if you have a Record with 2 synonym
     * values "a1" and "v1", and the other two synonyms supplied to
     * this method are named "c1" and "w1", then your Table should
     * be used to represent Record objects with 4 columns: "a1",
     * "v1" , "c1" and "w1".
     * NOTE: The synonyms in the Record object and the arguments
     *       "synOne", "synTwo" must all be different synonyms.
     *       Otherwise, this will result in an assertion failure.
     * @param colToSyn the column to synonym mapping for the
     *        Record
     * @param rec the Record to be first added
     * @param synOne the name of the first new synonym
     * @param valOne the integer value of the first new synonym
     * @param synTwo the name of the second new synonym
     * @param valTwo the string value of the second new synonym
     */
    void add_row(const std::map<int, std::string>& colToSyn,
            const Record& rec,
            const std::string& synOne, int valOne,
            const std::string& synTwo, const std::string& valTwo);

    /**
     * Adds the values of a Record and two new values (the first a
     * string, the second an integer) to the Table.
     * For instance, if you have a Record with 2 synonym
     * values "a1" and "v1", and the other two synonyms supplied to
     * this method are named "c1" and "w1", then your Table should
     * be used to represent Record objects with 4 columns: "a1",
     * "v1" , "c1" and "w1".
     * NOTE: The synonyms in the Record object and the arguments
     *       "synOne", "synTwo" must all be different synonyms.
     *       Otherwise, this will result in an assertion failure.
     * @param colToSyn the column to synonym mapping for the
     *        Record
     * @param rec the Record to be first added
     * @param synOne the name of the first new synonym
     * @param valOne the integer value of the first new synonym
     * @param synTwo the name of the second new synonym
     * @param valTwo the integer value of the second new synonym
     */
    void add_row(const std::map<int, std::string>& colToSyn,
            const Record& rec,
            const std::string& synOne, int valOne,
            const std::string& synTwo, int valTwo);

    /**
     * Adds the values of two Record objects to the Table.
     * For instance, if the first Record has columns "w1", "c2",
     * "a4" and "if3", and the second Record has columns "proc1",
     * "avar" and "s1", then the Table should be used to represent
     * Record objects with the following columns: "w1", "c2", "a4",
     * "if3", "proc1", "avar", "s1".
     * NOTE: The synonyms in the two Record objects must all be
     *       different synonyms. Otherwise, this will result in an
     *       assertion failure.
     * @param colToSyn the column to synonym mapping for the
     *        Record
     * @param rec the Record to be first added
     * @param synOne the name of the first new synonym
     * @param valOne the integer value of the first new synonym
     * @param synTwo the name of the second new synonym
     * @param valTwo the string value of the second new synonym
     */
    void add_row(const std::map<int, std::string>& colToSynOne,
            const Record& recOne,
            const std::map<int, std::string>& colToSynTwo,
            const Record& recTwo);

    /**
     * Start a transaction for marking rows to be preserved.
     * This should only be used by ResultsTable unless you know
     * what you are doing.
     * The mark_row_ok method is enabled after this method.
     */
    void mark_rows_transaction_begin();

    /**
     * Stops a transaction started by mark_rows_transaction_begin
     */
    void mark_rows_transaction_end();

    /**
     * Marks a row as ok
     */
    void mark_row_ok(int row);

    /**
     * Starts a transaction to add 1 additional column to the Table
     * by augmenting existing rows with 1 additional synonym.
     * This is very similar to augment_new_rows_transaction_begin,
     * except that this transaction assumes that you will only be
     * augmenting an existing row at most once.
     *
     * This should only be used by the ResultsTable unless you know
     * what you are doing.
     * The overloaded augment_existing_row methods are enabled by
     * this method. Please ensure that you use the same
     * augment_existing_row method and the same synonym argument
     * throughout the entire transaction.
     */
    void augment_existing_rows_transaction_begin();

    /**
     * Ends a transaction started by
     * augment_existing_rows_transaction_begin
     */
    void augment_existing_rows_transaction_end();

    /**
     * Augments an existing row with a string value
     * @param row the 0-indexed row to be augmented
     * @param syn the name of the synonym
     * @param val the string value of the synonym
     */
    void augment_existing_row(int row, const std::string& syn,
            const std::string& val);

    /**
     * Augments an existing row with an integer value
     * @param row the 0-indexed row to be augmented
     * @param syn the name of the synonym
     * @param val the string value of the synonym
     */
    void augment_existing_row(int row, const std::string& syn, int val);

    /**
     * Starts a transaction to add 1 additional column to the Table
     * by augmenting existing rows with 1 additional synonym.
     * This transaction is very similar to
     * augment_existing_transaction_begin, except that this transaction
     * assumes that you may need to augment the same row more than once.
     *
     * This method should only be used by the ResultsTable, otherwise
     * it is assumed that you know what you are doing.
     * The methods enabled by this method are the overloaded
     * augment_new_row methods.
     * Please use the same synonym for the augment_new_row methods
     * throughout the entire transaction.
     */
    void augment_new_rows_transaction_begin();

    /**
     * Creates a new row from an existing row by adding a string value
     * @param row the 0-indexed row to be used as a basis
     *            for augmentation
     * @param syn the name of the new synonym
     * @param val the string value of the synonym
     */
    void augment_new_row(int row, const std::string& syn,
            const std::string& val);

    /**
     * Creates a new row from an existing row by adding a string value
     * @param row the 0-indexed row to be used as a basis
     *            for augmentation
     * @param syn the name of the new synonym
     * @param val the integer value of the synonym
     */
    void augment_new_row(int row, const std::string& syn, int val);

    /**
     * Ends a transaction started by augment_new_rows_transaction_begin
     */
    void augment_new_rows_transaction_end();

    /**
     * Freezes the Table so it cannot be modified until it is
     * thawed by the unfreeze method
     */
    void freeze();

    /**
     * Unfreeze the Table so it can be modified.
     */
    void unfreeze();

private:
    /**
     * The array of valid TableState for an add_row_transaction and
     * the add_row methods.
     */
    static TableState VALID_ADD_ROW_STATES_ARR[14];
    /**
     * The set of valid TableState for an add_row_transaction and
     * the add_row methods. This is initialized from
     * VALID_ADD_ROW_STATES_ARR
     */
    static const std::set<TableState> VALID_ADD_ROW_STATES;
    /**
     * The array of valid TableState for an
     * augment_existing_rows_transaction and augment_existing_row
     * methods.
     */
    static TableState VALID_AUGMENT_EXISTING_ROW_STATES_ARR[3];
    /**
     * The set of valid TableState for an
     * augment_existing_rows_transaction and augment_existing_row
     * methods.
     * This is initialized from VALID_AUGMENT_EXISTING_ROW_STATES_ARR
     */
    static const std::set<TableState> VALID_AUGMENT_EXISTING_ROW_STATES;
    /**
     * The array of valid TableState for an
     * augment_new_rows_transaction and augment_new_row methods.
     */
    static TableState VALID_AUGMENT_NEW_ROW_STATES_ARR[3];
    /**
     * The set of valid TableState for an
     * augment_new_rows_transaction and augment_new_row methods.
     * This is initialized from VALID_AUGMENT_NEW_ROW_STATES_ARR
     */
    static const std::set<TableState> VALID_AUGMENT_NEW_ROW_STATES;

    /**
     * Used as a preamble to the add_row method with one synonym.
     * This ensures that:
     * 1. The Table is in a correct state (in VALID_ADD_ROW_STATES)
     * 2. If we are calling the add_row method for the first time,
     *    that some invariants are satisfied.
     * Refer to the implementation for more details.
     * @param idealState the state the Table should be in after this
     *                   method is executed
     * @param syn the name of the synonym argument
     */
    void add_row_syn_preamble(const TableState idealState,
            const std::string& syn);
    /**
     * Used as a preamble to the add_row method with two synonyms.
     * This ensures that:
     * 1. The Table is in a correct state (in VALID_ADD_ROW_STATES)
     * 2. If we are calling the add_row method for the first time,
     *    that some invariants are satisfied.
     * Refer to the implementation for more details.
     * @param idealState the state the Table should be in after this
     *                   method is executed
     * @param synOne the name of the first synonym
     * @param synTwo the name of the second synonym
     */
    void add_row_syn_syn_preamble(const TableState idealState,
            const std::string& synOne, const std::string& synTwo);
    /**
     * Used as a preamble to the add_row method with one Record and
     * one synonym.
     * This ensures that:
     * 1. The Table is in a correct state (in VALID_ADD_ROW_STATES)
     * 2. If we are calling the add_row method for the first time,
     *    that some invariants are satisfied.
     * Refer to the implementation for more details.
     * @param idealState the state the Table should be in after this
     *                   method is executed
     * @param colToSynM the column to synonym mapping for the Record
     * @param syn the name of the synonym argument
     */
    void add_row_record_syn_preamble(const TableState idealState,
            const std::map<int, std::string>& colToSynM,
            const std::string& syn);
    /**
     * Used as a preamble to the add_row method with one Record and
     * two synonyms.
     * This ensures that:
     * 1. The Table is in a correct state (in VALID_ADD_ROW_STATES)
     * 2. If we are calling the add_row method for the first time,
     *    that some invariants are satisfied.
     * Refer to the implementation for more details.
     * @param idealState the state the Table should be in after this
     *                   method is executed
     * @param colToSynM the column to synonym mapping for the Record
     * @param synOne the name of the first synonym argument
     * @param synTwo the name of the second synonym argument
     */
    void add_row_record_syn_syn_preamble(const TableState idealState,
            const std::map<int, std::string>& colToSynM,
            const std::string& synOne, const std::string& synTwo);
    /**
     * Adds the synonym of the auxiliary synonym map
     * @param syn the name of the synonym
     */
    void add_synonym_to_aux(const std::string& syn);
    /**
     * Adds the synonym to the current synonym map
     * @param syn the name of the synonym
     */
    void add_synonym_to_cur(const std::string& syn);
    /**
     * Adds all the synonyms in the argument map to the auxiliary
     * synonym map
     * @param colToSynM a column to synonym mapping
     */
    void add_synonyms_in_map(const std::map<int, std::string>& colToSynM);

    /**
     * Current state of the Table
     */
    enum TableState tableState;
    /**
     * true if the Table is alive, false if the Table is dead
     */
    bool alive;
    /**
     * Current Record objects.
     * This is a pointer to either entry 0 or 1 of the RECORDS field.
     */
    std::vector<Record> *curRecords;
    /**
     * Auxiliary Record objects.
     * This is used for transaction purposes
     * This is a pointer to either entry 0 or 1 of the RECORDS field.
     */
    std::vector<Record> *auxRecords;
    /**
     * Array of 2 vector<Record>. This is not used directly.
     * Instead, one of its entries is pointed to by curRecords,
     * the other by auxRecords
     */
    std::vector<Record> RECORDS[2];
    /**
     * Current synonym to column index mapping (0-indexed).
     * This is a pointer to either entry 0 or 1 of the SYNTOCOLS
     * field.
     */
    std::map<std::string, int> *curSynToCol;
    /**
     * Auxiliary synonym to column index mapping (0-indexed).
     * This is used for transaction purposes.
     * This is a pointer to either entry 0 or 1 of the SYNTOCOLS
     * field.
     */
    std::map<std::string, int> *auxSynToCol;
    /**
     * Array of 2 map<string,int>. This is not used directly.
     * Instead, one of its entries is pointed to by curSynToCol,
     * the other by auxSynToCol.
     */
    std::map<std::string, int> SYNTOCOLS[2];
    /**
     * Current column to synonym mapping (0-indexed).
     * This is a pointer to either entry 0 or 1 of the COLTOSYN
     * field.
     */
    std::map<int, std::string> *curColToSyn;
    /**
     * Auxiliary column to synonym mapping (0-indexed).
     * This is used for transaction purposes.
     * This is a pointer to either entry 0 or 1 of the COLTOSYN
     * field.
     */
    std::map<int, std::string> *auxColToSyn;
    /**
     * Array of 2 map<int,string>. This is not used directly.
     * Instead, one of its entries is pointed to by curColToSyn,
     * the other by auxColToSyn.
     */
    std::map<int, std::string> COLTOSYN[2];
    /**
     * Used by mark_row_transaction, augment_existing_rows_transaction
     * to indicate if a row is to be preserved.
     */
    std::vector<int> preserveRow;
};

#endif