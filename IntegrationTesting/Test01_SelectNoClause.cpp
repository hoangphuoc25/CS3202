#include <string>
#include <set>
#include <list>
#include "Test01_SelectNoClause.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::string;
using std::set;
using std::list;

void Test01_SelectNoClause::setUp()
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

void Test01_SelectNoClause::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test01_SelectNoClause);

void Test01_SelectNoClause::test_select_one_syn()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->SELECT_ONE_SIMPLEPROG;
    evaluator.parseSimple(simpleProg);
    // assign
    queryStr = "assign asdfa; Select asdfa";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet,
            SetWrapper<string>(18, "1", "2", "4", "6", "9", "11", "12",
            "13", "14", "16", "17", "18", "20", "21", "22", "24",
            "25", "26"));
    // if
    queryStr = "if bbb; Select bbb";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet,
            SetWrapper<string>(3, "3", "10", "23"));
    // while
    queryStr = " while ahafGS1; Select ahafGS1";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(3, "5", "8", "19"));
    // call
    queryStr = "call hah; Select hah";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(2, "7", "15"));
    // stmt
    queryStr = "stmt shs1; Select shs1";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet,
            SetWrapper<string>(26, "1", "2", "3", "4", "5", "6", "7",
                "8", "9", "10", "11", "12", "13", "14", "15", "16",
                "17", "18", "19", "20", "21", "22", "23", "24", "25", "26"));
    // progline
    queryStr = " prog_line gaba; Select gaba";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet,
            SetWrapper<string>(26, "1", "2", "3", "4", "5", "6", "7",
                "8", "9", "10", "11", "12", "13", "14", "15", "16",
                "17", "18", "19", "20", "21", "22", "23", "24", "25", "26"));
    // stmtLst
    queryStr = " stmtLst hhl5; Select hhl5";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet,
            SetWrapper<string>(12, "1", "4", "6", "9", "11", "12", "18",
                "20", "22", "24", "25", "26"));
    // const
    queryStr = " constant c134s; Select c134s ";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(2, "0", "55"));
    // var
    queryStr = " variable  gg; Select gg";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet,
            SetWrapper<string>(42, "a", "aa", "am", "b", "bad", "blah",
                    "bye", "cd", "down", "ee", "evil", "eye", "f",
                    "g", "gadfly", "gg", "ggGGggGG", "good", "gt",
                    "harryPotter", "harryPuttar",
                    "heat", "hell", "hi",
                    "i", "ish", "no", "not", "orange", "out", "red",
                    "sink", "tify", "tree",
                    "true", "two", "x", "xc", "xp", "y", "yea",
                    "yellow"));
    // procedure
    queryStr = " procedure pasf; Select pasf";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet,
            SetWrapper<string>(3, "pOne", "twoProng", "GGG"));
}

