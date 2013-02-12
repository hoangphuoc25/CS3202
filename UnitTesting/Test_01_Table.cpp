#include <string>
#include <map>
#include <vector>

#include "../SPA/Table.h"
#include "Test_01_Table.h"

using std::map;
using std::string;
using std::vector;

void Test_01_Table::setUp() {}
void Test_01_Table::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test_01_Table);

void Test_01_Table::test_add_row_s()
{
    Table table;
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    table.add_rows_transaction_begin();
    table.add_row("aOne", "a");
    table.add_row("aOne", "bad");
    table.add_row("aOne", "damn");
    table.add_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    const map<int, string>& colToSyn = table.get_col_to_synonym();
    CPPUNIT_ASSERT_EQUAL(1, (int)colToSyn.size());
    map<int, string>::const_iterator isIt = colToSyn.find(0);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("aOne"), isIt->second);
    const map<string, int>& synToCol = table.get_synonym_to_col();
    CPPUNIT_ASSERT_EQUAL(1, (int)synToCol.size());
    map<string, int>::const_iterator siIt = synToCol.find("aOne");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(0, siIt->second);
    const vector<Record>& records = table.get_records();
    CPPUNIT_ASSERT_EQUAL(3, (int)records.size());
    Record record;
    record.add_value("a");
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_value("bad");
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
    record.reset();
    record.add_value("damn");
    CPPUNIT_ASSERT_EQUAL(record, records[2]);
}

void Test_01_Table::test_add_row_i()
{
    Table table;
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    table.add_rows_transaction_begin();
    table.add_row("varXE", 126);
    table.add_row("varXE", 1718);
    table.add_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    const map<int, string>& colToSyn = table.get_col_to_synonym();
    CPPUNIT_ASSERT_EQUAL(1, (int)colToSyn.size());
    map<int, string>::const_iterator isIt = colToSyn.find(0);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(0, isIt->first);
    CPPUNIT_ASSERT_EQUAL(string("varXE"), isIt->second);
    const map<string, int>& synToCol = table.get_synonym_to_col();
    map<string, int>::const_iterator siIt = synToCol.find("varXE");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(string("varXE"), siIt->first);
    CPPUNIT_ASSERT_EQUAL(0, siIt->second);
    const vector<Record>& records = table.get_records();
    CPPUNIT_ASSERT_EQUAL(2, (int)records.size());
    Record record;
    record.add_value(126);
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_value(1718);
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
}

void Test_01_Table::test_add_row_ss()
{
    Table table;
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    table.add_rows_transaction_begin();
    table.add_row("yea", "man", "this", "great");
    table.add_row("yea", "hell", "this", "cell");
    table.add_row("yea", "yui", "this", "framework");
    table.add_row("yea", "ummmmS", "this", "amIright");
    table.add_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    const map<int, string>& colToSyn = table.get_col_to_synonym();
    CPPUNIT_ASSERT_EQUAL(2, (int)colToSyn.size());
    map<int, string>::const_iterator isIt = colToSyn.find(0);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("yea"), isIt->second);
    isIt = colToSyn.find(1);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("this"), isIt->second);
    const map<string, int>& synToCol = table.get_synonym_to_col();
    CPPUNIT_ASSERT_EQUAL(2, (int)synToCol.size());
    map<string, int>::const_iterator siIt = synToCol.find("yea");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(0, siIt->second);
    siIt = synToCol.find("this");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(1, siIt->second);
    const vector<Record>& records = table.get_records();
    CPPUNIT_ASSERT_EQUAL(4, (int)records.size());
    Record record;
    record.add_value("man");
    record.add_value("great");
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_value("hell");
    record.add_value("cell");
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
    record.reset();
    record.add_value("yui");
    record.add_value("framework");
    CPPUNIT_ASSERT_EQUAL(record, records[2]);
    record.reset();
    record.add_value("ummmmS");
    record.add_value("amIright");
    CPPUNIT_ASSERT_EQUAL(record, records[3]);
}

