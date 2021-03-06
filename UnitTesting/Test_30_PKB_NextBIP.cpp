#include <cstdarg>
#include <string>
#include <map>
#include <memory>
#include "Test_30_PKB_NextBIP.h"
#include "../SPA/Parser.h"
#include "../SPA/PKB.h"
#include "../SPA/SetWrapper.h"

using std::auto_ptr;
using std::string;
using std::map;

void Test_30_PKB_NextBIP::setUp(){}
void Test_30_PKB_NextBIP::tearDown(){}
CPPUNIT_TEST_SUITE_REGISTRATION(Test_30_PKB_NextBIP);

void Test_30_PKB_NextBIP::test_nextBIP()
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

    // Cross procedure out
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(4,20));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(7,20));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(9,20));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(11,20));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(14,20));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(17,20));

    CPPUNIT_ASSERT_EQUAL(true,pkb->nextBip_query_int_X_int_Y
        (ENT_STMT,4,ENT_STMT,20));
    CPPUNIT_ASSERT_EQUAL(true,pkb->nextBip_query_int_X_int_Y
        (ENT_STMT,7,ENT_STMT,20));
    CPPUNIT_ASSERT_EQUAL(true,pkb->nextBip_query_int_X_int_Y
        (ENT_STMT,9,ENT_STMT,20));
    CPPUNIT_ASSERT_EQUAL(true,pkb->nextBip_query_int_X_int_Y
        (ENT_STMT,11,ENT_STMT,20));
    CPPUNIT_ASSERT_EQUAL(true,pkb->nextBip_query_int_X_int_Y
        (ENT_STMT,14,ENT_STMT,20));
    CPPUNIT_ASSERT_EQUAL(true,pkb->nextBip_query_int_X_int_Y
        (ENT_STMT,17,ENT_STMT,20));

    /*
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next(4,20));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next(7,20));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next(9,20));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next(11,20));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next(14,20));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next(17,20));
    */
    // Cross procedure in
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(21,9));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(21,10));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(21,13));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(21,18));

    CPPUNIT_ASSERT_EQUAL(true,pkb->nextBip_query_int_X_int_Y
        (ENT_STMT,21,ENT_STMT,9));
    CPPUNIT_ASSERT_EQUAL(true,pkb->nextBip_query_int_X_int_Y
        (ENT_STMT,21,ENT_STMT,10));
    CPPUNIT_ASSERT_EQUAL(true,pkb->nextBip_query_int_X_int_Y
        (ENT_STMT,21,ENT_STMT,13));
    CPPUNIT_ASSERT_EQUAL(true,pkb->nextBip_query_int_X_int_Y
        (ENT_STMT,21,ENT_STMT,18));

    /*
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next(21,9));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next(21,10));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next(21,13));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next(21,18));
    */

    // Same procedure
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(3,4));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(2,12));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(13,14));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(10,2));

    CPPUNIT_ASSERT_EQUAL(true,pkb->nextBip_query_int_X_int_Y
        (ENT_STMT,3,ENT_STMT,4));
    CPPUNIT_ASSERT_EQUAL(true,pkb->nextBip_query_int_X_int_Y
        (ENT_STMT,2,ENT_STMT,12));
    CPPUNIT_ASSERT_EQUAL(true,pkb->nextBip_query_int_X_int_Y
        (ENT_STMT,13,ENT_STMT,14));
    CPPUNIT_ASSERT_EQUAL(true,pkb->nextBip_query_int_X_int_Y
        (ENT_STMT,10,ENT_STMT,2));

    // Link should be broken after calls for BIP
    //CPPUNIT_ASSERT_EQUAL(true,pkb->is_next(14,13));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next_BIP(14,13));
    //CPPUNIT_ASSERT_EQUAL(true,pkb->is_next(4,6));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next_BIP(4,6));
    //CPPUNIT_ASSERT_EQUAL(true,pkb->is_next(7,9));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next_BIP(7,9));
    //CPPUNIT_ASSERT_EQUAL(true,pkb->is_next(9,10));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next_BIP(9,10));
    //CPPUNIT_ASSERT_EQUAL(true,pkb->is_next(11,10));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next_BIP(11,10));
    //CPPUNIT_ASSERT_EQUAL(true,pkb->is_next(17,18));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next_BIP(17,18));

    CPPUNIT_ASSERT_EQUAL(false,pkb->nextBip_query_int_X_int_Y
        (ENT_STMT,14,ENT_STMT,13));
    CPPUNIT_ASSERT_EQUAL(false,pkb->nextBip_query_int_X_int_Y
        (ENT_STMT,4,ENT_STMT,6));
    CPPUNIT_ASSERT_EQUAL(false,pkb->nextBip_query_int_X_int_Y
        (ENT_STMT,7,ENT_STMT,9));
    CPPUNIT_ASSERT_EQUAL(false,pkb->nextBip_query_int_X_int_Y
        (ENT_STMT,9,ENT_STMT,10));
    CPPUNIT_ASSERT_EQUAL(false,pkb->nextBip_query_int_X_int_Y
        (ENT_STMT,11,ENT_STMT,10));
    CPPUNIT_ASSERT_EQUAL(false,pkb->nextBip_query_int_X_int_Y
        (ENT_STMT,17,ENT_STMT,18));


    stringSet = pkb->get_before_BIP(20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>
        (6, "4","7","9","11","14","17"),stringSet);
    stringSet = pkb->get_before_BIP(6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2,"5","21"),stringSet);
    stringSet = pkb->get_before_BIP(9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2,"8","21"),stringSet);
    stringSet = pkb->get_before_BIP(10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"21"),stringSet);
    stringSet = pkb->get_before_BIP(13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2,"12","21"),stringSet);
    stringSet = pkb->get_before_BIP(18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3,"13","16","21"),stringSet);
    stringSet = pkb->get_before_BIP(20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>
        (6,"4","7","9","11","14","17"),stringSet);
    stringSet = pkb->get_before_BIP(8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"6"),stringSet);
    stringSet = pkb->get_before_BIP(16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"15"),stringSet);
    stringSet = pkb->get_before_BIP(12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"2"),stringSet);
    stringSet = pkb->get_before_BIP(21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"20"),stringSet);

    stringSet = pkb->nextBip_X_Y_get_int_X_from_int_Y(ENT_CALL,ENT_STMT,20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>
        (6,"4","7","9","11","14","17"),stringSet);
    stringSet = pkb->nextBip_X_Y_get_int_X_from_int_Y(ENT_ASSIGN,ENT_STMT,20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>
        (0),stringSet);
    CPPUNIT_ASSERT_EQUAL(true,pkb->nextBip_X_Y_smth_int_Y(ENT_STMT,20));

    // get after
    stringSet = pkb->get_after_BIP(21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>
        (5, "6","9","10","13","18"),stringSet);
    stringSet = pkb->get_after_BIP(4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"20"),stringSet);
    stringSet = pkb->get_after_BIP(7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"20"),stringSet);
    stringSet = pkb->get_after_BIP(9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"20"),stringSet);
    stringSet = pkb->get_after_BIP(11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"20"),stringSet);
    stringSet = pkb->get_after_BIP(14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"20"),stringSet);
    stringSet = pkb->get_after_BIP(17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"20"),stringSet);
    stringSet = pkb->get_after_BIP(16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"18"),stringSet);
    stringSet = pkb->get_after_BIP(12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2,"13","15"),stringSet);
    stringSet = pkb->get_after_BIP(6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2,"7","8"),stringSet);

    stringSet = pkb->nextBip_X_Y_get_int_Y_from_int_X(ENT_STMT,ENT_STMT,12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2,"13","15"),stringSet);
    stringSet = pkb->nextBip_X_Y_get_int_Y_from_int_X(ENT_STMT,ENT_WHILE,12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"13"),stringSet);
    stringSet = pkb->nextBip_X_Y_get_int_Y_from_int_X(ENT_STMT,ENT_IF,12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"15"),stringSet);
    CPPUNIT_ASSERT_EQUAL(true,pkb->nextBip_X_Y_int_X_smth(ENT_ASSIGN,12));

}

