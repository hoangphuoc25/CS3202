#include <list>
#include <set>
#include <string>
#include "Test30_11_Pattern.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

CPPUNIT_TEST_SUITE_REGISTRATION(Test30_11_Pattern);

void Test30_11_Pattern::setUp()
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
}

void Test30_11_Pattern::tearDown() {}

void Test30_11_Pattern::test_2()
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

    //a(v, _)
    queryStr = "procedure p; while w; assign a; variable v;";
    queryStr += "Select <p, a> such that Modifies(p, v) and \
                Parent(w, a) pattern a(v, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "time,6","time,7",
        "time,16","jobs,16","relax,16",
        "jobs,6","relax,6"), stringSet);

    //a(v, "b+c")
    queryStr = "procedure p; while w; assign a; variable v;";
    queryStr += "Select <p, a> such that Modifies(p, v)\
                and Parent(w, a) pattern a(v, \"energy - 1\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "time,6", "jobs,6",
        "relax,6"), stringSet);

    //a(v, _"b+c"_)
    queryStr = "procedure p; while w; assign a; variable v;";
    queryStr += "Select <p, a> such that Modifies(p, v)\
                and Parent(w, a) pattern a(v, _\"energy - 1\"_)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "time,6", "jobs,6",
        "relax,6"), stringSet);
}
