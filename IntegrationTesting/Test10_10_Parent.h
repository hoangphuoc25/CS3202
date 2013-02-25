#ifndef T11_TEST10_10_PARENT_H
#define T11_TEST10_10_PARENT_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test10_10_Parent: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test10_10_Parent);
CPPUNIT_TEST(test_parent_while_call);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_parent_while_call();
};

#endif