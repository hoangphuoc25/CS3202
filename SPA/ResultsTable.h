#ifndef T11_RESULTS_TABLE_H
#define T11_RESULTS_TABLE_H

#include <map>
#include <set>
#include <string>
#include <vector>
#include "PQL.h"
#include "Table.h"

/**
 * All possible states of the ResultsTable.
 * This is for internal use only.
 */
enum ResultsTableState {
    RTS_START, RTS_DEAD, RTS_0_TRANSACT, RTS_1_TRANSACT,
    RTS_00_TRANSACT,
    RTS_01_TRANSACT, RTS_10_TRANSACT,
    RTS_11_TRANSACT, RTS_22_TRANSACT,
    RTS_CHECKOUT
};

/**
 * Type of the new synonym argument being added.
 * This is used by the various ResultsTable transactions.
 */
enum RecordValType {
    RV_INVALID, RV_STRING, RV_INT
};

/**
 * Stores 0 or more Table objects used to represent PQL
 * query evaluation results.
 * Each Table object has disjoint synonyms.
 *
 * Look at the documentation for the various transaction methods
 * to identify the correct transaction method to use.
 */
class ResultsTable {
public:
    /**
     * Constructor
     */
    ResultsTable();
    /**
     * Copy constructor
     * @param o the other ResultsTable to copy
     */
    ResultsTable(const ResultsTable& o);
    /**
     * Copy assignment operator
     * @param o the other ResultsTable to copy
     * @return a reference to this ResultsTable
     */
    ResultsTable& operator=(const ResultsTable& o);
    /**
     * Used to swap two ResultsTable objects
     * @param one the first ResultsTable
     * @param two the second ResultsTable
     */
    friend void swap(ResultsTable& one, ResultsTable& two);
    /**
     * Destructor
     */
    ~ResultsTable();
    /**
     * Checks if the ResultsTable contains a given synonym
     * @param syn the name of the synonym
     * @return true if the ResultsTable contains the given
     *         synonym, false otherwise
     */
    bool has_synonym(const std::string& syn) const;
    /**
     * Checks if two given synonyms are inside the same Table
     * object.
     * @param synOne the name of the first synonym
     * @param synTwo the name of the second synonym
     * @return true if both synonyms are inside the ResultsTable
     *         (i.e ResultsTable::has_synonym(synOne) and
     *              ResultsTable::has_synonym(synTwo) are true),
     *         and both synonyms are contained in the same Table
     *         object
     */
    bool syn_in_same_table(const std::string& synOne,
            const std::string& synTwo) const;
    /**
     * Checks if the ResultsTable is alive
     * @return true if the ResultsTable is alive, false otherwise
     */
    bool is_alive() const;
    /**
     * Absorbs a given Table object.
     *\n\n
     * NOTE 1: After this method is executed, control of the input
     *         Table object is transferred to this ResultsTable.
     *         From this point onwards, all operations that need
     *         to involve the input Table need to be conducted
     *         through this ResultsTable.
     *         This also means that you do not and should not free
     *         the memory for the input Table.
     *\n\n
     * NOTE 2: The synonyms in the input Table object should not be
     *         present in the ResultsTable, ie.
     *         ResultsTable.has_synonym(syn) == false for all
     *         syn in the input Table.
     *         Otherwise, this will result in an assertion failure
     * @param table pointer to Table object to be absorbed
     */
    void absorb_table(Table *table);
    /**
     * Absorbs another ResultsTable
     *\n\n
     * NOTE 1: After this method is executed, the input ResultsTable
     *         will be empty. All information in the input ResultsTable
     *         will be transferred to this ResultsTable.
     *         The input ResultsTable will be equivalent to a newly
     *         constructed ResultsTable.
     *\n\n
     * NOTE 2: All synonyms in the input ResultsTable should not be
     *         present in this ResultsTable, ie.
     *         ResultsTable.has_synonym(syn) == false for all syn
     *         in the input ResultsTable
     * @param o the ResultsTable to absorb
     */
    void absorb_ResultsTable(ResultsTable& o);
    /**
     * Kills off the ResultsTable.
     * This sets ResultsTable::alive to false and changes
     * ResultsTable::state to RTS_DEAD, so no meaningful operations
     * can be carried out on it.
     * This is primarily used by QueryEvaluator
     */
    void kill();

