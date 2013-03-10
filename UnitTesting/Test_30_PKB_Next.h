#ifndef T11_TEST_30_PKB_Next_H
#define T11_TEST_30_PKB_Next_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test_30_PKB_Next: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test_30_PKB_Next);
CPPUNIT_TEST(test_next);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_next();
};

#endif