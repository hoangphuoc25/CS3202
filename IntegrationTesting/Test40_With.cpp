#include <list>
#include <set>
#include <string>
#include "Test40_With.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

void Test40_With::setUp()
{
    this->IIProc =
        "procedure A { \
           a = b; \
           call Bob; \
           if true then { \
             x = y; \
             call Bob; \
             while false { \
               one = two; \
             } \
             mes = si + 6; \
           } else { \
             des = cartes; \
           } \
           poly = gon; \
         } \
         procedure Bob { \
           while fine { \
             sun = day; \
           } \
           tgif = friday; \
         }";

    this->CALL_PROC =
        "procedure first { \
           zee = day; \
           call second; \
           if true then { \
             a = b; \
             call third; \
           } else { \
             zelda = fried; \
           } \
         } \
         procedure second { \
           angle = big; \
         } \
         procedure third { \
           damn = it; \
           call flyP; \
         } \
         procedure flyP { \
           call second; \
           hyper = mart; \
           while true { \
             call cleanup; \
           } \
         } \
         procedure cleanup { \
           call Xproc; \
         } \
         procedure Xproc { \
           xg = gk; \
         } \
         procedure Y { \
           call Xproc; \
         }";
}

void Test40_With::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test40_With);

void Test40_With::test_ii_00()
{
    string queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    const string& simpleProg = this->IIProc;
    evaluator.parseSimple(simpleProg);
    queryStr = "assign a; stmt s; ";
    queryStr += " Select <a,s> with a.stmt# = s.stmt#";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // 1, 4, 7, 8, 9, 10, 12, 13
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(8, "1 1", "4 4", "7 7",
            "8 8", "9 9", "10 10", "12 12", "13 13"),
            stringSet);
}

void Test40_With::test_ii_01()
{
    string queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    const string& simpleProg = this->IIProc;
    evaluator.parseSimple(simpleProg);
    queryStr = "call c; prog_line pl; ";
    queryStr += " Select c such that Modifies(pl,_) with c.stmt# = pl";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "2", "5"),
            stringSet);
    queryStr = " while w; constant const; ";
    queryStr += " Select w such that Parent(w,_) ";
    queryStr += " with const.value = w.stmt#";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "6"),
            stringSet);
}

void Test40_With::test_ii_10()
{
    string queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    const string& simpleProg = this->IIProc;
    evaluator.parseSimple(simpleProg);
    queryStr = "if if1; prog_line pl; ";
    queryStr += " Select if1 such that Parent(if1,_) ";
    queryStr += " with if1.stmt# = pl.prog_line#";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"),
            stringSet);
}

void Test40_With::test_ii_11()
{
    string queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    const string& simpleProg = this->IIProc;
    evaluator.parseSimple(simpleProg);
    queryStr = "while w; prog_line pl; variable v; ";
    queryStr += " Select w such that Modifies(w,v) and ";
    queryStr += " Modifies(pl, v)";
    queryStr += " with w.stmt# = pl.prog_line#";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "6", "11"),
            stringSet);
}

void Test40_With::test_ii_22()
{
    string queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    const string& simpleProg = this->IIProc;
    evaluator.parseSimple(simpleProg);
    queryStr = "while w; prog_line pl; ";
    queryStr += " Select w such that Parent(w,_) and ";
    queryStr += " Modifies(pl, _)";
    queryStr += " with pl.prog_line# = w.stmt#";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "6", "11"),
            stringSet);
}

void Test40_With::test_ss_cpn_cpn_00()
{
    string queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    const string& simpleProg = this->CALL_PROC;
    evaluator.parseSimple(simpleProg);
    queryStr = " call c1, c2; ";
    queryStr += " Select <c1, c2> with c1.procName = c2.procName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(11, "2 2", "2 10",
            "5 5", "9 9", "10 2", "10 10", "13 13", "14 14", "14 16",
            "16 14", "16 16"),
            stringSet);
    // same as above but selecting procName
    queryStr = " call c1, c2; Select <c1.procName, c2.procName> ";
    queryStr += " with c1.procName = c2.procName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "second second",
            "third third", "flyP flyP", "cleanup cleanup",
            "Xproc Xproc"),
            stringSet);
    // same as above, but selecting procName and stmt#
    queryStr = " call c1, c2; Select <c1.procName, c2> ";
    queryStr += " with c1.procName = c2.procName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "second 2", "second 10",
            "third 5", "flyP 9", "cleanup 13", "Xproc 14", "Xproc 16"),
            stringSet);
}

