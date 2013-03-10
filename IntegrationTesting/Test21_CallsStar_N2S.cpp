#include <list>
#include <set>
#include <string>
#include "Test21_CallsStar_N2S.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

void Test21_CallsStar_N2S::setUp() {}

void Test21_CallsStar_N2S::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test21_CallsStar_N2S);

void Test21_CallsStar_N2S::test_callsStar_string_string()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure A { \
           call B; \
           call F; \
         } \
         procedure B { \
           call C; \
           call G; \
         } \
         procedure C { \
           call F; \
           call D; \
         } \
         procedure D { \
           call E; \
           call H; \
         } \
         procedure E { \
           a = b; \
         } \
         procedure F { \
           call G; \
         } \
         procedure G { \
           x = y; \
         } \
         procedure H { \
           fun = times; \
         } \
         procedure I { \
           shit = day; \
         } \
         procedure J { \
           not = me; \
         }";
    evaluator.parseSimple(simpleProg);
    // call graph:
    // A -> B -> C -> D -> E
    // A -> F, B -> G, C -> F, D -> H
    // I and J dont call or get called
    map<string, vector<string> > M;
    vector<string> V;
    // call chain for A
    V.push_back("B"); V.push_back("C"); V.push_back("D");
    V.push_back("E"); V.push_back("F"); V.push_back("G");
    V.push_back("H");
    M["A"] = V;
    // call chain for B
    V.clear();
    V.push_back("C"); V.push_back("D"); V.push_back("E");
    V.push_back("F"); V.push_back("G"); V.push_back("H");
    M["B"] = V;
    // call chain for C
    V.clear();
    V.push_back("D"); V.push_back("E"); V.push_back("F");
    V.push_back("H");
    M["C"] = V;
    // call chain for D
    V.clear();
    V.push_back("E"); V.push_back("H");
    M["D"] = V;
    // call chain for F
    V.clear();
    V.push_back("G");
    M["F"] = V;
    queryStr = "Select BOOLEAN such that Calls*(";
    StringBuffer querySb;
    for (map<string, vector<string> >::const_iterator it =
            M.begin(); it != M.end(); it++) {
        const string& proc = it->first;
        const vector<string>& okCalls = it->second;
        querySb.clear();
        querySb.append(queryStr);
        querySb.append('\"');
        querySb.append(proc);
        querySb.append('\"');
        querySb.append(',');
        for (vector<string>::const_iterator vIt = okCalls.begin();
                vIt != okCalls.end(); vIt++) {
            StringBuffer internalSb;
            internalSb.append(querySb.toString());
            internalSb.append('\"');
            const string& calledProc = *vIt;
            internalSb.append(calledProc);
            internalSb.append('\"');
            internalSb.append(')');
            evaluator.evaluate(internalSb.toString(), resultList);
            stringSet = SetWrapper<string>(resultList);
            CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                         ResultsProjector::TRUE_STR.c_str()),
                    stringSet);
        }
    }

    M.clear();
    // non call chain for A
    V.clear();
    V.push_back("A"); V.push_back("I"); V.push_back("J");
    V.push_back("unknown"); V.push_back("craP");
    M["A"] = V;
    // non call chain for B
    V.clear();
    V.push_back("A"); V.push_back("B"); V.push_back("I");
    V.push_back("J"); V.push_back("abra");
    M["B"] = V;
    // non call chain for C
    V.clear();
    V.push_back("A"); V.push_back("B"); V.push_back("C");
    V.push_back("I"); V.push_back("J"); V.push_back("wrong");
    M["C"] = V;
    // non call chain for D
    V.clear();
    V.push_back("A"); V.push_back("B"); V.push_back("C");
    V.push_back("D"); V.push_back("F"); V.push_back("G");
    V.push_back("I"); V.push_back("J");
    M["D"] = V;
    // non call chain for E
    V.clear();
    V.push_back("A"); V.push_back("B"); V.push_back("C");
    V.push_back("D"); V.push_back("E"); V.push_back("F");
    V.push_back("G"); V.push_back("H"); V.push_back("I");
    V.push_back("J"); V.push_back("shell");
    M["E"] = V;
    // non call chain for F
    V.clear();
    V.push_back("A"); V.push_back("B"); V.push_back("C");
    V.push_back("D"); V.push_back("E"); V.push_back("F");
    V.push_back("H"); V.push_back("I"); V.push_back("J");
    V.push_back("nonsense");
    M["F"] = V;
    // non call chain for G
    V.clear();
    V.push_back("A"); V.push_back("B"); V.push_back("C");
    V.push_back("D"); V.push_back("E"); V.push_back("F");
    V.push_back("G"); V.push_back("H"); V.push_back("I");
    V.push_back("J"); V.push_back("cs3233");
    M["G"] = V;
    // non call chain for H
    V.clear();
    V.push_back("A"); V.push_back("B"); V.push_back("C");
    V.push_back("D"); V.push_back("E"); V.push_back("F");
    V.push_back("G"); V.push_back("H"); V.push_back("I");
    V.push_back("J"); V.push_back("nomansLand");
    M["H"] = V;
    // non call chain for I
    V.clear();
    V.push_back("A"); V.push_back("B"); V.push_back("C");
    V.push_back("D"); V.push_back("E"); V.push_back("F");
    V.push_back("G"); V.push_back("H"); V.push_back("I");
    V.push_back("J"); V.push_back("yam");
    M["I"] = V;
    // non call chain for J
    V.clear();
    V.push_back("A"); V.push_back("B"); V.push_back("C");
    V.push_back("D"); V.push_back("E"); V.push_back("F");
    V.push_back("G"); V.push_back("H"); V.push_back("I");
    V.push_back("J"); V.push_back("monster");
    M["J"] = V;
    // non call chain for non-existent fn
    V.clear();
    V.push_back("A"); V.push_back("B"); V.push_back("C");
    V.push_back("D"); V.push_back("E"); V.push_back("F");
    V.push_back("G"); V.push_back("H"); V.push_back("I");
    V.push_back("J"); V.push_back("red");
    queryStr = "Select BOOLEAN such that Calls*(";
    for (map<string, vector<string> >::const_iterator it =
            M.begin(); it != M.end(); it++) {
        const string& proc = it->first;
        const vector<string>& notOkCalls = it->second;
        querySb.clear();
        querySb.append(queryStr);
        querySb.append('\"');
        querySb.append(proc);
        querySb.append('\"');
        querySb.append(',');
        for (vector<string>::const_iterator vIt = notOkCalls.begin();
                vIt != notOkCalls.end(); vIt++) {
            StringBuffer internalSb;
            internalSb.append(querySb.toString());
            internalSb.append('\"');
            const string& calledProc = *vIt;
            internalSb.append(calledProc);
            internalSb.append('\"');
            internalSb.append(')');
            evaluator.evaluate(internalSb.toString(), resultList);
            stringSet = SetWrapper<string>(resultList);
            CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                         ResultsProjector::FALSE_STR.c_str()),
                    stringSet);
        }
    }
}

