#ifndef TEST_00_SELECT_NO_CLAUSE_H
#define TEST_00_SELECT_NO_CLAUSE_H

#include "TestHelper.h"

class Test_00_SelectNoClause: public TestHelper {
CPPUNIT_TEST_SUITE(Test_00_SelectNoClause);
CPPUNIT_TEST(test_select_one_syn);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_select_one_syn();
};

#endif