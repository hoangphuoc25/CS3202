#ifndef T11_TEST21_NEXTANDSTAR_N2S_H
#define T11_TEST21_NEXTANDSTAR_N2S_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

/**
 * This file tests for Parent and Parent* Relation with 0 or 1
 * synonym arguments.
 */
class Test21_NextAndStar_N2S: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test21_NextAndStar_N2S);
CPPUNIT_TEST(test_next_syn_X);
CPPUNIT_TEST(test_nextStar_syn_X);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    std::string SIMPLE_PROG;

    void test_next_syn_X();
    void test_nextStar_syn_X();
};

#endif