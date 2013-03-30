#include <memory>
#include <set>
#include <string>
#include "Test_30_PKB_has_X.h"
#include "../SPA/Parser.h"
#include "../SPA/PKB.h"
#include "../SPA/PQL.h"
#include "../SPA/SetWrapper.h"

using std::auto_ptr;
using std::set;
using std::string;

void Test_30_PKB_has_X::setUp()
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

void Test_30_PKB_has_X::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test_30_PKB_has_X);

void Test_30_PKB_has_X::test_has_assign()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(1));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(2));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(3));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(4));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(5));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(6));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(7));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(8));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(9));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(10));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(11));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(12));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(13));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(14));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(15));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(16));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(17));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(18));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(19));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(20));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(21));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(22));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(23));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(24));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(25));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(26));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(27));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(28));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(29));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(30));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(31));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(32));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(33));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(34));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(35));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(36));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(37));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(38));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(39));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(40));
    // Out of range cases
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(0));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(-61));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(41));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(50));
}

void Test_30_PKB_has_X::test_has_call()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(1));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(2));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(3));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(4));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(5));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(6));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(7));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(8));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(9));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_call(10));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(11));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(12));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(13));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(14));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(15));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_call(16));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(17));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(18));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(19));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(20));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(21));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(22));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(23));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(24));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(25));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(26));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(27));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(28));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(29));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(30));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(31));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(32));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(33));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_call(34));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(35));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(36));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(37));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(38));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(39));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(40));
    // Out of range cases
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(0));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(-61));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(41));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(50));
}

void Test_30_PKB_has_X::test_has_if()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(1));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(2));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(3));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(4));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(5));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(6));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_if(7));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(8));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(9));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(10));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(11));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(12));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_if(13));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(14));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(15));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(16));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(17));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(18));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(19));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(20));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(21));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(22));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(23));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(24));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(25));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(26));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_if(27));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(28));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(29));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(30));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_if(31));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(32));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(33));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(34));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(35));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(36));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(37));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(38));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(39));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(40));
    // Out of range cases
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(0));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(-61));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(41));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(50));
}

void Test_30_PKB_has_X::test_has_while()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(1));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(2));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_while(3));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(4));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_while(5));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(6));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(7));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(8));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(9));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(10));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_while(11));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(12));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(13));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_while(14));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(15));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(16));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(17));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(18));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(19));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(20));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(21));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(22));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(23));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(24));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_while(25));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(26));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(27));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(28));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(29));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_while(30));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(31));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(32));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(33));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(34));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(35));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(36));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(37));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_while(38));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(39));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(40));
    // Out of range cases
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(0));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(-61));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(41));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(50));
}

void Test_30_PKB_has_X::test_has_stmt()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(1));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(2));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(3));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(4));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(5));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(6));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(7));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(8));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(9));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(10));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(11));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(12));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(13));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(14));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(15));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(16));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(17));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(18));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(19));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(20));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(21));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(22));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(23));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(24));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(25));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(26));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(27));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(28));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(29));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(30));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(31));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(32));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(33));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(34));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(35));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(36));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(37));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(38));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(39));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(40));
    // Out of range cases
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmt(0));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmt(-61));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmt(41));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmt(50));
}

void Test_30_PKB_has_X::test_has_progline()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(1));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(2));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(3));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(4));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(5));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(6));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(7));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(8));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(9));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(10));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(11));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(12));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(13));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(14));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(15));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(16));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(17));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(18));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(19));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(20));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(21));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(22));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(23));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(24));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(25));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(26));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(27));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(28));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(29));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(30));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(31));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(32));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(33));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(34));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(35));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(36));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(37));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(38));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(39));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(40));
    // Out of range cases
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_progline(0));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_progline(-61));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_progline(41));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_progline(50));
}

void Test_30_PKB_has_X::test_has_stmtLst()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(1));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(2));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(3));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(4));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(5));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(6));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(7));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(8));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(9));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(10));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(11));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(12));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(13));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(14));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(15));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(16));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(17));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(18));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(19));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(20));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(21));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(22));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(23));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(24));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(25));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(26));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(27));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(28));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(29));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(30));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(31));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(32));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(33));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(34));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(35));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(36));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(37));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(38));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(39));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(40));
    // Out of range cases
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(0));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(-61));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(41));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(50));
}

void Test_30_PKB_has_X::test_has_const()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_const(2));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_const(3));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_const(5));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_const(7));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_const(41));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_const(73));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_const(512));
    // negative tests
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_const(0));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_const(1000000));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_const(-15216));
}

void Test_30_PKB_has_X::test_has_variable()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    // variables: a, aone, all, b, ba1, bab, bba, brave, bx, c
    // cab, christmas, d3, evil, fire, fol, g, g2,
    // ga, gg, good, ha, haa, haas, harp, h2, hoho, merry
    // nn, no, none, onceOnly, one, p, pe, pf, pfg, t, t1, ten
    // this, tp, true, twice, ue, x, x1, xe, xz, y, z, zt1, zzz
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("a"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("aone"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("all"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("b"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("ba1"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("bab"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("bba"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("brave"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("bx"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("c"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("cab"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("christmas"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("d3"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("evil"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("fire"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("fol"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("g"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("g2"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("ga"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("gg"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("good"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("ha"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("haa"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("haas"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("harp"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("h2"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("hoho"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("merry"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("nn"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("no"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("none"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("onceOnly"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("one"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("p"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("pe"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("pf"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("pfg"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("t"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("t1"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("ten"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("this"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("tp"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("true"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("twice"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("ue"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("x"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("x1"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("xe"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("xz"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("y"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("z"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("zt1"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("zzz"));
    // negative cases
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_variable("NOSUCHVAR"));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_variable("Phoenix"));
}

void Test_30_PKB_has_X::test_has_procedure()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());

    CPPUNIT_ASSERT_EQUAL(true, pkb->has_procedure("pOne"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_procedure("secProc"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_procedure("thirdProc"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_procedure("procFOUR"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_procedure("cleanUP"));
    // negative tests
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_procedure("missingProc"));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_procedure("Pone"));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_procedure("main"));
}

void Test_30_PKB_has_X::test_has_call_procName()
{
    string simpleProg;
    simpleProg =
        "procedure A { \
           call B; \
           call C; \
         } \
         procedure B { \
           call F; \
         } \
         procedure C { \
           a = b; \
         } \
         procedure F { \
           x = y; \
         } \
         procedure G { \
           call H; \
           call C; \
         } \
         procedure H { \
           lo = behold; \
         } \
         procedure alone { \
           is = alone; \
         }";
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_any_call());
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_call_procName("B"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_call_procName("C"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_call_procName("F"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_call_procName("H"));
    // procedures in SIMPLE program but no one calls
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call_procName("A"));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call_procName("G"));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call_procName("alone"));
    // non existent procedures
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call_procName("sgg"));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call_procName("nonexistent"));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call_procName("huge"));
}