#include <cstdio>
#include <cstdarg>
#include <string>
#include <map>
#include <set>
#include <list>
#include <utility>
#include "Test10_00_Modifies.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::string;
using std::map;
using std::list;
using std::set;
using std::pair;
using std::make_pair;

void Test10_00_Modifies::setUp()
{
    this->MODIFIES_00_PROG =
        "procedure procOne { \
           x = y + 3; \
           a = 5; \
           b = bad + amp + 41; \
           while itsTrue { \
             y = 5 + 6 + a; \
             if xab then { \
               kerb = s + 2; \
             } else { \
               big = trouble + 11; \
               a = a + a; \
             } \
             g2 = g1 + 1; \
             if bad then { \
               call ascP; \
               xyz = 123; \
             } else { \
               aa = aabbx; \
             } \
           } \
           call doSmth; \
           well = goodness - me; \
           if x then { \
             aa = ta; \
           } else { \
             aa = b; \
           } \
           xc = 3 + 56 + ab; \
         } \
         \
         procedure ascP { \
           if gax then { \
             xcz = 12; \
             while xg { \
               while bb { \
                 a = b + bad + good; \
                 well = bbz; \
               } \
               x = vv; \
             } \
             vv = 2 + g; \
           } else { \
             noway = yesway + 2; \
             x = 5; \
           } \
           hi = bye + 113; \
           thank = goodness; \
        } \
        \
        \
        \
        procedure doSmth { \
          yes = hell + no; \
          call cleanUp; \
          dont = do + this; \
        } \
        procedure cleanUp { \
          im = done; \
        }";
}

void Test10_00_Modifies::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test10_00_Modifies);

void Test10_00_Modifies::test_modifies_assign_var()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->MODIFIES_00_PROG;
    evaluator.parseSimple(simpleProg);

    // Modifies(assign,var)
    queryStr = "assign a; variable v; Select v such that Modifies(a,v)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(19, "x", "a", "b",
            "y", "kerb", "big", "g2", "xcz", "well", "vv", "noway",
            "hi", "thank", "xyz", "aa", "yes", "im", "dont", "xc"),
            stringSet);
    queryStr = "assign abb; variable jnah#; Select abb such that ";
    queryStr += " Modifies(abb, jnah#   \n)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(26, "1", "2", "3",
            "5", "7", "8", "9", "10", "13", "14", "16", "18", "19", "20",
            "22", "25", "26", "27", "28", "29", "30", "31", "32", "33",
            "35", "36"));
}

void Test10_00_Modifies::test_modifies_procedure_var()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->MODIFIES_00_PROG;
    evaluator.parseSimple(simpleProg);
    // Modifies(procedure,var)
    queryStr = " procedure pla1; variable xyz; Select pla1 such that ";
    queryStr += " Modifies(pla1, xyz)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(4, "procOne",
            "ascP", "doSmth", "cleanUp"));
}

void Test10_00_Modifies::test_modifies_call_var()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->MODIFIES_00_PROG;
    evaluator.parseSimple(simpleProg);
    // Modifies(call,var); Select call
    queryStr = " call ca1; variable vv; Select ca1 such that ";
    queryStr += " Modifies(ca1,vv)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(3, "12", "15", "34"));
    // Modifies(call,var); Select call.stmt#
    queryStr = " call ba; variable v; Select ba.stmt# such that ";
    queryStr += " Modifies(ba,v)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(3, "12", "15", "34"));
    // Modifies(call, var); Select call.procName
    queryStr = " call ab#as; variable xza; Select ab#as.procName such that ";
    queryStr += " Modifies(ab#as,  xza)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(3, "ascP", "doSmth",
            "cleanUp"));
    // Modifies(call, var); Select var
    queryStr = " call aq1; variable hma; Select hma such that ";
    queryStr += " Modifies(aq1, hma)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(11, "xcz", "a",
            "well", "x", "vv", "noway", "hi", "thank", "yes", "im", "dont"));
    // Modifies(call, var); Select var.varName
    queryStr = " call uja1; variable baqw; Select baqw.varName such that ";
    queryStr += " Modifies(uja1, baqw)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(11, "xcz", "a",
            "well", "x", "vv", "noway", "hi", "thank", "yes", "im", "dont"));
}

void Test10_00_Modifies::test_modifies_while_var()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->MODIFIES_00_PROG;
    evaluator.parseSimple(simpleProg);
    // Modifies(while, var); Select while
    queryStr = " while as; variable gaw; Select as such that ";
    queryStr += " Modifies(as, gaw)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(3, "4", "23", "24"));
    // Modifies(while, var); Select while.stmt#
    queryStr = " while aa; variable yaa; Select aa.stmt# such that ";
    queryStr += " Modifies(aa,yaa)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(3, "4", "23", "24"));
    // Modifies(while, var); Select var
    queryStr = " while xaz1; variable hasdfS; Select hasdfS such that ";
    queryStr += " Modifies(xaz1, hasdfS)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(14, "a", "aa",
            "big", "g2", "hi", "kerb", "noway", "thank", "vv", "well",
            "x", "xcz", "xyz", "y"));
    // Modifies(while, var); Select var.varName
    queryStr = " while qw1; variable hHs; Select hHs.varName such that ";
    queryStr += " Modifies(qw1, hHs )";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(14, "a", "aa",
            "big", "g2", "hi", "kerb", "noway", "thank", "vv", "well",
            "x", "xcz", "xyz", "y"));
}

