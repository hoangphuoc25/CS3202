#ifndef T11_TEST_11_SELECT_DISJOINT_TABLES_H
#define T11_TEST_11_SELECT_DISJOINT_TABLES_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test_11_SelectDisjointTables: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test_11_SelectDisjointTables);
CPPUNIT_TEST(test_select_disjoint_tables);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_select_disjoint_tables();
};

#endif