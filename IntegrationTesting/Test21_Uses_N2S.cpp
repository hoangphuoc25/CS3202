#include <list>
#include <set>
#include <string>
#include "Test21_Uses_N2S.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

void Test21_Uses_N2S::setUp() {}

void Test21_Uses_N2S::tearDown() {}

void Test21_Uses_N2S::test_uses_string_string()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure bendDown { \
           a = 7; \
           b = black + sheep; \
           if uOne then { \
             xmen = 73; \
           } else { \
             while uTwo { \
               if uThree then { \
                 some = one * sheep; \
               } else { \
                 no = 157 - 34; \
               } \
               four = seven; \
             } \
             hero = sven; \
           } \
           call antRace; \
           seven = heaven; \
         } \
         procedure antRace { \
           mew = two; \
           ant = 123 + 46 + sugar; \
         }";
    evaluator.parseSimple(simpleProg);
    // Variables that are actually used by a given procedure
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"black\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"sheep\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"uOne\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"uTwo\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"uThree\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"one\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"seven\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"sven\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"heaven\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"two\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"sugar\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"antRace\", \"two\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"antRace\", \"sugar\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // Variables not used
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"a\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"b\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"xmen\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"some\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"no\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"four\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"hero\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"mew\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"ant\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"antRace\", \"mew\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"antRace\", \"ant\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    // Variables used but not by that procedure
    queryStr = "Select BOOLEAN such that Uses(\"antRace\", \"sheep\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"antRace\", \"seven\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
}