void Test40_With::test_ss_cpn_X_00()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure pOne { \
           a = b; \
           cv = d; \
           if true then { \
             well = true; \
             cleanUp = sake; \
           } else { \
             x = y; \
             call doSmth; \
           } \
           while doSmth { \
             ha = ha; \
             call nProc; \
           } \
         } \
         procedure someProc { \
           hey = nProc; \
         } \
         procedure cleanUp { \
           well = done; \
         } \
         procedure doSmth { \
           do = smth; \
         } \
         procedure nProc { \
           dont = disturb; \
           call doSmth; \
         } \
         procedure Aproc { \
           jaja = binks; \
           if zorro then { \
             you = are; \
           } else { \
             jack = sparrow; \
           } \
           call someProc; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = "call c1; variable v; Select <c1,v> with ";
    queryStr += " c1.procName = v.varName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "7 doSmth", "10 nProc",
            "15 doSmth"),
            stringSet);
    // same as above but reversed order of LHS and RHS
    queryStr = "call c1; variable v; Select <c1,v> with ";
    queryStr += " v.varName = c1.procName ";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "7 doSmth", "10 nProc",
            "15 doSmth"),
            stringSet);
}

void Test40_With::test_ss_00()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure pOne { \
           a = b; \
           cv = d; \
           if true then { \
             well = true; \
             cleanUp = sake; \
           } else { \
             x = y; \
             call doSmth; \
           } \
           while doSmth { \
             ha = ha; \
             call nProc; \
           } \
         } \
         procedure someProc { \
           hey = nProc; \
         } \
         procedure cleanUp { \
           well = done; \
         } \
         procedure doSmth { \
           do = smth; \
         } \
         procedure nProc { \
           dont = disturb; \
           call doSmth; \
         } \
         procedure Aproc { \
           jaja = binks; \
           if zorro then { \
             you = are; \
           } else { \
             jack = sparrow; \
           } \
           call someProc; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = " variable v; procedure p; ";
    queryStr += " Select <v,p> with v.varName = p.procName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "doSmth doSmth",
            "nProc nProc", "cleanUp cleanUp"),
            stringSet);
}

void Test40_With::test_ss_cpn_cpn_01()
{
    string queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    const string& simpleProg = this->CALL_PROC;
    evaluator.parseSimple(simpleProg);
    queryStr = "call c1, c2; Select <c1,c2> such that Modifies(c2,_) ";
    queryStr += " with c1.procName = c2.procName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(11, "2 2", "2 10", "5 5",
            "9 9", "10 2", "10 10", "13 13", "14 14", "14 16", "16 14",
            "16 16"),
            stringSet);
    // almost the same as above except in Modifies(c1,_)
    queryStr = "call c1, c2; Select <c1,c2> such that Modifies(c1,_) ";
    queryStr += " with c1.procName = c2.procName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(11, "2 2", "2 10", "5 5",
            "9 9", "10 2", "10 10", "13 13", "14 14", "14 16", "16 14",
            "16 16"),
            stringSet);
}

void Test40_With::test_ss_cpn_X_01()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure pOne { \
           a = b; \
           cv = d; \
           if true then { \
             well = true; \
             cleanUp = sake; \
           } else { \
             x = y; \
             call doSmth; \
           } \
           while doSmth { \
             ha = ha; \
             call nProc; \
           } \
         } \
         procedure someProc { \
           hey = nProc; \
         } \
         procedure cleanUp { \
           well = done; \
         } \
         procedure doSmth { \
           do = smth; \
         } \
         procedure nProc { \
           dont = disturb; \
           call doSmth; \
         } \
         procedure Aproc { \
           jaja = binks; \
           if zorro then { \
             you = are; \
           } else { \
             jack = sparrow; \
             someProc = crap; \
           } \
           call someProc; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = "variable v; call c; Select <c,v> such that Uses(_,v) ";
    queryStr += " with c.procName = v.varName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "7 doSmth", "10 nProc",
            "15 doSmth"),
            stringSet);
    queryStr = " variable v; call c; Select <c,v> such that ";
    queryStr += " Modifies(_,v) with c.procName = v.varName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "21 someProc"),
            stringSet);
    // same as above, but swap LHS and RHS
    queryStr = "variable v; call c; Select <c,v> such that Uses(_,v) ";
    queryStr += " with v.varName = c.procName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "7 doSmth", "10 nProc",
            "15 doSmth"),
            stringSet);
}

