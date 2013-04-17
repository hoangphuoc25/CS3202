#include <list>
#include <set>
#include <string>
#include "Test21_Uses_N2S.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

void Test21_Uses_N2S::setUp() {}

void Test21_Uses_N2S::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test21_Uses_N2S);

void Test21_Uses_N2S::test_uses_string_string()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure bendDown { \
           a = 7; \
           b = black + sheep; \
           if uOne then { \
             xmen = 73; \
           } else { \
             while uTwo { \
               if uThree then { \
                 some = one * sheep; \
               } else { \
                 no = 157 - 34; \
               } \
               four = seven; \
             } \
             hero = sven; \
           } \
           call antRace; \
           seven = heaven; \
         } \
         procedure antRace { \
           mew = two; \
           ant = 123 + 46 + sugar; \
         }";
    evaluator.parseSimple(simpleProg);
    // Variables that are actually used by a given procedure
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"black\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"sheep\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"uOne\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"uTwo\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"uThree\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"one\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"seven\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"sven\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"heaven\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"two\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"sugar\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"antRace\", \"two\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"antRace\", \"sugar\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // Variables not used
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"a\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"b\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"xmen\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"some\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"no\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"four\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"hero\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"mew\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"bendDown\", \"ant\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"antRace\", \"mew\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"antRace\", \"ant\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    // Variables used but not by that procedure
    queryStr = "Select BOOLEAN such that Uses(\"antRace\", \"sheep\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"antRace\", \"seven\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
}

void Test21_Uses_N2S::test_uses_string_wild()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure fireWall { \
           a = 123; \
           b = 45 * 47 - 62; \
         } \
         procedure normProc { \
           a = b; \
           if high then { \
             rest = 10; \
           } else { \
             well = done; \
           } \
         } \
         procedure ifUses { \
           a = 72; \
           if someVar then { \
             b = 41; \
           } else { \
             c = 82; \
           } \
         } \
         procedure whileUses { \
           while smth { \
             great = 116 - 132; \
           } \
           bayArea = 14642; \
         } \
         procedure callUses { \
           call normProc; \
         } \
         procedure callCallUses { \
           call callUses; \
         } \
         procedure callNoUses { \
           call fireWall; \
         } \
         procedure callCallNoUses { \
           call callNoUses; \
         }";
    evaluator.parseSimple(simpleProg);
    // procedure that doesnt use any variable
    queryStr = "Select BOOLEAN such that Uses(\"fireWall\", _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    // procedure with assignment and if
    queryStr = "Select BOOLEAN such that Uses(\"normProc\", _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // procedure with if; assignments use no variables
    queryStr = "Select BOOLEAN such that Uses(\"ifUses\", _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // procedure with while; assignments use no variables
    queryStr = "Select BOOLEAN such that Uses(\"whileUses\", _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // procedure with single call stmt; target fn uses variables
    queryStr = "Select BOOLEAN such that Uses(\"callUses\", _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // procedure with call -> call -> proc that uses variables
    queryStr = "Select BOOLEAN such that Uses(\"callCallUses\", _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // procedure with one call stmt; target fn uses nothing
    queryStr = "Select BOOLEAN such that Uses(\"callNoUses\", _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    // procedure with call -> call -> proc that does not use any var
    queryStr = "Select BOOLEAN such that Uses(\"callCallNoUses\", _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    // Non-existent procedures
    queryStr = "Select BOOLEAN such that Uses(\"notExistProc\", _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(\"doNth\", _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
}

