#ifndef T11_TEST_PKB_H
#define T11_TEST_PKB_H

#include <cppunit/extensions/HelperMacros.h>
#include <set>


using std::set;


class TestPKB: public CPPUNIT_NS::TestFixture {

CPPUNIT_TEST_SUITE(TestPKB);
CPPUNIT_TEST(test_one);
CPPUNIT_TEST(test_retrieve_all_X);
CPPUNIT_TEST(test_modifies);
CPPUNIT_TEST(test_uses);
//CPPUNIT_TEST(test_two);
//CPPUNIT_TEST(test_three);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

private:
    void test_one();
    void test_retrieve_all_X();
    void test_modifies();

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
    void test_uses();
    void test_two();
    void test_three();
};

#endif