void Test40_With::test_ss_cpn_X_10()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure pOne { \
           a = b; \
           cv = d; \
           if true then { \
             well = true; \
             cleanUp = sake; \
           } else { \
             x = y; \
             call doSmth; \
           } \
           while doSmth { \
             ha = ha; \
             call nProc; \
           } \
         } \
         procedure someProc { \
           hey = nProc; \
         } \
         procedure cleanUp { \
           well = done; \
         } \
         procedure doSmth { \
           do = smth; \
         } \
         procedure nProc { \
           dont = disturb; \
           call doSmth; \
         } \
         procedure Aproc { \
           jaja = binks; \
           if zorro then { \
             you = are; \
           } else { \
             jack = sparrow; \
             someProc = crap; \
           } \
           call someProc; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = " call c; variable v; ";
    queryStr += " Select <c,v> such that Modifies(c,_) ";
    queryStr += " with c.procName = v.varName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "7 doSmth", "10 nProc",
            "15 doSmth", "21 someProc"),
            stringSet);
}

void Test40_With::test_ss_01()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure pOne { \
           a = b; \
           cv = d; \
           if true then { \
             well = true; \
             cleanUp = sake; \
           } else { \
             x = y; \
             call doSmth; \
           } \
           while doSmth { \
             ha = ha; \
             call nProc; \
           } \
         } \
         procedure someProc { \
           hey = nProc; \
         } \
         procedure cleanUp { \
           well = done; \
         } \
         procedure doSmth { \
           do = smth; \
         } \
         procedure nProc { \
           dont = disturb; \
           call doSmth; \
         } \
         procedure Aproc { \
           jaja = binks; \
           if zorro then { \
             you = are; \
           } else { \
             jack = sparrow; \
             someProc = crap; \
           } \
           call someProc; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = " while w; variable v; procedure p; Select <v,p> ";
    queryStr += " such that Uses(w,v) with p.procName = v.varName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "doSmth doSmth"),
            stringSet);
    // same as above, but swap LHS and RHS
    queryStr = " while w; variable v; procedure p; Select <v,p> ";
    queryStr += " such that Uses(w,v) with v.varName = p.procName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "doSmth doSmth"),
            stringSet);
}

void Test40_With::test_ss_cpn_cpn_11()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure pOne { \
           a = b; \
           cv = d; \
           if true then { \
             well = true; \
             cleanUp = sake; \
           } else { \
             x = y; \
             call doSmth; \
           } \
           while doSmth { \
             ha = ha; \
             call nProc; \
           } \
         } \
         procedure someProc { \
           hey = nProc; \
         } \
         procedure cleanUp { \
           well = done; \
         } \
         procedure doSmth { \
           do = smth; \
         } \
         procedure nProc { \
           dont = disturb; \
           call doSmth; \
         } \
         procedure Aproc { \
           jaja = binks; \
           if zorro then { \
             you = are; \
           } else { \
             jack = sparrow; \
             someProc = crap; \
           } \
           call someProc; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = "call c1, c2; variable v; Select <c1,c2> ";
    queryStr += " such that Modifies(c1,v) ";
    queryStr += " and Modifies(c2,v) with c1.procName = c2.procName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "7 7", "7 15", "10 10",
            "15 7", "15 15", "21 21"),
            stringSet);
}

