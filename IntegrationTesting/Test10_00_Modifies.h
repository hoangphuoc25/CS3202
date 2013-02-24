#ifndef T11_TEST10_00_MODIFIES_H
#define T11_TEST10_00_MODIFIES_H

#include <map>
#include <set>
#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test10_00_Modifies: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test10_00_Modifies);
CPPUNIT_TEST(test_modifies_assign_var);
CPPUNIT_TEST(test_modifies_procedure_var);
CPPUNIT_TEST(test_modifies_call_var);
CPPUNIT_TEST(test_modifies_while_var);
CPPUNIT_TEST(test_modifies_if_var);
CPPUNIT_TEST(test_modifies_stmt_var);
CPPUNIT_TEST(test_modifies_progline_var);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

private:
    void test_modifies_assign_var();
    void test_modifies_procedure_var();
    void test_modifies_call_var();
    void test_modifies_while_var();
    void test_modifies_if_var();
    void test_modifies_stmt_var();
    void test_modifies_progline_var();
    std::string MODIFIES_00_PROG;
};

// procOne
// x, a, b, y, kerb, big, g2, xcz, well, vv, noway, hi, thank
// xyz, aa, yes, im, dont, xc,

// ascP
// xcz, a, well, x, vv, noway, hi, thank

// doSmth
// yes, im, dont

// cleanUp
// im

// procedure procOne
// stmt 1 [assign] - x
// stmt 2 [assign] - a
// stmt 3 [assign] - b
// stmt 4 [while] - y, kerb, big, a, g2, xcz, well, x, vv, noway, hi, thank,
//                  xyz, aa
// stmt 5 [assign] - y
// stmt 6 [if] - kerb, big, a
// stmt 7 [assign] - kerb
// stmt 8 [assign] - big
// stmt 9 [assign] - a
// stmt 10 [assign] - g2
// stmt 11 [if] - xcz, a, well, x, vv, noway, hi, thank, xyz, aa
// stmt 12 [call ascP] - xcz, a, well, x, vv, noway, hi, thank
// stmt 13 [assign] - xyz
// stmt 14 [assign] - aa
// stmt 15 [call doSmth] - yes, im, dont
// stmt 16 [assign] - well
// stmt 17 [if] - a
// stmt 18 [assign] - aa
// stmt 19 [assign] - aa
// stmt 20 [assign] - xc

// procedure ascP
// stmt 21 [if] - xcz, a, well, x, vv, noway
// stmt 22 [assign] - xcz
// stmt 23 [while] - a, well, x
// stmt 24 [while] - a, well
// stmt 25 [assign] - a
// stmt 26 [assign] - well
// stmt 27 [assign] - x
// stmt 28 [assign] - vv
// stmt 29 [assign] - noway
// stmt 30 [assign] - x
// stmt 31 [assign] - hi
// stmt 32 [assign] - thank

// procedure doSmth
// stmt 33 [assign] - yes
// stmt 34 [call cleanUp] - im
// stmt 35 [assign] - dont

// procedure cleanUp
// stmt 36 [assign] - im

#endif