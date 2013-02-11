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
    record.add_synonym("a");
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_synonym("bad");
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
    record.reset();
    record.add_synonym("damn");
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
    record.add_synonym(126);
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_synonym(1718);
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
    record.add_synonym("man");
    record.add_synonym("great");
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_synonym("hell");
    record.add_synonym("cell");
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
    record.reset();
    record.add_synonym("yui");
    record.add_synonym("framework");
    CPPUNIT_ASSERT_EQUAL(record, records[2]);
    record.reset();
    record.add_synonym("ummmmS");
    record.add_synonym("amIright");
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
    record.add_synonym("gee");
    record.add_synonym(9321);
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_synonym("testMAn");
    record.add_synonym(7);
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
    record.reset();
    record.add_synonym("ide");
    record.add_synonym(33);
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
    record.add_synonym(89467);
    record.add_synonym("aday");
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_synonym(15);
    record.add_synonym("Fha1");
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
    record.add_synonym(8468);
    record.add_synonym(66);
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_synonym(12465);
    record.add_synonym(1);
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
    record.reset();
    record.add_synonym(342467);
    record.add_synonym(8);
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
    table.add_rows_transaction_begin();
    table.add_row(firstTable, firstRecords[0], "aOne", "a");
    table.add_row(firstTable, firstRecords[1], "aOne", "bad");
    table.add_row(firstTable, firstRecords[2], "aOne", "damn");
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
    record.add_synonym(3);
    record.add_synonym("good");
    record.add_synonym("a");
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_synonym(72);
    record.add_synonym("mkbma");
    record.add_synonym("bad");
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
    record.reset();
    record.add_synonym(6246);
    record.add_synonym("gsg");
    record.add_synonym("damn");
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
    table.add_rows_transaction_begin();
    table.add_row(firstTable, firstRecords[0], "varXE", 126);
    table.add_row(firstTable, firstRecords[1], "varXE", 1718);
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
    record.add_synonym(3);
    record.add_synonym("good");
    record.add_synonym(126);
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_synonym(72);
    record.add_synonym("mkbma");
    record.add_synonym(1718);
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
    table.add_rows_transaction_begin();
    table.add_row(firstTable, firstRecords[0], "yea", "man",
            "this", "great");
    table.add_row(firstTable, firstRecords[1], "yea", "hell",
            "this", "cell");
    table.add_row(firstTable, firstRecords[2], "yea", "yui",
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
    record.add_synonym(3);
    record.add_synonym("good");
    record.add_synonym("man");
    record.add_synonym("great");
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_synonym(72);
    record.add_synonym("mkbma");
    record.add_synonym("hell");
    record.add_synonym("cell");
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
    record.reset();
    record.add_synonym(6246);
    record.add_synonym("gsg");
    record.add_synonym("yui");
    record.add_synonym("framework");
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
    table.add_rows_transaction_begin();
    table.add_row(firstTable, firstRecords[0], "Hobo", "gee",
            "ballooo", 9321);
    table.add_row(firstTable, firstRecords[1], "Hobo", "testMAn",
            "ballooo", 7);
    table.add_row(firstTable, firstRecords[2], "Hobo", "ide",
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
    record.add_synonym(3);
    record.add_synonym("good");
    record.add_synonym("gee");
    record.add_synonym(9321);
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_synonym(72);
    record.add_synonym("mkbma");
    record.add_synonym("testMAn");
    record.add_synonym(7);
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
    record.reset();
    record.add_synonym(6246);
    record.add_synonym("gsg");
    record.add_synonym("ide");
    record.add_synonym(33);
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
    table.add_rows_transaction_begin();
    table.add_row(firstTable, firstRecords[0], "Tysav", 89467,
            "Muba", "aday");
    table.add_row(firstTable, firstRecords[1], "Tysav", 15,
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
    record.add_synonym(3);
    record.add_synonym("good");
    record.add_synonym(89467);
    record.add_synonym("aday");
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_synonym(72);
    record.add_synonym("mkbma");
    record.add_synonym(15);
    record.add_synonym("Fha1");
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
    table.add_rows_transaction_begin();
    table.add_row(firstTable, firstRecords[0], "gleha1", 8468,
            "aAdgr1", 66);
    table.add_row(firstTable, firstRecords[1], "gleha1", 12465,
            "aAdgr1", 1);
    table.add_row(firstTable, firstRecords[2], "gleha1", 342467,
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
    record.add_synonym(3);
    record.add_synonym("good");
    record.add_synonym(8468);
    record.add_synonym(66);
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_synonym(72);
    record.add_synonym("mkbma");
    record.add_synonym(12465);
    record.add_synonym(1);
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
    record.reset();
    record.add_synonym(6246);
    record.add_synonym("gsg");
    record.add_synonym(342467);
    record.add_synonym(8);
    CPPUNIT_ASSERT_EQUAL(record, records[2]);
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
    record.add_synonym("a");
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_synonym("great");
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

void Test_01_Table::test_augment_row_s()
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
    table.augment_rows_transaction_begin();
    table.augment_row(0, "third", "X");
    table.augment_row(4, "third", "up");
    // augment non-existent row
    table.augment_row(141, "third", "blah");
    table.augment_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    const vector<Record>& records = table.get_records();
    CPPUNIT_ASSERT_EQUAL(2, (int)records.size());
    Record record;
    record.reset();
    record.add_synonym("down");
    record.add_synonym("up");
    record.add_synonym("X");
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_synonym("blasphemy");
    record.add_synonym("nope");
    record.add_synonym("up");
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
}

void Test_01_Table::test_augment_row_i()
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
    table.augment_rows_transaction_begin();
    table.augment_row(0, "third", 61);
    table.augment_row(3, "third", 71882);
    table.augment_row(2, "third", 1567);
    table.augment_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    const vector<Record>& records = table.get_records();
    CPPUNIT_ASSERT_EQUAL(3, (int)records.size());
    Record record;
    record.reset();
    record.add_synonym("down");
    record.add_synonym("up");
    record.add_synonym(61);
    CPPUNIT_ASSERT_EQUAL(record, records[0]);
    record.reset();
    record.add_synonym("down");
    record.add_synonym("areFired");
    record.add_synonym(1567);
    CPPUNIT_ASSERT_EQUAL(record, records[1]);
    record.reset();
    record.add_synonym("no");
    record.add_synonym("way");
    record.add_synonym(71882);
    CPPUNIT_ASSERT_EQUAL(record, records[2]);
}

void Test_01_Table::test_augment_row_dead()
{
    Table table;
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    table.add_rows_transaction_begin();
    table.add_row("colOne", "valOne", "colTwo", 2);
    table.add_row("colOne", "valTwo", "colTwo", 141);
    table.add_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(true, table.is_alive());
    table.augment_rows_transaction_begin();
    table.augment_rows_transaction_end();
    CPPUNIT_ASSERT_EQUAL(false, table.is_alive());
}