void Test40_With::test_ss_cpn_X_11()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure pOne { \
           a = b; \
           cv = d; \
           if true then { \
             well = true; \
             cleanUp = sake; \
           } else { \
             x = y; \
             call doSmth; \
           } \
           while doSmth { \
             ha = ha; \
             call nProc; \
           } \
         } \
         procedure someProc { \
           hey = nProc; \
         } \
         procedure cleanUp { \
           well = done; \
         } \
         procedure doSmth { \
           do = smth; \
           if do then { \
             doSmth = done; \
           } else { \
             to = hell; \
             nProc = 9; \
           } \
         } \
         procedure nProc { \
           dont = disturb; \
           call doSmth; \
         } \
         procedure Aproc { \
           jaja = binks; \
           if zorro then { \
             you = are; \
           } else { \
             jack = sparrow; \
             someProc = crap; \
           } \
           call someProc; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = "variable v; call c1, c2; Select <c1, v> such that ";
    queryStr += " Modifies(c1,v) with c1.procName = v.varName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "7 doSmth", "10 nProc",
            "19 doSmth"),
            stringSet);
    // same as above but swap LHS and RHS
    queryStr = "variable v; call c1, c2; Select <c1, v> such that ";
    queryStr += " Modifies(c1,v) with v.varName = c1.procName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "7 doSmth", "10 nProc",
            "19 doSmth"),
            stringSet);
}

void Test40_With::test_ss_11()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure pOne { \
           a = b; \
           cv = d; \
           if true then { \
             well = true; \
             cleanUp = sake; \
           } else { \
             x = y; \
             call doSmth; \
           } \
           while doSmth { \
             ha = ha; \
             call nProc; \
           } \
         } \
         procedure someProc { \
           hey = nProc; \
         } \
         procedure cleanUp { \
           well = done; \
           cleanUp = cool; \
         } \
         procedure doSmth { \
           do = smth; \
           doSmth = bhafg + 56; \
         } \
         procedure nProc { \
           dont = disturb; \
           call doSmth; \
         } \
         procedure Aproc { \
           jaja = binks; \
           if zorro then { \
             you = are; \
           } else { \
             jack = sparrow; \
             someProc = crap; \
           } \
           call someProc; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = " variable v; procedure p; Select <v,p> such that ";
    queryStr += " Modifies(p,v) with p.procName = v.varName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "cleanUp cleanUp",
            "doSmth doSmth"),
            stringSet);
    // same as above but swap LHS and RHS
    queryStr = " variable v; procedure p; Select <v,p> such that ";
    queryStr += " Modifies(p,v) with v.varName = p.procName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "cleanUp cleanUp",
            "doSmth doSmth"),
            stringSet);
    // empty set
    queryStr = " variable v; procedure p; Select <v,p> such that ";
    queryStr += " Uses(p,v) with p.procName = v.varName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
}

void Test40_With::test_ss_cpn_cpn_22()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure pOne { \
           a = b; \
           cv = d; \
           if true then { \
             well = true; \
             cleanUp = sake; \
           } else { \
             x = y; \
             call doSmth; \
           } \
           while doSmth { \
             ha = ha; \
             call nProc; \
           } \
         } \
         procedure someProc { \
           hey = nProc; \
           call cleanUp; \
         } \
         procedure cleanUp { \
           well = 1; \
           cleanUp = 12653 - 662; \
         } \
         procedure doSmth { \
           do = smth; \
           doSmth = bhafg + 56; \
         } \
         procedure nProc { \
           dont = disturb; \
           call doSmth; \
         } \
         procedure Aproc { \
           jaja = binks; \
           if zorro then { \
             you = are; \
           } else { \
             jack = sparrow; \
             someProc = crap; \
           } \
           call someProc; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = " call c1, c2; Select <c1, c2> such that Modifies(c1,_) ";
    queryStr += " and Uses(c2,_) with c1.procName = c2.procName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "7 7", "7 18", "10 10",
            "18 7", "18 18", "24 24"),
            stringSet);
}