void Test_30_PKB_NextBIP::test_nextBIP2()
{
        const string& simpleProg =
            "procedure nextBIP {\
                while one {\
                    call two;\
                }\
            }\
            procedure two {\
                call three;\
            }\
            procedure three {\
                four = 1;\
            }";
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());

    stringSet = pkb->get_before_BIP(1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"4"),stringSet);
    stringSet = pkb->get_before_BIP(2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"1"),stringSet);
    stringSet = pkb->get_before_BIP(3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"2"),stringSet);
    stringSet = pkb->get_before_BIP(4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"3"),stringSet);

    stringSet = pkb->get_after_BIP(1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"2"),stringSet);
    stringSet = pkb->get_after_BIP(2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"3"),stringSet);
    stringSet = pkb->get_after_BIP(3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"4"),stringSet);
    stringSet = pkb->get_after_BIP(4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"1"),stringSet);

    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(4,1));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(1,2));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(2,3));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(3,4));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next_BIP(3,1));

}

void Test_30_PKB_NextBIP::test_nextBIP_if()
{
        const string& simpleProg =
            "procedure manyif {\
                if i1 then {\
                    if i2 then {\
                        call three;\
                    } else {\
                        call four;\
                    }\
                } else {\
                    if i5 then {\
                        call six;\
                    } else {\
                        call seven;\
                    }\
                }\
            }\
            procedure three {\
                a = b8;\
            }\
            procedure four{\
                b = c9;\
            }\
            procedure six{\
                c = d10;\
            }\
            procedure seven{\
                e = f11;\
            }\
            procedure first{\
                call manyif;\
                allback = t13;\
            }";

    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());

    
    stringSet = pkb->get_before_BIP(1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"12"),stringSet);
    stringSet = pkb->get_before_BIP(2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"1"),stringSet);
    stringSet = pkb->get_before_BIP(3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"2"),stringSet);
    stringSet = pkb->get_before_BIP(4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"2"),stringSet);
    stringSet = pkb->get_before_BIP(5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"1"),stringSet);
    stringSet = pkb->get_before_BIP(6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"5"),stringSet);
    stringSet = pkb->get_before_BIP(7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"5"),stringSet);
    stringSet = pkb->get_before_BIP(8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"3"),stringSet);
    stringSet = pkb->get_before_BIP(9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"4"),stringSet);
    stringSet = pkb->get_before_BIP(10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"6"),stringSet);
    stringSet = pkb->get_before_BIP(11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"7"),stringSet);
    stringSet = pkb->get_before_BIP(12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),stringSet);
    stringSet = pkb->get_before_BIP(13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4,"8","9","10","11"),stringSet);

    stringSet = pkb->get_after_BIP(1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2,"2","5"),stringSet);
    stringSet = pkb->get_after_BIP(2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2,"3","4"),stringSet);
    stringSet = pkb->get_after_BIP(3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"8"),stringSet);
    stringSet = pkb->get_after_BIP(4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"9"),stringSet);
    stringSet = pkb->get_after_BIP(5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2,"6","7"),stringSet);
    stringSet = pkb->get_after_BIP(6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"10"),stringSet);
    stringSet = pkb->get_after_BIP(7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"11"),stringSet);
    stringSet = pkb->get_after_BIP(8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"13"),stringSet);
    stringSet = pkb->get_after_BIP(9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"13"),stringSet);
    stringSet = pkb->get_after_BIP(10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"13"),stringSet);
    stringSet = pkb->get_after_BIP(11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"13"),stringSet);
    stringSet = pkb->get_after_BIP(12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"1"),stringSet);
    stringSet = pkb->get_after_BIP(13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),stringSet);

    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(1,2));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(1,5));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(2,3));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(2,4));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(3,8));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(4,9));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(5,6));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(5,7));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(6,10));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(7,11));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(8,13));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(9,13));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(10,13));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(11,13));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(12,1));

}

