#ifndef T04_TEST_20_PQLPARSER_WITH_H
#define T04_TEST_20_PQLPARSER_WITH_H

#include <map>
#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test_20_PQLParser_With: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test_20_PQLParser_With);
CPPUNIT_TEST(test_with_string_string_same);
CPPUNIT_TEST(test_with_string_string_different_halt);
CPPUNIT_TEST(test_with_int_int_same);
CPPUNIT_TEST(test_with_int_int_different_halt);
CPPUNIT_TEST(test_with_normalize);
CPPUNIT_TEST(test_with_contradiction);
CPPUNIT_TEST(test_err_parse_dquoted_ident_invalid);
CPPUNIT_TEST(test_err_parse_dquoted_ident_missing_close_quote);
CPPUNIT_TEST(test_err_parse_ref_integer_error_str);
CPPUNIT_TEST(test_err_parse_withclause_ref_synonym_undeclared);
CPPUNIT_TEST(test_err_parse_withclause_ref_synonym_not_progline);
CPPUNIT_TEST(test_err_parse_withclause_type_mismatch);
CPPUNIT_TEST(test_err_parse_withclause_and_nosep);
CPPUNIT_TEST(test_err_parse_withclause_expect_ref_on_rhs);
CPPUNIT_TEST(test_err_parse_withclause_expect_with);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

private:
    char *buf;
    static const int BUFLEN = 10000;

    void test_with_string_string_same();
    void test_with_string_string_different_halt();
    void test_with_int_int_same();
    void test_with_int_int_different_halt();
    void test_with_normalize();
    void test_with_contradiction();

    void test_err_parse_dquoted_ident_invalid();
    void test_err_parse_dquoted_ident_missing_close_quote();
    void test_err_parse_ref_integer_error_str();
    void test_err_parse_withclause_ref_synonym_undeclared();
    void test_err_parse_withclause_ref_synonym_not_progline();
    void test_err_parse_withclause_type_mismatch();
    void test_err_parse_withclause_and_nosep();
    void test_err_parse_withclause_expect_ref_on_rhs();
    void test_err_parse_withclause_expect_with();
};

#endif