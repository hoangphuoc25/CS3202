#ifndef T11_TEST_00_SET_WRAPPER_H
#define T11_TEST_00_SET_WRAPPER_H

#ifndef T11_TEST_HELPER_H
#define T11_TEST_HELPER_H

#include <cppunit/extensions/HelperMacros.h>

class Test_00_SetWrapper: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test_00_SetWrapper);
CPPUNIT_TEST(test_set_ctor);
CPPUNIT_TEST(test_list_ctor);
CPPUNIT_TEST(test_copy_ctor);
CPPUNIT_TEST(test_equality);
CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
protected:
    void test_set_ctor();
    void test_list_ctor();
    void test_copy_ctor();
    void test_equality();
};

#endif

#endif