void Test_30_PKB_NextBIP::test_nextBIP_while()
{
        const string& simpleProg =
            "procedure willy{\
                while one{\
                a = 2;\
                call two;\
                }\
            }\
            procedure two{\
                a = 4;\
            }\
            procedure first{\
                call willy;\
                b = 6;\
                if i7 then {\
                    call two;\
                } else {\
                   a = 9;\
                }\
                while i10 {\
                    d = 11;\
                }\
            }";


    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());

    stringSet = pkb->get_before_BIP(1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2,"4","5"),stringSet);
    stringSet = pkb->get_before_BIP(2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"1"),stringSet);
    stringSet = pkb->get_before_BIP(3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"2"),stringSet);
    stringSet = pkb->get_before_BIP(4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2,"3","8"),stringSet);
    stringSet = pkb->get_before_BIP(5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),stringSet);
    stringSet = pkb->get_before_BIP(6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"1"),stringSet);
    stringSet = pkb->get_before_BIP(10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3,"4","9","11"),stringSet);

    stringSet = pkb->get_after_BIP(1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2,"2","6"),stringSet);
    stringSet = pkb->get_after_BIP(2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"3"),stringSet);
    stringSet = pkb->get_after_BIP(3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"4"),stringSet);
    stringSet = pkb->get_after_BIP(4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2,"1","10"),stringSet);
    stringSet = pkb->get_after_BIP(5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"1"),stringSet);
    stringSet = pkb->get_after_BIP(6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"7"),stringSet);

    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(1,2));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(1,6));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(2,3));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(3,4));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(4,1));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(5,1));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(4,10));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(9,10));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next_BIP(8,10));

}