void Test_01_Table::test_add_row_si()
{
    Table table;
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    table.add_rows_transaction_begin();
    table.add_row("Hobo", "gee", "ballooo", 9321);
    table.add_row("Hobo", "testMAn", "ballooo", 7);
    table.add_row("Hobo", "ide", "ballooo", 33);
    table.add_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    const map<int, string>& colToSyn = table.get_col_to_synonym();
    CPPUNIT_ASSERT_EQUAL(2, (int)colToSyn.size());
    map<int, string>::const_iterator isIt = colToSyn.find(0);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("Hobo"), isIt->second);
    isIt = colToSyn.find(1);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("ballooo"), isIt->second);
    const map<string, int>& synToCol = table.get_synonym_to_col();
    CPPUNIT_ASSERT_EQUAL(2, (int)synToCol.size());
    map<string, int>::const_iterator siIt = synToCol.find("Hobo");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(0, siIt->second);
    siIt = synToCol.find("ballooo");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(1, siIt->second);
    const vector<Record>& records = table.get_records();
    CPPUNIT_ASSERT_EQUAL(3, (int)records.size());
    Record record;
    record.add_value("gee");
    record.add_value(9321);
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_value("testMAn");
    record.add_value(7);
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
    record.reset();
    record.add_value("ide");
    record.add_value(33);
    CPPUNIT_ASSERT_EQUAL(record, records[2]);
}

void Test_01_Table::test_add_row_is()
{
    Table table;
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    table.add_rows_transaction_begin();
    table.add_row("Tysav", 89467, "Muba", "aday");
    table.add_row("Tysav", 15, "Muba", "Fha1");
    table.add_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    const map<int, string>& colToSyn = table.get_col_to_synonym();
    CPPUNIT_ASSERT_EQUAL(2, (int)colToSyn.size());
    map<int, string>::const_iterator isIt = colToSyn.find(0);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("Tysav"), isIt->second);
    isIt = colToSyn.find(1);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("Muba"), isIt->second);
    const map<string, int>& synToCol = table.get_synonym_to_col();
    CPPUNIT_ASSERT_EQUAL(2, (int)synToCol.size());
    map<string, int>::const_iterator siIt = synToCol.find("Tysav");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(0, siIt->second);
    siIt = synToCol.find("Muba");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(1, siIt->second);
    const vector<Record>& records = table.get_records();
    CPPUNIT_ASSERT_EQUAL(2, (int)records.size());
    Record record;
    record.add_value(89467);
    record.add_value("aday");
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_value(15);
    record.add_value("Fha1");
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
}

void Test_01_Table::test_add_row_ii()
{
    Table table;
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    table.add_rows_transaction_begin();
    table.add_row("gleha1", 8468, "aAdgr1", 66);
    table.add_row("gleha1", 12465, "aAdgr1", 1);
    table.add_row("gleha1", 342467, "aAdgr1", 8);
    table.add_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    const map<int, string>& colToSyn = table.get_col_to_synonym();
    CPPUNIT_ASSERT_EQUAL(2, (int)colToSyn.size());
    map<int, string>::const_iterator isIt = colToSyn.find(0);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("gleha1"), isIt->second);
    isIt = colToSyn.find(1);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("aAdgr1"), isIt->second);
    const map<string, int>& synToCol = table.get_synonym_to_col();
    CPPUNIT_ASSERT_EQUAL(2, (int)synToCol.size());
    map<string, int>::const_iterator siIt = synToCol.find("gleha1");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(0, siIt->second);
    siIt = synToCol.find("aAdgr1");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(1, siIt->second);
    const vector<Record>& records = table.get_records();
    CPPUNIT_ASSERT_EQUAL(3, (int)records.size());
    Record record;
    record.add_value(8468);
    record.add_value(66);
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_value(12465);
    record.add_value(1);
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
    record.reset();
    record.add_value(342467);
    record.add_value(8);
    CPPUNIT_ASSERT_EQUAL(record, records[2]);
}

void Test_01_Table::test_add_row_r_s()
{
    // Create one table first
    Table firstTable;
    firstTable.add_rows_transaction_begin();
    firstTable.add_row("first", 3, "secondCol", "good");
    firstTable.add_row("first", 72, "secondCol", "mkbma");
    firstTable.add_row("first", 6246, "secondCol", "gsg");
    firstTable.add_rows_transaction_end();
    const vector<Record>& firstRecords = firstTable.get_records();

    Table table;
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    const map<int, string>& firstTableColToSyn =
            firstTable.get_col_to_synonym();
    table.add_rows_transaction_begin();
    table.add_row(firstTableColToSyn, firstRecords[0], "aOne", "a");
    table.add_row(firstTableColToSyn, firstRecords[1], "aOne", "bad");
    table.add_row(firstTableColToSyn, firstRecords[2], "aOne", "damn");
    table.add_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    const map<int, string>& colToSyn = table.get_col_to_synonym();
    CPPUNIT_ASSERT_EQUAL(3, (int)colToSyn.size());
    map<int, string>::const_iterator isIt = colToSyn.find(0);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("first"), isIt->second);
    isIt = colToSyn.find(1);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("secondCol"), isIt->second);
    isIt = colToSyn.find(2);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("aOne"), isIt->second);
    const map<string, int>& synToCol = table.get_synonym_to_col();
    CPPUNIT_ASSERT_EQUAL(3, (int)synToCol.size());
    map<string, int>::const_iterator siIt = synToCol.find("first");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(0, siIt->second);
    siIt = synToCol.find("secondCol");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(1, siIt->second);
    siIt = synToCol.find("aOne");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(2, siIt->second);
    const vector<Record>& records = table.get_records();
    CPPUNIT_ASSERT_EQUAL(3, (int)records.size());
    Record record;
    record.add_value(3);
    record.add_value("good");
    record.add_value("a");
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_value(72);
    record.add_value("mkbma");
    record.add_value("bad");
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
    record.reset();
    record.add_value(6246);
    record.add_value("gsg");
    record.add_value("damn");
    CPPUNIT_ASSERT_EQUAL(record, records[2]);
}

