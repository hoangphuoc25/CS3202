#ifndef T11_TEST10_01_PARENT_H
#define T11_TEST10_01_PARENT_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test10_01_Parent: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test10_01_Parent);
CPPUNIT_TEST(test_parent_if_assign);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_parent_if_assign();
};

#endif