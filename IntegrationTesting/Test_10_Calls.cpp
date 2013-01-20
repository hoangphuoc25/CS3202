#include <list>
#include <set>
#include <string>
#include "Test_10_Calls.h"
#include "SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::list;
using std::set;
using std::string;

void Test_10_Calls::setUp()
{
    // call stmt
    // Procedure xProc
    // 4 [yProc], 7 [godoSmth]
    // Procedure yProc
    // 10 [aaaaa]
    // Procedure godoSmth
    // 11 [cleanUp], 13 [X], 14 [XProc]
    // Procedure aaaaa
    // N/A
    // Procedure cleanUp
    // N/A
    // Procedure X
    // 18 [cleanUp]
    SELECT_ONE_SIMPLEPROG =
        "procedure XProc { \
           a = b; \
           x = z2d; \
           ba = ba + black + sheep; \
           call yProc; \
           while i { \
             black = gold; \
             call godoSmth; \
           } \
           hell = yea; \
         } \
         procedure yProc { \
           no = time; \
           call aaaaa; \
         } \
         procedure godoSmth { \
           call cleanUp; \
           well = done; \
           call X; \
           call XProc; \
         } \
         procedure aaaaa { \
           aa = abb; \
         } \
         procedure cleanUp { \
           job = done; \
         } \
         procedure X { \
           x = y; \
           call cleanUp; \
         }";

    // call stmt
    // Procedure xProc
    // 4 [yProc], 7 [godoSmth]
    // Procedure yProc
    // 10 [aaaaa]
    // Procedure godoSmth
    // 11 [cleanUp], 13 [X], 14 [XProc]
    // Procedure aaaaa
    // N/A
    // Procedure cleanUp
    // N/A
    // Procedure X
    // 18 [cleanUp]
}

void Test_10_Calls::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test_10_Calls);

void Test_10_Calls::test_select_one_syn()
{
    const string simpleProg = this->SELECT_ONE_SIMPLEPROG;
    string queryStr;
    QueryEvaluator evaluator;
    // evaluator.parseSimple(simpleProg);
}