    /**
     * Begins a transaction to allow Table objects containing
     * a desired synonym to be checked out.
     * This enables the checkout_table method.
     * NOTE: All Table objects checked out should be considered
     * read-only.
     */
    void checkout_transaction_begin();
    /**
     * Ends a transaction started by checkout_transaction_begin
     */
    void checkout_transaction_end();
    /**
     * Retrieves the Table containing a given synonym
     *\n\n
     * NOTE: The input synonym must exist in the ResultsTable,
     *       otherwise this will trigger an assertion failure
     * @param syn the name of the synonym
     * @return the Table* containing the synonym. The Table*
     *         will be frozen by Table::freeze
     */
    Table *checkout_table(const std::string& syn);

    /**
     * Beings a transaction to add one new synonym into the
     * ResultsTable.
     *
     * Use case:
     * <pre><code>
     *     while w; Select w such that Parent*(w,25)
     * </code></pre>
     * In the above query, we only have a single Relation clause,
     * "Parent*(w,25)". The 2nd argument of Parent* is a concrete
     * value 5, and "w" is the only synonym. Before we evaluate
     * "Parent*(w,25)", it is unseen
     * (hence 0 in syn_0_transaction_begin).
     *
     * We should retrieve the while statements which are ancestors
     * of statement 25, and add them to the ResultsTable.
     *
     * Code usage will be like this:
     * <pre><code>
     *     // obtain a ResultsTable rTable
     *     string synNew = "w";
     *     rTable.syn_0_transaction_begin(synNew, RV_INT);
     *     rTable.syn_0_add_row(23);
     *     rTable.syn_0_add_row(20);
     *     rTable.syn_0_transaction_end();
     * </code></pre>
     *
     * This method enables the overloaded syn_0_add_row methods.
     *
     * NOTE: You should stick to the same syn_0_add_row method
     *       throughout an entire transaction.
     * @param syn the new synonym. This should NOT exist inside
     *            the ResultsTable, ie.
     *            ResultsTable.has_synonym(syn) == false
     *            Otherwise this will trigger an assertion failure.
     * @param rvType type of the synonym, either RV_INT (for integers)
     *               or RV_STRING (for strings)
     */
    void syn_0_transaction_begin(const std::string& syn,
            RecordValType rvType);
    /**
     * Ends a transaction started by syn_0_transaction_begin
     */
    void syn_0_transaction_end();
    /**
     * Adds a new row containing a single string value
     * @param val string value to be added
     */
    void syn_0_add_row(const std::string& val);
    /**
     * Adds a new row containing a single integer value
     * @param val integer value to be added
     */
    void syn_0_add_row(int val);