void Test_30_PKB_NextBIP::test_nextBIP_multiproc()
{
        const string& simpleProg =
            "procedure first{\
                call multiproc;\
                a = 2;\
            }\
            procedure second{\
                call multiproc;\
                a = 4;\
            }\
            procedure third{\
                call multiproc;\
                a = 6;\
            }\
            procedure multiproc{\
                a = 7;\
                call last;\
            }\
            procedure last{\
               a = 9;\
            }";

    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());

    
    stringSet = pkb->get_before_BIP(1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),stringSet);
    stringSet = pkb->get_before_BIP(2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"9"),stringSet);
    stringSet = pkb->get_before_BIP(3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),stringSet);
    stringSet = pkb->get_before_BIP(4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"9"),stringSet);
    stringSet = pkb->get_before_BIP(5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),stringSet);
    stringSet = pkb->get_before_BIP(6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"9"),stringSet);
    stringSet = pkb->get_before_BIP(7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3,"1","3","5"),stringSet);
    stringSet = pkb->get_before_BIP(8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"7"),stringSet);
    stringSet = pkb->get_before_BIP(9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"8"),stringSet);

    stringSet = pkb->get_after_BIP(1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"7"),stringSet);
    stringSet = pkb->get_after_BIP(2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),stringSet);
    stringSet = pkb->get_after_BIP(3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"7"),stringSet);
    stringSet = pkb->get_after_BIP(4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),stringSet);
    stringSet = pkb->get_after_BIP(5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"7"),stringSet);
    stringSet = pkb->get_after_BIP(6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),stringSet);
    stringSet = pkb->get_after_BIP(7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"8"),stringSet);
    stringSet = pkb->get_after_BIP(8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"9"),stringSet);
    stringSet = pkb->get_after_BIP(9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3,"2","4","6"),stringSet);

    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(1,7));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(3,7));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(5,7));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(7,8));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(8,9));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(9,2));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(9,4));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_BIP(9,6));
}

