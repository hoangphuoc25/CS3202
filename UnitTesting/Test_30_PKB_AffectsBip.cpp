#include <cstdarg>
#include <string>
#include <map>
#include <memory>
#include "Test_30_PKB_AffectsBip.h"
#include "../SPA/Parser.h"
#include "../SPA/PKB.h"
#include "../SPA/SetWrapper.h"

using std::auto_ptr;
using std::string;
using std::map;

void Test_30_PKB_AffectsBip::setUp(){}
void Test_30_PKB_AffectsBip::tearDown(){}
CPPUNIT_TEST_SUITE_REGISTRATION(Test_30_PKB_AffectsBip);

void Test_30_PKB_AffectsBip::test_AffectsBip()
{
        const string& simpleProg =
            "procedure left {\
                dd = 1 + cc;\
                bb = 2 + aa;\
            }\
            procedure one {\
                call two;\
            }\
            procedure two{\
                cc = 4 +bb;\
            }\
            procedure main{\
                while i5 {\
                    if i6 then {\
                        call left;\
                    } else {\
                        call right; }\
                    a = 9 + b;\
                    b = 10 + a;\
                }\
            }\
            procedure right{\
                ee = 11 + dd;\
                call one;\
                aa = 13;\
            }";

    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());

    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(9,10));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(10,9));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(13,2));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(2,4));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(4,1));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(1,11));

    stringSet = pkb->get_affects_Bip(9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"10"),stringSet);
    stringSet = pkb->get_affects_Bip(10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"9"),stringSet);
    stringSet = pkb->get_affects_Bip(13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"2"),stringSet);
    stringSet = pkb->get_affects_Bip(2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"4"),stringSet);
    stringSet = pkb->get_affects_Bip(4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"1"),stringSet);
    stringSet = pkb->get_affects_Bip(1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"11"),stringSet);

    stringSet = pkb->get_affected_by_Bip(10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"9"),stringSet);
    stringSet = pkb->get_affected_by_Bip(9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"10"),stringSet);
    stringSet = pkb->get_affected_by_Bip(2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"13"),stringSet);
    stringSet = pkb->get_affected_by_Bip(1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"4"),stringSet);
    stringSet = pkb->get_affected_by_Bip(11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"1"),stringSet);
    stringSet = pkb->get_affected_by_Bip(4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"2"),stringSet);



}

void Test_30_PKB_AffectsBip::test_AffectsBip_multiproc()
{
        const string& simpleProg =
            "procedure one{\
                a = 1;\
                call mid;\
                aa = 3 + c;\
            }\
            procedure two {\
                b = 4;\
                call mid;\
                bb = 6 + a;\
            }\
            procedure three{\
                c = 7;\
                call mid;\
                cc = 9 + b;\
            }\
            procedure mid{\
                d = 10;\
            }\
            procedure four{\
                d = 11;\
                call mid;\
                dd = 13 + d;\
            }\
            procedure left {\
                call right;\
                call right;\
                call right;\
            }\
            procedure right{\
                a = b;\
                b = c;\
                c = a;\
            }";

    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());

    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(19,18));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(18,17));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(17,19));

    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(10,13));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_affects_Bip(1,6));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_affects_Bip(4,9));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_affects_Bip(7,3));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_affects_Bip(11,13));

    stringSet = pkb->get_affects_Bip(19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"18"),stringSet);
    stringSet = pkb->get_affects_Bip(18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"17"),stringSet);
    stringSet = pkb->get_affects_Bip(17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"19"),stringSet);
    stringSet = pkb->get_affects_Bip(10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"13"),stringSet);
    stringSet = pkb->get_affects_Bip(1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),stringSet);
    stringSet = pkb->get_affects_Bip(4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),stringSet);
    stringSet = pkb->get_affects_Bip(7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),stringSet);
    stringSet = pkb->get_affects_Bip(11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),stringSet);

    stringSet = pkb->get_affected_by_Bip(17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"18"),stringSet);
    stringSet = pkb->get_affected_by_Bip(18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"19"),stringSet);
    stringSet = pkb->get_affected_by_Bip(19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"17"),stringSet);
    stringSet = pkb->get_affected_by_Bip(13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"10"),stringSet);
    stringSet = pkb->get_affected_by_Bip(11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),stringSet);
}

