#include <list>
#include <set>
#include <string>
#include "Test10_01_Uses.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

void Test10_01_Uses::setUp() {}

void Test10_01_Uses::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test10_01_Uses);

void Test10_01_Uses::test_uses_assign_var()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    string simpleProg =
        "procedure Fone { \
           xyz = 123; \
           axe = hero; \
           if true then { \
             hail = axe; \
           } else { \
             gangnam = style; \
           } \
           mr = bombastic; \
           hair = style; \
           while peace { \
             true = not; \
             if manny then { \
               jquery = rocks; \
             } else { \
               no = time; \
             } \
             tornado = server - 5; \
           } \
           style = this; \
           call forkBomb; \
           all = done; \
         } \
         procedure forkBomb { \
           time = bomb; \
           since = when; \
           got = axe; \
           manny = pacquiao; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = " assign a1, a2; variable v1; ";
    queryStr += " Select <a1,v1,a2> such that ";
    queryStr += " Modifies(a1,v1) and Uses(a2,v1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Modifies(a1,v1)
    // a1 | v1
    // (1,xyz), (2,axe), (4,hail), (5,gangnam), (6,mr), (7,hair)
    // (9,true), (11,jquery), (12,no), (13,tornado), (14,style),
    // (16,all), (17,time), (18,since), (19,got), (20,manny)
    // ---
    // Uses(a2,v1)
    // a1 | a2 | v1
    // (2,axe,4), (2,axe,19), (14,style,5), (14,style,7), (17,time,12)
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "2,axe,4", "2,axe,19",
            "14,style,5", "14,style,7", "17,time,12"),
            stringSet);
}

void Test10_01_Uses::test_uses_procedure_var()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;
    string simpleProg =
        "procedure Fone { \
           xyz = 123; \
           axe = hero; \
           if true then { \
             hail = axe; \
           } else { \
             gangnam = style; \
           } \
           mr = bombastic; \
           hair = style; \
           while peace { \
             true = not; \
             if manny then { \
               jquery = rocks; \
             } else { \
               no = time; \
             } \
             tornado = server - 5; \
           } \
           style = this; \
           call forkBomb; \
           all = done; \
         } \
         procedure forkBomb { \
           time = bomb; \
           since = when; \
           got = axe; \
           manny = pacquiao; \
           not = true; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = " assign a1; procedure procOne; variable v1; ";
    queryStr += " Select <a1,v1,procOne> such that ";
    queryStr += " Modifies(a1,v1) and Uses(procOne,v1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Modifies(a1,v1)
    // a1 | v1
    // (1,xyz), (2,axe), (4,hail), (5,gangnam), (6,mr), (7,hair)
    // (9,true), (11,jquery), (12,no), (13,tornado), (14,style),
    // (16,all), (17,time), (18,since), (19,got), (20,manny),
    // (21,not)
    // ---
    // Uses(a2,v1)
    // a1 | a2 | v1
    // (2,axe,Fone), (2,axe,forkBomb), (9,true,Fone)
    // (9,true,forkBomb), (14,style,Fone)
    // (17,time,Fone), (20,many,Fone), (21,not,Fone)
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(8, "2,axe,Fone",
            "2,axe,forkBomb", "9,true,Fone", "9,true,forkBomb",
            "14,style,Fone", "17,time,Fone", "20,manny,Fone",
            "21,not,Fone"),
            stringSet);
}