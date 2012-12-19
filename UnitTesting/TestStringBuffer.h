#ifndef T11_TEST_STRINGBUFFER_H
#define T11_TEST_STRINGBUFFER_H

#include <cppunit/extensions/HelperMacros.h>

class TestStringBuffer: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(TestStringBuffer);
CPPUNIT_TEST(testAppendChar);
CPPUNIT_TEST(testAppendCString);
CPPUNIT_TEST(testAppendString);
CPPUNIT_TEST(testAppendMixed);
CPPUNIT_TEST(testClear);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

private:
    void testAppendChar();
    void testAppendCString();
    void testAppendString();
    void testAppendMixed();
    void testClear();
};

#endif