void Test40_With::test_ss_cpn_X_22()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure pOne { \
           a = b; \
           cv = d; \
           if true then { \
             well = true; \
             cleanUp = sake; \
           } else { \
             x = y; \
             call doSmth; \
           } \
           while doSmth { \
             ha = ha; \
             call nProc; \
           } \
         } \
         procedure someProc { \
           hey = nProc; \
           call cleanUp; \
         } \
         procedure cleanUp { \
           well = 1; \
           cleanUp = 12653 - 662; \
         } \
         procedure doSmth { \
           do = smth; \
           doSmth = bhafg + 56; \
         } \
         procedure nProc { \
           dont = disturb; \
           call doSmth; \
         } \
         procedure Aproc { \
           jaja = binks; \
           if zorro then { \
             you = are; \
           } else { \
             jack = sparrow; \
             someProc = crap; \
           } \
           call someProc; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = " call c; variable v; Select <c,v> such that ";
    queryStr += " Uses(c,_) and Modifies(_,v) ";
    queryStr += " with c.procName = v.varName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "7 doSmth",
            "18 doSmth", "24 someProc"),
            stringSet);
}

void Test40_With::test_ss_22()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure pOne { \
           a = b; \
           cv = d; \
           if Aproc then { \
             well = true; \
             cleanUp = sake; \
           } else { \
             x = y; \
             call doSmth; \
           } \
           while blame { \
             ha = ha; \
             call nProc; \
           } \
         } \
         procedure someProc { \
           hey = nProc; \
           call cleanUp; \
         } \
         procedure cleanUp { \
           well = 1; \
           xy = cleanUp - 662; \
         } \
         procedure doSmth { \
           do = smth; \
           doSmth = bhafg + 56; \
           x = doSmth; \
         } \
         procedure nProc { \
           dont = disturb; \
           call doSmth; \
           if gg then { \
             x = pOne; \
           } else { \
             x = pTwo; \
           } \
         } \
         procedure Aproc { \
           jaja = binks; \
           if zorro then { \
             you = are; \
           } else { \
             jack = sparrow; \
             someProc = crap; \
           } \
           call someProc; \
           if pOne then { \
             x = 123; \
           } else { \
             p = 456; \
           } \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = " if if1; variable v; procedure p; ";
    queryStr += "Select <if1, v> such that Modifies(p,_) and ";
    queryStr += " Uses(if1, v) with p.procName = v.varName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "3 doSmth", "3 Aproc",
            "20 pOne", "29 pOne"),
            stringSet);
    // same as above but swap LHS and RHS
    queryStr = " if if1; variable v; procedure p; ";
    queryStr += "Select <if1, v> such that Modifies(p,_) and ";
    queryStr += " Uses(if1, v) with v.varName = p.procName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "3 doSmth", "3 Aproc",
            "20 pOne", "29 pOne"),
            stringSet);

    simpleProg =
        "procedure pOne { \
           a = b; \
           cv = d; \
           if Aproc then { \
             well = true; \
             cleanUp = sake; \
           } else { \
             x = y; \
             call doSmth; \
           } \
           while blame { \
             ha = ha; \
             call nProc; \
           } \
         } \
         procedure someProc { \
           hey = nProc; \
           call cleanUp; \
         } \
         procedure cleanUp { \
           well = 1; \
           xy = cleanUp - 662; \
         } \
         procedure doSmth { \
           do = smth; \
           doSmth = bhafg + 56; \
           x = doSmth; \
         } \
         procedure nProc { \
           dont = disturb; \
           call doSmth; \
           if gg then { \
             x = pOne; \
           } else { \
             x = pTwo; \
           } \
         } \
         procedure Aproc { \
           jaja = binks; \
           if zorro then { \
             you = are; \
           } else { \
             jack = sparrow; \
             someProc = crap; \
             while cleanUp { \
               x = y; \
             } \
           } \
           call someProc; \
           if pOne then { \
             x = 123; \
           } else { \
             p = 456; \
           } \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = " while w; variable v; procedure p; ";
    queryStr += "Select <w, v> such that Modifies(p,_) and ";
    queryStr += " Uses(w, v) with p.procName = v.varName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "8 doSmth", "8 pOne",
            "28 cleanUp"),
            stringSet);
    // same as above but swap LHS and RHS
    queryStr = " while w; variable v; procedure p; ";
    queryStr += "Select <w, v> such that Modifies(p,_) and ";
    queryStr += " Uses(w, v) with v.varName = p.procName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "8 doSmth", "8 pOne",
            "28 cleanUp"),
            stringSet);
}