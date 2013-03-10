#ifndef T11_TEST_20_PQLPARSER_DEADQUERY_H
#define T11_TEST_20_PQLPARSER_DEADQUERY_H

#include <cppunit/extensions/HelperMacros.h>

class Test_20_PQLParser_DeadQuery: public CPPUNIT_NS::TestFixture {

CPPUNIT_TEST_SUITE(Test_20_PQLParser_DeadQuery);
CPPUNIT_TEST(test_kill_qinfo);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

private:
    void test_kill_qinfo();
};

#endif