void Test_30_PKB_AffectsBip::test_AffectsBip_procBack()
{
        const string& simpleProg =
            "procedure main{\
                a = 1;\
                call two;\
                call three;\
                call four;\
                e = b+5;\
            }\
            procedure two{\
                call one;\
            }\
            procedure three{\
                call one;\
            }\
            procedure four{\
                call one;\
                d = c+9;\
            }\
            procedure one{\
                c = b + 10;\
                b = 11 + a;\
                call five;\
            }\
            procedure five{\
                b= 13;\
            }";

        // Assign: 1, 5, 9, 10, 11, 13 
        // 13 -> 10 -> 9
        // 13 -> 5
        // 1 -> 11
        // 11 -/-> 10, 5

    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());

    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(1,11));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(13,5));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(13,10));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(10,9));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_affects_Bip(11,10));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_affects_Bip(11,5));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_affects_Bip(12,5));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_affects_Bip(11,8));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_affects_Bip(1,10));

    stringSet = pkb->get_affects_Bip(13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2,"5","10"),stringSet);
    stringSet = pkb->get_affects_Bip(1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"11"),stringSet);
    stringSet = pkb->get_affects_Bip(10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"9"),stringSet);
    stringSet = pkb->get_affects_Bip(11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),stringSet);
    stringSet = pkb->get_affects_Bip(12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),stringSet);

    stringSet = pkb->get_affected_by_Bip(1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),stringSet);
    stringSet = pkb->get_affected_by_Bip(5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"13"),stringSet);
    stringSet = pkb->get_affected_by_Bip(9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"10"),stringSet);
    stringSet = pkb->get_affected_by_Bip(10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"13"),stringSet);
    stringSet = pkb->get_affected_by_Bip(11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"1"),stringSet);
    stringSet = pkb->get_affected_by_Bip(13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),stringSet);

}

void Test_30_PKB_AffectsBip::test_AffectsBip_affectedby()
{
        const string& simpleProg =
            "procedure one{\
                a = b + c + d + 1;\
                h = e + f +g;\
            }\
            procedure two {\
                b = 3;\
                call one;\
                f = b + 5;\
                c = f + h + e + 6;\
                call one;\
            }\
            procedure three{\
                e = 8;\
                f = 9;\
                call one;\
                f = 11;\
                call two;\
                g = 13;\
            }";

        /* Assign: 1, 2,3,5,6,8,11,13
           2 -> 6
           3 -> 1, 5
           5-> 2, 6
           6 -> 1
           8 -> 2, 6
           9 -> 2
           11 -> 2
           13 -/-> 2 */

    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());

    CPPUNIT_ASSERT_EQUAL(true,pkb->is_next_star_BIP(8,6));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(2,6));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(3,1));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(3,5));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(5,2));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(5,6));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(6,1));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(8,2));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(8,6));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(9,2));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(11,2));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_affects_Bip(13,2));

    stringSet = pkb->get_affects_Bip(2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"6"),stringSet);
    stringSet = pkb->get_affects_Bip(3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2,"1","5"),stringSet);
    stringSet = pkb->get_affects_Bip(5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2,"2","6"),stringSet);
    stringSet = pkb->get_affects_Bip(6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"1"),stringSet);
    stringSet = pkb->get_affects_Bip(8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2,"2","6"),stringSet);
    stringSet = pkb->get_affects_Bip(11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"2"),stringSet);
    stringSet = pkb->get_affects_Bip(13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),stringSet);

    stringSet = pkb->get_affected_by_Bip(2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4,"5","8","9","11"),stringSet);
    stringSet = pkb->get_affected_by_Bip(3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),stringSet);
    stringSet = pkb->get_affected_by_Bip(5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"3"),stringSet);
    stringSet = pkb->get_affected_by_Bip(10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),stringSet);
    stringSet = pkb->get_affected_by_Bip(6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3,"2","5","8"),stringSet);
    stringSet = pkb->get_affected_by_Bip(11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),stringSet);
    stringSet = pkb->get_affected_by_Bip(13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),stringSet);

}


