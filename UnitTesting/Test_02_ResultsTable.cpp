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

void Test_02_ResultsTable::test_syn_00_transaction_ss()
{
    ResultsTable rTable;
    CPPUNIT_ASSERT_EQUAL(true, rTable.is_alive());
    rTable.syn_00_transaction_begin("Course", RV_STRING, "Difficulty",
            RV_STRING);
    rTable.syn_00_add_row("CS1101S", "hard");
    rTable.syn_00_add_row("CS2101", "easy");
    rTable.syn_00_add_row("CS2104", "slack");
    rTable.syn_00_add_row("MA1101R", "tedious");
    rTable.syn_00_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, rTable.is_alive());
    rTable.checkout_transaction_begin();
    Table *table = rTable.checkout_table("Course");
    Table *tabTwo = rTable.checkout_table("Difficulty");
    CPPUNIT_ASSERT_EQUAL(table, tabTwo);
    const map<int, string>& colToSyn = table->get_col_to_synonym();
    CPPUNIT_ASSERT_EQUAL(2, (int)colToSyn.size());
    map<int, string>::const_iterator isIt = colToSyn.find(0);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("Course"), isIt->second);
    isIt = colToSyn.find(1);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("Difficulty"), isIt->second);
    const map<string, int>& synToCol = table->get_synonym_to_col();
    CPPUNIT_ASSERT_EQUAL(2, (int)synToCol.size());
    map<string, int>::const_iterator siIt = synToCol.find("Course");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(0, siIt->second);
    siIt = synToCol.find("Difficulty");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(1, siIt->second);
    const vector<Record>& records = table->get_records();
    CPPUNIT_ASSERT_EQUAL(4, (int)records.size());
    Record record;
    record.reset();
    record.add_value("CS1101S");
    record.add_value("hard");
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_value("CS2101");
    record.add_value("easy");
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
    record.reset();
    record.add_value("CS2104");
    record.add_value("slack");
    CPPUNIT_ASSERT_EQUAL(record, records[2]);
    record.reset();
    record.add_value("MA1101R");
    record.add_value("tedious");
    CPPUNIT_ASSERT_EQUAL(record, records[3]);
    rTable.checkout_transaction_end();
}

void Test_02_ResultsTable::test_syn_00_transaction_si()
{
    ResultsTable rTable;
    CPPUNIT_ASSERT_EQUAL(true, rTable.is_alive());
    rTable.syn_00_transaction_begin("Course", RV_STRING, "Score",
            RV_INT);
    rTable.syn_00_add_row("CS1101S", 96);
    rTable.syn_00_add_row("CS2101", 80);
    rTable.syn_00_add_row("CS2104", 85);
    rTable.syn_00_add_row("MA1101R", 82);
    rTable.syn_00_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, rTable.is_alive());
    rTable.checkout_transaction_begin();
    Table *table = rTable.checkout_table("Course");
    Table *tabTwo = rTable.checkout_table("Score");
    CPPUNIT_ASSERT_EQUAL(table, tabTwo);
    const map<int, string>& colToSyn = table->get_col_to_synonym();
    CPPUNIT_ASSERT_EQUAL(2, (int)colToSyn.size());
    map<int, string>::const_iterator isIt = colToSyn.find(0);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("Course"), isIt->second);
    isIt = colToSyn.find(1);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("Score"), isIt->second);
    const map<string, int>& synToCol = table->get_synonym_to_col();
    CPPUNIT_ASSERT_EQUAL(2, (int)synToCol.size());
    map<string, int>::const_iterator siIt = synToCol.find("Course");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(0, siIt->second);
    siIt = synToCol.find("Score");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(1, siIt->second);
    const vector<Record>& records = table->get_records();
    CPPUNIT_ASSERT_EQUAL(4, (int)records.size());
    Record record;
    record.reset();
    record.add_value("CS1101S");
    record.add_value(96);
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_value("CS2101");
    record.add_value(80);
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
    record.reset();
    record.add_value("CS2104");
    record.add_value(85);
    CPPUNIT_ASSERT_EQUAL(record, records[2]);
    record.reset();
    record.add_value("MA1101R");
    record.add_value(82);
    CPPUNIT_ASSERT_EQUAL(record, records[3]);
    rTable.checkout_transaction_end();
}

