#ifndef T11_TEST10_22_USES_H
#define T11_TEST10_22_USES_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test10_22_Uses: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test10_22_Uses);
CPPUNIT_TEST(test_uses_while_var);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_uses_while_var();
};

#endif