void Test_01_Table::test_add_row_r_i()
{
    // Create one table first
    Table firstTable;
    firstTable.add_rows_transaction_begin();
    firstTable.add_row("first", 3, "secondCol", "good");
    firstTable.add_row("first", 72, "secondCol", "mkbma");
    firstTable.add_rows_transaction_end();
    const vector<Record>& firstRecords = firstTable.get_records();

    Table table;
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    const map<int, string>& firstTableColToSyn =
            firstTable.get_col_to_synonym();
    table.add_rows_transaction_begin();
    table.add_row(firstTableColToSyn, firstRecords[0], "varXE", 126);
    table.add_row(firstTableColToSyn, firstRecords[1], "varXE", 1718);
    table.add_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    const map<int, string>& colToSyn = table.get_col_to_synonym();
    CPPUNIT_ASSERT_EQUAL(3, (int)colToSyn.size());
    map<int, string>::const_iterator isIt = colToSyn.find(0);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("first"), isIt->second);
    isIt = colToSyn.find(1);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("secondCol"), isIt->second);
    isIt = colToSyn.find(2);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("varXE"), isIt->second);
    const map<string, int>& synToCol = table.get_synonym_to_col();
    CPPUNIT_ASSERT_EQUAL(3, (int)synToCol.size());
    map<string, int>::const_iterator siIt = synToCol.find("first");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(0, siIt->second);
    siIt = synToCol.find("secondCol");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(1, siIt->second);
    siIt = synToCol.find("varXE");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(2, siIt->second);
    const vector<Record>& records = table.get_records();
    CPPUNIT_ASSERT_EQUAL(2, (int)records.size());
    Record record;
    record.add_value(3);
    record.add_value("good");
    record.add_value(126);
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_value(72);
    record.add_value("mkbma");
    record.add_value(1718);
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
}

void Test_01_Table::test_add_row_r_ss()
{
    // Create one table first
    Table firstTable;
    firstTable.add_rows_transaction_begin();
    firstTable.add_row("first", 3, "secondCol", "good");
    firstTable.add_row("first", 72, "secondCol", "mkbma");
    firstTable.add_row("first", 6246, "secondCol", "gsg");
    firstTable.add_rows_transaction_end();
    const vector<Record>& firstRecords = firstTable.get_records();

    Table table;
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    const map<int, string>& firstTableColToSyn =
            firstTable.get_col_to_synonym();
    table.add_rows_transaction_begin();
    table.add_row(firstTableColToSyn, firstRecords[0], "yea", "man",
            "this", "great");
    table.add_row(firstTableColToSyn, firstRecords[1], "yea", "hell",
            "this", "cell");
    table.add_row(firstTableColToSyn, firstRecords[2], "yea", "yui",
            "this", "framework");
    table.add_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    const map<int, string>& colToSyn = table.get_col_to_synonym();
    CPPUNIT_ASSERT_EQUAL(4, (int)colToSyn.size());
    map<int, string>::const_iterator isIt = colToSyn.find(0);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("first"), isIt->second);
    isIt = colToSyn.find(1);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("secondCol"), isIt->second);
    isIt = colToSyn.find(2);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("yea"), isIt->second);
    isIt = colToSyn.find(3);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("this"), isIt->second);
    const map<string, int>& synToCol = table.get_synonym_to_col();
    CPPUNIT_ASSERT_EQUAL(4, (int)synToCol.size());
    map<string, int>::const_iterator siIt = synToCol.find("first");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(0, siIt->second);
    siIt = synToCol.find("secondCol");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(1, siIt->second);
    siIt = synToCol.find("yea");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(2, siIt->second);
    siIt = synToCol.find("this");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(3, siIt->second);
    const vector<Record>& records = table.get_records();
    CPPUNIT_ASSERT_EQUAL(3, (int)records.size());
    Record record;
    record.add_value(3);
    record.add_value("good");
    record.add_value("man");
    record.add_value("great");
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_value(72);
    record.add_value("mkbma");
    record.add_value("hell");
    record.add_value("cell");
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
    record.reset();
    record.add_value(6246);
    record.add_value("gsg");
    record.add_value("yui");
    record.add_value("framework");
    CPPUNIT_ASSERT_EQUAL(record, records[2]);
}

