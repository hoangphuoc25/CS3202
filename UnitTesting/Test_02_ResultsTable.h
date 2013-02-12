#ifndef T11_TEST_02_RESULTSTABLE_H
#define T11_TEST_02_RESULTSTABLE_H

#include <cppunit/extensions/HelperMacros.h>

class Test_02_ResultsTable: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test_02_ResultsTable);
CPPUNIT_TEST(test_syn_0_transaction);
CPPUNIT_TEST(test_syn_1_transaction);
CPPUNIT_TEST(test_syn_11_transaction);
CPPUNIT_TEST(test_syn_22_transaction);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

private:
    void test_syn_0_transaction();
    void test_syn_1_transaction();
    void test_syn_11_transaction();
    void test_syn_22_transaction();
};

#endif