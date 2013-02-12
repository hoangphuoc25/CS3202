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
    rTable.syn_0_transaction_begin("firstCol", RV_STRING);
    CPPUNIT_ASSERT_EQUAL(true, rTable.is_alive());
    rTable.syn_0_add_row("valOne");
    rTable.syn_0_add_row("valTwo");
    rTable.syn_0_add_row("valThree");
    rTable.syn_0_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, rTable.is_alive());
    CPPUNIT_ASSERT_EQUAL(true, rTable.has_synonym("firstCol"));
    rTable.checkout_transaction_begin();
    Table *table = rTable.checkout_table("firstCol");
    const map<int, string>& colToSyn = table->get_col_to_synonym();
    CPPUNIT_ASSERT_EQUAL(1, (int)colToSyn.size());
    map<int, string>::const_iterator isIt = colToSyn.find(0);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("firstCol"), isIt->second);
    const map<string, int>& synToCol = table->get_synonym_to_col();
    CPPUNIT_ASSERT_EQUAL(1, (int)synToCol.size());
    map<string, int>::const_iterator siIt = synToCol.find("firstCol");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(0, siIt->second);
    const vector<Record>& records = table->get_records();
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
    rTable.checkout_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, rTable.is_alive());
}

void Test_02_ResultsTable::test_syn_1_transaction()
{
    ResultsTable rTable;
    rTable.syn_0_transaction_begin("firstCol", RV_INT);
    CPPUNIT_ASSERT_EQUAL(true, rTable.is_alive());
    rTable.syn_0_add_row(1);
    rTable.syn_0_add_row(26156);
    rTable.syn_0_add_row(351);
    rTable.syn_0_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, rTable.is_alive());

    const vector<Record>& recordsOne =
            rTable.syn_1_transaction_begin("firstCol");
    CPPUNIT_ASSERT_EQUAL(3, (int)recordsOne.size());
    Record record;
    record.reset();
    record.add_value(1);
    CPPUNIT_ASSERT_EQUAL(record, recordsOne[0]);
    record.reset();
    record.add_value(26156);
    CPPUNIT_ASSERT_EQUAL(record, recordsOne[1]);
    record.reset();
    record.add_value(351);
    CPPUNIT_ASSERT_EQUAL(record, recordsOne[2]);
    rTable.syn_1_mark_row_ok(1);
    rTable.syn_1_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, rTable.is_alive());

    rTable.checkout_transaction_begin();
    Table *table = rTable.checkout_table("firstCol");
    const map<int, string>& colToSyn = table->get_col_to_synonym();
    CPPUNIT_ASSERT_EQUAL(1, (int)colToSyn.size());
    map<int, string>::const_iterator isIt = colToSyn.find(0);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("firstCol"), isIt->second);
    const map<string, int>& synToCol = table->get_synonym_to_col();
    CPPUNIT_ASSERT_EQUAL(1, (int)synToCol.size());
    map<string, int>::const_iterator siIt = synToCol.find("firstCol");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(0, siIt->second);
    const vector<Record>& records = table->get_records();
    CPPUNIT_ASSERT_EQUAL(1, (int)records.size());
    record.reset();
    record.add_value(26156);
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    rTable.checkout_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, rTable.is_alive());
}

void Test_02_ResultsTable::test_syn_11_transaction()
{
}

void Test_02_ResultsTable::test_syn_22_transaction()
{
}