void Test_02_ResultsTable::test_syn_00_transaction_is()
{
    ResultsTable rTable;
    CPPUNIT_ASSERT_EQUAL(true, rTable.is_alive());
    rTable.syn_00_transaction_begin("Day", RV_INT, "Country",
            RV_STRING);
    rTable.syn_00_add_row(5, "China");
    rTable.syn_00_add_row(71, "Australia");
    rTable.syn_00_add_row(3261, "South Africa");
    rTable.syn_00_add_row(22, "Egypt");
    rTable.syn_00_add_row(761115, "Nowhere");
    rTable.syn_00_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, rTable.is_alive());
    rTable.checkout_transaction_begin();
    Table *table = rTable.checkout_table("Day");
    Table *tabTwo = rTable.checkout_table("Country");
    CPPUNIT_ASSERT_EQUAL(table, tabTwo);
    const map<int, string>& colToSyn = table->get_col_to_synonym();
    CPPUNIT_ASSERT_EQUAL(2, (int)colToSyn.size());
    map<int, string>::const_iterator isIt = colToSyn.find(0);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("Day"), isIt->second);
    isIt = colToSyn.find(1);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("Country"), isIt->second);
    const map<string, int>& synToCol = table->get_synonym_to_col();
    CPPUNIT_ASSERT_EQUAL(2, (int)synToCol.size());
    map<string, int>::const_iterator siIt = synToCol.find("Day");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(0, siIt->second);
    siIt = synToCol.find("Country");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(1, siIt->second);
    const vector<Record>& records = table->get_records();
    CPPUNIT_ASSERT_EQUAL(5, (int)records.size());
    Record record;
    record.reset();
    record.add_value(5);
    record.add_value("China");
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_value(71);
    record.add_value("Australia");
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
    record.reset();
    record.add_value(3261);
    record.add_value("South Africa");
    CPPUNIT_ASSERT_EQUAL(record, records[2]);
    record.reset();
    record.add_value(22);
    record.add_value("Egypt");
    CPPUNIT_ASSERT_EQUAL(record, records[3]);
    record.reset();
    record.add_value(761115);
    record.add_value("Nowhere");
    CPPUNIT_ASSERT_EQUAL(record, records[4]);
    rTable.checkout_transaction_end();
}

void Test_02_ResultsTable::test_syn_00_transaction_ii()
{
    ResultsTable rTable;
    CPPUNIT_ASSERT_EQUAL(true, rTable.is_alive());
    rTable.syn_00_transaction_begin("Day", RV_INT, "Time",
            RV_INT);
    rTable.syn_00_add_row(5, 721);
    rTable.syn_00_add_row(71, 33216);
    rTable.syn_00_add_row(3261, 7);
    rTable.syn_00_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, rTable.is_alive());
    rTable.checkout_transaction_begin();
    Table *table = rTable.checkout_table("Day");
    Table *tabTwo = rTable.checkout_table("Time");
    CPPUNIT_ASSERT_EQUAL(table, tabTwo);
    const map<int, string>& colToSyn = table->get_col_to_synonym();
    CPPUNIT_ASSERT_EQUAL(2, (int)colToSyn.size());
    map<int, string>::const_iterator isIt = colToSyn.find(0);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("Day"), isIt->second);
    isIt = colToSyn.find(1);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("Time"), isIt->second);
    const map<string, int>& synToCol = table->get_synonym_to_col();
    CPPUNIT_ASSERT_EQUAL(2, (int)synToCol.size());
    map<string, int>::const_iterator siIt = synToCol.find("Day");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(0, siIt->second);
    siIt = synToCol.find("Time");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(1, siIt->second);
    const vector<Record>& records = table->get_records();
    CPPUNIT_ASSERT_EQUAL(3, (int)records.size());
    Record record;
    record.reset();
    record.add_value(5);
    record.add_value(721);
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_value(71);
    record.add_value(33216);
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
    record.reset();
    record.add_value(3261);
    record.add_value(7);
    CPPUNIT_ASSERT_EQUAL(record, records[2]);
    rTable.checkout_transaction_end();
}

void Test_02_ResultsTable::test_syn_11_transaction()
{
}

void Test_02_ResultsTable::test_syn_22_transaction()
{
}