#include <list>
#include <set>
#include <string>
#include "Test10_00_Next.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"


using std::list;
using std::set;
using std::string;

void Test10_00_Next::setUp() 
{
    this->NEXT_00_PROG = 
        "procedure next {\
            a = 1;\
            while b2 {\
                if c3 then {\
                    call lala; }\
                else {\
                    e5 = 1;}\
                if f6 then {\
                    call lala; }\
                else {\
                    h8 = 1; }\
                call lala;\
                while j10 {\
                    call lala; }}\
            if l12 then {\
                while m13 {\
                    n14 = 1; }}\
            else {\
                if o15 then {\
                    p16 = 1; }\
                else {\
                    call lala; }}\
            r18 = 1;\
            s19 = 1;\
        }\
        procedure lala {\
            a = 1;\
        }";
}

void Test10_00_Next::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test10_00_Next);


/*
    assgin:1,5,8,14,16,18,19
    call: 4,7,9,11,17
    if: 3,6,12,15
    while: 2,10,13
*/


void Test10_00_Next::test_next_stmt_00()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    const string& simpleProg = this->NEXT_00_PROG;
    evaluator.parseSimple(simpleProg);

    queryStr = "stmt s1,s2;";
    queryStr += " Select s1 such that Next(s1,s2)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(18, "1", "2","3","4","5","6",
            "7","8","9","10","11","12","13","14","15","16","17","18"),
            stringSet);

    queryStr = "stmt s1,s2;";
    queryStr += " Select s2 such that Next(s1,s2)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(18, "19", "2","3","4","5","6",
            "7","8","9","10","11","12","13","14","15","16","17","18"),
            stringSet);

    queryStr = "prog_line n1,n2;";
    queryStr += " Select n2 such that Next(n1,n2)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(18, "19", "2","3","4","5","6",
            "7","8","9","10","11","12","13","14","15","16","17","18"),
            stringSet);

    queryStr = "prog_line n1,n2;";
    queryStr += " Select n1 such that Next(n1,n2)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(18, "1", "2","3","4","5","6",
            "7","8","9","10","11","12","13","14","15","16","17","18"),
            stringSet);
}

void Test10_00_Next::test_next_assign_00()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    const string& simpleProg = this->NEXT_00_PROG;
    evaluator.parseSimple(simpleProg);

    queryStr = "assign a; stmt s;";
    queryStr += " Select a such that Next(a,s)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "1","5","8","14","16","18"),
            stringSet);

    queryStr = "assign a; prog_line n;";
    queryStr += " Select a such that Next(a,n)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "1","5","8","14","16","18"),
            stringSet);

    queryStr = "assign a; if i;";
    queryStr += " Select a such that Next(a,i)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);

    queryStr = "assign a; call c;";
    queryStr += " Select a such that Next(a,c)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "8"),
            stringSet);

    queryStr = "assign a; while w;";
    queryStr += " Select a such that Next(a,w)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "1","14"),
            stringSet);

    queryStr = "assign a; stmt s;";
    queryStr += " Select s such that Next(a,s)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "2","6","9","13","18","19"),
            stringSet);

    queryStr = "assign a; prog_line n;";
    queryStr += " Select n such that Next(a,n)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "2","6","9","13","18","19"),
            stringSet);

    queryStr = "assign a; if i;";
    queryStr += " Select i such that Next(a,i)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "6"),
            stringSet);

    queryStr = "assign a; call c;";
    queryStr += " Select c such that Next(a,c)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "9"),
            stringSet);

    queryStr = "assign a; while w;";
    queryStr += " Select w such that Next(a,w)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "2","13"),
            stringSet);


}

void Test10_00_Next::test_next_while_00()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    const string& simpleProg = this->NEXT_00_PROG;
    evaluator.parseSimple(simpleProg);

    queryStr = "while w; stmt s;";
    queryStr += " Select w such that Next(w,s)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3,"2","10","13"),
            stringSet);

    queryStr = "while w; prog_line n;";
    queryStr += " Select w such that Next(w,n)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3,"2","10","13"),
            stringSet);

    queryStr = "while w; if i;";
    queryStr += " Select w such that Next(w,i)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "2"),
            stringSet);

    queryStr = "while w; call c;";
    queryStr += " Select w such that Next(w,c)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "10"),
            stringSet);


    queryStr = "while w;";
    queryStr += " Select w such that Next(w,w)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),
            stringSet);

    queryStr = "while w; stmt s;";
    queryStr += " Select s such that Next(w,s)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);

    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "2", "3",
            "11", "12", "14", "18"),
            stringSet);

    queryStr = "while w; prog_line n;";
    queryStr += " Select n such that Next(w,n)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "2", "3",
            "11", "12", "14", "18"),
            stringSet);

    queryStr = "while w; if i;";
    queryStr += " Select i such that Next(w,i)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "12"),
            stringSet);

    queryStr = "while w; call c;";
    queryStr += " Select c such that Next(w,c)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "11"),
            stringSet);

}

void Test10_00_Next::test_next_if_00()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    const string& simpleProg = this->NEXT_00_PROG;
    evaluator.parseSimple(simpleProg);

    queryStr = "if i; stmt s;";
    queryStr += " Select i such that Next(i,s)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4,"3","6","12","15"),
            stringSet);

    queryStr = "if i; prog_line n;";
    queryStr += " Select i such that Next(i,n)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4,"3","6","12","15"),
            stringSet);

    queryStr = "if i1,i2;";
    queryStr += " Select i1 such that Next(i1,i2)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"12"),
            stringSet);

    queryStr = "if i; call c;";
    queryStr += " Select i such that Next(i,c)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3,"3","6","15"),
            stringSet);

    queryStr = "if i; while w;";
    queryStr += " Select i such that Next(i,w)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"12"),
            stringSet);

    queryStr = "if i; stmt s;";
    queryStr += " Select s such that Next(i,s)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(8, "4","5","7","8","13","15","16","17"),
            stringSet);

    queryStr = "if i; prog_line n;";
    queryStr += " Select n such that Next(i,n)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(8, "4","5","7","8","13","15","16","17"),
            stringSet);

    queryStr = "if i; call c;";
    queryStr += " Select c such that Next(i,c)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "4","7","17"),
            stringSet);
}

void Test10_00_Next::test_next_call_00()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    const string& simpleProg = this->NEXT_00_PROG;
    evaluator.parseSimple(simpleProg);

    queryStr = "call c; stmt s;";
    queryStr += " Select c such that Next(c,s)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5,"4","7","9","11","17"),
            stringSet);

    queryStr = "call c; prog_line n;";
    queryStr += " Select c such that Next(c,n)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5,"4","7","9","11","17"),
            stringSet);

    queryStr = "if i; call c;";
    queryStr += " Select c such that Next(c,i)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"4"),
            stringSet);

    queryStr = "if i; call c;";
    queryStr += " Select i such that Next(c,i)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"6"),
            stringSet);

    queryStr = "call c; while w;";
    queryStr += " Select c such that Next(c,w)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2,"9","11"),
            stringSet);

    queryStr = "call c; stmt s;";
    queryStr += " Select s such that Next(c,s)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4,"6","9","10","18"),
            stringSet);

    queryStr = "call c; prog_line n;";
    queryStr += " Select n such that Next(c,n)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4,"6","9","10","18"),
            stringSet);

    queryStr = "call c1,c2;";
    queryStr += " Select c1 such that Next(c1,c2)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"7"),
            stringSet);


}