void Test21_Uses_N2S::test_uses_int_string()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure firstProc { \
           if true then { \
             a = b; \
           } else { \
             c = 127; \
           } \
           while notTrue { \
             d = 73; \
           } \
           f = g; \
           call someFn; \
           damn = 0; \
           call anotherFn; \
           noUse = 1566; \
           call fnTwo; \
           call fnThree; \
           haha = great; \
           call indirNever; \
         } \
         procedure someFn { \
           a = 123; \
         } \
         procedure anotherFn { \
           damn = good; \
         } \
         procedure fnTwo { \
           if hell then { \
             a = 123; \
           } else { \
             dee = free; \
           } \
         } \
         procedure fnThree { \
           call someFn; \
         } \
         procedure indirNever { \
           call fnThree; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = "Select BOOLEAN such that Uses(1, \"b\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // negative case
    queryStr = "Select BOOLEAN such that Uses(1, \"c\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(2, \"b\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // line 3 "c = 127;" doesnt use anything
    queryStr = "Select BOOLEAN such that Uses(3, \"b\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(4, \"notTrue\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // line 5 "d = 73;" doesnt use anything
    queryStr = "Select BOOLEAN such that Uses(5, \"b\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(6, \"g\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // line 7 "call someFn;" doesnt use anything
    queryStr = "Select BOOLEAN such that Uses(7, \"b\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    // line 8 "damn = 0;" doesnt use anything
    queryStr = "Select BOOLEAN such that Uses(8, \"b\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(9, \"good\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // line 10 "noUse = 1566;" doesnt use anything
    queryStr = "Select BOOLEAN such that Uses(10, \"b\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(11, \"hell\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(11, \"free\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // line 12 "call fnThree;" doesnt use anything
    queryStr = "Select BOOLEAN such that Uses(12, \"b\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(13, \"great\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // line 14 "call indirNever;" doesnt use anything
    queryStr = "Select BOOLEAN such that Uses(14, \"b\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    // line 15 "a = 123;" doesnt use anything
    queryStr = "Select BOOLEAN such that Uses(15, \"b\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(16, \"good\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(17, \"hell\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(17, \"free\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // line 18 "a = 123;" doesnt use anything
    queryStr = "Select BOOLEAN such that Uses(18, \"b\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(19, \"free\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // line 20 "call someFn;" doesnt use anything
    queryStr = "Select BOOLEAN such that Uses(20, \"b\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    // line 21 "call fnThree;" doesnt use anything
    queryStr = "Select BOOLEAN such that Uses(21, \"b\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);

    // Out of range statements
    queryStr = "Select BOOLEAN such that Uses(0, \"b\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(-1, \"b\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(-236, \"b\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(22, \"b\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(23, \"b\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(236247, \"b\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
}

void Test21_Uses_N2S::test_uses_int_wild()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure firstProc { \
           if true then { \
             a = b; \
           } else { \
             c = 127; \
           } \
           while notTrue { \
             d = 73; \
           } \
           f = g; \
           call someFn; \
           damn = 0; \
           call anotherFn; \
           noUse = 1566; \
           call fnTwo; \
           call fnThree; \
           haha = great; \
           call indirNever; \
         } \
         procedure someFn { \
           a = 123; \
         } \
         procedure anotherFn { \
           damn = good; \
         } \
         procedure fnTwo { \
           if hell then { \
             a = 123; \
           } else { \
             dee = free; \
           } \
         } \
         procedure fnThree { \
           call someFn; \
         } \
         procedure indirNever { \
           call fnThree; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = "Select BOOLEAN such that Uses(1, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(2, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // line 3 "c = 127;" doesnt use anything
    queryStr = "Select BOOLEAN such that Uses(3, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(4, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // line 5 "d = 73;" doesnt use anything
    queryStr = "Select BOOLEAN such that Uses(5, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(6, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // line 7 "call someFn;" doesnt use anything
    queryStr = "Select BOOLEAN such that Uses(7, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    // line 8 "damn = 0;" doesnt use anything
    queryStr = "Select BOOLEAN such that Uses(8, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(9, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // line 10 "noUse = 1566;" doesnt use anything
    queryStr = "Select BOOLEAN such that Uses(10, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(11, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(11, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // line 12 "call fnThree;" doesnt use anything
    queryStr = "Select BOOLEAN such that Uses(12, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(13, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // line 14 "call indirNever;" doesnt use anything
    queryStr = "Select BOOLEAN such that Uses(14, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    // line 15 "a = 123;" doesnt use anything
    queryStr = "Select BOOLEAN such that Uses(15, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(16, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(17, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(17, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // line 18 "a = 123;" doesnt use anything
    queryStr = "Select BOOLEAN such that Uses(18, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(19, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::TRUE_STR.c_str()),
            stringSet);
    // line 20 "call someFn;" doesnt use anything
    queryStr = "Select BOOLEAN such that Uses(20, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    // line 21 "call fnThree;" doesnt use anything
    queryStr = "Select BOOLEAN such that Uses(21, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);

    // Out of range statements
    queryStr = "Select BOOLEAN such that Uses(0, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(-1, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(-236, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(22, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(23, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(236247, _)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
}