void Test01_SelectNoClause::test_select_one_syn_attr()
{
    const string& simpleProg = this->SELECT_ONE_SIMPLEPROG;
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    evaluator.parseSimple(simpleProg);
    // assign.stmt#
    queryStr = "assign nbva15; Select nbva15.stmt#";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet,
            SetWrapper<string>(18, "1", "2", "4", "6", "9", "11", "12",
                    "13", "14", "16", "17", "18", "20", "21", "22", "24",
                    "25", "26"));
    // if.stmt#
    queryStr = "if yY1ns1b; Select yY1ns1b.stmt#";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(3, "3", "10", "23"));
    // while.stmt#
    queryStr = " while pqga2G; Select pqga2G.stmt#";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(3, "5", "8", "19"));
    // stmt.stmt#
    queryStr = "stmt hafd1; Select hafd1.stmt#";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet,
            SetWrapper<string>(26, "1", "2", "3", "4", "5", "6", "7", "8",
                    "9", "10", "11", "12", "13", "14", "15", "16", "17",
                    "18", "19", "20", "21", "22", "23", "24", "25", "26"));
    // progline.prog_line#
    queryStr = " prog_line ghsh1; Select ghsh1.prog_line#";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(26, "1", "2", "3",
            "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14",
            "15", "16", "17", "18", "19", "20", "21", "22", "23", "24",
            "25", "26"));
    // stmtLst.stmt#
    queryStr = " stmtLst sbt12; Select sbt12.stmt#";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(12, "1", "4", "6",
            "9", "11", "12", "18", "20", "22", "24", "25", "26"));
    // constant.value
    queryStr = " constant jnaWg12; Select jnaWg12.value ";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(2, "0", "55"));
    // variable.varName
    queryStr = " variable yaja1; Select yaja1.varName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(42, "a", "aa",
            "am", "b", "bad", "blah",
            "bye", "cd", "down", "ee", "evil", "eye", "f",
            "g", "gadfly", "gg", "ggGGggGG", "good", "gt",
            "harryPotter", "harryPuttar",
            "heat", "hell", "hi",
            "i", "ish", "no", "not", "orange", "out", "red",
            "sink", "tify", "tree",
            "true", "two", "x", "xc", "xp", "y", "yea",
            "yellow"));
    // procedure.procName
    queryStr = " procedure fyqs; Select fyqs.procName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(3, "pOne",
            "twoProng", "GGG"));
    // call.stmt#
    queryStr = "call billGates; Select billGates.stmt#";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(2, "7", "15"));
    // important case - call.procName. should return procedure name
    // call.procName
    queryStr = "call fadsbv; Select fadsbv.procName";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(2, "twoProng", "GGG"));
}

void Test01_SelectNoClause::test_select_two_same_syn()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->SELECT_ONE_SIMPLEPROG;
    evaluator.parseSimple(simpleProg);
    // assign
    queryStr = "assign bhad; Select <bhad,bhad>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(18, "1 1", "2 2",
            "4 4", "6 6", "9 9", "11 11", "12 12", "13 13", "14 14",
            "16 16", "17 17", "18 18", "20 20", "21 21", "22 22", "24 24",
            "25 25", "26 26"));
    // if
    queryStr = "if mhs; Select <mhs,mhs>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(3, "3 3", "10 10",
            "23 23"));
    // while
    queryStr = " while kjfh21; Select <kjfh21,kjfh21>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(3, "5 5", "8 8",
            "19 19"));
    // call
    queryStr = "call gasd; Select <gasd  ,  gasd>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(2, "7 7", "15 15"));
    // stmt
    queryStr = "stmt awe1; Select <awe1, awe1>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(26, "1 1", "2 2",
            "3 3", "4 4", "5 5", "6 6", "7 7", "8 8", "9 9", "10 10",
            "11 11", "12 12", "13 13", "14 14", "15 15", "16 16", "17 17",
            "18 18", "19 19", "20 20", "21 21", "22 22", "23 23", "24 24",
            "25 25", "26 26"));
    // progline
    queryStr = " prog_line gfhns1#; Select  <gfhns1#  , gfhns1#>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(26, "1 1", "2 2",
            "3 3", "4 4", "5 5", "6 6", "7 7", "8 8", "9 9", "10 10",
            "11 11", "12 12", "13 13", "14 14", "15 15", "16 16", "17 17",
            "18 18", "19 19", "20 20", "21 21", "22 22", "23 23", "24 24",
            "25 25", "26 26"));
    // stmtLst
    queryStr = " stmtLst hhl5; Select <hhl5,hhl5>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(12, "1 1", "4 4",
            "6 6", "9 9", "11 11", "12 12", "18 18", "20 20", "22 22",
            "24 24", "25 25", "26 26"));
    // const
    queryStr = " constant hhafd1; Select  <hhafd1 ,\t hhafd1> ";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(2, "0 0", "55 55"));
    // var
    queryStr = " variable  uts; Select  <uts,uts>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(42, "a a", "aa aa",
            "am am", "b b", "bad bad", "blah blah",
            "bye bye", "cd cd", "down down", "ee ee", "evil evil",
            "eye eye", "f f", "g g", "gadfly gadfly", "gg gg",
            "ggGGggGG ggGGggGG", "good good", "gt gt",
            "harryPotter harryPotter", "harryPuttar harryPuttar",
            "heat heat", "hell hell", "hi hi", "i i", "ish ish", "no no",
            "not not", "orange orange", "out out", "red red",
            "sink sink", "tify tify", "tree tree",
            "true true", "two two", "x x", "xc xc", "xp xp", "y y",
            "yea yea", "yellow yellow"));
    // procedure
    queryStr = " procedure   h4Adfs; Select   <h4Adfs,h4Adfs>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(3, "pOne pOne",
            "twoProng twoProng", "GGG GGG"));
}

