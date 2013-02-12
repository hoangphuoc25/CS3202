#ifndef T11_TEST_02_RESULTSTABLE_H
#define T11_TEST_02_RESULTSTABLE_H

#include <cppunit/extensions/HelperMacros.h>

class Test_02_ResultsTable: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test_02_ResultsTable);
CPPUNIT_TEST(test_syn_0_transaction);
CPPUNIT_TEST(test_syn_1_transaction);
CPPUNIT_TEST(test_syn_00_transaction_ss);
CPPUNIT_TEST(test_syn_00_transaction_si);
CPPUNIT_TEST(test_syn_00_transaction_is);
CPPUNIT_TEST(test_syn_00_transaction_ii);
CPPUNIT_TEST(test_syn_01_transaction_s);
CPPUNIT_TEST(test_syn_01_transaction_i);
CPPUNIT_TEST(test_syn_11_transaction);
CPPUNIT_TEST(test_syn_22_transaction);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

private:
    void test_syn_0_transaction();
    void test_syn_1_transaction();
    void test_syn_00_transaction_ss();
    void test_syn_00_transaction_si();
    void test_syn_00_transaction_is();
    void test_syn_00_transaction_ii();
    void test_syn_01_transaction_s();
    void test_syn_01_transaction_i();
    void test_syn_11_transaction();
    void test_syn_22_transaction();
};

#endif