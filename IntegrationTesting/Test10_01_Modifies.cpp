#include <cstdio>
#include <cstdarg>
#include <string>
#include <map>
#include <set>
#include <list>
#include <utility>
#include "Test10_01_Modifies.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::string;
using std::map;
using std::list;
using std::set;
using std::pair;
using std::make_pair;

void Test10_01_Modifies::setUp()
{
    this->MODIFIES_01_PROG =
        "procedure pOne { \
           px = ty; \
           abc = sun; \
           if t then { \
             sun = rise; \
             while true { \
               heck = it + la; \
             } \
             pipe = dream; \
           } else { \
             dawn = now; \
             while smth { \
               snake = here; \
               if notTrue then { \
                 nobodyUses = 23; \
               } else { \
                 nobodyUses = abcd; \
               } \
             } \
           } \
           my = friend; \
           while germ { \
             sun = no + sun; \
           } \
           great = things; \
           come = hard; \
           call procTwo; \
         } \
         procedure procTwo { \
           hell = no; \
           while fine { \
             dont = heck; \
           } \
           no = go; \
           call procThree; \
         } \
         procedure procThree { \
           man = human; \
           whos = here; \
           hell = yes; \
         }";
}

void Test10_01_Modifies::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test10_01_Modifies);

void Test10_01_Modifies::test_modifies_assign_var_01()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    // Uses(procedure,var)
    const string& simpleProg = this->MODIFIES_01_PROG;
    // vacuously correct but no choice for now
    evaluator.parseSimple(simpleProg);
    queryStr = "assign a, a2; variable v1, v2; procedure p; ";
    queryStr += " Select a2 such that Modifies(a,v1) and Modifies(a2,v1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Modifies(a,v1)
    // (1,px), (2,abc), (4,sun), (6,heck), (7,pipe), (8,dawn), (10,snake)
    // (12,nobodyUses), (13,nobodyUses), (14,my), (16,sun),
    // (17,great), (18,come), (20,hell), (22,dont), (23,no),
    // (25,man), (26,whos), (27, hell)
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(19, "1", "2", "4", "6",
            "7", "8", "10", "12", "13", "14", "16", "17", "18",
            "20", "22", "23", "25", "26", "27"),
            stringSet);
}

void Test10_01_Modifies::test_modifies_proc_var_01()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    // Uses(procedure,var)
    const string& simpleProg = this->MODIFIES_01_PROG;
    // vacuously correct but no choice for now
    evaluator.parseSimple(simpleProg);
    queryStr = "assign a, a2; variable v1, v2; procedure p; ";
    queryStr += " Select p such that Modifies(a,v1) and Modifies(p,v1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Modifies(a,v1)
    // (1,px), (2,abc), (4,sun), (6,heck), (7,pipe), (8,dawn), (10,snake)
    // (12,nobodyUses), (13,nobodyUses), (14,my), (16,sun),
    // (17,great), (18,come), (20,hell), (22,dont), (23,no),
    // (25,man), (26,whos), (27, hell)
    //
    // Modifies(p,v1)
    // a | v1 | p
    // (1,px,pOne), (2,abc,pOne), (4,sun,pOne), (6,heck,pOne),
    // (7,pipe,pOne), (8,dawn,pOne), (10,snake,pOne), (12,nobodyUses,pOne),
    // (13,nobodyUses,pOne), (14,my,pOne), (16,sun,pOne),
    // (17,great,pOne), (18,come,pOne), (20,hell,pOne),
    // (20,hell,procTwo), (20,hell,procThree), (22,dont,pOne),
    // (22,dont,procTwo),
    // (23,no,pOne), (23,no,procTwo), (25,man,pOne), (25,man,procTwo),
    // (25,man,procThree), (26,whos,pOne), (26,whos,procTwo),
    // (26,whos,procThree), (27,hell,pOne), (27,hell,procTwo),
    // (27,hell,procThree)
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "pOne", "procTwo",
            "procThree"),
            stringSet);
    // select whole table
    queryStr = "assign a, a2; variable v1, v2; procedure p; ";
    queryStr += " Select <a,v1,p> such that Modifies(a,v1) and ";
    queryStr += " Modifies(p,v1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(29, "1 px pOne", "2 abc pOne",
            "4 sun pOne", "6 heck pOne", "7 pipe pOne", "8 dawn pOne",
            "10 snake pOne",
            "12 nobodyUses pOne", "13 nobodyUses pOne", "14 my pOne",
            "16 sun pOne", "17 great pOne", "18 come pOne",
            "20 hell pOne", "20 hell procTwo", "20 hell procThree",
            "22 dont pOne",
            "22 dont procTwo", "23 no pOne", "23 no procTwo",
            "25 man pOne", "25 man procTwo", "25 man procThree",
            "26 whos pOne", "26 whos procTwo", "26 whos procThree",
            "27 hell pOne", "27 hell procTwo", "27 hell procThree"),
            stringSet);
}