    /**
     * Begins a transaction to possibly mark rows containing a
     * seen synonym.
     *
     * Use case:
     * <pre><code>
     *   while w; assign a; Select w such that Parent*(w,a) and
     *                        Parent(w,25)
     * </code></pre>
     *
     * Suppose we evaluate the query in textual order.
     * The clause to pay attention to in this case is the
     * "Parent(w,25)" clause.
     *
     * First, we evaluate "Parent*(w,a)". After this, the synonyms
     * "w" and "a" are seen.
     *
     * Next, we evaluate "Parent(w,25)". Note that 25 is a concrete
     * value and "w" is the only synonym in this Relation.
     *
     * We have previously encountered "w" in "Parent*(w,a)".
     * Our intention here is to preserve the rows containing "w"
     * that is a Parent of 25. Hence, we initiate this transaction
     * to mark those rows with "w" that satisfy "Parent(w,25)" as
     * rows to be preserved.
     *
     * Code Usage:
     * <pre><code>
     *     // obtain ResultsTable called "rTable" somewhere above
     *     pair<const vector<Record>*, int> viPair =
     *         rTable.syn_1_transaction("w");
     *     const vector<Record>& records = *(viPair.first);
     *     int colIdx = viPair.second;
     *     int nrRecords = records.size();
     *     for (int i = 0; i < nrRecords; i++) {
     *         const Record& record = records[i];
     *         const pair<string, int>& siPair =
     *             record.get_column(colIdx);
     *         int val = siPair.second;
     *         if (check_parent(val, 25)) {
     *             rTable.syn_1_mark_row_ok(i);
     *         }
     *     }
     *     rTable.syn_1_transaction_end();
     * </code></pre>
     *
     * This transaction enables the syn_1_mark_row_ok method.
     *
     * @param syn the name of the synonym. This synonym must be
     *            present inside the ResultsTable, ie.
     *            ResultsTable.has_synonym(syn) == true
     *            Otherwise, this will result in an assertion failure
     * @return a pair<vector<Record> *, int>. The vector<Record> *
     *         is the vector of Record objects of the Table containing
     *         the synonym, and the integer is the column index
     *         of the synonym in the Record objects.
     */
    std::pair<const std::vector<Record> *, int>
    syn_1_transaction_begin(const std::string& syn);
    /**
     * Ends a transaction started by syn_1_transaction_begin
     */
    void syn_1_transaction_end();
    /**
     * Marks a row as ok (after syn_1_transaction_begin is invoked)
     */
    void syn_1_mark_row_ok(int row);

    /**
     * Initiates a transaction where we add rows containing 2 new
     * synonyms.
     *
     * Use case:
     * <pre><code>
     *     assign a; variable v; Select a such that Modifies(a,v)
     * </code></pre>
     * In this case, we only have a single clause, "Modifies(a,v)".
     * We need to add rows containing "a" and "v" that satisfy
     * Modifies(a,v) into the ResultsTable.
     * Since "a" and "v" are both not seen, this is a 00 transaction.
     *
     * Code Usage:
     * <pre><code>
     *     // obtain a ResultsTable named "rTable" above
     *     string synOne = "a";
     *     string synTwo = "v";
     *     rTable.syn_00_transaction_begin(synOne, RV_INT,
     *         synTwo, RV_STRING);
     *     set<int> allAssign = get_all_assign();
     *     for (set<int>::const_iterator assignIt = allAssign.begin();
     *             assignIt != allAssign.end(); assignIt++) {
     *         int assignVal = *assignIt;
     *         set<string> vars = get_vars_modified_by_assign(assignVal);
     *         for (set<string>::const_iterator varIt = vars.begin();
     *                 varIt != vars.end(); varIt++) {
     *             rTable.syn_00_add_row(assignVal, *varIt);
     *         }
     *     }
     *     rTable.syn_00_transaction_end();
     * </code></pre>
     *
     * This enables the overloaded syn_00_add_row methods.
     *
     * NOTE: Please use the same syn_00_add_row method throughout
     *       the course of an entire transaction.
     *
     * NOTE: Both input synonyms must be be in the ResultsTable,
     *       ie. ResultsTable.has_synonym(synA) == false and
     *       ResultsTable.has_synonym(synB) == false.
     *       Otherwise, this will cause an assertion failure.
     *
     * @param synA the first synonym. This must not be in the
     *             ResultsTable, ie.
     *             ResultsTable.has_synoynm(synA) == false
     *             Otherwise, this will trigger an assertion failure
     * @param rvAType either RV_INT (for integers) or RV_STRING
     *                (for strings) depending on the type of value
     *                synA can take on.
     * @param synB the second synonym. This must not be in the
     *             ResultsTable, ie.
     *             ResultsTable.has_synonym(synB) == false
     *             Otherwise, this will trigger an assertion failure
     * @param rvBType either RV_INT (for integers) or RV_STRING
     *                (for strings) depending on the type of value
     *                synB can take on.
     */
    void syn_00_transaction_begin(const std::string& synA,
            RecordValType rvAType, const std::string& synB,
            RecordValType rvBType);
    /**
     * Ends a transaction started by syn_00_transaction_begin
     */
    void syn_00_transaction_end();
    /**
     * In a 00 transaction, adds a new row with 2 string values.
     * @param valA string value for first synonym
     * @param valB string value for second synonym
     */
    void syn_00_add_row(const std::string& valA, const std::string& valB);
    /**
     * In a 00 transaction, adds a new row with 1 string value and
     * 1 integer value.
     * @param valA string value for first synonym
     * @param valB integer value for second synonym
     */
    void syn_00_add_row(const std::string& valA, int valB);
    /**
     * In a 00 transaction, adds a new row with 1 integer value and
     * 1 string value.
     * @param valA integer value for first synonym
     * @param valB string value for second synonym
     */
    void syn_00_add_row(int valA, const std::string& valB);
    /**
     * In a 00 transaction, adds a new row with 2 integer values.
     * @param valA integer value for first synonym
     * @param valB integer value for second synonym
     */
    void syn_00_add_row(int valA, int valB);

