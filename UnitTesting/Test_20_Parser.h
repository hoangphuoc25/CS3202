#ifndef T11_TEST_20_PARSER_H
#define T11_TEST_20_PARSER_H

#include <cppunit/extensions/HelperMacros.h>
#include "../SPA/Node.h"

class Test_20_Parser: public CPPUNIT_NS::TestFixture {

CPPUNIT_TEST_SUITE(Test_20_Parser);
//CPPUNIT_TEST(test_one);
//CPPUNIT_TEST(test_two);
//CPPUNIT_TEST(test_three);
//CPPUNIT_TEST(test_four);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

private:
    void test_one();
    void test_two();
    void test_three();
    void test_four();
    void dump(Node* n);

};

#endif