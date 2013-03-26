#ifndef T11_TEST21_PARENTANDSTAR_N2S_H
#define T11_TEST21_PARENTANDSTAR_N2S_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

/**
 * This file tests for Parent and Parent* Relation with 0 or 1
 * synonym arguments.
 */
class Test21_ParentAndStar_N2S: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test21_ParentAndStar_N2S);
CPPUNIT_TEST(test_parent_X_syn);
CPPUNIT_TEST(test_parentStar_X_syn);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_parent_X_syn();
    void test_parentStar_X_syn();

    std::string SIMPLE_PROG;
};

#endif