void Test01_SelectNoClause::test_select_syn_syn_attr()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->SELECT_ONE_SIMPLEPROG;
    evaluator.parseSimple(simpleProg);
    // assign
    queryStr = "assign msfn; Select <msfn,msfn.stmt#>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(18, "1 1", "2 2",
            "4 4", "6 6", "9 9", "11 11", "12 12", "13 13", "14 14",
            "16 16", "17 17", "18 18", "20 20", "21 21", "22 22", "24 24",
            "25 25", "26 26"));
    // if
    queryStr = "if  ina; Select <ina,ina.stmt#>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(3, "3 3", "10 10",
            "23 23"));
    // while
    queryStr = " while dh1; Select <dh1,dh1.stmt#>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(3, "5 5", "8 8",
            "19 19"));
    // call, call.stmt#
    queryStr = "call jkjag; Select <jkjag  ,  jkjag.stmt#>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(2, "7 7", "15 15"));
    // call, call.procName
    queryStr = "call Th2; Select <Th2  ,  Th2.procName>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(2, "7 twoProng",
            "15 GGG"));
    // stmt
    queryStr = "stmt uea; Select <uea, uea.stmt#>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(26, "1 1", "2 2",
            "3 3", "4 4", "5 5", "6 6", "7 7", "8 8", "9 9", "10 10",
            "11 11", "12 12", "13 13", "14 14", "15 15", "16 16", "17 17",
            "18 18", "19 19", "20 20", "21 21", "22 22", "23 23", "24 24",
            "25 25", "26 26"));
    // progline
    queryStr = " prog_line xe1#; Select  <xe1#  , xe1#.prog_line#>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(26, "1 1", "2 2",
            "3 3", "4 4", "5 5", "6 6", "7 7", "8 8", "9 9", "10 10",
            "11 11", "12 12", "13 13", "14 14", "15 15", "16 16", "17 17",
            "18 18", "19 19", "20 20", "21 21", "22 22", "23 23", "24 24",
            "25 25", "26 26"));
    // stmtLst
    queryStr = " stmtLst loa1; Select <loa1,loa1.stmt#>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(12, "1 1", "4 4",
            "6 6", "9 9", "11 11", "12 12", "18 18", "20 20", "22 22",
            "24 24", "25 25", "26 26"));
    // const
    queryStr = " constant yar; Select  <yar ,\t yar.value> ";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(2, "0 0", "55 55"));
    // var
    queryStr = " variable  yabza; Select  <yabza,yabza.varName>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(42, "a a", "aa aa",
            "am am", "b b", "bad bad", "blah blah",
            "bye bye", "cd cd", "down down", "ee ee", "evil evil",
            "eye eye", "f f", "g g", "gadfly gadfly", "gg gg",
            "ggGGggGG ggGGggGG", "good good", "gt gt",
            "harryPotter harryPotter", "harryPuttar harryPuttar",
            "heat heat", "hell hell", "hi hi", "i i", "ish ish", "no no",
            "not not", "orange orange", "out out", "red red",
            "sink sink", "tify tify", "tree tree",
            "true true", "two two", "x x", "xc xc", "xp xp", "y y",
            "yea yea", "yellow yellow"));
    // procedure
    queryStr = " procedure   pofs; Select   <pofs,pofs.procName>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(3, "pOne pOne",
            "twoProng twoProng", "GGG GGG"));
}

