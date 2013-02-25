#ifndef T11_TEST_PKB_PARENT_H
#define T11_TEST_PKB_PARENT_H

#include <cppunit/extensions/HelperMacros.h>
#include <set>
#include <string>

using std::set;


class Test_30_PKB_Parent: public CPPUNIT_NS::TestFixture {

CPPUNIT_TEST_SUITE(Test_30_PKB_Parent);
CPPUNIT_TEST(test_parent_X_assign);
CPPUNIT_TEST(test_parent_X_call);
CPPUNIT_TEST(test_parent_X_if);
CPPUNIT_TEST(test_parent_X_while);
CPPUNIT_TEST(test_parent_X_stmt);
CPPUNIT_TEST(test_parent_X_progline);
CPPUNIT_TEST(test_parent_while_Y);
CPPUNIT_TEST(test_parent_if_Y);
CPPUNIT_TEST(test_parent_stmt_Y);
CPPUNIT_TEST(test_parent_progline_Y);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

private:
    std::string TEST_MODIFIES_SIMPLE_PROG;

    void test_parent_X_assign();
    void test_parent_X_call();
    void test_parent_X_if();
    void test_parent_X_while();
    void test_parent_X_stmt();
    void test_parent_X_progline();
    void test_parent_while_Y();
    void test_parent_if_Y();
    void test_parent_stmt_Y();
    void test_parent_progline_Y();
};

#endif
/*
  "procedure pOne { \
01   aone = b + c; \
02   d3 = 5 + 7; \
03   while x { \
04     this = bx + d3; \
05     while a { \
06       x1 = b + ha; \
07       if g2 then { \
08         t1 = t + bab; \
09         h2 = 2 + ga; \
10         call secProc; \
11         while ten { \
12           y = y + ue; \
           } \
13         if tp then { \
14           while one { \
15             x = y + z; \
16             call thirdProc; \
             } \
           } else { \
17           fire = a + fire; \
           } \
         } else { \
18         xe = a * cab; \
         } \
19       good = evil + evil; \
20       pe = 2 * 3 + zt1; \
       } \
21     fol = y + g2; \
     } \
22   g2 = xz + brave; \
   } \
   procedure secProc { \
23   a = b + c; \
24   xe = 2 + 73; \
25   while gg { \
26     onceOnly = true; \
27     if twice then { \
28       all = 3 * 5; \
       } else { \
29       none = bba; \
30       while p { \
31         if xe then { \
32           harp = 41; \
           } else { \
33           nn = ba1; \
           } \
         } \
       } \
     } \
34   call procFOUR; \
   } \
   procedure thirdProc { \
35   hoho = merry + christmas; \
36   haa = haas; \
   } \
   procedure procFOUR { \
37   pfg = pf + g; \
38   while x { \
39     ue = no ; \
     } \
   } \
   procedure cleanUP { \
40   zzz = 512; \
   }";
*/