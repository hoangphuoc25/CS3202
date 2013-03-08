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