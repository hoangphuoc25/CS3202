#include <string>
#include <map>
#include <memory>
#include "Test_30_PKB_Parent.h"
#include "../SPA/Parser.h"
#include "../SPA/PKB.h"
#include "../SPA/SetWrapper.h"

using std::auto_ptr;
using std::string;
using std::map;


void Test_30_PKB_Parent::setUp()
{
    this->TEST_MODIFIES_SIMPLE_PROG =
        "procedure pOne { \
           aone = b + c; \
           d3 = 5 + 7; \
           while x { \
             this = bx + d3; \
             while a { \
               x1 = b + ha; \
               if g2 then { \
                 t1 = t + bab; \
                 h2 = 2 + ga; \
                 call secProc; \
                 while ten { \
                   y = y + ue; \
                 } \
                 if tp then { \
                   while one { \
                     x = y + z; \
                     call thirdProc; \
                   } \
                 } else { \
                   fire = a + fire; \
                 } \
               } else { \
                 xe = a * cab; \
               } \
               good = evil + evil; \
               pe = 2 * 3 + zt1; \
             } \
             fol = y + g2; \
           } \
           g2 = xz + brave; \
         } \
         procedure secProc { \
           a = b + c; \
           xe = 2 + 73; \
           while gg { \
             onceOnly = true; \
             if twice then { \
               all = 3 * 5; \
             } else { \
               none = bba; \
               while p { \
                 if xe then { \
                   harp = 41; \
                 } else { \
                   nn = ba1; \
                 } \
               } \
             } \
           } \
           call procFOUR; \
         } \
         procedure thirdProc { \
           hoho = merry + christmas; \
           haa = haas; \
         } \
         procedure procFOUR { \
           pfg = pf + g; \
           while x { \
             ue = no ; \
           } \
         } \
         procedure cleanUP { \
           zzz = 512; \
         }";
}

void Test_30_PKB_Parent::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test_30_PKB_Parent);

void Test_30_PKB_Parent::test_parent_X_assign()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    // Parent(while,assign)
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "11"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "14"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "25"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "38"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, 0);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_ASSIGN, -1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);

    // Parent(if,assign)
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "13"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "27"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "27"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "31"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "31"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, 0);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_ASSIGN, -1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);

    // Parent(stmt,assign)
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "11"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "14"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "13"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "25"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "27"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "27"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "31"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "31"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "38"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, 0);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_ASSIGN, -1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);

    // Parent(prog_line,assign)
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "11"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "14"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "13"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "25"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "27"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "27"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "31"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "31"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "38"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, 0);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_ASSIGN, -1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
}

void Test_30_PKB_Parent::test_parent_X_call()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    // Parent(while,call)
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "14"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, 0);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_CALL, -1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);

    // Parent(if,call)
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, 0);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_CALL, -1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);

    // Parent(stmt,call)
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "14"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, 0);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_CALL, -1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);

    // Parent(prog_line,call)
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "14"), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, 0);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_CALL, -1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
}

void Test_30_PKB_Parent::test_parent_X_if()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    // Parent(while,if)
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "25"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "30"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, 0);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_IF, -1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);

    // Parent(if,if)
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, 0);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_IF, -1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);

    // Parent(stmt,if)
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "25"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "30"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, 0);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_IF, -1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);

    // Parent(prog_line,if)
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "25"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "30"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, 0);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_IF, -1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
}

void Test_30_PKB_Parent::test_parent_X_while()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    // Parent(while,while)
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, 0);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_WHILE, -1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);

    // Parent(if,while)
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "13"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "27"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, 0);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_WHILE, -1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);

    // Parent(stmt,while)
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "13"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "27"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, 0);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_WHILE, -1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);

    // Parent(prog_line,while)
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "13"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "27"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, 0);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_WHILE, -1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
}

void Test_30_PKB_Parent::test_parent_X_stmt()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    // Parent(while,stmt)
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "11"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "14"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "14"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "25"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "25"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "30"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "38"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, 0);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_STMT, -1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);

    // Parent(if,stmt)
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "13"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "13"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "27"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "27"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "27"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "31"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "31"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, 0);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_STMT, -1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);

    // Parent(stmt,stmt)
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "11"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "13"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "14"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "14"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "13"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "25"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "25"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "27"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "27"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "27"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "30"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "31"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "31"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "38"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 0);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, -1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);

    // Parent(prog_line,stmt)
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "11"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "13"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "14"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "14"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "13"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "25"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "25"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "27"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "27"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "27"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "30"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "31"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "31"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "38"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, 0);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_STMT, -1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
}

void Test_30_PKB_Parent::test_parent_X_progline()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    // Parent(while,prog_line)
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "11"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "14"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "14"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "25"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "25"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "30"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "38"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, 0);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_WHILE,
            ENT_PROGLINE, -1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);

    // Parent(if,prog_line)
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "13"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "13"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "27"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "27"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "27"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "31"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "31"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, 0);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_IF,
            ENT_PROGLINE, -1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);

    // Parent(stmt,prog_line)
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "11"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "13"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "14"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "14"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "13"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "25"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "25"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "27"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "27"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "27"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "30"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "31"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "31"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "38"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, 0);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_PROGLINE, -1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);

    // Parent(prog_line,prog_line)
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "11"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "13"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "14"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "14"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "13"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "25"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "25"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "27"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "27"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "27"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "30"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "31"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "31"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "38"),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, 0);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    stringSet = pkb->parent_X_Y_get_int_X_from_int_Y(ENT_PROGLINE,
            ENT_PROGLINE, -1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
}