#ifndef T11_TEST60_PARSE_FROM_FILE_H
#define T11_TEST60_PARSE_FROM_FILE_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test60_ParseFromFile: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test60_ParseFromFile);
CPPUNIT_TEST(test_parse_from_file);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_parse_from_file();
};

#endif