#ifndef T11_TEST00_QE_MISC_H
#define T11_TEST01_QE_MISC_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test00_QE_misc: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test00_QE_misc);
CPPUNIT_TEST(test_readconfig);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_readconfig();
};

#endif