    /**
     * Initiates a transaction where we have the first synonym
     * being a new synonym (0) and the second synonym being
     * a seen synonym (1), and we wish to add new rows based
     * on existing rows by augmenting them with 1 column containing
     * the values of the new synonym.
     *
     * Use case:
     * <pre><code>
     * assign a; variable v; while w;
     * Select <a,w> such that Modifies(a,v) and Parent*(w,a)
     * </code></pre>
     * We assume that the query is evaluated in textual order.
     *
     * First, we evaluate Modifies(a,v). After that, the synonyms
     * "a" and "v" are both seen.
     * Next, we evaluate Parent*(w,a). We have not seen "w" (0) but
     * we have seen "a". This is a 01 transaction.
     * We want to augment the rows with one new column for "w".
     * Therefore, this is the transaction to use.
     *
     * Code Usage:
     * <pre><code>
     *     // obtain a ResultsTable called "rTable" above
     *     string synA = "w";
     *     string synB = "a";
     *     pair<const vector<Record> *, int> viPair =
     *         rTable.syn_01_transaction_begin(synA, synB, RV_INT);
     *     const vector<Record>& records = *(viPair.first);
     *     int nrRecords = records.size();
     *     int colIdx = viPair.second;
     *     // loop through row i
     *     for (int i = 0; i < nrRecords; i++) {
     *         const Record& record = records[i];
     *         const pair<string, int>& siPair =
     *                 record.get_column(colIdx);
     *         int whileSyn = siPair.second;
     *         set<int> assignChildren =
     *                 get_all_assign_children_of_while(whileSyn);
     *         for (set<int>::const_iterator aIt = assignChildren.begin();
     *                 aIt != assignChildren.end(); aIt++) {
     *             // create a new row based using row i appended
     *             // with *aIt
     *             // After the transaction, only the augmented rows
     *             // will exist.
     *             rTable.syn_01_augment_new_row(i, *aIt);
     *         }
     *     }
     *     rTable.syn_01_transaction_end();
     * </code></pre>
     *
     * This method enables the overloaded syn_01_augment_new_row
     * methods.
     *
     * NOTE: Please stick to the same syn_01_augment_new_row method
     *       throughout the course of the transaction.
     * @param synNew the new (unseen) synonym. This must not be inside
     *               the ResultsTable, ie.
     *               ResultsTable.has_synonym(synNew) == false
     *               Otherwise, this will trigger an assertion failure
     * @param synOld the existing (seen) synonym. This must be inside
     *               the ResultsTable, ie.
     *               ResultsTable.has_synonym(synOld) == true
     *               Otherwise, this will trigger an assertion failure
     * @return a pair<const vector<Record>*, int>.
     *         The const vector<Record>* are all the rows
     *         (Record objects) from the Table containing the synOld
     *         synonym. The integer indicates the column index of the
     *         synOld synonym for the Record objects.
     */
    std::pair<const std::vector<Record> *, int>
    syn_01_transaction_begin(const std::string& synNew,
            const std::string& synOld, RecordValType rvType);
    /**
     * Ends a transaction started by syn_01_transaction_begin
     */
    void syn_01_transaction_end();
    /**
     * In a 01 transaction, creates a new row based on an
     * existing row appended with a new string value.
     * @param row the 0-indexed row of the current Table involved
     *            in the transaction. Refer to the code example
     *            in the documentation for syn_01_transaction_begin
     *            if you are unsure what this parameter means
     * @param val string value of the synonym
     */
    void syn_01_augment_new_row(int row, const std::string& val);
    /**
     * In a 01 transaction, creates a new row based on an
     * existing row appended with a new string value.
     * @param row the 0-indexed row of the current Table involved
     *            in the transaction. Refer to the code example
     *            in the documentation for syn_01_transaction_begin
     *            if you are unsure what this parameter means
     * @param val string value of the synonym
     */
    void syn_01_augment_new_row(int row, int val);

