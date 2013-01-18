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

void Test_00_SelectNoClause::test_select_two_same_syn()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    set<string> stringSet;
    const string& simpleProg = this->SELECT_ONE_SIMPLEPROG;
    evaluator.parseSimple(simpleProg);
    // assign
    queryStr = "assign bhad; Select <bhad,bhad>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 18, "1,1", "2,2", "4,4", "6,6",
            "9,9", "11,11", "12,12", "13,13", "14,14", "16,16", "17,17",
            "18,18", "20,20", "21,21", "22,22", "24,24", "25,25",
            "26,26");
    // if
    queryStr = "if mhs; Select <mhs,mhs>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 3, "3,3", "10,10", "23,23");
    // while
    queryStr = " while kjfh21; Select <kjfh21,kjfh21>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 3, "5,5", "8,8", "19,19");
    // call
    queryStr = "call gasd; Select <gasd  ,  gasd>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 2, "7,7", "15,15");
    // stmt
    queryStr = "stmt awe1; Select <awe1, awe1>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 26, "1,1", "2,2", "3,3", "4,4",
            "5,5", "6,6", "7,7", "8,8", "9,9", "10,10", "11,11", "12,12",
            "13,13", "14,14", "15,15", "16,16", "17,17", "18,18", "19,19",
            "20,20", "21,21", "22,22", "23,23", "24,24", "25,25", "26,26");
    // progline
    queryStr = " prog_line gfhns1#; Select  <gfhns1#  , gfhns1#>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 26, "1,1", "2,2", "3,3", "4,4",
            "5,5", "6,6", "7,7", "8,8", "9,9", "10,10", "11,11", "12,12",
            "13,13", "14,14", "15,15", "16,16", "17,17", "18,18", "19,19",
            "20,20", "21,21", "22,22", "23,23", "24,24", "25,25", "26,26");
    // stmtLst
    queryStr = " stmtLst hhl5; Select <hhl5,hhl5>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 12, "1,1", "4,4", "6,6", "9,9",
        "11,11", "12,12", "18,18", "20,20", "22,22", "24,24", "25,25",
        "26,26");
    // const
    queryStr = " constant hhafd1; Select  <hhafd1 ,\t hhafd1> ";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 2, "0,0", "55,55");
    // var
    queryStr = " variable  uts; Select  <uts,uts>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 42, "a,a", "aa,aa",
            "am,am", "b,b", "bad,bad", "blah,blah",
            "bye,bye", "cd,cd", "down,down", "ee,ee", "evil,evil",
            "eye,eye", "f,f", "g,g", "gadfly,gadfly", "gg,gg",
            "ggGGggGG,ggGGggGG", "good,good", "gt,gt",
            "harryPotter,harryPotter", "harryPuttar,harryPuttar",
            "heat,heat", "hell,hell", "hi,hi", "i,i", "ish,ish", "no,no",
            "not,not", "orange,orange", "out,out", "red,red",
            "sink,sink", "tify,tify", "tree,tree",
            "true,true", "two,two", "x,x", "xc,xc", "xp,xp", "y,y",
            "yea,yea", "yellow,yellow");
    // procedure
    queryStr = " procedure   h4Adfs; Select   <h4Adfs,h4Adfs>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 3, "pOne,pOne",
            "twoProng,twoProng", "GGG,GGG");
}

void Test_00_SelectNoClause::test_select_syn_syn_attr()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    set<string> stringSet;
    const string& simpleProg = this->SELECT_ONE_SIMPLEPROG;
    evaluator.parseSimple(simpleProg);
    // assign
    queryStr = "assign msfn; Select <msfn,msfn.stmt#>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 18, "1,1", "2,2", "4,4", "6,6",
            "9,9", "11,11", "12,12", "13,13", "14,14", "16,16", "17,17",
            "18,18", "20,20", "21,21", "22,22", "24,24", "25,25",
            "26,26");
    // if
    queryStr = "if  ina; Select <ina,ina.stmt#>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 3, "3,3", "10,10", "23,23");
    // while
    queryStr = " while dh1; Select <dh1,dh1.stmt#>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 3, "5,5", "8,8", "19,19");
    // call, call.stmt#
    queryStr = "call jkjag; Select <jkjag  ,  jkjag.stmt#>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 2, "7,7", "15,15");
    // call, call.procName
    queryStr = "call Th2; Select <Th2  ,  Th2.procName>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 2, "7,twoProng", "15,GGG");
    // stmt
    queryStr = "stmt uea; Select <uea, uea.stmt#>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 26, "1,1", "2,2", "3,3", "4,4",
            "5,5", "6,6", "7,7", "8,8", "9,9", "10,10", "11,11", "12,12",
            "13,13", "14,14", "15,15", "16,16", "17,17", "18,18", "19,19",
            "20,20", "21,21", "22,22", "23,23", "24,24", "25,25", "26,26");
    // progline
    queryStr = " prog_line xe1#; Select  <xe1#  , xe1#.stmt#>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 26, "1,1", "2,2", "3,3", "4,4",
            "5,5", "6,6", "7,7", "8,8", "9,9", "10,10", "11,11", "12,12",
            "13,13", "14,14", "15,15", "16,16", "17,17", "18,18", "19,19",
            "20,20", "21,21", "22,22", "23,23", "24,24", "25,25", "26,26");
    // stmtLst
    queryStr = " stmtLst loa1; Select <loa1,loa1.stmt#>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 12, "1,1", "4,4", "6,6", "9,9",
        "11,11", "12,12", "18,18", "20,20", "22,22", "24,24", "25,25",
        "26,26");
    // const
    queryStr = " constant yar; Select  <yar ,\t yar.value> ";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 2, "0,0", "55,55");
    // var
    queryStr = " variable  yabza; Select  <yabza,yabza.varName>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 42, "a,a", "aa,aa",
            "am,am", "b,b", "bad,bad", "blah,blah",
            "bye,bye", "cd,cd", "down,down", "ee,ee", "evil,evil",
            "eye,eye", "f,f", "g,g", "gadfly,gadfly", "gg,gg",
            "ggGGggGG,ggGGggGG", "good,good", "gt,gt",
            "harryPotter,harryPotter", "harryPuttar,harryPuttar",
            "heat,heat", "hell,hell", "hi,hi", "i,i", "ish,ish", "no,no",
            "not,not", "orange,orange", "out,out", "red,red",
            "sink,sink", "tify,tify", "tree,tree",
            "true,true", "two,two", "x,x", "xc,xc", "xp,xp", "y,y",
            "yea,yea", "yellow,yellow");
    // procedure
    queryStr = " procedure   pofs; Select   <pofs,pofs.procName>";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 3, "pOne,pOne",
            "twoProng,twoProng", "GGG,GGG");
}