void Test10_01_Modifies::test_modifies_call_var_01()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    const string& simpleProg = this->MODIFIES_01_PROG;
    evaluator.parseSimple(simpleProg);
    queryStr = "assign a; variable v1, v2; call c; ";
    queryStr += " Select <a,v1,c> such that Modifies(a,v1) ";
    queryStr += " and Modifies(c,v1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Modifies(a,v1)
    // a | v1
    // (1,px), (2,abc), (4,sun), (6,heck), (7,pipe), (8,dawn), (10,snake)
    // (12,nobodyUses), (13,nobodyUses), (14,my), (16,sun),
    // (17,great), (18,come), (20,hell), (22,dont), (23,no),
    // (25,man), (26,whos), (27, hell)
    // ---
    // Modifies(c,v1)
    // a | v1 | c
    // (20,hell,19), (20,hell,24), (22,dont,19), (23,no,19), (25,man,19),
    // (25,man,24), (26,whos,19), (26,whos,24), (27,hell,19),
    // (27,hell,24)
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(10, "20 hell 19", "20 hell 24",
            "22 dont 19", "23 no 19", "25 man 19", "25 man 24",
            "26 whos 19", "26 whos 24", "27 hell 19", "27 hell 24"),
            stringSet);
}

void Test10_01_Modifies::test_modifies_while_var_01()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    const string& simpleProg = this->MODIFIES_01_PROG;
    evaluator.parseSimple(simpleProg);
    queryStr = "assign a; variable v1, v2; while w; ";
    queryStr += " Select <a,v1,w> such that Modifies(a,v1) ";
    queryStr += " and Modifies(w,v1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Modifies(a,v1)
    // a | v1
    // (1,px), (2,abc), (4,sun), (6,heck), (7,pipe), (8,dawn), (10,snake)
    // (12,nobodyUses), (13,nobodyUses), (14,my), (16,sun),
    // (17,great), (18,come), (20,hell), (22,dont), (23,no),
    // (25,man), (26,whos), (27, hell)
    // ---
    // Modifies(w,v1)
    // a | v1 | w
    // (4,sun,13), (6,heck,5), (10,snake,9), (12,nobodyUses,9)
    // (13,nobodyuses,9), (16,sun,15), (22,dont,21)
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "4 sun 15", "6 heck 5",
            "10 snake 9", "12 nobodyUses 9", "13 nobodyUses 9",
            "16 sun 15", "22 dont 21"),
            stringSet);
}

void Test10_01_Modifies::test_modifies_if_var_01()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    const string& simpleProg = this->MODIFIES_01_PROG;
    evaluator.parseSimple(simpleProg);
    queryStr = "assign a; variable v1, v2; if if1; ";
    queryStr += " Select <a,v1,if1> such that Modifies(a,v1) and ";
    queryStr += " Modifies(if1,v1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Modifies(a,v1)
    // a | v1
    // (1,px), (2,abc), (4,sun), (6,heck), (7,pipe), (8,dawn), (10,snake)
    // (12,nobodyUses), (13,nobodyUses), (14,my), (16,sun),
    // (17,great), (18,come), (20,hell), (22,dont), (23,no),
    // (25,man), (26,whos), (27, hell)
    // ---
    // Modifies(if1,v1)
    // a | v1 | if1
    // (4,sun,3), (6,heck,3), (7,pipe,3), (8,dawn,3), (10,snake,3)
    // (12,nobodyUses,3), (12,nobodyUses,11), (13,nobodyUses,3),
    // (13,nobodyUses,11), (16,sun,3)
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(10, "4 sun 3", "6 heck 3",
            "7 pipe 3", "8 dawn 3", "10 snake 3", "12 nobodyUses 3",
            "12 nobodyUses 11", "13 nobodyUses 3", "13 nobodyUses 11",
            "16 sun 3"),
            stringSet);
}