void Test10_00_Modifies::test_modifies_if_var()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->MODIFIES_00_PROG;
    evaluator.parseSimple(simpleProg);
    // Modifies(if, var); Select if
    queryStr = "if ia1; variable vx; Select ia1 such that ";
    queryStr += " Modifies(ia1, vx)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(4, "6", "11", "17",
            "21"));
    // Modifies(if, var); Select if.stmt#
    queryStr = "if bas; variable vtrq; Select bas.stmt# such that ";
    queryStr += " Modifies(bas, vtrq)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(4, "6", "11", "17",
            "21"));
    // Modifies(if, var); Select var
    queryStr = " if cbj; variable kl; Select kl such that ";
    queryStr += " Modifies(cbj, kl)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(12, "a", "aa",
            "big", "hi", "kerb", "noway", "thank", "vv", "well", "x",
            "xcz", "xyz"));
    // Modifies(if, var); Select var.varName
    queryStr = " if ya; variable asd; Select asd.varName such that ";
    queryStr += " Modifies(ya, asd)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(12, "a", "aa",
            "big", "hi", "kerb", "noway", "thank", "vv", "well", "x",
            "xcz", "xyz"));
}

void Test10_00_Modifies::test_modifies_stmt_var()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->MODIFIES_00_PROG;
    evaluator.parseSimple(simpleProg);
    // Modifies(stmt, var); Select stmt
    queryStr = "stmt s1; variable v11; Select s1 such that ";
    queryStr += " Modifies(s1, v11)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(36, "1", "2", "3",
            "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14",
            "15", "16", "17", "18", "19", "20", "21", "22", "23", "24",
            "25", "26", "27", "28", "29", "30", "31", "32", "33", "34",
            "35", "36"));
    // Modifies(stmt, var); Select stmt.stmt#
    queryStr = "stmt hga4; variable tas; Select hga4.stmt# such that ";
    queryStr += " Modifies(hga4, tas)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(36, "1", "2", "3",
            "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14",
            "15", "16", "17", "18", "19", "20", "21", "22", "23", "24",
            "25", "26", "27", "28", "29", "30", "31", "32", "33", "34",
            "35", "36"));
    // Modifies(stmt,var); Select var
    queryStr = " stmt sx; variable mh; Select mh such that ";
    queryStr += " Modifies(sx, mh)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(19, "a", "aa", "b",
            "big", "dont", "g2", "hi", "im", "kerb", "noway", "thank",
            "vv", "well", "x", "xc", "xcz", "xyz", "y", "yes"));
    // Modifies(stmt,var); Select var.varName
    queryStr = " stmt hgf; variable yw; Select yw.varName such that ";
    queryStr += " Modifies(hgf, yw)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(19, "a", "aa", "b",
            "big", "dont", "g2", "hi", "im", "kerb", "noway", "thank",
            "vv", "well", "x", "xc", "xcz", "xyz", "y", "yes"));
}

void Test10_00_Modifies::test_modifies_progline_var()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->MODIFIES_00_PROG;
    evaluator.parseSimple(simpleProg);
    // Modifies(prog_line, var); Select prog_line
    queryStr = " prog_line plgf; variable v11; Select plgf such that ";
    queryStr += " Modifies(plgf, v11)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(36, "1", "2", "3",
            "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14",
            "15", "16", "17", "18", "19", "20", "21", "22", "23", "24",
            "25", "26", "27", "28", "29", "30", "31", "32", "33", "34",
            "35", "36"));
    // Modifies(prog_line, var); Select prog_line.stmt#
    queryStr = "prog_line hga4; variable tas; ";
    queryStr += " Select hga4.prog_line# such that ";
    queryStr += " Modifies(hga4, tas)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(36, "1", "2", "3",
            "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14",
            "15", "16", "17", "18", "19", "20", "21", "22", "23", "24",
            "25", "26", "27", "28", "29", "30", "31", "32", "33", "34",
            "35", "36"));
    // Modifies(prog_line,var); Select var
    queryStr = " prog_line sx; variable mh; Select mh such that ";
    queryStr += " Modifies(sx, mh)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(19, "a", "aa", "b",
            "big", "dont", "g2", "hi", "im", "kerb", "noway", "thank",
            "vv", "well", "x", "xc", "xcz", "xyz", "y", "yes"));
    // Modifies(prog_line,var); Select var.varName
    queryStr = " prog_line hgf; variable yw; Select yw.varName such that ";
    queryStr += " Modifies(hgf, yw)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(19, "a", "aa", "b",
            "big", "dont", "g2", "hi", "im", "kerb", "noway", "thank",
            "vv", "well", "x", "xc", "xcz", "xyz", "y", "yes"));
}