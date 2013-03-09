#ifndef T11_TEST_30_PKB_HAS_ANY_ENT_H
#define T11_TEST_30_PKB_HAS_ANY_ENT_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

/**
 * This file tests for Modifies Relation with 0 or 1
 * synonym arguments.
 */
class Test_30_PKB_has_any_ent: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test_30_PKB_has_any_ent);
CPPUNIT_TEST(test_has_any_ent);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_has_any_ent();
};

#endif