void Test10_01_Modifies::test_modifies_stmt_var_01()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    const string& simpleProg = this->MODIFIES_01_PROG;
    evaluator.parseSimple(simpleProg);
    queryStr = "assign a; variable v1, v2; stmt s1; ";
    queryStr += " Select <a,v1,s1> such that Modifies(a,v1) and ";
    queryStr += " Modifies(s1,v1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Modifies(a,v1)
    // a | v1
    // (1,px), (2,abc), (4,sun), (6,heck), (7,pipe), (8,dawn), (10,snake)
    // (12,nobodyUses), (13,nobodyUses), (14,my), (16,sun),
    // (17,great), (18,come), (20,hell), (22,dont), (23,no),
    // (25,man), (26,whos), (27, hell)
    // ---
    // Modifies(s1,v1)
    // a | v1 | s1
    // (1,px,1), (2,abc,2), (4,sun,3), (4,sun,4), (4,sun,15)
    // (4,sun,16), (6,heck,3), (6,heck,5), (6,heck,6), (7,pipe,3)
    // (7,pipe,7), (8,dawn,3), (8,dawn,8), (10,snake,3), (10,snake,9)
    // (10,snake,10), (12,nobodyUses,3),  (12,nobodyUses,9),
    // (12,nobodyUses,11), (12,nobodyUses,12), (12,nobodyUses,13),
    // (13,nobodyUses,3), (13,nobodyUses,9), (13,nobodyUses,11)
    // (13,nobodyUses,12), (13,nobodyUses,13), (14,my,14), (16,sun,3)
    // (16,sun,4), (16,sun,15), (16,sun,16), (17,great,17), (18,come,18)
    // (20,hell,19), (20,hell,20), (20,hell,24), (20,hell,27)
    // (22,dont,19), (22,dont,21), (22,dont,22), (23,no,19)
    // (23,no,23), (25,man,19), (25,man,24), (25,man,25), (26,whos,19)
    // (26,whos,24), (26,whos,26), (27,hell,19), (27,hell,20)
    // (27,hell,24), (27,hell,27)
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(52, "1 px 1", "2 abc 2",
            "4 sun 3", "4 sun 4", "4 sun 15", "4 sun 16", "6 heck 3",
            "6 heck 5", "6 heck 6", "7 pipe 3", "7 pipe 7", "8 dawn 3",
            "8 dawn 8", "10 snake 3", "10 snake 9", "10 snake 10",
            "12 nobodyUses 3", "12 nobodyUses 9", "12 nobodyUses 11",
            "12 nobodyUses 12", "12 nobodyUses 13", "13 nobodyUses 3",
            "13 nobodyUses 9", "13 nobodyUses 11", "13 nobodyUses 12",
            "13 nobodyUses 13", "14 my 14", "16 sun 3", "16 sun 4",
            "16 sun 15", "16 sun 16", "17 great 17", "18 come 18",
            "20 hell 19", "20 hell 20", "20 hell 24", "20 hell 27",
            "22 dont 19", "22 dont 21", "22 dont 22", "23 no 19",
            "23 no 23", "25 man 19", "25 man 24", "25 man 25",
            "26 whos 19", "26 whos 24", "26 whos 26", "27 hell 19",
            "27 hell 20", "27 hell 24", "27 hell 27"),
            stringSet);
}

void Test10_01_Modifies::test_modifies_progline_var()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    const string& simpleProg = this->MODIFIES_01_PROG;
    evaluator.parseSimple(simpleProg);
    queryStr = "assign a; variable v1, v2; prog_line Kbv; ";
    queryStr += " Select <a,v1,Kbv> such that Modifies(a,v1) and ";
    queryStr += " Modifies(Kbv,v1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Modifies(a,v1)
    // a | v1
    // (1,px), (2,abc), (4,sun), (6,heck), (7,pipe), (8,dawn), (10,snake)
    // (12,nobodyUses), (13,nobodyUses), (14,my), (16,sun),
    // (17,great), (18,come), (20,hell), (22,dont), (23,no),
    // (25,man), (26,whos), (27, hell)
    // ---
    // Modifies(s1,v1)
    // a | v1 | s1
    // (1,px,1), (2,abc,2), (4,sun,3), (4,sun,4), (4,sun,15)
    // (4,sun,16), (6,heck,3), (6,heck,5), (6,heck,6), (7,pipe,3)
    // (7,pipe,7), (8,dawn,3), (8,dawn,8), (10,snake,3), (10,snake,9)
    // (10,snake,10), (12,nobodyUses,3),  (12,nobodyUses,9),
    // (12,nobodyUses,11), (12,nobodyUses,12), (12,nobodyUses,13),
    // (13,nobodyUses,3), (13,nobodyUses,9), (13,nobodyUses,11)
    // (13,nobodyUses,12), (13,nobodyUses,13), (14,my,14), (16,sun,3)
    // (16,sun,4), (16,sun,15), (16,sun,16), (17,great,17), (18,come,18)
    // (20,hell,19), (20,hell,20), (20,hell,24), (20,hell,27)
    // (22,dont,19), (22,dont,21), (22,dont,22), (23,no,19)
    // (23,no,23), (25,man,19), (25,man,24), (25,man,25), (26,whos,19)
    // (26,whos,24), (26,whos,26), (27,hell,19), (27,hell,20)
    // (27,hell,24), (27,hell,27)
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(52, "1 px 1", "2 abc 2",
            "4 sun 3", "4 sun 4", "4 sun 15", "4 sun 16", "6 heck 3",
            "6 heck 5", "6 heck 6", "7 pipe 3", "7 pipe 7", "8 dawn 3",
            "8 dawn 8", "10 snake 3", "10 snake 9", "10 snake 10",
            "12 nobodyUses 3", "12 nobodyUses 9", "12 nobodyUses 11",
            "12 nobodyUses 12", "12 nobodyUses 13", "13 nobodyUses 3",
            "13 nobodyUses 9", "13 nobodyUses 11", "13 nobodyUses 12",
            "13 nobodyUses 13", "14 my 14", "16 sun 3", "16 sun 4",
            "16 sun 15", "16 sun 16", "17 great 17", "18 come 18",
            "20 hell 19", "20 hell 20", "20 hell 24", "20 hell 27",
            "22 dont 19", "22 dont 21", "22 dont 22", "23 no 19",
            "23 no 23", "25 man 19", "25 man 24", "25 man 25",
            "26 whos 19", "26 whos 24", "26 whos 26", "27 hell 19",
            "27 hell 20", "27 hell 24", "27 hell 27"),
            stringSet);
}