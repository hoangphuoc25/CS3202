#ifndef T11_TEST_00_STRINGBUFFER_H
#define T11_TEST_00_STRINGBUFFER_H

#include <cppunit/extensions/HelperMacros.h>

class Test_00_StringBuffer: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test_00_StringBuffer);
CPPUNIT_TEST(testAppendChar);
CPPUNIT_TEST(testAppendCString);
CPPUNIT_TEST(testAppendString);
CPPUNIT_TEST(testAppendInt);
CPPUNIT_TEST(testAppendMixed);
CPPUNIT_TEST(testClear);
CPPUNIT_TEST(testStrcmp);
CPPUNIT_TEST(testCstr);
CPPUNIT_TEST(testSprintf);
CPPUNIT_TEST(testSubstitutef);
CPPUNIT_TEST(testRemovespaces);
CPPUNIT_TEST(testSize);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

private:
    void testAppendChar();
    void testAppendCString();
    void testAppendString();
    void testAppendInt();
    void testAppendMixed();
    void testClear();
    void testStrcmp();
    void testCstr();
    void testSprintf();
    void testSubstitutef();
    void testRemovespaces();
    void testSize();
};

#endif