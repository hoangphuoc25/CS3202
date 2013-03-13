#include <list>
#include <set>
#include <string>

#include "Test10_00_ParentStar.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

void Test10_00_ParentStar::setUp()
{
    this->TEST_PROG =
        "procedure pOne { \
           a = b;\
           while good { \
             damn = it; \
             if hell then { \
               try = x; \
               follow = star; \
               if gg then { \
                 get = lost; \
                 while p { \
                   call QQ; \
                   q = xp; \
                 } \
                 dang = it; \
               } else { \
                 fun = times; \
                 while aa { \
                   stuff = lost; \
                 } \
               } \
               lol = lol; \
             } else { \
               if true then { \
                 dont = go; \
               } else { \
                 while go { \
                   call prq; \
                   forecast = cloudy; \
                 } \
               } \
             } \
             low = blow; \
           } \
           blast = off; \
         } \
         procedure QQ { \
           while par { \
             find = stuff; \
             great = food; \
             if pal then { \
               drive = by; \
             } else { \
               owe = money; \
             } \
           } \
         } \
         procedure prq { \
           last = assign; \
         } \
         procedure whileNoAssign { \
           while x { \
             if ab then { \
               a = a; \
             } else { \
               b = b; \
             } \
           } \
         } \
         procedure ifNoAssign { \
           if i then { \
             while g { \
               f = f; \
             } \
             call whileNoAssign; \
           } else { \
             while f { \
               g = g; \
             } \
           } \
         }";
}

void Test10_00_ParentStar::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test10_00_ParentStar);

void Test10_00_ParentStar::test_parentstar_while_assign()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->TEST_PROG;
    evaluator.parseSimple(simpleProg);

    // ParentStar(while,assign)
    queryStr = " while ww; assign aa; Select ww such that ";
    queryStr += "Parent*(ww, aa)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(8,
            "2", "9", "14", "19", "24", "31", "36", "39"),
            stringSet);
}

void Test10_00_ParentStar::test_parentstar_while_prog_line()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->TEST_PROG;
    evaluator.parseSimple(simpleProg);

    // ParentStar(while,prog_line)
    queryStr = " while ww; stmt ss; Select ww such that ";
    queryStr += "Parent*(ww, ss)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(8,
            "2", "9", "14", "19", "24", "31", "36", "39"),
            stringSet);
}

void Test10_00_ParentStar::test_parentstar_while_call()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->TEST_PROG;
    evaluator.parseSimple(simpleProg);

    // ParentStar(while,call)
    queryStr = " while ww; call cc; Select ww such that ";
    queryStr += "Parent*(ww, cc)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "2", "9", "19"),
             stringSet);
}

void Test10_00_ParentStar::test_parentstar_while_if()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->TEST_PROG;
    evaluator.parseSimple(simpleProg);

    // ParentStar(while,if)
    queryStr = " while ww; if if; Select ww such that ";
    queryStr += "Parent*(ww, if)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "2", "24", "31"),
             stringSet);
}

void Test10_00_ParentStar::test_parentstar_while_while()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->TEST_PROG;
    evaluator.parseSimple(simpleProg);

    // ParentStar(while,while)
    queryStr = " while ww; while www; Select ww such that ";
    queryStr += "Parent*(ww, www)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "2"),
             stringSet);
}

void Test10_00_ParentStar::test_parentstar_if_while()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->TEST_PROG;
    evaluator.parseSimple(simpleProg);

    // ParentStar(if,while)
    queryStr = " if if; while ww; Select if such that ";
    queryStr += "Parent*(if, ww)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "4", "7", "17", "35"),
             stringSet);
}

void Test10_00_ParentStar::test_parentstar_if_assign()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->TEST_PROG;
    evaluator.parseSimple(simpleProg);

    // ParentStar(if,assign)
    queryStr = " if if; assign aa; Select if such that ";
    queryStr += "Parent*(if, aa)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6,
             "4", "7", "17", "27", "32", "35"),
             stringSet);
}

void Test10_00_ParentStar::test_parentstar_if_prog_line()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->TEST_PROG;
    evaluator.parseSimple(simpleProg);

    // ParentStar(if,prog_line)
    queryStr = " if if; prog_line pl; Select if such that ";
    queryStr += "Parent*(if, pl)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6,
             "4", "7", "17", "27", "32", "35"),
             stringSet);
}

void Test10_00_ParentStar::test_parentstar_if_call()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->TEST_PROG;
    evaluator.parseSimple(simpleProg);

    // ParentStar(if,call)
    queryStr = " if if; call cc; Select if such that ";
    queryStr += "Parent*(if, cc)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "4", "7", "17", "35"),
             stringSet);
}

void Test10_00_ParentStar::test_parentstar_if_if()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->TEST_PROG;
    evaluator.parseSimple(simpleProg);

    // ParentStar(if,if)
    queryStr = " if if; if if2; Select if such that ";
    queryStr += "Parent*(if, if2)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "4"),
             stringSet);
}

void Test10_00_ParentStar::test_parentstar_prog_line_assign()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->TEST_PROG;
    evaluator.parseSimple(simpleProg);

    // ParentStar(prog_line,assign)
    queryStr = "prog_line pl; assign aa; Select pl such that ";
    queryStr += "Parent*(pl, aa)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(14, "2", "4", "7", "9",
            "14", "17", "19", "24", "27", "31", "32", "35", "36",
            "39"),
             stringSet);
}

void Test10_00_ParentStar::test_parentstar_prog_line_prog_line()
{
    string  queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->TEST_PROG;
    evaluator.parseSimple(simpleProg);

    // ParentStar(prog_line,prog_line)
    queryStr = "prog_line pl; prog_line pl2; Select pl such that ";
    queryStr += "Parent*(pl, pl2)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(14, "2", "4", "7", "9",
            "14", "17", "19", "24", "27", "31", "32", "35", "36",
            "39"),
             stringSet);
}

void Test10_00_ParentStar::test_parentstar_prog_line_call()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->TEST_PROG;
    evaluator.parseSimple(simpleProg);

    // ParentStar(prog_line,call)
    queryStr = "prog_line pl; call cc; Select pl such that ";
    queryStr += "Parent*(pl, cc)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "2", "4", "7", "9",
            "17", "19", "35"),
             stringSet);
}

void Test10_00_ParentStar::test_parentstar_prog_line_if()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->TEST_PROG;
    evaluator.parseSimple(simpleProg);

    // ParentStar(prog_line,if)
    queryStr = "prog_line pl; if if; Select pl such that ";
    queryStr += "Parent*(pl, if)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "2", "4", "24", "31"),
             stringSet);
}

void Test10_00_ParentStar::test_parentstar_prog_line_while()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    const string& simpleProg = this->TEST_PROG;
    evaluator.parseSimple(simpleProg);

    // ParentStar(prog_line,while)
    queryStr = "prog_line pl; while ww; Select pl such that ";
    queryStr += "Parent*(pl, ww)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "2", "4", "7", "17",
            "35"),
             stringSet);
}