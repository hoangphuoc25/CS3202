#ifndef T11_TEST_30_PKB_HAS_X_H
#define T11_TEST_30_PKB_HAS_X_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

/**
 * This file tests the has_any_X methods in the PKB
 */
class Test_30_PKB_has_X: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test_30_PKB_has_X);
CPPUNIT_TEST(test_has_call_procName);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_has_call_procName();
};

#endif