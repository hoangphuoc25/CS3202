#ifndef T11_TEST_30_PKB_Affects_H
#define T11_TEST_30_PKB_Affects_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test_30_PKB_Affects: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test_30_PKB_Affects);
CPPUNIT_TEST(test_affects);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_affects();
};

#endif