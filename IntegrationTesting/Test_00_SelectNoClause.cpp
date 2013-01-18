#include <string>
#include <set>
#include <list>
#include "Test_00_SelectNoClause.h"
#include "../SPA/QueryEvaluator.h"

using std::string;
using std::set;
using std::list;

void Test_00_SelectNoClause::setUp()
{
    this->SELECT_ONE_SIMPLEPROG =
        "procedure pOne { \n\
           a = b + cd; \
           g = a * xc; \
           if i then { \
             true = 0; \
             while xp { \
               good = evil + bad; \
               call twoProng; \
               while cd { \n\
                 blah = f; \
                 if gt then { \
                   hi = bye; \n \
                 } else { \
                   no = tify; \
                 } \
                 down = out; \
               } \
               hell = yea; \
               call GGG; \
             } \
             good = good; \
             heat = sink + 55; \
           } else { \
             i = am + evil; \
             while two { \
               eye = ee; \
             } \
           } \
           tree = ish; \
         } \n\
         procedure twoProng { \n \
           harryPotter = not - harryPuttar; \
           if x then { \
             y = aa + gadfly; \
           } else { \
             red = yellow + orange; \
           }\
         }\
         procedure GGG { \
           gg = ggGGggGG; \
         }";
}

void Test_00_SelectNoClause::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test_00_SelectNoClause);

void Test_00_SelectNoClause::test_select_one_syn()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    set<string> stringSet;
    const string& simpleProg = this->SELECT_ONE_SIMPLEPROG;
    evaluator.parseSimple(simpleProg);
    // assign
    queryStr = "assign asdfa; Select asdfa";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 18, "1", "2", "4", "6", "9", "11",
            "12", "13", "14", "16", "17", "18", "20", "21", "22", "24",
            "25", "26");
    // if
    queryStr = "if bbb; Select bbb";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 3, "3", "10", "23");
    // while
    queryStr = " while ahafGS1; Select ahafGS1";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 3, "5", "8", "19");
    // call
    queryStr = "call hah; Select hah";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 2, "7", "15");
    // stmt
    queryStr = "stmt shs1; Select shs1";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 26, "1", "2", "3", "4", "5",
            "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16",
            "17", "18", "19", "20", "21", "22", "23", "24", "25", "26");
    // progline
    queryStr = " prog_line gaba; Select gaba";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 26, "1", "2", "3", "4", "5",
            "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16",
            "17", "18", "19", "20", "21", "22", "23", "24", "25", "26");
    // stmtLst
    queryStr = " stmtLst hhl5; Select hhl5";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 12, "1", "4", "6", "9", "11",
        "12", "18", "20", "22", "24", "25", "26");
    // const
    queryStr = " constant c134s; Select c134s ";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 2, "0", "55");
    // var
    queryStr = " variable  gg; Select gg";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 42, "a", "aa",
            "am", "b", "bad", "blah",
            "bye", "cd", "down", "ee", "evil", "eye", "f",
            "g", "gadfly", "gg", "ggGGggGG", "good", "gt",
            "harryPotter", "harryPuttar",
            "heat", "hell", "hi",
            "i", "ish", "no", "not", "orange", "out", "red",
            "sink", "tify", "tree",
            "true", "two", "x", "xc", "xp", "y", "yea",
            "yellow");
    // procedure
    queryStr = " procedure pasf; Select pasf";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 3, "pOne", "twoProng", "GGG");
}

void Test_00_SelectNoClause::test_select_one_syn_attr()
{
    const string& simpleProg = this->SELECT_ONE_SIMPLEPROG;
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    set<string> stringSet;

    evaluator.parseSimple(simpleProg);
    // assign.stmt#
    queryStr = "assign nbva15; Select nbva15.stmt#";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 18, "1", "2", "4", "6", "9", "11",
            "12", "13", "14", "16", "17", "18", "20", "21", "22", "24",
            "25", "26");
    // if.stmt#
    queryStr = "if yY1ns1b; Select yY1ns1b.stmt#";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 3, "3", "10", "23");
    // while.stmt#
    queryStr = " while pqga2G; Select pqga2G.stmt#";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 3, "5", "8", "19");
    // stmt.stmt#
    queryStr = "stmt hafd1; Select hafd1";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 26, "1", "2", "3", "4", "5",
            "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16",
            "17", "18", "19", "20", "21", "22", "23", "24", "25", "26");
    // TODO: Check if progline.stmt# is allowed
    // progline.stmt#
    queryStr = " prog_line ghsh1; Select ghsh1.stmt#";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 26, "1", "2", "3", "4", "5",
            "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16",
            "17", "18", "19", "20", "21", "22", "23", "24", "25", "26");
    // TODO: Check if stmtLst.stmt# is allowed
    // stmtLst.stmt#
    queryStr = " stmtLst sbt12; Select sbt12";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 12, "1", "4", "6", "9", "11",
        "12", "18", "20", "22", "24", "25", "26");
    // constant.value
    queryStr = " constant jnaWg12; Select jnaWg12.value ";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 2, "0", "55");
    // variable.varName
    queryStr = " variable yaja1; Select yaja1.varName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 42, "a", "aa",
            "am", "b", "bad", "blah",
            "bye", "cd", "down", "ee", "evil", "eye", "f",
            "g", "gadfly", "gg", "ggGGggGG", "good", "gt",
            "harryPotter", "harryPuttar",
            "heat", "hell", "hi",
            "i", "ish", "no", "not", "orange", "out", "red",
            "sink", "tify", "tree",
            "true", "two", "x", "xc", "xp", "y", "yea",
            "yellow");
    // procedure.procName
    queryStr = " procedure fyqs; Select fyqs.procName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 3, "pOne", "twoProng", "GGG");
    // call.stmt#
    queryStr = "call billGates; Select billGates.stmt#";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 2, "7", "15");
    // important case - call.procName. should return procedure name
    // call.procName
    queryStr = "call fadsbv; Select fadsbv.procName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 2, "twoProng", "GGG");
}