void Test_30_PKB_NextBIP::test_nextBipStar()
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

    // NextBip Cross procedure out 
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(4,20));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(7,20));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(9,20));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(11,20));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(14,20));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(17,20));

    //  NextBip Cross procedure in
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(21,9));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(21,10));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(21,13));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(21,18));

    // NextBip Same procedure
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(3,4));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(2,12));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(13,14));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(10,2));
    
    //NextBip Star Cross procedure out 
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(1,21));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(6,21));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(10,20));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(15,20));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next_star_BIP(18,20));

    //  NextBip Cross procedure in
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(20,9));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(20,19));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(20,3));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next_star_BIP(20,1));

    // NextBip Same procedure
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(21,20));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(20,20));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(21,21));

    // get before
    stringSet = pkb->get_before_BIP(20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>
        (6, "4","7","9","11","14","17"),stringSet);
    stringSet = pkb->get_before_BIP(6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2,"5","21"),stringSet);
    stringSet = pkb->get_before_BIP(9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2,"8","21"),stringSet);
    stringSet = pkb->get_before_BIP(10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"21"),stringSet);
    stringSet = pkb->get_before_BIP(13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2,"12","21"),stringSet);
    stringSet = pkb->get_before_BIP(18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3,"13","16","21"),stringSet);
    stringSet = pkb->get_before_BIP(20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>
        (6,"4","7","9","11","14","17"),stringSet);
    stringSet = pkb->get_before_BIP(8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"6"),stringSet);
    stringSet = pkb->get_before_BIP(16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"15"),stringSet);
    stringSet = pkb->get_before_BIP(12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"2"),stringSet);
    stringSet = pkb->get_before_BIP(21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"20"),stringSet);

    // get after
    stringSet = pkb->get_after_BIP(21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>
        (5, "6","9","10","13","18"),stringSet);
    stringSet = pkb->get_after_BIP(4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"20"),stringSet);
    stringSet = pkb->get_after_BIP(7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"20"),stringSet);
    stringSet = pkb->get_after_BIP(9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"20"),stringSet);
    stringSet = pkb->get_after_BIP(11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"20"),stringSet);
    stringSet = pkb->get_after_BIP(14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"20"),stringSet);
    stringSet = pkb->get_after_BIP(17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"20"),stringSet);
    stringSet = pkb->get_after_BIP(16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"18"),stringSet);
    stringSet = pkb->get_after_BIP(12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2,"13","15"),stringSet);
    stringSet = pkb->get_after_BIP(6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2,"7","8"),stringSet);
}

