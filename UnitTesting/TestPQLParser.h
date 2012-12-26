#ifndef T11_TEST_PQLPARSER_H
#define T11_TEST_PQLPARSER_H

#include <map>
#include <string>
#include <cppunit/extensions/HelperMacros.h>

class TestPQLParser: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(TestPQLParser);
CPPUNIT_TEST(test_one_decl_one);
CPPUNIT_TEST(test_one_decl);
CPPUNIT_TEST(test_mult_decl);
CPPUNIT_TEST(test_select_bool);
CPPUNIT_TEST(test_select_tuple);
CPPUNIT_TEST(test_select_attrRef);
CPPUNIT_TEST(test_modifies);
CPPUNIT_TEST(test_err_parse_decl_empty_syn);
CPPUNIT_TEST(test_err_parse_decl_repeated_syn);
CPPUNIT_TEST(test_err_parse_decl_invalid_syn);
CPPUNIT_TEST(test_err_parse_decl_ent_syn_invalid_sep);
CPPUNIT_TEST(test_err_parse_decl_no_terminator);
CPPUNIT_TEST(test_err_parse_no_select_after_decl);
CPPUNIT_TEST(test_err_select_undeclared);
CPPUNIT_TEST(test_err_select_undef_attrname);
CPPUNIT_TEST(test_err_select_undeclared_attrRef);
CPPUNIT_TEST(test_err_select_attrRef_syn_attrName_type_error);
CPPUNIT_TEST(test_err_select_invalid_attrRef);
CPPUNIT_TEST(test_err_select_tuple_no_close);
CPPUNIT_TEST(test_err_select_nothing);
CPPUNIT_TEST(test_err_rel_argone);
CPPUNIT_TEST(test_err_rel_no_comma);
CPPUNIT_TEST(test_err_rel_argtwo);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

private:
    char *buf;
    static const int BUFLEN = 10000;

    void test_one_decl_one();
    void test_one_decl();
    void test_mult_decl();
    void test_select_bool();
    void test_select_tuple();
    void test_select_attrRef();
    void test_modifies();
    void test_err_parse_decl_empty_syn();
    void test_err_parse_decl_repeated_syn();
    void test_err_parse_decl_invalid_syn();
    void test_err_parse_decl_ent_syn_invalid_sep();
    void test_err_parse_decl_no_terminator();
    void test_err_parse_no_select_after_decl();
    void test_err_select_undeclared();
    void test_err_select_undef_attrname();
    void test_err_select_undeclared_attrRef();
    void test_err_select_attrRef_syn_attrName_type_error();
    void test_err_select_invalid_attrRef();
    void test_err_select_tuple_no_close();
    void test_err_select_nothing();
    void test_err_rel_argone();
    void test_err_rel_no_comma();
    void test_err_rel_argtwo();
};

#endif