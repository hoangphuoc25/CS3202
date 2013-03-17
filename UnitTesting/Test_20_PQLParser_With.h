#ifndef T04_TEST_20_PQLPARSER_WITH_H
#define T04_TEST_20_PQLPARSER_WITH_H

#include <map>
#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test_20_PQLParser_With: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test_20_PQLParser_With);
CPPUNIT_TEST(test_with_string_string_same);
CPPUNIT_TEST(test_with_string_string_different_halt);
CPPUNIT_TEST(test_err_parse_dquoted_ident_invalid);
CPPUNIT_TEST(test_err_parse_dquoted_ident_missing_close_quote);
CPPUNIT_TEST(test_err_parse_ref_integer_error_str);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

private:
    char *buf;
    static const int BUFLEN = 10000;

    void test_with_string_string_same();
    void test_with_string_string_different_halt();

    void test_err_parse_dquoted_ident_invalid();
    void test_err_parse_dquoted_ident_missing_close_quote();
    void test_err_parse_ref_integer_error_str();
};

#endif