void Test_01_Table::test_add_row_r_si()
{
    // Create one table first
    Table firstTable;
    firstTable.add_rows_transaction_begin();
    firstTable.add_row("first", 3, "secondCol", "good");
    firstTable.add_row("first", 72, "secondCol", "mkbma");
    firstTable.add_row("first", 6246, "secondCol", "gsg");
    firstTable.add_rows_transaction_end();
    const vector<Record>& firstRecords = firstTable.get_records();

    Table table;
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    const map<int, string>& firstTableColToSyn =
            firstTable.get_col_to_synonym();
    table.add_rows_transaction_begin();
    table.add_row(firstTableColToSyn, firstRecords[0], "Hobo", "gee",
            "ballooo", 9321);
    table.add_row(firstTableColToSyn, firstRecords[1], "Hobo", "testMAn",
            "ballooo", 7);
    table.add_row(firstTableColToSyn, firstRecords[2], "Hobo", "ide",
            "ballooo", 33);
    table.add_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    const map<int, string>& colToSyn = table.get_col_to_synonym();
    CPPUNIT_ASSERT_EQUAL(4, (int)colToSyn.size());
    map<int, string>::const_iterator isIt = colToSyn.find(0);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("first"), isIt->second);
    isIt = colToSyn.find(1);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("secondCol"), isIt->second);
    isIt = colToSyn.find(2);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("Hobo"), isIt->second);
    isIt = colToSyn.find(3);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("ballooo"), isIt->second);
    const map<string, int>& synToCol = table.get_synonym_to_col();
    CPPUNIT_ASSERT_EQUAL(4, (int)synToCol.size());
    map<string, int>::const_iterator siIt = synToCol.find("first");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(0, siIt->second);
    siIt = synToCol.find("secondCol");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(1, siIt->second);
    siIt = synToCol.find("Hobo");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(2, siIt->second);
    siIt = synToCol.find("ballooo");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(3, siIt->second);
    const vector<Record>& records = table.get_records();
    CPPUNIT_ASSERT_EQUAL(3, (int)records.size());
    Record record;
    record.add_value(3);
    record.add_value("good");
    record.add_value("gee");
    record.add_value(9321);
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_value(72);
    record.add_value("mkbma");
    record.add_value("testMAn");
    record.add_value(7);
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
    record.reset();
    record.add_value(6246);
    record.add_value("gsg");
    record.add_value("ide");
    record.add_value(33);
    CPPUNIT_ASSERT_EQUAL(record, records[2]);
}

void Test_01_Table::test_add_row_r_is()
{
    // Create one table first
    Table firstTable;
    firstTable.add_rows_transaction_begin();
    firstTable.add_row("first", 3, "secondCol", "good");
    firstTable.add_row("first", 72, "secondCol", "mkbma");
    firstTable.add_rows_transaction_end();
    const vector<Record>& firstRecords = firstTable.get_records();

    Table table;
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    const map<int, string>& firstTableColToSyn =
            firstTable.get_col_to_synonym();
    table.add_rows_transaction_begin();
    table.add_row(firstTableColToSyn, firstRecords[0], "Tysav", 89467,
            "Muba", "aday");
    table.add_row(firstTableColToSyn, firstRecords[1], "Tysav", 15,
            "Muba", "Fha1");
    table.add_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    const map<int, string>& colToSyn = table.get_col_to_synonym();
    CPPUNIT_ASSERT_EQUAL(4, (int)colToSyn.size());
    map<int, string>::const_iterator isIt = colToSyn.find(0);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("first"), isIt->second);
    isIt = colToSyn.find(1);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("secondCol"), isIt->second);
    isIt = colToSyn.find(2);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("Tysav"), isIt->second);
    isIt = colToSyn.find(3);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("Muba"), isIt->second);
    const map<string, int>& synToCol = table.get_synonym_to_col();
    CPPUNIT_ASSERT_EQUAL(4, (int)synToCol.size());
    map<string, int>::const_iterator siIt = synToCol.find("first");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(0, siIt->second);
    siIt = synToCol.find("secondCol");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(1, siIt->second);
    siIt = synToCol.find("Tysav");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(2, siIt->second);
    siIt = synToCol.find("Muba");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(3, siIt->second);
    const vector<Record>& records = table.get_records();
    CPPUNIT_ASSERT_EQUAL(2, (int)records.size());
    Record record;
    record.add_value(3);
    record.add_value("good");
    record.add_value(89467);
    record.add_value("aday");
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_value(72);
    record.add_value("mkbma");
    record.add_value(15);
    record.add_value("Fha1");
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
}

