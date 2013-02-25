#ifndef T11_TEST10_22_MODIFIES_H
#define T11_TEST10_22_MODIFIES_H

#include <map>
#include <set>
#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test10_22_Modifies: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test10_22_Modifies);
CPPUNIT_TEST(test_modifies_assign_var);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

private:
    void test_modifies_assign_var();
    std::string MODIFIES_10_SIMPLE_PROG;
};

#endif