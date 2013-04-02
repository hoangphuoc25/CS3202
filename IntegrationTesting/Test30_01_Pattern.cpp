#include <list>
#include <set>
#include <string>
#include "Test30_01_Pattern.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

void Test30_01_Pattern::setUp() {}
void Test30_01_Pattern::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test30_01_Pattern);

void Test30_01_Pattern::test_2()
{
    const string simpleProg = "\
    procedure time {\
        I = 1231;\
        energy = I;\
        health = 0;\
        do = 1;\
        while do {\
            energy = energy - 1;\
            do = do - 1;\
            if do then {\
                call jobs;\
                energy = energy - 1;\
            } else {\
                health = (health + energy) * 2;\
            }\
        }\
    }\
    procedure jobs {\
        task = 5;\
        done = 1;\
        hp = 1000;\
        while hp {\
            hp = hp - task * 50;\
            if hp then {\
                hp = hp - 50;\
            } else {\
                call relax;\
            }\
        }\
    }\
    procedure relax {\
        hp = hp + 500;\
        time = time - 1;\
        energy = energy + 100;\
    }";
    string queryStr;
    QueryEvaluator evaluator;
    evaluator.parseSimple(simpleProg);
    list<string> resultList;
    SetWrapper<string> stringSet;

    //a(v, "b+c")
    queryStr = "while w; assign a; variable v;";
    queryStr += "Select a such that Modifies(w, v) pattern a(v,\"energy - 1\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "6", "10"), stringSet);

    queryStr = "while w; assign a; variable v;";
    queryStr += "Select w such that Modifies(w, v) pattern a(v,\"energy - 1\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "5", "15"), stringSet);

    //a(v, _)
    queryStr = "while w; assign a; variable v;";
    queryStr += "Select w such that Parent(w, a) pattern a(_,\"energy - 1\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"), stringSet);

    //a(v, _"b+c"_)
    queryStr = "while w; assign a; variable v;";
    queryStr += "Select <w, v> such that Modifies(w, v) pattern a(v, _\"health + energy\"_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5,health"), stringSet);

    //a(_, _)
    queryStr = "procedure p; while w; assign a; variable v;";
    queryStr += "Select p such that Modifies(p, v) pattern a(_, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "time", "jobs", "relax"), stringSet);

    //a(_, "b+c")
    queryStr = "procedure p; while w; assign a; variable v;";
    queryStr += "Select p such that Modifies(p, v) pattern a(_, \"task*50\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0), stringSet);

    //a(_, _"b+c"_)
    queryStr = "procedure p; while w; assign a; variable v;";
    queryStr += "Select p such that Modifies(p, v) pattern a(_, _\"task*50\"_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "time", "jobs", "relax"), stringSet);

    //a("x", _)
    queryStr = "procedure p; while w; assign a; variable v;";
    queryStr += "Select <p, a> such that Modifies(p, v) pattern a(\"hp\", _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(12, "time,14", "time,16", "time,18",
        "time,20","jobs,14", "jobs,16", "jobs,18","jobs,20","relax,14",
        "relax,16","relax,18","relax,20"), stringSet);

    //a("x", "b+c")
    queryStr = "procedure p; while w; assign a; variable v;";
    queryStr += "Select <p, a> such that Modifies(p, v) pattern a(\"energy\",\"energy - 1\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "time,6", "time,10", "relax,6",
        "relax,10","jobs,6","jobs,10"), stringSet);

    //a("x", _"b+c"_)
    queryStr = "procedure p; while w; assign a; variable v;";
    queryStr += "Select <p, a> such that Modifies(p, v) pattern a(\"energy\",_\"energy - 1\"_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "jobs,6","jobs,10","time,6",
        "time,10","relax,6","relax,10"), stringSet);
}