void Test_01_Table::test_add_row_r_ii()
{
    // Create one table first
    Table firstTable;
    firstTable.add_rows_transaction_begin();
    firstTable.add_row("first", 3, "secondCol", "good");
    firstTable.add_row("first", 72, "secondCol", "mkbma");
    firstTable.add_row("first", 6246, "secondCol", "gsg");
    firstTable.add_rows_transaction_end();
    const vector<Record>& firstRecords = firstTable.get_records();

    Table table;
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    const map<int, string>& firstTableColToSyn =
            firstTable.get_col_to_synonym();
    table.add_rows_transaction_begin();
    table.add_row(firstTableColToSyn, firstRecords[0], "gleha1", 8468,
            "aAdgr1", 66);
    table.add_row(firstTableColToSyn, firstRecords[1], "gleha1", 12465,
            "aAdgr1", 1);
    table.add_row(firstTableColToSyn, firstRecords[2], "gleha1", 342467,
            "aAdgr1", 8);
    table.add_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    const map<int, string>& colToSyn = table.get_col_to_synonym();
    CPPUNIT_ASSERT_EQUAL(4, (int)colToSyn.size());
    map<int, string>::const_iterator isIt = colToSyn.find(0);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("first"), isIt->second);
    isIt = colToSyn.find(1);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("secondCol"), isIt->second);
    isIt = colToSyn.find(2);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("gleha1"), isIt->second);
    isIt = colToSyn.find(3);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("aAdgr1"), isIt->second);
    const map<string, int>& synToCol = table.get_synonym_to_col();
    CPPUNIT_ASSERT_EQUAL(4, (int)synToCol.size());
    map<string, int>::const_iterator siIt = synToCol.find("first");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(0, siIt->second);
    siIt = synToCol.find("secondCol");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(1, siIt->second);
    siIt = synToCol.find("gleha1");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(2, siIt->second);
    siIt = synToCol.find("aAdgr1");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(3, siIt->second);
    const vector<Record>& records = table.get_records();
    CPPUNIT_ASSERT_EQUAL(3, (int)records.size());
    Record record;
    record.add_value(3);
    record.add_value("good");
    record.add_value(8468);
    record.add_value(66);
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_value(72);
    record.add_value("mkbma");
    record.add_value(12465);
    record.add_value(1);
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
    record.reset();
    record.add_value(6246);
    record.add_value("gsg");
    record.add_value(342467);
    record.add_value(8);
    CPPUNIT_ASSERT_EQUAL(record, records[2]);
}