void Test_30_PKB_NextBIP::test_nextBipStar_multiproc()
{
        const string& simpleProg =
            "procedure left {\
                a = 1;\
                b = 2;\
            }\
            procedure one {\
                call two;\
            }\
            procedure two{\
                d = 4;\
            }\
            procedure main{\
                while i5 {\
                    if i6 then {\
                        call left;\
                    } else {\
                        call right; }\
                    f = 9;\
                    g = 10;\
                }\
            }\
            procedure right{\
                bb = 11;\
                call one;\
                cc = 13;\
            }";

    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());

    // NextBip Cross procedure out
    // Dist 1
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(7,1));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(8,11));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(12,3));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(3,4));
    // Dist 2
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(6,1));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(6,11));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(8,3));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(8,4));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(12,4));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(3,13));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(4,9));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(10,2));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(10,12));
    // Dist 3
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(1,11));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(2,11));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(9,4));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(11,4));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(11,13));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(11,10));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(11,2));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(7,3));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(7,4));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(8,1));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(8,2));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(10,3));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(6,13));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(7,11));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(4,1));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(1,1));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(2,2));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(12,12));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(4,4));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(3,3));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(7,8));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(5,5));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(2,1));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(13,4));

    stringSet = pkb->get_after_BIP_star(1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(13,"1","2","3","4","5","6",
        "7","8","9","10","11","12","13"),stringSet);
    stringSet = pkb->get_after_BIP_star(2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(13,"1","2","3","4","5","6",
        "7","8","9","10","11","12","13"),stringSet);
    stringSet = pkb->get_after_BIP_star(3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(13,"1","2","3","4","5","6",
        "7","8","9","10","11","12","13"),stringSet);
    stringSet = pkb->get_after_BIP_star(4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(13,"1","2","3","4","5","6",
        "7","8","9","10","11","12","13"),stringSet);
    stringSet = pkb->get_after_BIP_star(5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(13,"1","2","3","4","5","6",
        "7","8","9","10","11","12","13"),stringSet);
    stringSet = pkb->get_after_BIP_star(6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(13,"1","2","3","4","5","6",
        "7","8","9","10","11","12","13"),stringSet);
    stringSet = pkb->get_after_BIP_star(7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(13,"1","2","3","4","5","6",
        "7","8","9","10","11","12","13"),stringSet);
    stringSet = pkb->get_after_BIP_star(8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(13,"1","2","3","4","5","6",
        "7","8","9","10","11","12","13"),stringSet);
    stringSet = pkb->get_after_BIP_star(9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(13,"1","2","3","4","5","6",
        "7","8","9","10","11","12","13"),stringSet);
    stringSet = pkb->get_after_BIP_star(10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(13,"1","2","3","4","5","6",
        "7","8","9","10","11","12","13"),stringSet);
    stringSet = pkb->get_after_BIP_star(11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(13,"1","2","3","4","5","6",
        "7","8","9","10","11","12","13"),stringSet);
    stringSet = pkb->get_after_BIP_star(12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(13,"1","2","3","4","5","6",
        "7","8","9","10","11","12","13"),stringSet);
    stringSet = pkb->get_after_BIP_star(13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(13,"1","2","3","4","5","6",
        "7","8","9","10","11","12","13"),stringSet);
}

