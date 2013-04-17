#include <list>
#include <set>
#include <string>
#include "Test21_Modifies_N2S.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

void Test21_Modifies_N2S::setUp() {}

void Test21_Modifies_N2S::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test21_Modifies_N2S);

void Test21_Modifies_N2S::test_modifies_int_string()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure destroyTree { \
           a = 56; \
           while x { \
             we = are + one; \
           } \
           seven = 86 * a51; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = "Select BOOLEAN such that Modifies(1, \"a\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Modifies(1, \"b\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);

    queryStr = "assign a; Select a such that Modifies(3, \"we\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "1", "3", "4"),
            stringSet);
}

void Test21_Modifies_N2S::test_modifies_string_string()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure destroyTree { \
           a = 56; \
           while x { \
             we = are + one; \
           } \
           seven = 86 * a51; \
           call pTwo; \
         } \
         procedure pTwo { \
           hell = not + this; \
           if true then { \
             false = 55; \
           } else { \
             table = squared; \
           } \
           we = are + done; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = "Select BOOLEAN such that Modifies( \"destroyTree\", \n";
    queryStr += " \t\n \"we\" \n\t)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);

    queryStr = "assign a; Select a such that ";
    queryStr += " Modifies( \"destroyTree\", \n\"false\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "1", "3", "4", "6", "8",
            "9", "10"),
            stringSet);

    evaluator.parseSimple(simpleProg);
    queryStr = "Select BOOLEAN such that Modifies( \"pTwo\", \n";
    queryStr += " \"seven\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
}

void Test21_Modifies_N2S::test_modifies_string_wild()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure evaluate { \
           a = 123; \
           b = 456; \
         } \
         procedure secProc { \
           if true then { \
             while mad { \
               g = g + 1;\
             } \
           } else { \
             x = y; \
           } \
         } \
         procedure thirdProc { \
           call fourthProc; \
         } \
         procedure fourthProc { \
           a = a + 1; \
         } \
         procedure fifthProc { \
           call thirdProc; \
         }";
    evaluator.parseSimple(simpleProg);
    // procedure with assignment stmt
    queryStr = "Select BOOLEAN such that Modifies(\"evaluate\",_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // procedure with assignment stmts nested inside if and while
    queryStr = "Select BOOLEAN such that Modifies(\"secProc\",_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // procedure having no assignment stmts, but calls another
    // procedure with assignment stmts
    queryStr = "Select BOOLEAN such that Modifies(\"thirdProc\",_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // procedure with assignment stmt
    queryStr = "Select BOOLEAN such that Modifies(\"fourthProc\",_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // procedure which has no assignment stmt, calls another
    // procedure which has no assignment, but that procedure calls
    // another procedure with assignment stmt
    queryStr = "Select BOOLEAN such that Modifies(\"fifthProc\",_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // non-existent procedure
    queryStr = "Select BOOLEAN such that Modifies(\"blah\",_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
}

void Test21_Modifies_N2S::test_modifies_int_wild()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure evaluate { \
           a = 123; \
           b = 456; \
         } \
         procedure secProc { \
           if true then { \
             while mad { \
               g = g + 1;\
             } \
           } else { \
             x = y; \
           } \
         } \
         procedure thirdProc { \
           call fourthProc; \
         } \
         procedure fourthProc { \
           a = a + 1; \
         } \
         procedure fifthProc { \
           call thirdProc; \
         }";
    evaluator.parseSimple(simpleProg);
    // In theory, every stmt should modify smth
    // unless it is out of range
    queryStr = "Select BOOLEAN such that Modifies(1,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Modifies(2,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Modifies(3,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Modifies(4,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Modifies(5,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Modifies(6,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Modifies(7,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Modifies(8,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Modifies(9,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // Out of range statements
    queryStr = "Select BOOLEAN such that Modifies(0,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Modifies(-1,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Modifies(-55,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Modifies(10,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Modifies(11,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Modifies(350,_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
}

void Test21_Modifies_N2S::test_modifies_wild_string()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure procOne { \
           firstVar = 613; \
           while notMod { \
             secVar = true; \
             if notMod2 then { \
               thirdVar = 61 * 52; \
             } else { \
               fourthVar = 61 + aVar; \
             } \
             fifthVar = 157; \
           } \
           call eightNine; \
         } \
         procedure eightNine { \
           sixthVar = 6661; \
         }";
    evaluator.parseSimple(simpleProg);
    // Variables actually being modified
    queryStr = "Select BOOLEAN such that Modifies(_, \"firstVar\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Modifies(_, \"secVar\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Modifies(_, \"thirdVar\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Modifies(_, \"fourthVar\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Modifies(_, \"fifthVar\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Modifies(_, \"sixthVar\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    // variables not being modified
    queryStr = "Select BOOLEAN such that Modifies(_, \"notMod\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Modifies(_, \"notMod2\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Modifies(_, \"aVar\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    // non-existent variables
    queryStr = "Select BOOLEAN such that Modifies(_, \"notHere\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Modifies(_, \"dontKnow\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
}

void Test21_Modifies_N2S::test_modifies_wild_wild()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure procOne { \
           firstVar = 613; \
           while notMod { \
             secVar = true; \
             if notMod2 then { \
               thirdVar = 61 * 52; \
             } else { \
               fourthVar = 61 + aVar; \
             } \
             fifthVar = 157; \
           } \
           call eightNine; \
         } \
         procedure eightNine { \
           sixthVar = 6661; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = "Select BOOLEAN such that Modifies(_, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
}

void Test21_Modifies_N2S::test_modifies_string_syn()
{
    string queryStr, simpleProg;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure Aone { \
           a = b; \
           if true then { \
             var = x; \
           } else { \
             truth = false; \
           } \
           x = abc; \
           while it { \
             no = way; \
           } \
           ya = lor; \
         } \
         procedure procTwo { \
           gj = good + luck; \
           x = y; \
           good = day; \
           it = 57; \
         }";
    evaluator.parseSimple(simpleProg);
    // Modifies(string,syn) 0
    queryStr = " variable v; Select v such that Modifies(\"Aone\",v)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "a", "var", "truth",
                "x", "no", "ya"),
                stringSet);
    // Modifies(string,syn) 1
    queryStr = "assign a; variable v; ";
    queryStr += " Select v such that Uses(a,v) and ";
    queryStr += " Modifies(\"procTwo\", v)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "x", "good"),
            stringSet);
    // Modifies(int,syn) 0
    queryStr = " variable v; Select v such that Modifies(2, v)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "var", "truth"),
            stringSet);
    // Modifies(int,syn) 1
    queryStr = " if if1; variable v; ";
    queryStr += " Select v such that Uses(if1,v) and Modifies(5,v)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "x"),
            stringSet);
    // Modifies(_,syn) 0
    queryStr = " variable v; Select v such that Modifies(_,v)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    // Modifies(_,syn) 1
    queryStr = " stmt s; variable v; ";
    queryStr += " Select v such that Uses(s,v) and  Modifies(_,v)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
}