void Test_01_Table::test_add_row_r_r()
{
    Table firstTable;
    firstTable.add_rows_transaction_begin();
    firstTable.add_row("firstCol", "avalue");
    firstTable.add_row("firstCol", "256");
    firstTable.add_row("firstCol", "firstEntry");
    firstTable.add_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, firstTable.is_alive());
    const vector<Record>& firstRecords = firstTable.get_records();

    Table secTable;
    secTable.add_rows_transaction_begin();
    secTable.add_row("secCol", 265, "thirdCol", "fire");
    secTable.add_row("secCol", 7, "thirdCol", "well");
    secTable.add_row("secCol", 8468, "thirdCol", "cool");
    secTable.add_row("secCol", 111811, "thirdCol", "kay");
    secTable.add_row("secCol", 9932, "thirdCol", "hsx");
    secTable.add_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, secTable.is_alive());
    const vector<Record>& secRecords = secTable.get_records();

    Table table;
    const map<int, string>& firstTableColToSyn =
            firstTable.get_col_to_synonym();
    const map<int, string>& secTableColToSyn =
            secTable.get_col_to_synonym();
    table.add_rows_transaction_begin();
    table.add_row(firstTableColToSyn, firstRecords[0],
            secTableColToSyn, secRecords[1]);
    table.add_row(firstTableColToSyn, firstRecords[2],
            secTableColToSyn, secRecords[3]);
    table.add_row(firstTableColToSyn, firstRecords[1],
            secTableColToSyn, secRecords[4]);
    table.add_row(firstTableColToSyn, firstRecords[0],
            secTableColToSyn, secRecords[2]);
    table.add_row(firstTableColToSyn, firstRecords[1],
            secTableColToSyn, secRecords[2]);
    table.add_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    const vector<Record>& finalRecords = table.get_records();
    CPPUNIT_ASSERT_EQUAL(5, (int)finalRecords.size());
    Record record;
    record.reset();
    record.add_value("avalue");
    record.add_value(7);
    record.add_value("well");
    CPPUNIT_ASSERT_EQUAL(record, finalRecords[0]);
    record.reset();
    record.add_value("firstEntry");
    record.add_value(111811);
    record.add_value("kay");
    CPPUNIT_ASSERT_EQUAL(record, finalRecords[1]);
    record.reset();
    record.add_value("256");
    record.add_value(9932);
    record.add_value("hsx");
    CPPUNIT_ASSERT_EQUAL(record, finalRecords[2]);
    record.reset();
    record.add_value("avalue");
    record.add_value(8468);
    record.add_value("cool");
    CPPUNIT_ASSERT_EQUAL(record, finalRecords[3]);
    record.reset();
    record.add_value("256");
    record.add_value(8468);
    record.add_value("cool");
    CPPUNIT_ASSERT_EQUAL(record, finalRecords[4]);
}

void Test_01_Table::test_add_row_r_r_reuse_table()
{
    Table firstTable;
    firstTable.add_rows_transaction_begin();
    firstTable.add_row("firstCol", "avalue");
    firstTable.add_row("firstCol", "256");
    firstTable.add_row("firstCol", "firstEntry");
    firstTable.add_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, firstTable.is_alive());
    const vector<Record>& firstRecords = firstTable.get_records();

    Table secTable;
    secTable.add_rows_transaction_begin();
    secTable.add_row("secCol", 265, "thirdCol", "fire");
    secTable.add_row("secCol", 7, "thirdCol", "well");
    secTable.add_row("secCol", 8468, "thirdCol", "cool");
    secTable.add_row("secCol", 111811, "thirdCol", "kay");
    secTable.add_row("secCol", 9932, "thirdCol", "hsx");
    secTable.add_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, secTable.is_alive());
    const vector<Record>& secRecords = secTable.get_records();

    const map<int, string>& firstTableColToSyn =
            firstTable.get_col_to_synonym();
    const map<int, string>& secTableColToSyn =
            secTable.get_col_to_synonym();
    firstTable.add_rows_transaction_begin();
    firstTable.add_row(firstTableColToSyn, firstRecords[0],
            secTableColToSyn, secRecords[1]);
    firstTable.add_row(firstTableColToSyn, firstRecords[2],
            secTableColToSyn, secRecords[3]);
    firstTable.add_row(firstTableColToSyn, firstRecords[1],
            secTableColToSyn, secRecords[4]);
    firstTable.add_row(firstTableColToSyn, firstRecords[0],
            secTableColToSyn, secRecords[2]);
    firstTable.add_row(firstTableColToSyn, firstRecords[1],
            secTableColToSyn, secRecords[2]);
    firstTable.add_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, firstTable.is_alive());
    const vector<Record>& finalRecords = firstTable.get_records();
    CPPUNIT_ASSERT_EQUAL(5, (int)finalRecords.size());
    Record record;
    record.reset();
    record.add_value("avalue");
    record.add_value(7);
    record.add_value("well");
    CPPUNIT_ASSERT_EQUAL(record, finalRecords[0]);
    record.reset();
    record.add_value("firstEntry");
    record.add_value(111811);
    record.add_value("kay");
    CPPUNIT_ASSERT_EQUAL(record, finalRecords[1]);
    record.reset();
    record.add_value("256");
    record.add_value(9932);
    record.add_value("hsx");
    CPPUNIT_ASSERT_EQUAL(record, finalRecords[2]);
    record.reset();
    record.add_value("avalue");
    record.add_value(8468);
    record.add_value("cool");
    CPPUNIT_ASSERT_EQUAL(record, finalRecords[3]);
    record.reset();
    record.add_value("256");
    record.add_value(8468);
    record.add_value("cool");
    CPPUNIT_ASSERT_EQUAL(record, finalRecords[4]);
}