void Test01_SelectNoClause::test_select_X_Y_Xattr()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    simpleProg =
        "procedure pOne { \
           a = b; \
           call progTwo; \
           while x { \
             if as then { \
               ya = lor; \
               fly = away + 61; \
             } else { \
               xen = hypervisor + 425; \
             } \
             journey = ends; \
           } \
           call progTwo; \
           time = travel - 781; \
           sheldon = cooper * 2; \
         } \
         procedure progTwo { \
           wow = cool; \
           if true then { \
             always = true; \
             happy = new + year + 2013; \
           } else { \
             fun = times; \
           } \
           terrible = fate; \
           call doSmth; \
         } \
         procedure doSmth { \
           do = smth; \
         } \
         procedure unreachableProc { \
           none = reaches + here; \
         }";
    evaluator.parseSimple(simpleProg);
    // assign, proc, assign.stmt#
    queryStr = "assign a; procedure proc; Select <a, proc, a.stmt#>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(56, "1 pOne 1",
            "1 progTwo 1",
            "1 doSmth 1", "1 unreachableProc 1", "5 pOne 5", "5 progTwo 5",
            "5 doSmth 5", "5 unreachableProc 5", "6 pOne 6", "6 progTwo 6",
            "6 doSmth 6", "6 unreachableProc 6", "7 pOne 7", "7 progTwo 7",
            "7 doSmth 7", "7 unreachableProc 7", "8 pOne 8", "8 progTwo 8",
            "8 doSmth 8", "8 unreachableProc 8", "10 pOne 10",
            "10 progTwo 10", "10 doSmth 10", "10 unreachableProc 10",
            "11 pOne 11", "11 progTwo 11", "11 doSmth 11",
            "11 unreachableProc 11",
            "12 pOne 12", "12 progTwo 12", "12 doSmth 12",
            "12 unreachableProc 12",
            "14 pOne 14", "14 progTwo 14", "14 doSmth 14",
            "14 unreachableProc 14",
            "15 pOne 15", "15 progTwo 15", "15 doSmth 15",
            "15 unreachableProc 15",
            "16 pOne 16", "16 progTwo 16", "16 doSmth 16",
            "16 unreachableProc 16",
            "17 pOne 17", "17 progTwo 17", "17 doSmth 17",
            "17 unreachableProc 17",
            "19 pOne 19", "19 progTwo 19", "19 doSmth 19",
            "19 unreachableProc 19",
            "20 pOne 20", "20 progTwo 20", "20 doSmth 20",
            "20 unreachableProc 20"));
    // call, proc, call.stmt#
    queryStr = "call hba; procedure ha1ga; Select <hba, ha1ga, hba.stmt#>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(12, "2 pOne 2",
            "2 progTwo 2", "2 doSmth 2", "2 unreachableProc 2",
            "9 pOne 9", "9 progTwo 9", "9 doSmth 9", "9 unreachableProc 9",
            "18 pOne 18", "18 progTwo 18", "18 doSmth 18",
            "18 unreachableProc 18"));
    // call, proc, call.procName
    queryStr = "call hba; procedure ha1ga; ";
    queryStr += " Select <hba, ha1ga, hba.procName>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(12, "2 pOne progTwo",
            "2 progTwo progTwo", "2 doSmth progTwo",
            "2 unreachableProc progTwo", "9 pOne progTwo",
            "9 progTwo progTwo", "9 doSmth progTwo",
            "9 unreachableProc progTwo", "18 pOne doSmth",
            "18 progTwo doSmth", "18 doSmth doSmth",
            "18 unreachableProc doSmth"));
    // while, proc, while.stmt#
    queryStr = " while bba1tgz; procedure pas;";
    queryStr += " Select <bba1tgz, pas, bba1tgz.stmt#>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(4, "3 pOne 3",
            "3 progTwo 3", "3 doSmth 3", "3 unreachableProc 3"));
    // if, proc, if.stmt#
    queryStr = " if uyha; procedure tya; Select <uyha,tya,uyha.stmt#>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(8, "4 pOne 4",
            "4 progTwo 4", "4 doSmth 4", "4 unreachableProc 4", "13 pOne 13",
            "13 progTwo 13", "13 doSmth 13", "13 unreachableProc 13"));
    // variable, if, variable.varName
    queryStr = " variable ha; if ixa; Select <ha, ixa, ha.varName>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(64, "a 4 a", "a 13 a",
            "always 4 always", "always 13 always", "as 4 as", "as 13 as",
            "away 4 away", "away 13 away", "b 4 b", "b 13 b", "cool 4 cool",
            "cool 13 cool", "cooper 4 cooper", "cooper 13 cooper",
            "do 4 do", "do 13 do", "ends 4 ends", "ends 13 ends",
            "fate 4 fate", "fate 13 fate", "fly 4 fly", "fly 13 fly",
            "fun 4 fun", "fun 13 fun", "happy 4 happy", "happy 13 happy",
            "here 4 here", "here 13 here", "hypervisor 4 hypervisor",
            "hypervisor 13 hypervisor", "journey 4 journey",
            "journey 13 journey", "lor 4 lor", "lor 13 lor", "new 4 new",
            "new 13 new", "none 4 none", "none 13 none", "reaches 4 reaches",
            "reaches 13 reaches", "sheldon 4 sheldon", "sheldon 13 sheldon",
            "smth 4 smth", "smth 13 smth", "terrible 4 terrible",
            "terrible 13 terrible", "time 4 time", "time 13 time",
            "times 4 times", "times 13 times", "travel 4 travel",
            "travel 13 travel", "true 4 true", "true 13 true", "wow 4 wow",
            "wow 13 wow", "x 4 x", "x 13 x", "xen 4 xen", "xen 13 xen",
            "ya 4 ya", "ya 13 ya", "year 4 year", "year 13 year"));
    // constant, if, constant.value
    queryStr = " constant ka1; if aa; Select <ka1, aa, ka1.value> ";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(10, "2 4 2",
            "2 13 2", "61 4 61", "61 13 61", "425 4 425", "425 13 425",
            "781 4 781", "781 13 781", "2013 4 2013", "2013 13 2013"));
    // stmtLst, if, stmtLst.stmt#
    queryStr = " stmtLst sa1; if nb; Select <sa1, nb, sa1.stmt#> ";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(18, "1 4 1",
            "1 13 1", "4 4 4", "4 13 4", "5 4 5", "5 13 5", "7 4 7",
            "7 13 7", "12 4 12", "12 13 12", "14 4 14", "14 13 14",
            "16 4 16", "16 13 16", "19 4 19", "19 13 19", "20 4 20",
            "20 13 20"));
    // stmt, if, stmt.stmt#
    queryStr = " stmt xa; if bb; Select <xa, bb, xa.stmt#>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(40, "1 4 1",
            "1 13 1", "2 4 2",
            "2 13 2", "3 4 3", "3 13 3", "4 4 4", "4 13 4", "5 4 5",
            "5 13 5", "6 4 6", "6 13 6", "7 4 7", "7 13 7", "8 4 8",
            "8 13 8", "9 4 9", "9 13 9", "10 4 10", "10 13 10", "11 4 11",
            "11 13 11", "12 4 12", "12 13 12", "13 4 13", "13 13 13",
            "14 4 14", "14 13 14", "15 4 15", "15 13 15", "16 4 16",
            "16 13 16", "17 4 17", "17 13 17", "18 4 18", "18 13 18",
            "19 4 19", "19 13 19", "20 4 20", "20 13 20"));
    // progline, if, progline.stmt#
    queryStr = " prog_line pla1; if i; Select <pla1, i, pla1.prog_line#>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(40, "1 4 1",
            "1 13 1", "2 4 2",
            "2 13 2", "3 4 3", "3 13 3", "4 4 4", "4 13 4", "5 4 5",
            "5 13 5", "6 4 6", "6 13 6", "7 4 7", "7 13 7", "8 4 8",
            "8 13 8", "9 4 9", "9 13 9", "10 4 10", "10 13 10", "11 4 11",
            "11 13 11", "12 4 12", "12 13 12", "13 4 13", "13 13 13",
            "14 4 14", "14 13 14", "15 4 15", "15 13 15", "16 4 16",
            "16 13 16", "17 4 17", "17 13 17", "18 4 18", "18 13 18",
            "19 4 19", "19 13 19", "20 4 20", "20 13 20"));
}

void Test01_SelectNoClause::test_select_boolean()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;
    simpleProg =
        "procedure P { \
           a = 123; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = "Select BOOLEAN";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
}