void Test21_Uses_N2S::test_uses_wild_string()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure stringCopy { \
           a = 123; \
           if uOne then { \
             while uTwo { \
               bah = black; \
             } \
             help = me; \
           } else { \
             deus = ex; \
             b = a; \
           } \
           follow = me; \
         } \
         procedure memset { \
           idx = 0; \
           while idxLTLen { \
             mem = zeroed; \
             idx = idx + 1; \
           } \
           hoho = done; \
         }";
    evaluator.parseSimple(simpleProg);
    // variables that are being used
    queryStr = "Select BOOLEAN such that Uses(_, \"a\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(_, \"black\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(_, \"done\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(_, \"ex\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(_, \"idx\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(_, \"idxLTLen\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(_, \"me\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(_, \"uOne\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(_, \"uTwo\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(_, \"zeroed\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);

    // variables in program but not used
    queryStr = "Select BOOLEAN such that Uses(_, \"b\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(_, \"bah\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(_, \"deus\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(_, \"follow\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(_, \"help\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(_, \"hoho\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(_, \"mem\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);

    // Variables totally not in the program
    queryStr = "Select BOOLEAN such that Uses(_, \"tough\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(_, \"enough\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    queryStr = "Select BOOLEAN such that Uses(_, \"cppUnit\")";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
}

void Test21_Uses_N2S::test_uses_wild_wild()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;
    queryStr = "Select BOOLEAN such that Uses(_,_)";

    // SIMPLE program with an assignment
    simpleProg =
        "procedure exitProc { \
           ret = zero; \
         }";
    evaluator.parseSimple(simpleProg);
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    // SIMPLE program with an if statement
    simpleProg =
        "procedure getLength { \
           five = 15; \
         } \
         procedure sizeOf { \
           size = 0; \
         } \
         procedure fooBar { \
           if truth then { \
             vone = 2; \
           } else { \
             vtwo = 16 * 170 - 86; \
           } \
         }";
    evaluator.parseSimple(simpleProg);
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    // SIMPLE program with a while statement
    simpleProg =
        "procedure deer { \
           five = 15; \
         } \
         procedure doe { \
           size = 0; \
         } \
         procedure mZI { \
           while false { \
             a = 1; \
           } \
         }";
    evaluator.parseSimple(simpleProg);
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    // SIMPLE program that uses no variables
    simpleProg =
        "procedure famine { \
           famine = 0; \
         } \
         procedure pestilence { \
           pestilence = 17; \
         } \
         procedure War { \
           war = 100; \
           War = 783 * 47; \
           compute = 6737; \
         } \
         procedure Death { \
           Death = 200; \
           death = 2674757; \
         }";
    evaluator.parseSimple(simpleProg);
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
    // SIMPLE program with an assignment (just to make sure it works)
    simpleProg =
        "procedure exitProc { \
           ret = zero; \
         }";
    evaluator.parseSimple(simpleProg);
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,
                                 ResultsProjector::FALSE_STR.c_str()),
            stringSet);
}

void Test21_Uses_N2S::test_uses_X_syn()
{
    string queryStr, simpleProg;
    QueryEvaluator evaluator;
    SetWrapper<string> stringSet;
    list<string> resultList;

    simpleProg =
        "procedure yayProc { \
           avar = c; \
           x = y; \
           if useIf then { \
             wow = x; \
             this = is + cool; \
           } else { \
             darn = it; \
           } \
           oh = crap; \
           while useWhile { \
             mm = mm; \
             thats = true; \
           } \
           haha = go; \
           hmm = 5; \
           call calledProc; \
         } \
         procedure secProc { \
           darn = it - useWhile; \
           it = is + true; \
           useIf = 73; \
         } \
         procedure calledProc { \
           abba = daba; \
           yabba = daba + doo; \
         }";
    evaluator.parseSimple(simpleProg);
    // Uses(string,syn) 0
    queryStr = "variable v; Select v such that Uses(\"secProc\", v)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "is", "it", "true",
            "useWhile"),
            stringSet);
    // Uses(string,syn) 1
    queryStr = " while w; variable v; ";
    queryStr += " Select v such that Uses(w,v) and ";
    queryStr += " Uses(\"secProc\", v)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "true", "useWhile"),
            stringSet);
    // Uses(int,syn) 0
    queryStr = " variable v; Select v such that Uses(13, v)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "daba", "doo"),
            stringSet);
    // Uses(int,syn) 1
    queryStr = " while w; variable v; ";
    queryStr += " Select v such that Modifies(w,v) and Uses(9,v)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "mm"),
            stringSet);
    // Uses(_,syn) 0
    queryStr = " variable v; Select v such that Uses(_,v)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
    // Uses(_,syn) 1
    queryStr = " if if1; variable v; ";
    queryStr += " Select v such that Uses(if1,v) and Uses(_,v)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(),
            stringSet);
}