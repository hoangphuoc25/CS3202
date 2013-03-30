#include <memory>
#include <set>
#include <string>
#include "Test_30_PKB_has_X.h"
#include "../SPA/Parser.h"
#include "../SPA/PKB.h"
#include "../SPA/PQL.h"

using std::auto_ptr;
using std::set;
using std::string;

void Test_30_PKB_has_X::setUp() {}

void Test_30_PKB_has_X::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test_30_PKB_has_X);


void Test_30_PKB_has_X::test_has_call_procName()
{
    string simpleProg;
    simpleProg =
        "procedure A { \
           call B; \
           call C; \
         } \
         procedure B { \
           call F; \
         } \
         procedure C { \
           a = b; \
         } \
         procedure F { \
           x = y; \
         } \
         procedure G { \
           call H; \
           call C; \
         } \
         procedure H { \
           lo = behold; \
         } \
         procedure alone { \
           is = alone; \
         }";
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_any_call());
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_call_procName("B"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_call_procName("C"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_call_procName("F"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_call_procName("H"));
    // procedures in SIMPLE program but no one calls
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call_procName("A"));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call_procName("G"));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call_procName("alone"));
    // non existent procedures
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call_procName("sgg"));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call_procName("nonexistent"));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call_procName("huge"));
}