void Test_01_Table::test_add_row_dead()
{
    Table table;
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    table.add_rows_transaction_begin();
    table.add_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(false, table.is_alive());
}

void Test_01_Table::test_mark_row()
{
    Table table;
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    table.add_rows_transaction_begin();
    table.add_row("aOne", "a");
    table.add_row("aOne", "bad");
    table.add_row("aOne", "damn");
    table.add_row("aOne", "great");
    table.add_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    table.mark_rows_transaction_begin();
    table.mark_row_ok(0);
    table.mark_row_ok(3);
    table.mark_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    const vector<Record>& records = table.get_records();
    Record record;
    record.reset();
    record.add_value("a");
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_value("great");
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
}

void Test_01_Table::test_mark_row_dead()
{
    Table table;
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    table.add_rows_transaction_begin();
    table.add_row("aOne", "a");
    table.add_row("aOne", "bad");
    table.add_row("aOne", "damn");
    table.add_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    table.mark_rows_transaction_begin();
    table.mark_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(false, table.is_alive());
}

void Test_01_Table::test_augment_existing_row_s()
{
    Table table;
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    table.add_rows_transaction_begin();
    table.add_row("c130", "down", "f16", "up");
    table.add_row("c130", "aa", "f16", "bb");
    table.add_row("c130", "you", "f16", "areFired");
    table.add_row("c130", "no", "f16", "way");
    table.add_row("c130", "blasphemy", "f16", "nope");
    table.add_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    table.augment_existing_rows_transaction_begin();
    table.augment_existing_row(0, "third", "X");
    table.augment_existing_row(4, "third", "up");
    // augment non-existent row
    table.augment_existing_row(141, "third", "blah");
    table.augment_existing_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    const vector<Record>& records = table.get_records();
    CPPUNIT_ASSERT_EQUAL(2, (int)records.size());
    Record record;
    record.reset();
    record.add_value("down");
    record.add_value("up");
    record.add_value("X");
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_value("blasphemy");
    record.add_value("nope");
    record.add_value("up");
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
}

void Test_01_Table::test_augment_existing_row_i()
{
    Table table;
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    table.add_rows_transaction_begin();
    table.add_row("c130", "down", "f16", "up");
    table.add_row("c130", "aa", "f16", "bb");
    table.add_row("c130", "down", "f16", "areFired");
    table.add_row("c130", "no", "f16", "way");
    table.add_row("c130", "blasphemy", "f16", "nope");
    table.add_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    table.augment_existing_rows_transaction_begin();
    table.augment_existing_row(0, "third", 61);
    table.augment_existing_row(3, "third", 71882);
    table.augment_existing_row(2, "third", 1567);
    table.augment_existing_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    const vector<Record>& records = table.get_records();
    CPPUNIT_ASSERT_EQUAL(3, (int)records.size());
    Record record;
    record.reset();
    record.add_value("down");
    record.add_value("up");
    record.add_value(61);
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_value("down");
    record.add_value("areFired");
    record.add_value(1567);
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
    record.reset();
    record.add_value("no");
    record.add_value("way");
    record.add_value(71882);
    CPPUNIT_ASSERT_EQUAL(record, records[2]);
}

void Test_01_Table::test_augment_existing_row_dead()
{
    Table table;
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    table.add_rows_transaction_begin();
    table.add_row("colOne", "valOne", "colTwo", 2);
    table.add_row("colOne", "valTwo", "colTwo", 141);
    table.add_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    table.augment_existing_rows_transaction_begin();
    table.augment_existing_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(false, table.is_alive());
}

