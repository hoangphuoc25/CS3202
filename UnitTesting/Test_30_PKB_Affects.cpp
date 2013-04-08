#include <cstdarg>
#include <string>
#include <map>
#include <memory>
#include "Test_30_PKB_Affects.h"
#include "../SPA/Parser.h"
#include "../SPA/PKB.h"
#include "../SPA/SetWrapper.h"

using std::auto_ptr;
using std::string;
using std::map;

void Test_30_PKB_Affects::setUp(){}
void Test_30_PKB_Affects::tearDown(){}
CPPUNIT_TEST_SUITE_REGISTRATION(Test_30_PKB_Affects);

void Test_30_PKB_Affects::test_affects()
{
        const string& simpleProg =
"procedure affects{\
    while w1 {\
        if i2 then {\
            if i3 then {\
                if i4 then {\
                    a = a + 5;\
                } else {\
                    c = b + 6;\
                }\
            } else {\
                if i7 then {\
                    b = a + 8;\
                } else {\
                    d = c + 9;\
                }\
            }\
        } else {\
            if i10 then {\
                if i11 then {\
                    b = a +12;\
                } else {\
                    d = c + 13;\
                }\
            } else {\
                while w14 {\
                    b = e + 15;\
                    e = d + 16;\
                    d = 17;\
                }\
            }\
        }\
        call lala;\
    }\
}\
procedure lala{\
    f = 1;\
    call rara;\
    g = f;\
}\
procedure rara {\
    f = 2;\
}";

    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    CPPUNIT_ASSERT_EQUAL(false,
            pkb->affects_query_int_X_int_Y(ENT_ASSIGN, 17,
                    ENT_ASSIGN, 17));
    CPPUNIT_ASSERT_EQUAL(false,
            pkb->affects_query_int_X_int_Y(ENT_ASSIGN, 17,
                    ENT_ASSIGN, 17));
    CPPUNIT_ASSERT_EQUAL(false,
            pkb->affects_query_int_X_int_Y(ENT_ASSIGN, 9, ENT_ASSIGN, 9));
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"16"),SetWrapper<string>
            (pkb->affects_X_Y_get_int_Y_from_int_X(ENT_ASSIGN,
                    ENT_ASSIGN, 9)));
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"6"),
            SetWrapper<string>
                    (pkb->affects_X_Y_get_int_X_from_int_Y(ENT_ASSIGN,
                            ENT_ASSIGN,9)));
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"),
            SetWrapper<string>(
                    pkb->affects_X_Y_get_int_X_from_int_Y(ENT_ASSIGN,
                            ENT_ASSIGN,5)));
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3,"5","8","12"),
            SetWrapper<string>(pkb->affects_X_Y_get_int_Y_from_int_X(
                    ENT_ASSIGN,ENT_ASSIGN,5)));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->affectsStar_query_int_X_int_Y(ENT_ASSIGN, 9,
                    ENT_ASSIGN, 9));

    // Testing loops
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5,"6","9","13","16","15"),
        SetWrapper<string>(
                pkb->affectsStar_X_Y_get_int_Y_from_int_X(
                        ENT_ASSIGN, ENT_ASSIGN, 6)));
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5,"6","9","13","16","15"),
        SetWrapper<string>(
                pkb->affectsStar_X_Y_get_int_Y_from_int_X(
                        ENT_ASSIGN, ENT_ASSIGN, 9)));
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5,"6","9","13","16","15"),
        SetWrapper<string>(
                pkb->affectsStar_X_Y_get_int_Y_from_int_X(
                        ENT_ASSIGN, ENT_ASSIGN, 13)));
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5,"6","9","13","16","15"),
        SetWrapper<string>(
                pkb->affectsStar_X_Y_get_int_Y_from_int_X(
                        ENT_ASSIGN, ENT_ASSIGN, 16)));
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5,"6","9","13","16","15"),
        SetWrapper<string>(
                pkb->affectsStar_X_Y_get_int_Y_from_int_X(
                        ENT_ASSIGN, ENT_ASSIGN, 15)));

    CPPUNIT_ASSERT_EQUAL(false,
            pkb->affects_query_int_X_int_Y(ENT_ASSIGN, 17,
                    ENT_ASSIGN, 15));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->affectsStar_query_int_X_int_Y(ENT_ASSIGN, 17,
                    ENT_ASSIGN, 15));
    CPPUNIT_ASSERT_EQUAL(false,
            pkb->affects_query_int_X_int_Y(ENT_ASSIGN, 8,
                    ENT_ASSIGN, 16));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->affectsStar_query_int_X_int_Y(ENT_ASSIGN, 8,
                    ENT_ASSIGN, 16));
    CPPUNIT_ASSERT_EQUAL(false,
            pkb->affects_query_int_X_int_Y(ENT_ASSIGN, 13,
                    ENT_ASSIGN, 8));
    CPPUNIT_ASSERT_EQUAL(false,
            pkb->affectsStar_query_int_X_int_Y(ENT_ASSIGN, 13,
                    ENT_ASSIGN, 8));

    CPPUNIT_ASSERT_EQUAL(true,
        pkb->affectsStar_query_int_X_int_Y(ENT_ASSIGN,15,ENT_ASSIGN,15));
    CPPUNIT_ASSERT_EQUAL(false,
        pkb->affectsStar_query_int_X_int_Y(ENT_ASSIGN,12,ENT_ASSIGN,12));
    CPPUNIT_ASSERT_EQUAL(true,
        pkb->affectsStar_query_int_X_int_Y(ENT_ASSIGN,17,ENT_ASSIGN,13));

    CPPUNIT_ASSERT_EQUAL(false,
        pkb->affects_query_int_X_int_Y(ENT_ASSIGN,17,ENT_ASSIGN,15));
    CPPUNIT_ASSERT_EQUAL(true,
        pkb->affects_query_int_X_int_Y(ENT_ASSIGN,17,ENT_ASSIGN,16));

    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"6"),
        SetWrapper<string>(pkb->affects_X_Y_get_int_Y_from_int_X(
            ENT_ASSIGN,ENT_ASSIGN,8)));
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"16"),
        SetWrapper<string>(pkb->affects_X_Y_get_int_Y_from_int_X(
            ENT_ASSIGN,ENT_ASSIGN,13)));
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"6"),
        SetWrapper<string>(pkb->affects_X_Y_get_int_Y_from_int_X(
            ENT_ASSIGN,ENT_ASSIGN,15)));

    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"16"), SetWrapper<string>
        (pkb->affects_X_Y_get_int_X_from_int_Y(ENT_ASSIGN,ENT_ASSIGN,15)));
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3,"8","12","15"),
        SetWrapper<string>(pkb->affects_X_Y_get_int_X_from_int_Y(
            ENT_ASSIGN,ENT_ASSIGN,6)));
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3,"9","13","17"),
        SetWrapper<string>(pkb->affects_X_Y_get_int_X_from_int_Y(
            ENT_ASSIGN,ENT_ASSIGN,16)));

    CPPUNIT_ASSERT_EQUAL(true,
            pkb->affectsStar_query_int_X_int_Y(ENT_ASSIGN, 15,
                    ENT_ASSIGN, 15));
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5,"6","9","13","16","15"),
        SetWrapper<string>(pkb->affectsStar_X_Y_get_int_Y_from_int_X
            (ENT_ASSIGN,ENT_ASSIGN,15)));
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5,"6","9","13","16","15"),
        SetWrapper<string>(pkb->affectsStar_X_Y_get_int_Y_from_int_X
            (ENT_ASSIGN,ENT_ASSIGN,16)));
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5,"6","9","13","16","15"),
        SetWrapper<string>(pkb->affectsStar_X_Y_get_int_Y_from_int_X
            (ENT_ASSIGN,ENT_ASSIGN,6)));
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5,"6","9","13","16","15"),
        SetWrapper<string>(pkb->affectsStar_X_Y_get_int_Y_from_int_X
            (ENT_ASSIGN,ENT_ASSIGN,9)));
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5,"6","9","13","16","15"),
        SetWrapper<string>(pkb->affectsStar_X_Y_get_int_Y_from_int_X
            (ENT_ASSIGN,ENT_ASSIGN,13)));

    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>
        (9,"5","8","12","6","9","13","16","15","17"),
            SetWrapper<string>(
                    pkb->affectsStar_X_Y_get_int_X_from_int_Y(
                            ENT_ASSIGN, ENT_ASSIGN, 15)));
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>
        (9,"5","8","12","6","9","13","16","15","17"),
        SetWrapper<string>(pkb->affectsStar_X_Y_get_int_X_from_int_Y
                (ENT_ASSIGN,ENT_ASSIGN,15)));
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>
        (9,"5","8","12","6","9","13","16","15","17"),
            SetWrapper<string>(pkb->affectsStar_X_Y_get_int_X_from_int_Y
                (ENT_ASSIGN,ENT_ASSIGN,6)));
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>
            (9,"5","8","12","6","9","13","16","15","17"),
            SetWrapper<string>(pkb->affectsStar_X_Y_get_int_X_from_int_Y
                (ENT_ASSIGN,ENT_ASSIGN,13)));
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1,"5"),
        SetWrapper<string>(pkb->affectsStar_X_Y_get_int_X_from_int_Y
            (ENT_ASSIGN,ENT_ASSIGN,12)));
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(0),
        SetWrapper<string>(pkb->affectsStar_X_Y_get_int_X_from_int_Y
            (ENT_ASSIGN,ENT_ASSIGN,17)));
}