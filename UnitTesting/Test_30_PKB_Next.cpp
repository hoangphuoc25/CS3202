#include <cstdarg>
#include <string>
#include <map>
#include <memory>
#include "Test_30_PKB_Next.h"
#include "../SPA/Parser.h"
#include "../SPA/PKB.h"
#include "../SPA/SetWrapper.h"

using std::auto_ptr;
using std::string;
using std::map;

void Test_30_PKB_Next::setUp(){}
void Test_30_PKB_Next::tearDown(){}
CPPUNIT_TEST_SUITE_REGISTRATION(Test_30_PKB_Next);

void Test_30_PKB_Next::test_next()
{
        const string& simpleProg =
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
                        call lala; }}\
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
                e = (x+y)+1;\
            }";

    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());

    //CPPUNIT_ASSERT_EQUAL(true,pkb->next_query_int_X_int_Y
        //(ENT_WHILE,13,ENT_ASSIGN,14));
    CPPUNIT_ASSERT_EQUAL(false,pkb->next_query_int_X_int_Y
        (ENT_ASSIGN,14,ENT_ASSIGN,18));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->next_query_int_X_int_Y(ENT_STMT, 14, ENT_STMT, 13));
    CPPUNIT_ASSERT_EQUAL(true,pkb->nextStar_query_int_X_int_Y
        (ENT_ASSIGN,14,ENT_ASSIGN,18));
    CPPUNIT_ASSERT_EQUAL(true,pkb->nextStar_query_int_X_int_Y
        (ENT_IF,3,ENT_WHILE,2));
    CPPUNIT_ASSERT_EQUAL(true,pkb->nextStar_query_int_X_int_Y
        (ENT_CALL,4,ENT_ASSIGN,8));
    //pkb->is_next(13,14);
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->next_query_int_X_int_Y(ENT_STMT, 13, ENT_STMT, 14));
    CPPUNIT_ASSERT_EQUAL(false,
            pkb->nextStar_query_int_X_int_Y(ENT_STMT, 10, ENT_STMT, 20));
    CPPUNIT_ASSERT_EQUAL(false,pkb->nextStar_query_int_X_int_Y(ENT_WHILE,10,
    ENT_ASSIGN,20));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_valid_stmtNo(14));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->nextStar_query_int_X_int_Y(ENT_STMT, 2, ENT_STMT, 2));
    stringSet = pkb->nextStar_X_Y_get_int_X_from_int_Y(ENT_STMT,
            ENT_STMT, 2);
   // CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "14","18"),stringSet);


}