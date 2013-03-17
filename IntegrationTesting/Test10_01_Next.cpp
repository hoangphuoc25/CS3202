#include <list>
#include <set>
#include <string>
#include "Test10_01_Next.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

void Test10_01_Next::setUp()
{
    this->NEXT_01_PROG = 
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

void Test10_01_Next::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test10_01_Next);

/*
    assgin:1,5,8,14,16,18,19
    call: 4,7,9,11,17
    if: 3,6,12,15
    while: 2,10,13
*/


void Test10_01_Next::test_next_stmt_01()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    const string& simpleProg = this->NEXT_01_PROG;
    evaluator.parseSimple(simpleProg);

    queryStr = "stmt s1,s2; while w;";
    queryStr += " Select s1 such that Next(w,s2) and Next(s1,s2)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "1","2","10","13","16","17"),
            stringSet);

    queryStr = "stmt s1,s2; while w;";
    queryStr += " Select s2 such that Next(w,s2) and Next(s1,s2)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6,"2","3","11","12","14","18"),
           stringSet);

    queryStr = "prog_line n1,n2; while w;";
    queryStr += " Select n2 such that Next(w,n2) and Next(n1,n2)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6,"2","3","11","12","14","18"),
           stringSet);

    queryStr = "prog_line n1,n2; while w;";
    queryStr += " Select n1 such that Next(w,n2) and Next(n1,n2)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "1","2","10","13","16","17"),
            stringSet);
}

void Test10_01_Next::test_next_assign_01()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    const string& simpleProg = this->NEXT_01_PROG;
    evaluator.parseSimple(simpleProg);

    queryStr = "assign a; stmt s; if i;";
    queryStr += " Select a such that Next(a,s) and Next(i,a)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3,"5","8","16"),
            stringSet);

    queryStr = "assign a; prog_line n; if i;";
    queryStr += " Select a such that Next(a,n) and Next(i,a)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3,"5","8","16"),
            stringSet);

    queryStr = "assign a; if i1,i2;";
    queryStr += " Select a such that Next(a,i2) and Next(i1,a)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            stringSet);

    queryStr = "assign a; call c;while w;";
    queryStr += " Select a such that Next(a,c) and Next(c,a)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),
            stringSet);

    queryStr = "assign a; while w; if i;";
    queryStr += " Select a such that Next(a,w) and Next(i,a)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),
            stringSet);

    queryStr = "assign a; stmt s; if i;";
    queryStr += " Select s such that Next(s,i) and Next(a,s)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "2"),
            stringSet);

    queryStr = "assign a; prog_line n; if i;";
    queryStr += " Select n such that Next(n,i) and Next(a,n)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "2"),
            stringSet);

    queryStr = "assign a; if i; stmt s;";
    queryStr += " Select i such that Next(i,s) and Next(a,i)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "6"),
            stringSet);

    queryStr = "assign a; call c; stmt s;";
    queryStr += " Select c such that Next(a,c) and Next(a,c)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "9"),
            stringSet);

    queryStr = "assign a; while w; stmt s;";
    queryStr += " Select w such that Next(s,w) and Next(a,w)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "2","13"),
            stringSet);


}

void Test10_01_Next::test_next_while_01()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    const string& simpleProg = this->NEXT_01_PROG;
    evaluator.parseSimple(simpleProg);

    queryStr = "while w; stmt s; call c;";
    queryStr += " Select w such that Next(w,s) and Next(c,w)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"10"),
            stringSet);

    queryStr = "while w; prog_line n; call c;";
    queryStr += " Select w such that Next(w,n) and Next(c,w)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"10"),
            stringSet);

    
    queryStr = "while w; if i;assign a;";
    queryStr += "Select w such that Next(w,i) and Next(a,w)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "2"),
            stringSet);

    queryStr = "while w; call c;";
    queryStr += "Select w such that Next(w,c) and Next(c,w)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "10"),
            stringSet);


    queryStr = "while w;stmt s;";
    queryStr += " Select w such that Next(s,w) and Next(w,w)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),
            stringSet);

    queryStr = "while w; stmt s;assign a;";
    queryStr += " Select s such that Next(w,s) and Next(a,s)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);


    queryStr = "while w; prog_line n;assign a;";
    queryStr += " Select n such that Next(w,n) and Next(a,n)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "2","18"),
            stringSet);

    queryStr = "while w1,w2; if i;";
    queryStr += " Select i such that Next(i,w2) and Next(w1,i)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"12"),
            stringSet);

    queryStr = "while w; call c;";
    queryStr += " Select c such that Next(c,w) and Next(w,c)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "11"),
            stringSet);

}

void Test10_01_Next::test_next_if_01()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    const string& simpleProg = this->NEXT_01_PROG;
    evaluator.parseSimple(simpleProg);

    queryStr = "if i; stmt s;assign a;";
    queryStr += " Select i such that Next(i,s) and Next(a,i)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"6"),
            stringSet);

    queryStr = "if i; prog_line n; call c;";
    queryStr += " Select i such that Next(i,n) and Next(c,i)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"6"),
            stringSet);

    queryStr = "if i1,i2;assign a;";
    queryStr += " Select i2 such that Next(i2,a) and Next(i1,i2)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"15"),
            stringSet);

    queryStr = "if i; call c;stmt s;";
    queryStr += " Select i such that Next(i,c) and Next(s,i)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3,"3","6","15"),
            stringSet);

    queryStr = "if i; while w;call c;";
    queryStr += " Select i such that Next(i,w) and Next(c,i)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),
            stringSet);

    queryStr = "if i; stmt s; assign a;";
    queryStr += " Select s such that Next(i,a) and Next(i,s)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "4","5","7","8","16","17"),
            stringSet);

    queryStr = "if i; prog_line n; while w;";
    queryStr += " Select n such that Next(w,i) and Next(i,n)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "4","5","13","15"),
            stringSet);

    queryStr = "if i; call c;call c2;";
    queryStr += " Select c such that Next(c2,i) and Next(i,c)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"7"),
            stringSet);
}

void Test10_01_Next::test_next_call_01()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    const string& simpleProg = this->NEXT_01_PROG;
    evaluator.parseSimple(simpleProg);

    queryStr = "call c; stmt s;if i;";
    queryStr += " Select c such that Next(c,s) and Next(i,c)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3,"4","7","17"),
            stringSet);

    queryStr = "call c; prog_line n;if i;";
    queryStr += " Select c such that Next(c,n) and Next(i,c)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3,"4","7","17"),
            stringSet);

    queryStr = "if i; call c; assign a;";
    queryStr += " Select c such that Next(c,i) and Next(a,c)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),
            stringSet);

    queryStr = "if i; call c; stmt s;";
    queryStr += " Select i such that Next(c,s) and Next(c,i)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"6"),
            stringSet);

    queryStr = "call c; while w; if i;";
    queryStr += " Select c such that Next(c,w) and Next(i,c)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),
            stringSet);

    queryStr = "call c; stmt s1,s2;";
    queryStr += " Select s2 such that Next(s1,s2) and Next(c,s2)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4,"6","9","10","18"),
            stringSet);

    queryStr = "call c; prog_line n; call c2;";
    queryStr += " Select n such that Next(c2,n) and Next(c,n)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4,"6","9","10","18"),
            stringSet);

    queryStr = "call c1,c2;assign a;";
    queryStr += " Select c2 such that Next(c1,c2) and Next(a,c2)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"9"),
            stringSet);
}