    /**
     * Initiates a transaction where the first synonym has been seen (1)
     * and the second synonym has not been seen (0).
     *
     * Use case:
     * <pre><code>
     *     while w; assign a; variable v;
     *     Select <w,a,v> such that Parent(w,a) and Uses(w,v)
     * </code></pre>
     *
     * We assume evaluation of the clauses is in textual order.
     * The Relation to focus on is "Modifies(w,v)".
     * After evaluating "Parent(w,a)" but before evaluating
     * "Modifies(w,v)", we have seen synonym "w" but not "v".
     * We should retrieve, from the ResultsTable, all the "w" that
     * satisfy the query so far, and for each "w" (each row has
     * a "w"), obtain the set of variables "v" that it uses.
     * For each "w" row, we will create a new row based on that
     * row and a new column containing "v".
     *
     * Code example:
     * <pre><code>
     *     // Get a ResultsTable named "rTable" from above
     *     string synA = "w";
     *     string synB = "v";
     *     pair<const vector<Record>*, int> viPair =
     *             rTable.syn_10_transaction_begin(synA, synB, RV_STRING);
     *     const vector<Record>& records = *(viPair.first);
     *     int nrRecords = records.size();
     *     int colIdx = viPair.second;
     *     // loop through each row
     *     for (int i = 0; i < nrRecords; i++) {
     *         const Record& record = records[i];
     *         const pair<string, int> siPair =
     *                 record.get_column(colidx);
     *         int whileSyn = siPair.second;
     *         set<string> vars = get_all_vars_used_by_while(whileSyn);
     *         for (set<string>::const_iterator varIt = vars.begin();
     *                 varIt != vars.end(); varIt++) {
     *             // create a new row based on existing row i appended
     *             // with a new value
     *             rTable.syn_10_augment_row(i, *varIt);
     *         }
     *     }
     *     rTable.syn_10_transaction_end();
     * </code></pre>
     *
     * This method enables the overloaded syn_10_augment_new_row
     * methods.
     *
     * NOTE: Please use the same syn_10_augment_new_row method
     *       throughout the course of the transaction
     *
     * @param synOld name of the old (existing) synonym. This synonym
     *               must exist in the ResultsTable, ie.
     *               ResultsTable.has_synonym(synOld) == true
     *               Otherwise this will trigger an assertion failure
     * @param synNew name of the new (unseen) synonym. This synonym
     *               must not exist in the ResultsTable, ie.
     *               ResultsTable.has_synonym(synNew) == false
     *               Otherwise this will trigger an assertion failure
     * @param rvType type of synNew, RV_INT (for integer synonym) or
     *               RV_STRING (for string synonym)
     * @return pair<const vector<Record>*,int>.
     *         The const vector<Record>* are all the rows of the
     *         Table containing synOld. The integer is the column
     *         index of the synOld synonym within the Table.
     */
    std::pair<const std::vector<Record> *, int>
    syn_10_transaction_begin(const std::string& synOld,
            const std::string& synNew, RecordValType rvType);
    /**
     * Ends a transaction started by syn_10_transaction_begin
     */
    void syn_10_transaction_end();
    /**
     * In a 10 transaction, create a new row based on an existing
     * row appended with one string value.
     * @param row 0-indexed row of the Table (containing the old
     *            synonym) to be used for creating the new row.
     *            Please refer to the code example in the
     *            documentation for syn_10_transaction if you are
     *            not sure what this parameter means.
     * @param val new string value to be appended
     */
    void syn_10_augment_new_row(int row, const std::string& val);
    /**
     * In a 10 transaction, create a new row based on an existing
     * row appended with one integer value.
     * @param row 0-indexed row of the Table (containing the old
     *            synonym) to be used for creating the new row.
     *            Please refer to the code example in the
     *            documentation for syn_10_transaction if you are
     *            not sure what this parameter means.
     * @param val new integer value to be appended
     */
    void syn_10_augment_new_row(int row, int val);

