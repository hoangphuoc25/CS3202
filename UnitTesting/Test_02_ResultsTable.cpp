#include <string>
#include <map>
#include <vector>

#include "../SPA/ResultsTable.h"
#include "Test_02_ResultsTable.h"

using std::map;
using std::string;
using std::vector;

void Test_02_ResultsTable::setUp() {}
void Test_02_ResultsTable::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test_02_ResultsTable);

void Test_02_ResultsTable::test_syn_0_transaction()
{
    ResultsTable rTable;
    Table *table = rTable.syn_0_transaction_begin("firstCol");
    CPPUNIT_ASSERT_EQUAL(true, table->is_alive());
    table->add_rows_transaction_begin();
    table->add_row("firstCol", "valOne");
    table->add_row("firstCol", "valTwo");
    table->add_row("firstCol", "valThree");
    table->add_rows_transaction_end();
    rTable.syn_0_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, rTable.is_alive());
    CPPUNIT_ASSERT_EQUAL(true, rTable.has_synonym("firstCol"));
    Table *tableTwo = rTable.retrieve_table_for_synonym("firstCol");
    CPPUNIT_ASSERT_EQUAL(table, tableTwo);
    const map<int, string>& colToSyn = tableTwo->get_col_to_synonym();
    CPPUNIT_ASSERT_EQUAL(1, (int)colToSyn.size());
    map<int, string>::const_iterator isIt = colToSyn.find(0);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("firstCol"), isIt->second);
    const map<string, int>& synToCol = tableTwo->get_synonym_to_col();
    CPPUNIT_ASSERT_EQUAL(1, (int)synToCol.size());
    map<string, int>::const_iterator siIt = synToCol.find("firstCol");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(0, siIt->second);
    const vector<Record>& records = tableTwo->get_records();
    CPPUNIT_ASSERT_EQUAL(3, (int)records.size());
    Record record;
    record.reset();
    record.add_value("valOne");
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_value("valTwo");
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
    record.reset();
    record.add_value("valThree");
    CPPUNIT_ASSERT_EQUAL(record, records[2]);
}

void Test_02_ResultsTable::test_syn_1_transaction()
{
    ResultsTable rTable;
    Table *table = rTable.syn_0_transaction_begin("firstCol");
    CPPUNIT_ASSERT_EQUAL(true, table->is_alive());
    table->add_rows_transaction_begin();
    table->add_row("firstCol", "valOne");
    table->add_row("firstCol", "valTwo");
    table->add_row("firstCol", "valThree");
    table->add_rows_transaction_end();
    rTable.syn_0_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, rTable.is_alive());

    Table *tableTwo = rTable.syn_1_transaction_begin("firstCol");
    CPPUNIT_ASSERT_EQUAL(table, tableTwo);
    tableTwo->mark_rows_transaction_begin();
    tableTwo->mark_row_ok(1);
    tableTwo->mark_rows_transaction_end();
    rTable.syn_1_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, rTable.is_alive());

    tableTwo = rTable.retrieve_table_for_synonym("firstCol");
    CPPUNIT_ASSERT_EQUAL(table, tableTwo);
    const map<int, string>& colToSyn = tableTwo->get_col_to_synonym();
    CPPUNIT_ASSERT_EQUAL(1, (int)colToSyn.size());
    map<int, string>::const_iterator isIt = colToSyn.find(0);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("firstCol"), isIt->second);
    const map<string, int>& synToCol = tableTwo->get_synonym_to_col();
    CPPUNIT_ASSERT_EQUAL(1, (int)synToCol.size());
    map<string, int>::const_iterator siIt = synToCol.find("firstCol");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(0, siIt->second);
    const vector<Record>& records = tableTwo->get_records();
    CPPUNIT_ASSERT_EQUAL(1, (int)records.size());
    Record record;
    record.reset();
    record.add_value("valTwo");
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
}

void Test_02_ResultsTable::test_syn_11_transaction()
{
}

void Test_02_ResultsTable::test_syn_22_transaction()
{
}