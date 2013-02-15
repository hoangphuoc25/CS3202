#ifndef T11_TEST_PKB_H
#define T11_TEST_PKB_H

#include <cppunit/extensions/HelperMacros.h>
#include <set>
#include <string>

using std::set;


class Test_30_PKB: public CPPUNIT_NS::TestFixture {

CPPUNIT_TEST_SUITE(Test_30_PKB);
CPPUNIT_TEST(test_one);
CPPUNIT_TEST(test_retrieve_all_X);
CPPUNIT_TEST(test_modifies_procedure_var);
CPPUNIT_TEST(test_modifies_assign_var);
CPPUNIT_TEST(test_modifies_call_var);
CPPUNIT_TEST(test_modifies_if_var);
CPPUNIT_TEST(test_modifies_while_var);
CPPUNIT_TEST(test_modifies_stmt_var);
CPPUNIT_TEST(test_modifies_progline_var);
CPPUNIT_TEST(test_uses_procedure_var);
CPPUNIT_TEST(test_uses_assign_var);
CPPUNIT_TEST(test_uses_call_var);
CPPUNIT_TEST(test_uses_if_var);
CPPUNIT_TEST(test_uses_while_var);
CPPUNIT_TEST(test_uses_stmt_var);
CPPUNIT_TEST(test_uses_progline_var);
CPPUNIT_TEST(test_has_assign);
CPPUNIT_TEST(test_has_call);
CPPUNIT_TEST(test_has_if);
CPPUNIT_TEST(test_has_while);
CPPUNIT_TEST(test_has_stmt);
CPPUNIT_TEST(test_has_progline);
CPPUNIT_TEST(test_has_stmtLst);
CPPUNIT_TEST(test_has_const);
CPPUNIT_TEST(test_has_variable);
//CPPUNIT_TEST(test_two);
//CPPUNIT_TEST(test_three);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

private:
    std::string TEST_MODIFIES_SIMPLE_PROG;
    std::string TEST_USES_SIMPLE_PROG;

    void test_one();
    void test_retrieve_all_X();
    // pOne modifies:
    // a, all, aone, d3, fire, fol, g2, good, h2, haa, harp, hoho, nn,
    // none, onceOnly, pe, pfg, t1, this, ue, x, x1, xe, y
    //
    // secProc modifies:
    // a, all, harp, nn, none, onceOnly, pfg, ue, xe
    //
    // thirdProc modifies:
    // haa, hoho
    //
    // procFOUR modifies:
    // pfg, ue
    //
    // cleanUP modifies:
    // zzz
    //
    // a - 3 [while], 5 [while], 7 [if], 10 [call], 23 [assign]
    // all - 3 [while], 5 [while], 7 [if], 10 [call], 25 [while],
    //       27 [if], 28 [assign]
    // aone - 1 [assign]
    // d3 - 2 [assign]
    // fire - 3 [while], 5 [while], 7 [if], 13 [if], 17 [assign]
    // fol - 3 [while], 21 [assign]
    // g2 - 22 [assign]
    // good - 3 [while], 5 [while], 19 [assign]
    // h2 - 3 [while], 5 [while], 7 [if], 9 [assign]
    // haa - 3 [while], 5 [while], 7 [if], 13 [if], 14 [while],
    //       16 [call], 36 [assign]
    // harp - 3 [while], 5 [while], 7 [if], 10 [call], 25 [while],
    //        27 [if], 30 [while], 31 [if], 32 [assign]
    // hoho - 3 [while], 5 [while], 7 [if], 13 [if], 14 [while],
    //        16 [call], 35 [assign]
    // nn - 3 [while], 5 [while], 7 [if], 10 [call], 25 [while],
    //      27 [if], 30 [while], 31 [if], 33 [assign]
    // none - 3 [while], 5 [while], 7 [if], 10 [call], 25 [while],
    //        27 [if], 29 [assign]
    // onceOnly - 3 [while], 5 [while], 7 [if], 10 [call], 25 [while],
    //            26 [assign]
    // pe - 3 [while], 5 [while], 20 [assign]
    // pfg - 3 [while], 5 [while], 7 [if], 10 [call], 34 [call],
    //       37 [assign]
    // t1 - 3 [while], 5 [while], 7 [if], 8 [assign]
    // this - 3 [while], 4 [assign]
    // ue - 3 [while], 5 [while], 7 [if], 10 [call], 34 [call],
    //      38 [while], 39 [assign]
    // x - 3 [while], 5 [while], 7 [if], 13 [if], 14 [while],
    //     15 [assign]
    // x1 - 3 [while], 5 [while], 6 [assign]
    // xe - 3 [while], 5 [while], 7 [if], 10 [call], 18 [assign]
    //      24 [assign]
    // y - 3 [while], 5 [while], 7 [if], 11 [while], 12 [assign]
    // zzz - 40 [assign]
    //
    // stmt 1 [assign] - aone
    // stmt 2 [assign] - d3
    // stmt 3 [while] - a, all, fire, fol, good, h2, haa, harp, hoho,
    //                  nn, none, onceOnly, pe, pfg, t1, ue, this, x,
    //                  x1, xe, y
    // stmt 4 [assign] - this
    // stmt 5 [while] - a, all, fire, good, h2, haa, harp, hoho,
    //                  onceOnly, nn, none, pe, pfg, t1, ue, x, x1, xe, y
    // stmt 6 [assign] - x1
    // stmt 7 [if] - a, all, fire, h2, haa, harp, hoho, nn, none, pfg,
    //               onceOnly, t1, ue, x, xe, y
    // stmt 8 [assign] - t1
    // stmt 9 [assign] - h2
    // stmt 10 [call] - a, all, harp, nn, none, onceOnly, pfg, ue, xe
    // stmt 11 [while] - y
    // stmt 12 [assign] - y
    // stmt 13 [if] - fire, haa, hoho, x
    // stmt 14 [while] - haa, hoho, x
    // stmt 15 [assign] - x
    // stmt 16 [call] - haa, hoho
    // stmt 17 [assign] - fire
    // stmt 18 [assign] - xe
    // stmt 19 [assign] - good
    // stmt 20 [assign] - pe
    // stmt 21 [assign] - fol
    // stmt 22 [assign] - g2
    //
    // secProc
    // stmt 23 [assign] - a
    // stmt 24 [assign] - xe
    // stmt 25 [while] - all, harp, nn, none, onceOnly
    // stmt 26 [assign] - onceOnly
    // stmt 27 [if] - all, harp, nn, none
    // stmt 28 [assign] - all
    // stmt 29 [assign] - none
    // stmt 30 [while] - harp, nn
    // stmt 31 [if] - harp, nn
    // stmt 32 [assign] - harp
    // stmt 33 [assign] - nn
    // stmt 34 [call] - pfg, ue
    //
    // thirdProc
    // stmt 35 [assign] - hoho
    // stmt 36 [assign] - haa
    //
    // procFour
    // stmt 37 [assign] - pfg
    // stmt 38 [while] - ue
    // stmt 39 [assign] - ue
    //
    // cleanUP
    // stmt 40 [assign] - zzz
    void test_modifies_procedure_var();
    void test_modifies_assign_var();
    void test_modifies_call_var();
    void test_modifies_if_var();
    void test_modifies_while_var();
    void test_modifies_stmt_var();
    void test_modifies_progline_var();