    /**
     * Initiates a transaction with 2 seen synonyms and both
     * are inside the same Table, ie.
     * ResultsTable.syn_in_same_table(synOne, synTwo) == true
     *
     * Use case:
     * <pre><code>
     *     assign a; variable v;
     *     Select <a,v> such that Modifies(a,v) and Uses(a,v)
     * </code></pre>
     *
     * We assume evaluation proceeds in textual order.
     * We shall focus on the "Uses(a,v)" Relation.
     * After evaluating "Modifies(a,v)" and before evaluating
     * "Uses(a,v)", we have seen synonyms "a" and "v".
     * Both of the are in the same Table, since they were both
     * involved in a relation ("Modifies(a,v)").
     *
     * In this case, we wish to preserve the rows where
     * Uses(a,v) is satisfied. Both synonyms are seen and in
     * the same Table, hence this is a syn_11 transaction.
     *
     * Code example:
     * <pre><code>
     *     // obtain a ResultsTable called "rTable" above
     *     string synOne = "a";
     *     string synTwo = "v";
     *     pair<const vector<Record>*, pair<int, int> > viiPair =
     *             rTable.syn_11_transaction_begin(synOne, synTwo);
     *     const vector<Record>& records = *(viiPair.first);
     *     int nrRecords = records.size();
     *     int colA = viiPair.second.first;
     *     int colB = viiPair.second.second;
     *     for (int i = 0; i < nrRecords; i++) {
     *         const Record& record = records[i];
     *         const pair<string, int> pairA =
     *                 record.get_column(colA);
     *         int assignSyn = pairA.second;
     *         const pair<string, int> pairB =
     *                 record.get_column(colB);
     *         const string& varName = pairB.first;
     *         // preserve row i since it satisfies Uses(a,v)
     *         if (assign_uses_var(assignSyn, varName)) {
     *             rTable.syn_11_mark_row_ok(i);
     *         }
     *     }
     *     rTable.syn_11_transaction_end();
     * </code></pre>
     *
     * This method enables the use of syn_11_mark_row_ok
     *
     * NOTE: Both synOne and synTwo must exist in the ResultsTable
     *       and belong to the same Table, ie.
     *       ResultsTable.syn_in_same_table(synOne, synTwo) == true
     *       Otherwise, this will trigger an assertion failure
     *
     * @param synOne name of the first synonym. This synonym
     *               must exist in the ResultsTable, ie.
     *               ResultsTable.has_synonym(synOne) == true
     *               Otherwise, this will trigger an assertion failure
     * @param synTwo name of the second synonym. This synonym must
     *               exist in the ResultsTable, ie.
     *               ResultsTable.has_synonym(synTwo) == true
     *               Otherwise, this will trigger an assertion failure
     * @return pair<const vector<Record>*, pair<int,int> >
     *         The const vector<Record>* is the vector containing
     *         all the rows for the Table involved in this transaction
     *         (the Table for the synonyms synOne and synTwo).
     *         The pair<int, int>'s fields refer to the column indices
     *         for synOne and synTwo respectively.
     */
    std::pair<const std::vector<Record> *, std::pair<int, int> >
    syn_11_transaction_begin(const std::string& synOne,
            const std::string& synTwo);
    /**
     * Ends a transaction started by syn_11_transaction_begin
     */
    void syn_11_transaction_end();
    /**
     * In a 11 transaction, marks an existing row as to be preserved.
     * @param row 0-indexed row of an existing row in the Table to
     *            be preserved. If you are not sure what this parameter
     *            means, please refer to the code example in the
     *            documentation for the syn_11_transaction_begin method.
     */
    void syn_11_mark_row_ok(int row);

