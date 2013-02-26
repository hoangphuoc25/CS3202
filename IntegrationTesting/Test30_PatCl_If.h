#ifndef T11_TEST30_PATCL_IF_H
#define T11_TEST30_PATCL_IF_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test30_PatCl_If: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test30_PatCl_If);
CPPUNIT_TEST(test_if_var_syn_11);
CPPUNIT_TEST(test_if_var_syn_22);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_if_var_syn_11();
    void test_if_var_syn_22();
};

#endif