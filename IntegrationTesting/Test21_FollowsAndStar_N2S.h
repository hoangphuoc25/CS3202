#ifndef T11_TEST21_FOLLOWSANDSTAR_N2S_H
#define T11_TEST21_FOLLOWSANDSTAR_N2S_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

/**
 * This file tests for Parent and Parent* Relation with 0 or 1
 * synonym arguments.
 */
class Test21_FollowsAndStar_N2S: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test21_FollowsAndStar_N2S);
CPPUNIT_TEST(test_follows_syn_X);
CPPUNIT_TEST(test_followsStar_syn_X);
CPPUNIT_TEST(test_follows_X_syn);
CPPUNIT_TEST(test_followsStar_X_syn);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    std::string SIMPLE_PROG;

    void test_follows_syn_X();
    void test_followsStar_syn_X();
    void test_follows_X_syn();
    void test_followsStar_X_syn();
};

#endif