    /**
     * Initiates a transaction where both synonyms are seen but
     * in different tables, ie. ResultsTable.has_synonym(synOne) == true
     * and ResultsTable.has_synonym(synTwo) == true, but
     * ResultsTable.syn_in_same_table(synOne, synTwo) == false.
     *
     * Use case:
     * <pre><code>
     *     procedure proc1, proc2; assign a; variable v;
     *     Select proc1 such that Calls(proc1, proc2) and
     *         Modifies(a,v) and Modifies(proc2,v)
     * </code></pre>
     *
     * We assume query evaluation proceeds in textual order.
     * The Relation to focus on is "Modifies(proc2,v)".
     * After evaluating "Calls(proc1,proc2)" and "Modifies(a,v)"
     * but before evaluating "Modifies(proc2,v)", we have seen
     * "proc1", "proc2", "a", "v".
     * However, the tables for (proc1,proc2) and (a,v) are
     * disjoint.
     * We will need to do a cross product to see which proc2
     * modify v
     * This calls for a 22 transaction.
     *
     * Code example:
     * <pre><code>
     *     // obtain a ResultsTable named "rTable" above
     *     string synOne = "proc2";
     *     string synTwo = "v";
     *     pair<pair<const vector<Record>*, int>,
     *          pair<const vector<Record>*, int> > viviPair =
     *             rTable.syn_22_transaction_begin(synOne, synTwo);
     *     const vector<Record>& vecOne = *(viviPair.first.first);
     *     int nrVecOne = vecOne.size();
     *     int colOne = viviPair.first.second;
     *     const vector<Record>& vecTwo = *(viviPair.second.first);
     *     int nrVecTwo = vecTwo.size();
     *     int colTwo = viviPair.second.second;
     *     // Micro-optimization. Collect all argument 2 first.
     *     // The accumulation into a vector can be skipped if you
     *     // do it inside the inner loop of the second loop in
     *     // this code snippet but that is likely going to be
     *     // less efficient than this
     *     vector<string *> varVec;
     *     for (int i = 0; i < nrVecTwo; i++) {
     *         const Record& record = vecTwo[i];
     *         const pair<string, int>& siPair =
     *                 record.get_column(colTwo);
     *         varVec.push_back(&(siPair.first));
     *     }
     *     for (int i = 0; i < nrVecOne; i++) {
     *         const Record& recOne = vecOne[i];
     *         const pair<string, int>& siPair =
     *                recOne.get_column(colone);
     *         const string& procName = recOne.first;
     *         for (int k = 0; k < nrVecTwo; k++) {
     *             const string& varName = *(varVec[k]);
     *             // create a new row by merging the row i of
     *             // the first Table and row k of the second Table
     *             if (procedure_uses_var(procName, varName)) {
     *                 rTable.syn_22_add_row(i, k);
     *             }
     *         }
     *     }
     *     rTable.syn_22_transaction_end();
     * </code></pre>
     *
     * This method enables the overloaded syn_22_add_row methods.
     *
     * NOTE: You should stick to the same syn_22_add_row methods
     *       throughout the course of this transaction.
     * NOTE: It is highly recommended for you to use the
     *       syn_22_add_row method which takes in two integer arguments
     *       instead of the one taking in two Record arguments.
     *
     * @param synOne the name of the first synonym
     * @param synTwo the name of the second synonym
     * @return pair<pair<const vector<Record>*, int>,
     *              pair<const vector<Record>*, int> >
     *         The first pair in this pair represents the Record
     *         entries and column index for the first Table (which
     *         houses synOne), and the second pair works similarly
     *         for synTwo.
     */
    std::pair<std::pair<const std::vector<Record> *, int>,
              std::pair<const std::vector<Record> *, int> >
    syn_22_transaction_begin(const std::string& synOne,
            const std::string& synTwo);
    /**
     * Ends a transaction started by syn_22_transaction_begin
     */
    void syn_22_transaction_end();
    /**
     * In a 22 transaction, adds a new row based on two Record objects.
     * NOTE: You are advised to use the syn_22_add_row method taking
     *       in 2 integer arguments instead of this method.
     * @param recOne first Record object
     * @param recTwo second Record object
     */
    void syn_22_add_row(const Record& recOne, const Record& recTwo);
    /**
     * In a 22 transaction, adds a new row by merging rowOne from
     * the first Table and rowTwo from the second Table
     * @param rowOne 0-indexed row of the first Table (containing synOne)
     *        in this transaction. If you are unsure of what this
     *        parameter means, please refer to the code example in the
     *        documentation for syn_22_transaction_begin
     * @param rowTwo 0-indexed row of the second Table (contaning synTwo)
     *        in this transaction. If you are unsure of what this
     *        parameter means, please refer to the code example in the
     *        documentation for syn_22_transaction_begin
     */
    void syn_22_add_row(int rowOne, int rowTwo);

private:
    /**
     * Represents the state the ResultsTable is in.
     */
    ResultsTableState state;
    /**
     * Used by checkout_transaction to keep track of the
     * Table objects checked out for reading purposes.
     */
    std::set<Table *> tablesCheckedOut;
    /**
     * Indicates the Table containing the first synonym.
     * This is uUsed by the various transaction methods.
     */
    Table *tableCheckedOutA;
    /**
     * Indicates the Table containing the second synonym.
     * This is used by the various transaction methods.
     */
    Table *tableCheckedOutB;
    /**
     * Indicates the index of the Table containing the first synonym.
     * This is used by the various transaction methods.
     */
    int tableAIdx;
    /**
     * Indicates the index of the Table containing the second synonym.
     * This is used by the various transaction methods.
     */
    int tableBIdx;
    /**
     * Indicates the synonym tableCheckedOutA is being checked out on.
     * This is used by the various transaction methods.
     */
    std::string tableASyn;
    /**
     * Indicates the synonym tableCheckedOutB is being checked out on.
     * This is used by the various transaction methods.
     */
    std::string tableBSyn;
    /**
     * type of tableASyn
     */
    RecordValType synAType;
    /**
     * type of tableBSyn
     */
    RecordValType synBType;
    /**
     * true if the ResultsTable is alive, false otherwise
     */
    bool alive;
    /**
     * Synonym to Table index mapping
     */
    std::map<std::string, int> synMap;
    /**
     * Table index to Table mapping.
     * The reason for using a map instead of a vector or array
     * is because this simplifies matters when we need to destroy
     * Table objects.
     */
    std::map<int, Table *> tables;
    /**
     * The index of the next Table to be added to ResultsTable::tables
     */
    int nextTable;
};

#endif