void Test_01_Table::test_augment_new_row_s()
{
    Table table;
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    table.add_rows_transaction_begin();
    table.add_row("name", "T Dog", "age", 45);
    table.add_row("name", "Jerry", "age", 17);
    table.add_row("name", "George Washington", "age", 200);
    table.add_row("name", "Denzel Washington", "age", 50);
    table.add_row("name", "Santa Claus", "age", 1000);
    table.add_row("name", "Isaac Newton", "age", 300);
    table.add_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    table.augment_new_rows_transaction_begin();
    table.augment_new_row(0, "Health", "good");
    table.augment_new_row(2, "Health", "poor");
    table.augment_new_row(4, "Health", "Never better!");
    table.augment_new_row(1, "Health", "well");
    table.augment_new_row(2, "Health", "damned good");
    table.augment_new_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    const map<int, string>& colToSyn = table.get_col_to_synonym();
    CPPUNIT_ASSERT_EQUAL(3, (int)colToSyn.size());
    map<int, string>::const_iterator isIt = colToSyn.find(0);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("name"), isIt->second);
    isIt = colToSyn.find(1);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("age"), isIt->second);
    isIt = colToSyn.find(2);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("Health"), isIt->second);
    const map<string, int>& synToCol = table.get_synonym_to_col();
    CPPUNIT_ASSERT_EQUAL(3, (int)synToCol.size());
    map<string, int>::const_iterator siIt = synToCol.find("name");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(0, siIt->second);
    siIt = synToCol.find("age");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(1, siIt->second);
    siIt = synToCol.find("Health");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(2, siIt->second);
    const vector<Record>& records = table.get_records();
    CPPUNIT_ASSERT_EQUAL(5, (int)records.size());
    Record record;
    record.reset();
    record.add_value("T Dog");
    record.add_value(45);
    record.add_value("good");
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_value("George Washington");
    record.add_value(200);
    record.add_value("poor");
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
    record.reset();
    record.add_value("Santa Claus");
    record.add_value(1000);
    record.add_value("Never better!");
    CPPUNIT_ASSERT_EQUAL(record, records[2]);
    record.reset();
    record.add_value("Jerry");
    record.add_value(17);
    record.add_value("well");
    CPPUNIT_ASSERT_EQUAL(record, records[3]);
    record.reset();
    record.add_value("George Washington");
    record.add_value(200);
    record.add_value("damned good");
    CPPUNIT_ASSERT_EQUAL(record, records[4]);
}

void Test_01_Table::test_augment_new_row_i()
{
    Table table;
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    table.add_rows_transaction_begin();
    table.add_row("name", "T Dog", "age", 45);
    table.add_row("name", "Jerry", "age", 17);
    table.add_row("name", "George Washington", "age", 200);
    table.add_row("name", "Denzel Washington", "age", 50);
    table.add_row("name", "Santa Claus", "age", 1000);
    table.add_row("name", "Isaac Newton", "age", 300);
    table.add_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    table.augment_new_rows_transaction_begin();
    table.augment_new_row(0, "Fame", 4);
    table.augment_new_row(2, "Fame", 5124124);
    table.augment_new_row(4, "Fame", 10000000);
    table.augment_new_row(1, "Fame", 478);
    table.augment_new_row(2, "Fame", 184616);
    table.augment_new_row(3, "Fame", 1000);
    table.augment_new_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    const map<int, string>& colToSyn = table.get_col_to_synonym();
    CPPUNIT_ASSERT_EQUAL(3, (int)colToSyn.size());
    map<int, string>::const_iterator isIt = colToSyn.find(0);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("name"), isIt->second);
    isIt = colToSyn.find(1);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("age"), isIt->second);
    isIt = colToSyn.find(2);
    CPPUNIT_ASSERT(isIt != colToSyn.end());
    CPPUNIT_ASSERT_EQUAL(string("Fame"), isIt->second);
    const map<string, int>& synToCol = table.get_synonym_to_col();
    CPPUNIT_ASSERT_EQUAL(3, (int)synToCol.size());
    map<string, int>::const_iterator siIt = synToCol.find("name");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(0, siIt->second);
    siIt = synToCol.find("age");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(1, siIt->second);
    siIt = synToCol.find("Fame");
    CPPUNIT_ASSERT(siIt != synToCol.end());
    CPPUNIT_ASSERT_EQUAL(2, siIt->second);
    const vector<Record>& records = table.get_records();
    CPPUNIT_ASSERT_EQUAL(6, (int)records.size());
    Record record;
    record.reset();
    record.add_value("T Dog");
    record.add_value(45);
    record.add_value(4);
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_value("George Washington");
    record.add_value(200);
    record.add_value(5124124);
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
    record.reset();
    record.add_value("Santa Claus");
    record.add_value(1000);
    record.add_value(10000000);
    CPPUNIT_ASSERT_EQUAL(record, records[2]);
    record.reset();
    record.add_value("Jerry");
    record.add_value(17);
    record.add_value(478);
    CPPUNIT_ASSERT_EQUAL(record, records[3]);
    record.reset();
    record.add_value("George Washington");
    record.add_value(200);
    record.add_value(184616);
    CPPUNIT_ASSERT_EQUAL(record, records[4]);
    record.reset();
    record.add_value("Denzel Washington");
    record.add_value(50);
    record.add_value(1000);
    CPPUNIT_ASSERT_EQUAL(record, records[5]);
}

void Test_01_Table::test_augment_new_row_dead()
{
    Table table;
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    table.augment_new_rows_transaction_begin();
    table.augment_new_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(false, table.is_alive());
}