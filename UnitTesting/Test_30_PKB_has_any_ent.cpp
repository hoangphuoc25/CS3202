#include <memory>
#include <set>
#include <string>
#include "Test_30_PKB_has_any_ent.h"
#include "../SPA/Parser.h"
#include "../SPA/PKB.h"
#include "../SPA/PQL.h"

using std::auto_ptr;
using std::set;
using std::string;

void Test_30_PKB_has_any_ent::setUp() {}

void Test_30_PKB_has_any_ent::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test_30_PKB_has_any_ent);

void Test_30_PKB_has_any_ent::test_has_any_ent()
{
    PKB *pkbPtr;
    string queryStr, simpleProg;
    simpleProg =
        "procedure abc { \
           call xyz; \
         } \
         procedure xyz { \
           call F; \
         } \
         procedure F { \
           keyboard = typist; \
         }";
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    // no if, no while, no const
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_any_ent(ENT_ASSIGN));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_any_ent(ENT_CALL));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_any_ent(ENT_IF));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_any_ent(ENT_WHILE));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_any_ent(ENT_STMT));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_any_ent(ENT_PROGLINE));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_any_ent(ENT_PROC));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_any_ent(ENT_VAR));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_any_ent(ENT_CONST));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_any_ent(ENT_STMTLST));
    pkbPtr = pkb.release();
    delete pkbPtr;
    pkbPtr = NULL;

    // no call
    simpleProg =
        "procedure abc { \
           if myFriend then { \
             you = good; \
           } else { \
             you = bad; \
           } \
         } \
         procedure xyz { \
           while fun { \
             k = k + 62; \
           } \
         } \
         procedure F { \
           keyboard = typist; \
         }";
    parser = Parser(simpleProg, FROMSTRING);
    parser.init();
    pkb = auto_ptr<PKB>(parser.get_pkb());
    // no if, no while, no const
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_any_ent(ENT_ASSIGN));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_any_ent(ENT_CALL));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_any_ent(ENT_IF));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_any_ent(ENT_WHILE));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_any_ent(ENT_STMT));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_any_ent(ENT_PROGLINE));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_any_ent(ENT_PROC));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_any_ent(ENT_VAR));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_any_ent(ENT_CONST));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_any_ent(ENT_STMTLST));
}