    // Test Uses: variables - Statements which use them
    // a - 3 [while], 5 [while], 7 [if], 13 [if], 17 [assign], 18 [assign]
    // b - 1 [assign], 3 [while], 5 [while], 6 [assign], 7 [if], 10 [call],
    //     23 [assign]
    // ba1 - 3 [while], 5 [while], 7 [if], 10 [call], 25 [while], 27 [if]
    //       30 [while], 31 [if], 33 [assign]
    // bab - 3 [while], 5 [while], 7 [if], 8 [assign]
    // bba - 3 [while], 5 [while], 7 [if], 10 [call], 25 [while], 27 [if]
    //       29 [assign]
    // brave - 22 [assign]
    // bx - 3 [while], 4 [assign]
    // c - 1 [assign], 3 [while], 5 [while], 7 [if], 10 [call], 23 [assign]
    // cab - 3 [while], 5 [while], 7 [if], 18 [assign]
    // christmas - 3 [while], 5 [while], 7 [if], 13 [if], 14 [while],
    //             16 [call], 35 [assign]
    // d3 - 3 [while], 4 [assign]
    // evil - 3 [while], 5 [while], 19 [assign]
    // fire - 3 [while], 5 [while], 7 [if], 13 [if], 17 [assign]
    // g - 3 [while], 5 [while], 7 [if], 10 [call], 34 [call], 37 [assign]
    //     48 [call]
    // g2 - 3 [while], 5 [while], 7 [if], 21 [assign]
    // ga - 3 [while], 5 [while], 7 [if], 9 [assign]
    // gg - 3 [while], 5 [while], 7 [if], 10 [call], 25 [while]
    // ha - 3 [while], 5 [while], 6 [assign]
    // haas - 3 [while], 5 [while], 7 [if], 13 [if], 14 [while], 16 [call]
    //        36 [assign]
    // merry - 3 [while], 5 [while], 7 [if], 13 [if], 14 [while], 16 [call],
    //         35 [assign]
    // no - 3 [while], 5 [while], 7 [if], 10 [call], 34 [call], 38 [while],
    //      39 [assign], 48 [call]
    // one - 3 [while], 5 [while], 7 [if], 13 [if], 14 [while]
    // p - 3 [while], 5 [while], 7 [if], 10 [call], 25 [while], 27 [if]
    //     30 [while]
    // pf - 3 [while], 5 [while], 7 [if], 10 [call], 34 [call], 37 [assign],
    //      48 [call]
    // t - 3 [while], 5 [while], 7 [if], 8 [assign]
    // ten - 3 [while], 5 [while], 7 [if], 11 [while]
    // tp - 3 [while], 5 [while], 7 [if], 13 [if]
    // true - 3 [while], 5 [while], 7 [if], 10 [call], 25 [while], 26 [assign]
    // twice - 3 [while], 5 [while], 7 [if], 10 [call], 25 [while], 27 [if]
    // ue - 3 [while], 5 [while], 7 [if], 11 [while], 12 [assign]
    // x - 3 [while], 5 [while], 7 [if], 10 [call], 34 [call], 38 [while],
    //     48 [call]
    // xe - 3 [while], 5 [while], 7 [if], 10 [call], 25 [while], 27 [if]
    //      30 [while], 31 [if]
    // xz - 22 [assign]
    // y - 3 [while], 5 [while], 7 [if], 11 [while], 12 [assign], 13 [if],
    //     14 [while], 15 [assign], 21 [assign]
    // z - 3 [while], 5 [while], 7 [if], 13 [if], 14 [while], 15 [assign]
    // zt1 - 3 [while], 5 [while], 20 [assign]
    // zzz - 49 [assign]
    //
    // pOne uses:
    // a, b, ba1, bab, bba, brave, bx, c, cab, christmas, d3, evil,
    // fire, g, g2, ga, gg, ha, haas, merry, no, one, p, pf, t, ten,
    // tp, true, twice, ue, x, xe, xz, y, z, zt1
    //
    // stmt 1 [assign] - b, c
    // stmt 2 [assign] - #
    // stmt 3 [while] - a, b, ba1, bab, bba, bx, c, cab, christmas, d3,
    //                  evil, fire, g, g2, ga, gg, ha, haas, merry, no,
    //                  one, p, pf, t, ten, tp, true, twice, ue, x, xe,
    //                  y, z, zt1
    // stmt 4 [assign] - bx, d3
    // stmt 5 [while] - a, b, ba1, bab, bba, c, cab, christmas, evil,
    //                  fire, g, g2, ga, gg,  ha, haas, merry, no, one,
    //                  p, pf, t, ten, tp, true, twice, ue, x, xe, y,
    //                  z, zt1
    // stmt 6 [assign] - b, ha
    // stmt 7 [if] - a, b, ba1, bab, bba, c, cab, christmas, fire, g,
    //               g2, ga, gg, haas, merry, no, one, p, pf, t, ten,
    //               tp, true, twice, ue, x, xe, y, z
    // stmt 8 [assign] - bab, t
    // stmt 9 [assign] - ga
    // stmt 10 [call, secProc] - b, ba1, bba, c, g, gg, no, p, pf, true,
    //                           twice, x, xe
    // stmt 11 [while] - ten, ue, y
    // stmt 12 [assign] - ue, y
    // stmt 13 [if] - a, christmas, fire, haas, merry, one, tp, y, z
    // stmt 14 [while] - christmas, haas, merry, one, y, z
    // stmt 15 [assign] - y, z
    // stmt 16 [call, thirdProc] - christmas, haas, merry
    // stmt 17 [assign] - a, fire
    // stmt 18 [assign] - a, cab
    // stmt 19 [assign] - evil
    // stmt 20 [assign] - zt1
    // stmt 21 [assign] - g2, y
    // stmt 22 [assign] - brave, xz
    //
    // secProc uses:
    // b, ba1, bba, c, g, gg, no, p, pf, true, twice, x, xe
    // stmt 23 [assign] - b, c
    // stmt 24 [assign] - #
    // stmt 25 [while] - ba1, bba, gg, p, true, twice, xe
    // stmt 26 [assign] - true
    // stmt 27 [if] - ba1, bba, p, twice, xe
    // stmt 28 [assign] - #
    // stmt 29 [assign] - bba
    // stmt 30 [while] - ba1, p, xe
    // stmt 31 [if] - ba1, xe
    // stmt 32 [assign] - #
    // stmt 33 [assign] - ba1
    // stmt 34 [call, procFOUR] - g, no, pf, x
    //
    // thirdProc uses:
    // christmas, haas, merry
    // stmt 35 [assign] - merry, christmas
    // stmt 36 [assign] - haas
    //
    // procFOUR uses:
    // g, no, pf, x
    // stmt 37 [assign] - g, pf
    // stmt 38 [while] - no, x
    // stmt 39 [assign] - no
    //
    // execute uses:
    // #
    // stmt 40 [assign] - #
    // stmt 41 [assign] - #
    // stmt 42 [assign] - #
    // stmt 43 [assign] - #
    //
    // useCall uses:
    // g, no, pf, x
    // stmt 44 [assign] - #
    // stmt 45 [assign] - #
    // stmt 46 [assign] - #
    // stmt 47 [assign] - #
    // stmt 48 [call, procFOUR] - g, no, pf, x
    //
    // useOne uses:
    // zzz
    // stmt 49 [assign] - zzz
    void test_uses_procedure_var();
    void test_uses_assign_var();
    void test_uses_call_var();
    void test_uses_if_var();
    void test_uses_while_var();
    void test_uses_stmt_var();
    void test_uses_progline_var();

    // Test has_X methods
    // We use the TEST_MODIFIES_SIMPLE_PROG
    void test_has_assign();
    void test_has_call();
    void test_has_if();
    void test_has_while();
    void test_has_stmt();
    void test_has_progline();
    void test_has_stmtLst();
    void test_has_const();
    void test_has_variable();
    void test_two();
    void test_three();
};

#endif