void Test_30_PKB_NextBIP::test_nextBipStar_procback()
{
        const string& simpleProg =
            "procedure willy{\
                while one{\
                a = 2;\
                call two;\
                }\
            }\
            procedure two{\
                a = 4;\
            }\
            procedure first{\
                call willy;\
                b = 6;\
                if i7 then {\
                    call two;\
                } else {\
                   a = 9;\
                }\
                while i10 {\
                    d = 11;\
                }\
            }\
            procedure three {\
                call willy;\
                call four;\
            }\
            procedure four{\
                gg = 14;\
            }\
            procedure five {\
                call two;\
                hh = 16;\
           }";


    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    
    // Normal Next
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(1,2));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(1,6));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(2,3));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(3,4));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(4,1));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(5,1));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(4,10));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(9,10));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(8,10));

    CPPUNIT_ASSERT_EQUAL(true,pkb->nextBipStar_query_int_X_int_Y
        (ENT_STMT,1,ENT_STMT,6));
    CPPUNIT_ASSERT_EQUAL(true,pkb->nextBipStar_query_int_X_int_Y
        (ENT_STMT,2,ENT_STMT,3));
    CPPUNIT_ASSERT_EQUAL(true,pkb->nextBipStar_query_int_X_int_Y
        (ENT_STMT,5,ENT_STMT,1));
    CPPUNIT_ASSERT_EQUAL(true,pkb->nextBipStar_query_int_X_int_Y
        (ENT_STMT,4,ENT_STMT,10));
    CPPUNIT_ASSERT_EQUAL(true,pkb->nextBipStar_query_int_X_int_Y
        (ENT_STMT,8,ENT_STMT,10));
    CPPUNIT_ASSERT_EQUAL(true,pkb->nextBipStar_query_int_X_int_Y
        (ENT_STMT,9,ENT_STMT,10));


    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(2,10));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(3,11));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(3,11));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next_star_BIP(7,3));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next_star_BIP(9,1));

    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(2,4));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(2,6));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(2,13));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(2,14));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next_star_BIP(2,16));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(5,3));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(5,4));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(8,4));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(12,2));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(12,4));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(12,13));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(12,14));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next_star_BIP(12,6));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next_star_BIP(12,10));

    // Only topLvl terminators can go to all procs
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next_star_BIP(3,16));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next_star_BIP(5,16));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next_star_BIP(5,13));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next_star_BIP(8,16));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next_star_BIP(8,1));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next_star_BIP(8,13));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next_star_BIP(5,13));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next_star_BIP(5,14));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next_star_BIP(12,16));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(5,2));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(12,1));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(12,2));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(3,1));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(3,13));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(4,14));

    CPPUNIT_ASSERT_EQUAL(true,pkb->nextBipStar_query_int_X_int_Y
        (ENT_STMT,12,ENT_STMT,1));
    CPPUNIT_ASSERT_EQUAL(true,pkb->nextBipStar_query_int_X_int_Y
        (ENT_STMT,3,ENT_STMT,13));
    CPPUNIT_ASSERT_EQUAL(false,pkb->nextBipStar_query_int_X_int_Y
        (ENT_STMT,5,ENT_STMT,16));

    stringSet = pkb->get_after_BIP_star(1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(12,"1","2","3","4","6",
        "7","8","9","10","11","13","14"),stringSet);
    stringSet = pkb->get_after_BIP_star(2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(12,"1","2","3","4","6",
        "7","8","9","10","11","13","14"),stringSet);
    stringSet = pkb->get_after_BIP_star(3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(12,"1","2","3","4","6",
        "7","8","9","10","11","13","14"),stringSet);
    stringSet = pkb->get_after_BIP_star(4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(13,"1","2","3","4","6",
        "7","8","9","10","11","13","14","16"),stringSet);
    stringSet = pkb->get_after_BIP_star(5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(10,"1","2","3","4","6",
        "7","8","9","10","11"),stringSet);
    stringSet = pkb->get_after_BIP_star(6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6,"4",
        "7","8","9","10","11"),stringSet);
    stringSet = pkb->get_after_BIP_star(7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5,"4",
        "8","9","10","11"),stringSet);
    stringSet = pkb->get_after_BIP_star(8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3,
        "4","10","11"),stringSet);
    stringSet = pkb->get_after_BIP_star(9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2,"10","11"),stringSet);
    stringSet = pkb->get_after_BIP_star(10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2,"10","11"),stringSet);
    stringSet = pkb->get_after_BIP_star(11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2,"10","11"),stringSet);
    stringSet = pkb->get_after_BIP_star(12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6,"1","2","3","4",
        "13","14"),stringSet);
    stringSet = pkb->get_after_BIP_star(13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"14"),stringSet);
    stringSet = pkb->get_after_BIP_star(14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),stringSet);
    stringSet = pkb->get_after_BIP_star(15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2,"4","16"),stringSet);
    stringSet = pkb->get_after_BIP_star(16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),stringSet);

    stringSet = pkb->nextBipStar_X_Y_get_int_Y_from_int_X(ENT_STMT,ENT_STMT,15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2,"4","16"),stringSet);
    stringSet = pkb->nextBipStar_X_Y_get_int_Y_from_int_X(ENT_STMT,ENT_STMT,12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6,"1","2","3","4",
        "13","14"),stringSet);
    stringSet = pkb->nextBipStar_X_Y_get_int_Y_from_int_X(ENT_STMT,ENT_STMT,3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(12,"1","2","3","4","6",
        "7","8","9","10","11","13","14"),stringSet);
    stringSet = pkb->nextBipStar_X_Y_get_int_Y_from_int_X(ENT_STMT,ENT_ASSIGN,3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6,"2","4","6",
        "9","11","14"),stringSet);

    stringSet = pkb->get_before_BIP_star(1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(10,"12","5","4","3","2",
        "15","8","7","6","1"),stringSet);
    stringSet = pkb->get_before_BIP_star(2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(10,"12","5","4","3","2",
        "15","8","7","6","1"),stringSet);
    stringSet = pkb->get_before_BIP_star(3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(10,"12","5","4","3","2",
        "15","8","7","6","1"),stringSet);
    stringSet = pkb->get_before_BIP_star(4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(10,"12","5","4","3","2",
        "15","8","7","6","1"),stringSet);
    stringSet = pkb->get_before_BIP_star(5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),stringSet);
    stringSet = pkb->get_before_BIP_star(6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(10,"12","5","4","3","2",
        "15","8","7","6","1"),stringSet);
    stringSet = pkb->get_before_BIP_star(7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(10,"12","5","4","3","2",
        "15","8","7","6","1"),stringSet);
    stringSet = pkb->get_before_BIP_star(8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(10,"12","5","4","3","2",
        "15","8","7","6","1"),stringSet);
    stringSet = pkb->get_before_BIP_star(9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(10,"12","5","4","3","2",
        "15","8","7","6","1"),stringSet);
    stringSet = pkb->get_before_BIP_star(10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(13,"12","5","4","3","2",
        "15","8","7","6","1","9","10","11"),stringSet);
    stringSet = pkb->get_before_BIP_star(11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(13,"12","5","4","3","2",
        "15","8","7","6","1","9","10","11"),stringSet);
    stringSet = pkb->get_before_BIP_star(12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),stringSet);
    stringSet = pkb->get_before_BIP_star(13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(11,"12","5","4","3","2",
        "15","8","7","6","1","12"),stringSet);
    stringSet = pkb->get_before_BIP_star(14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(12,"12","5","4","3","2",
        "15","8","7","6","1","12","13"),stringSet);
    stringSet = pkb->get_before_BIP_star(15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),stringSet);
    stringSet = pkb->get_before_BIP_star(16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(11,"12","5","4","3","2",
        "15","8","7","6","1","15"),stringSet);


    stringSet = pkb->nextBipStar_X_Y_get_int_X_from_int_Y(ENT_STMT,ENT_STMT,13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(11,"12","5","4","3","2",
        "15","8","7","6","1","12"),stringSet);
    stringSet = pkb->nextBipStar_X_Y_get_int_X_from_int_Y(ENT_STMT,ENT_STMT,16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(11,"12","5","4","3","2",
        "15","8","7","6","1","15"),stringSet);
    stringSet = pkb->nextBipStar_X_Y_get_int_X_from_int_Y(ENT_CALL,ENT_STMT,16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5,"12","5","3",
        "15","8"),stringSet);

    CPPUNIT_ASSERT_EQUAL(true,pkb->nextBipStar_X_Y_smth_int_Y(ENT_STMT,16));
    CPPUNIT_ASSERT_EQUAL(true,pkb->nextBipStar_X_Y_int_X_smth(ENT_STMT,3));
}