void Test21_CallsStar_N2S::test_callsStar_string_wild()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure A { \
           call B; \
           call F; \
         } \
         procedure B { \
           call C; \
           call G; \
         } \
         procedure C { \
           call F; \
           call D; \
         } \
         procedure D { \
           call E; \
           call H; \
         } \
         procedure E { \
           a = b; \
         } \
         procedure F { \
           call G; \
         } \
         procedure G { \
           x = y; \
         } \
         procedure H { \
           fun = times; \
         } \
         procedure I { \
           shit = day; \
         } \
         procedure J { \
           not = me; \
         }";
    evaluator.parseSimple(simpleProg);
    // call graph:
    // A -> B -> C -> D -> E
    // A -> F, B -> G, C -> F, F-> G, D -> H
    // I and J dont call or get called
    queryStr = "Select BOOLEAN such that Calls*(\"A\", _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Calls*(\"B\", _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Calls*(\"C\", _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Calls*(\"D\", _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Calls*(\"F\", _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // non-existent calls
    queryStr = "Select BOOLEAN such that Calls*(\"E\", _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Calls*(\"G\", _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Calls*(\"H\", _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Calls*(\"I\", _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Calls*(\"J\", _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Calls*(\"doesntExist\", _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
}

void Test21_CallsStar_N2S::test_callsStar_wild_string()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure A { \
           call B; \
           call F; \
         } \
         procedure B { \
           call C; \
           call G; \
         } \
         procedure C { \
           call F; \
           call D; \
         } \
         procedure D { \
           call E; \
           call H; \
         } \
         procedure E { \
           a = b; \
         } \
         procedure F { \
           call G; \
         } \
         procedure G { \
           x = y; \
         } \
         procedure H { \
           fun = times; \
         } \
         procedure I { \
           shit = day; \
         } \
         procedure J { \
           not = me; \
         }";
    evaluator.parseSimple(simpleProg);
    // call graph:
    // A -> B -> C -> D -> E
    // A -> F, B -> G, C -> F, F-> G, D -> H
    // I and J dont call or get called
    queryStr = "Select BOOLEAN such that Calls*(_, \"B\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Calls*(_, \"C\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Calls*(_, \"D\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Calls*(_, \"E\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Calls*(_, \"F\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Calls*(_, \"G\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Calls*(_, \"H\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);

    // Negative cases
    queryStr = "Select BOOLEAN such that Calls*(_, \"A\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Calls*(_, \"I\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Calls*(_, \"J\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Calls*(_, \"joke\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
}