void Test_30_PKB_NextBIP::test_gifts()
{
        const string& simpleProg =
            "procedure Bill {\
            x = 5;\
            call Mary;\
            y = x + 6;\
            call John;\
            z = x * y + 2;\
            }\
            \
            procedure Mary {\
            y = x * 3 ;\
            call John;\
            z = x + y;\
            }\
            \
            procedure John {\
            if i then {\
                x = x + z; }\
            else {\
                y = x * y; }\
            }";

    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());

    //stringSet = pkb->nextBipStar_X_Y_get_int_Y_from_int_X(ENT_STMT,ENT_STMT,9);
//    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(9,9));
    stringSet = pkb->get_after_BIP_star(9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7,"10", "11", "8", "5", "3", "4", "9"
        ),stringSet);
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_next_star_BIP(4,4));
    CPPUNIT_ASSERT_EQUAL(false,pkb->nextBipStar_query_int_X_int_Y(ENT_STMT,4,ENT_STMT,4));
    stringSet = pkb->get_before_BIP_star(4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(9,"3","8", "10", "11", "9", "7", "6", "2", "1"
        ),stringSet);
    stringSet = pkb->nextBipStar_X_Y_get_int_X_from_int_Y(ENT_STMT,ENT_STMT,4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(9,"3","8", "10", "11", "9", "7", "6", "2", "1"
        ),stringSet);
}

