#include <cstdarg>
#include <string>
#include <map>
#include <memory>
#include "Test_30_PKB.h"
#include "../SPA/Parser.h"
#include "../SPA/PKB.h"
#include "../SPA/SetWrapper.h"

using std::auto_ptr;
using std::string;
using std::map;


void Test_30_PKB::setUp()
{
    this->TEST_MODIFIES_SIMPLE_PROG =
        "procedure pOne { \
           aone = b + c; \
           d3 = 5 + 7; \
           while x { \
             this = bx + d3; \
             while a { \
               x1 = b + ha; \
               if g2 then { \
                 t1 = t + bab; \
                 h2 = 2 + ga; \
                 call secProc; \
                 while ten { \
                   y = y + ue; \
                 } \
                 if tp then { \
                   while one { \
                     x = y + z; \
                     call thirdProc; \
                   } \
                 } else { \
                   fire = a + fire; \
                 } \
               } else { \
                 xe = a * cab; \
               } \
               good = evil + evil; \
               pe = 2 * 3 + zt1; \
             } \
             fol = y + g2; \
           } \
           g2 = xz + brave; \
         } \
         procedure secProc { \
           a = b + c; \
           xe = 2 + 73; \
           while gg { \
             onceOnly = true; \
             if twice then { \
               all = 3 * 5; \
             } else { \
               none = bba; \
               while p { \
                 if xe then { \
                   harp = 41; \
                 } else { \
                   nn = ba1; \
                 } \
               } \
             } \
           } \
           call procFOUR; \
         } \
         procedure thirdProc { \
           hoho = merry + christmas; \
           haa = haas; \
         } \
         procedure procFOUR { \
           pfg = pf + g; \
           while x { \
             ue = no ; \
           } \
         } \
         procedure cleanUP { \
           zzz = 512; \
         }";

    this->TEST_USES_SIMPLE_PROG =
        "procedure pOne { \
           aone = b + c; \
           d3 = 5 + 7; \
           while x { \
             this = bx + d3; \
             while a { \
               x1 = b + ha; \
               if g2 then { \
                 t1 = t + bab; \
                 h2 = 2 + ga; \
                 call secProc; \
                 while ten { \
                   y = y + ue; \
                 } \
                 if tp then { \
                   while one { \
                     x = y + z; \
                     call thirdProc; \
                   } \
                 } else { \
                   fire = a + fire; \
                 } \
               } else { \
                 xe = a * cab; \
               } \
               good = evil + evil; \
               pe = 2 * 3 + zt1; \
             } \
             fol = y + g2; \
           } \
           g2 = xz + brave; \
         } \
         procedure secProc { \
           a = b + c; \
           xe = 2 + 73; \
           while gg { \
             onceOnly = true; \
             if twice then { \
               all = 3 * 5; \
             } else { \
               none = bba; \
               while p { \
                 if xe then { \
                   harp = 41; \
                 } else { \
                   nn = ba1; \
                 } \
               } \
             } \
           } \
           call procFOUR; \
         } \
         procedure thirdProc { \
           hoho = merry + christmas; \
           haa = haas; \
         } \
         procedure procFOUR { \
           pfg = pf + g; \
           while x { \
             ue = no ; \
           } \
         } \
         procedure execute { \
           this = 4 + 5; \
           proc = 542 - 1; \
           uses = 77 + 14 * 7231; \
           nothing = 62 + 51 + 666; \
         } \
         procedure useCall { \
           this = 62 - 721; \
           proc = 673 + 89811; \
           usesThings = 5124 + 777; \
           byCalling = 11 - 5 * 712; \
           call procFOUR; \
         } \
         procedure useOne { \
           a = zzz; \
         }";
}

void Test_30_PKB::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test_30_PKB);

// Test banks
void Test_30_PKB::test_one(){
    
    Parser p;
    p = Parser("Test_30_PKB\\assign1.txt",FROMFILE);
    p.init();
    PKB pkb = *p.get_pkb();

    SetWrapper<string> stringSet;
    set<string> s;
    set<int> s1;
    set<int> intSet;
    set<int>::iterator it;
    int i;

    // Variables
    CPPUNIT_ASSERT(pkb.get_control_var(9) == "i");
    CPPUNIT_ASSERT_EQUAL(string("i"), pkb.get_control_var(19));
    CPPUNIT_ASSERT_EQUAL(string("i"), pkb.get_control_var(28));

    s = pkb.get_all_vars();
    stringSet = SetWrapper<string>(s);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "d", "e", "i", "x", "y",
            "z"), stringSet);

    s = pkb.uses_X_Y_get_string_Y_from_string_X(ENT_PROC, ENT_VAR, "Bill");
    stringSet = SetWrapper<string>(s);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "d", "e", "i", "x", "y",
            "z"), stringSet);

    s = pkb.uses_X_Y_get_string_Y_from_string_X(ENT_PROC, ENT_VAR, "Mary");
    stringSet = SetWrapper<string>(s);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "d", "e", "i", "x", "y",
            "z"), stringSet);

    s = pkb.uses_X_Y_get_string_Y_from_string_X(ENT_PROC, ENT_VAR, "Jane");
    stringSet = SetWrapper<string>(s);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "d", "x", "z"), stringSet);

    s = pkb.uses_X_Y_get_string_Y_from_string_X(ENT_PROC, ENT_VAR, "John");
        stringSet = SetWrapper<string>(s);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "d", "e", "i", "x", "y",
            "z"), stringSet);
    
    // Calls 
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_calls("Mary", "John"));
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_calls("Bill", "Mary"));
    CPPUNIT_ASSERT_EQUAL(false, pkb.is_calls("Jane", "John"));

    CPPUNIT_ASSERT_EQUAL(true, pkb.is_calls_star("Bill", "John"));

    s = pkb.get_calls("Bill");
    stringSet = SetWrapper<string>(s);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "John", "Jane", "Mary"),
            stringSet);

    s = pkb.get_calls_star("Bill");
    stringSet = SetWrapper<string>(s);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "John", "Jane", "Mary"),
            stringSet);

    s = pkb.get_called_by("John");
    stringSet = SetWrapper<string>(s);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "Bill", "Mary"),
            stringSet);

    s = pkb.get_called_by_star("John");
        stringSet = SetWrapper<string>(s);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "Bill", "Mary"),
            stringSet);

    // Modifies
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_modifies("Mary", "z"));
    CPPUNIT_ASSERT_EQUAL(false, pkb.is_modifies("Mary", "x"));

    CPPUNIT_ASSERT_EQUAL(true, pkb.is_modifies(1, "z"));
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_modifies(30, "z"));

    s = pkb.modifies_X_Y_get_string_X_from_string_Y(ENT_PROC, ENT_VAR, "i");
    stringSet = SetWrapper<string>(s);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "Bill", "Mary"),
            stringSet);

    s1 = pkb.modifies_X_Y_get_int_X_from_string_Y(ENT_STMT, ENT_VAR, "i");
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "13", "16", "22", "9",
            "11", "19", "18"), stringSet);

    s = pkb.modifies_X_Y_get_string_Y_from_string_X(ENT_PROC, ENT_VAR,
            "Jane");
    stringSet = SetWrapper<string>(s);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "x", "z"), stringSet);

    s = pkb.modifies_X_Y_get_string_Y_from_int_X(ENT_STMT, ENT_VAR, 6);
    stringSet = SetWrapper<string>(s);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "d"), stringSet);
    
    s = pkb.modifies_X_Y_get_string_Y_from_int_X(ENT_STMT, ENT_VAR, 15);
        stringSet = SetWrapper<string>(s);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "x", "z"), stringSet);

    s = pkb.modifies_X_Y_get_string_Y_from_int_X(ENT_STMT, ENT_VAR, 9);
    stringSet = SetWrapper<string>(s);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "e", "i", "x", "y", "z"),
            stringSet);

    // Uses
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_uses("Mary", "x"));
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_uses("Mary", "d"));

    CPPUNIT_ASSERT_EQUAL(true, pkb.is_uses(3, "z"));
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_uses(9, "y"));
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_uses(21, "i"));

    s = pkb.uses_X_Y_get_string_X_from_string_Y(ENT_PROC, ENT_VAR, "d");
    stringSet = SetWrapper<string>(s);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "Bill", "John", "Mary",
            "Jane"), stringSet);

    s1 = pkb.uses_X_Y_get_int_X_from_string_Y(ENT_STMT, ENT_VAR, "i");
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(11, "9", "11", "16", "19",
            "18", "22", "23", "28", "5", "21", "27"), stringSet);

    s = pkb.uses_X_Y_get_string_Y_from_string_X(ENT_PROC, ENT_VAR, "Jane");
    stringSet = SetWrapper<string>(s);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "d", "x", "z"), stringSet);

    s = pkb.get_var_stmt_uses(9);
    stringSet = SetWrapper<string>(s);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "d", "i", "x", "y", "z"),
            stringSet);

    // Parent

    CPPUNIT_ASSERT(pkb.is_parent(11, 15));
    CPPUNIT_ASSERT(pkb.is_parent(11, 15));

    CPPUNIT_ASSERT(pkb.is_parent_star(11, 15));
    CPPUNIT_ASSERT(pkb.is_parent_star(9, 15));

    CPPUNIT_ASSERT(11 == pkb.get_parent(15));

    s1 = pkb.get_parent_star(16);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "9", "11"), stringSet);

    s1 = pkb.get_children_star(9);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(8, "10", "11", "12", "13",
            "14", "15", "16", "17"), stringSet);

    s1 = pkb.get_children(9);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "10", "11", "17"),
            stringSet);

    s1 = pkb.get_children_star(9);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(8, "10", "11", "12", "13",
            "14", "15", "16", "17"), stringSet);
    CPPUNIT_ASSERT_EQUAL(8, (int)s1.size());

    // Follows
    CPPUNIT_ASSERT(pkb.is_follows(9, 18));
    CPPUNIT_ASSERT(!pkb.is_follows(11, 15));

    CPPUNIT_ASSERT(pkb.is_follows_star(3, 4));
    CPPUNIT_ASSERT(pkb.is_follows_star(3, 18));
    CPPUNIT_ASSERT(!pkb.is_follows_star(12, 15));

    CPPUNIT_ASSERT_EQUAL(23, pkb.get_successor(19));
    CPPUNIT_ASSERT_EQUAL(26, pkb.get_successor(24));

    s1 = pkb.get_successor_star(7);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "8", "9", "18"),
            stringSet);

    CPPUNIT_ASSERT_EQUAL(19, pkb.get_predecessor(23));
    CPPUNIT_ASSERT_EQUAL(24, pkb.get_predecessor(26));

    s1 = pkb.get_predecessor_star(6);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "2", "3", "4", "5", "1"),
            stringSet);

    // Constant
    CPPUNIT_ASSERT(pkb.has_const(3));
    CPPUNIT_ASSERT(pkb.has_const(1));
    CPPUNIT_ASSERT(!pkb.has_const(100));

    intSet = pkb.get_all_const();
    stringSet = SetWrapper<string>(intSet);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "10", "5", "4", "12",
            "1", "3", "2"), stringSet);

    // Others
    s1 = pkb.get_all_stmt();
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(30, "1", "2", "3", "4", "5",
            "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16",
            "17", "18", "19", "20", "21", "22", "23", "24", "25", "26",
            "27", "28", "29", "30"), stringSet);

    s1 = pkb.get_all_stmt_by_proc("Mary");
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "19", "20", "21", "22",
            "23"), stringSet);

    s1 = pkb.filter_by_proc("Mary", pkb.get_all_stmt());
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "19", "20", "21", "22",
            "23"), stringSet);

    s1 = pkb.filter_by_stmtType(ENT_WHILE, pkb.get_all_stmt());
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "9", "19", "24", "27"),
            stringSet);

    // Assignment 1
    // Q1
    CPPUNIT_ASSERT_EQUAL(-1, pkb.get_parent(3));
    CPPUNIT_ASSERT_EQUAL(9, pkb.get_parent(11));
    CPPUNIT_ASSERT_EQUAL(11, pkb.get_parent(13));
    CPPUNIT_ASSERT_EQUAL(19, pkb.get_parent(21));

    // Q2
    CPPUNIT_ASSERT_EQUAL(-1, pkb.get_parent(3));
    CPPUNIT_ASSERT_EQUAL(11, pkb.get_parent(13));
    CPPUNIT_ASSERT_EQUAL(11, pkb.get_parent(15));
    CPPUNIT_ASSERT_EQUAL(19, pkb.get_parent(22));

    // Q3
    s1 = pkb.get_children(2);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    s1 = pkb.get_children(9);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "10", "11", "17"),
            stringSet);
    s1 = pkb.get_children(10);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    s1 = pkb.get_children(11);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "12", "13", "14", "15",
            "16"), stringSet);

    // Q4
    s1 = pkb.get_parent_star(2);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    s1 = pkb.get_parent_star(10);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "9"), stringSet);
    s1 = pkb.get_parent_star(15);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "9", "11"), stringSet);
    s1 = pkb.get_parent_star(21);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "19"), stringSet);

    // Q5
    s1 = pkb.filter_by_stmtType(ENT_WHILE, pkb.get_parent_star(2));
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    s1 = pkb.filter_by_stmtType(ENT_WHILE, pkb.get_parent_star(10));
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "9"), stringSet);
    s1 = pkb.filter_by_stmtType(ENT_WHILE, pkb.get_parent_star(13));
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "9"), stringSet);
    s1 = pkb.filter_by_stmtType(ENT_WHILE, pkb.get_parent_star(17));
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "9"), stringSet);
    s1 = pkb.filter_by_stmtType(ENT_WHILE, pkb.get_parent_star(22));
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "19"), stringSet);

    // Q7
    CPPUNIT_ASSERT_EQUAL(-1, pkb.get_predecessor(1));
    CPPUNIT_ASSERT_EQUAL(2, pkb.get_predecessor(3));
    CPPUNIT_ASSERT_EQUAL(8, pkb.get_predecessor(9));
    CPPUNIT_ASSERT_EQUAL(-1, pkb.get_predecessor(10));
    CPPUNIT_ASSERT_EQUAL(-1, pkb.get_predecessor(19));

    // Q8
    CPPUNIT_ASSERT_EQUAL(-1, pkb.filter_by_stmtType(ENT_ASSIGN,
        pkb.get_predecessor(1)));
    CPPUNIT_ASSERT_EQUAL(2, pkb.filter_by_stmtType(ENT_ASSIGN,
        pkb.get_predecessor(3)));
    CPPUNIT_ASSERT_EQUAL(8, pkb.filter_by_stmtType(ENT_ASSIGN,
        pkb.get_predecessor(9)));
    CPPUNIT_ASSERT_EQUAL(-1, pkb.filter_by_stmtType(ENT_ASSIGN,
        pkb.get_predecessor(10)));
    CPPUNIT_ASSERT_EQUAL(-1, pkb.filter_by_stmtType(ENT_ASSIGN,
        pkb.get_predecessor(18)));

    // Q10
    s1 = pkb.get_predecessor_star(2);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "1"), stringSet);
    s1 = pkb.get_predecessor_star(10);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    s1 = pkb.get_predecessor_star(11);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "10"), stringSet);
    s1 = pkb.get_predecessor_star(21);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "20"), stringSet);

    // Q11
    s1 = pkb.filter_by_stmtType(ENT_IF,pkb.get_predecessor_star(10));
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    s1 = pkb.filter_by_stmtType(ENT_IF,pkb.get_predecessor_star(17));
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "11"), stringSet);

    // Q12
    s1 = pkb.filter_by_stmtType(ENT_ASSIGN,pkb.get_predecessor_star(4));
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "1", "2", "3"),
            stringSet);
    s1 = pkb.filter_by_stmtType(ENT_ASSIGN,pkb.get_predecessor_star(5));
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "1", "2", "3", "4"),
            stringSet);
    s1 = pkb.filter_by_stmtType(ENT_ASSIGN,pkb.get_predecessor_star(9));
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "1", "2", "3", "4", "6",
            "8"), stringSet);
    s1 = pkb.filter_by_stmtType(ENT_ASSIGN,pkb.get_predecessor_star(17));
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "10"), stringSet);
    s1 = pkb.filter_by_stmtType(ENT_ASSIGN,pkb.get_predecessor_star(22));
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "20"), stringSet);

    // Q13
    s = pkb.get_var_stmt_modifies(3);
    stringSet = SetWrapper<string>(s);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "y"), stringSet);
    s = pkb.modifies_X_Y_get_string_Y_from_int_X(ENT_STMT, ENT_VAR, 5);
    stringSet = SetWrapper<string>(s);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "y", "z"), stringSet);
    s = pkb.modifies_X_Y_get_string_Y_from_int_X(ENT_STMT, ENT_VAR, 9);
    stringSet = SetWrapper<string>(s);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "e", "i", "x", "y", "z"),
            stringSet);
    s = pkb.modifies_X_Y_get_string_Y_from_int_X(ENT_STMT, ENT_VAR, 11);
    stringSet = SetWrapper<string>(s);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "i", "x", "y", "z"),
            stringSet);

    // Q14
    s1 = pkb.filter_by_stmtType(ENT_WHILE, pkb.get_stmt_modifies("i"));
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "9", "19"), stringSet);
    s1 = pkb.filter_by_stmtType(ENT_WHILE, pkb.get_stmt_modifies("y"));
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "9", "19", "27"),
            stringSet);

    // Q15
    s = pkb.modifies_X_Y_get_string_Y_from_string_X(ENT_PROC, ENT_VAR,
            "Mary");
    stringSet = SetWrapper<string>(s);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "i", "y", "z"),
            stringSet);

    // Q16
    s1 = pkb.uses_X_Y_get_int_X_from_string_Y(ENT_STMT, ENT_VAR, "i");
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(11, "5", "9", "11", "16",
            "18", "19", "21", "22", "23", "27", "28"), stringSet);
    s1 = pkb.uses_X_Y_get_int_X_from_string_Y(ENT_STMT, ENT_VAR, "y");
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(17, "4", "5", "9", "10",
            "11", "12", "13", "14", "17", "18", "19", "20", "21", "23",
            "27", "28", "30"), stringSet);

    // Q17
    s = pkb.get_var_stmt_uses(10);
    stringSet = SetWrapper<string>(s);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "x", "y"), stringSet);
    s = pkb.get_var_stmt_uses(18);
    stringSet = SetWrapper<string>(s);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "d", "e", "i", "x", "y",
            "z"), stringSet);

    // Q23
    s = pkb.get_called_by_star("John");
    stringSet = SetWrapper<string>(s);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "Bill", "Mary"),
            stringSet);

    // Q39
    s1 = pkb.get_after(1);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "2"), stringSet);
    s1 = pkb.get_after(9);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "10", "18"), stringSet);
    s1 = pkb.get_after(11);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "12", "14"), stringSet);
    s1 = pkb.get_after(13);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "17"), stringSet);
    s1 = pkb.get_after(15);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "16"), stringSet);
    s1 = pkb.get_after(17);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "9"), stringSet);
    s1 = pkb.get_after(18);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);

    // Q40
    s1 = pkb.get_before(1);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    s1 = pkb.get_before(9);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "8", "17"), stringSet);
    s1 = pkb.get_before(10);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "9"), stringSet);
    s1 = pkb.get_before(17);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "13", "16"), stringSet);
    s1 = pkb.get_before(18);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "9"), stringSet);
    s1 = pkb.get_before(19);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "22"), stringSet);

    // Q43
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_affects(1, 2));
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_affects(1, 3));
    CPPUNIT_ASSERT_EQUAL(false, pkb.is_affects(1, 5));
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_affects(2, 6));
    CPPUNIT_ASSERT_EQUAL(false, pkb.is_affects(2, 8));
    CPPUNIT_ASSERT_EQUAL(false, pkb.is_affects(3, 12));
    CPPUNIT_ASSERT_EQUAL(false, pkb.is_affects(3, 13));
    CPPUNIT_ASSERT_EQUAL(false, pkb.is_affects(16, 21));

    // Q44
    s1 = pkb.get_affected_by(1);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    s1 = pkb.get_affected_by(10);
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_affects(17, 10));
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_affects(12, 10));
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "12", "17"), stringSet);

    // Q45
    s1 = pkb.get_affects(1);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "2", "3"), stringSet);
    s1 = pkb.get_affects(13);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "16"), stringSet);

    // Q46
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_affects_star(1, 2));
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_affects_star(1, 3));
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_affects_star(1, 6));
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_affects_star(1, 8));
    CPPUNIT_ASSERT_EQUAL(false, pkb.is_affects_star(11, 14));
    CPPUNIT_ASSERT_EQUAL(false, pkb.is_affects_star(20, 20));

    // Q47
    s1 = pkb.get_affected_by_star(12);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    s1 = pkb.get_affected_by_star(26);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "25"), stringSet);

    // Q48
    s1 = pkb.get_affects_star(20);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    s1 = pkb.get_affects_star(6);
    stringSet = SetWrapper<string>(s1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "8"), stringSet);
}

// Test procTable
void Test_30_PKB::test_two(){


}

void Test_30_PKB::test_three(){

}

void Test_30_PKB::test_retrieve_all_X()
{
    string simpleProg, queryStr;
    set<string> S;
    set<int> intSet;
    SetWrapper<string> stringSet;
    simpleProg =
        "procedure Xproc { \
           a = x + y + 3; \
           b73 = xid - 62; \
           if good then { \
             bc = 2 + 73; \
             tie = fighter; \
             sad = 3 + 2; \
             while true { \
               gather = food; \
               if cond then { \
                 call execVE; \
                 cleanup = 156; \
               } else { \
                 while x { \
                   hungry = eat; \
                   tired = sleep; \
                 } \
                 hell = no; \
               } \
               follows = star; \
               modifies = P; \
             } \
             program = cool; \
             pkgmgr = pacman; \
           } else { \
             call oneTwoThree; \
             elseVar = 511; \
           } \
           last = varHere; \
         } \
         procedure execVE { \
           execVar = 0; \
           cool = stuff; \
           if cool then { \
             call lastProc; \
             save = state; \
           } else { \
             exitVal = 675; \
           } \
           retVal = exitVal; \
         } \
         procedure oneTwoThree { \
           one = twoThree; \
           bill = paid; \
           lastProc = sameName; \
         } \
         procedure lastProc { \
           while notEmpty { \
             doStuff = 1; \
           } \
           im = done; \
         }";
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    PKB *pkb = parser.get_pkb();
    // assign
    intSet = pkb->get_all_assign();
    stringSet = SetWrapper<string>(intSet);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(26, "1", "2", "4", "5", "6",
            "8", "11", "13", "14", "15", "16", "17", "18", "19", "21",
            "22", "23", "24", "27", "28", "29", "30", "31", "32", "34",
            "35"), stringSet);
    // if
    intSet = pkb->get_all_if();
    stringSet = SetWrapper<string>(intSet);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "9", "25"),
            stringSet);
    // while
    intSet = pkb->get_all_while();
    stringSet = SetWrapper<string>(intSet);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "7", "12", "33"),
            stringSet);
    // call
    intSet = pkb->get_all_call();
    stringSet = SetWrapper<string>(intSet);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "10", "20", "26"),
            stringSet);
    // const
    intSet = pkb->get_all_const();
    stringSet = SetWrapper<string>(intSet);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(9, "3", "62", "2", "73",
            "156", "511", "0", "675", "1"), stringSet);
    // stmt
    intSet = pkb->get_all_stmt();
    stringSet = SetWrapper<string>(intSet);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(35, "1", "2", "3", "4", "5",
            "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16",
            "17", "18", "19", "20", "21", "22", "23", "24", "25", "26",
            "27", "28", "29", "30", "31", "32", "33", "34", "35"),
            stringSet);
    // progline
    intSet = pkb->get_all_progline();
    stringSet = SetWrapper<string>(intSet);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(35, "1", "2", "3", "4", "5",
            "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16",
            "17", "18", "19", "20", "21", "22", "23", "24", "25", "26",
            "27", "28", "29", "30", "31", "32", "33", "34", "35"),
            stringSet);
    // stmtLst
    intSet = pkb->get_all_stmtLst();
    stringSet = SetWrapper<string>(intSet);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(13, "1", "4", "8", "10", "12",
            "13", "20", "23", "26", "28", "30", "33", "34"),
            stringSet);
    // variable
    S = pkb->get_all_vars();
    stringSet = SetWrapper<string>(S);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(48, "a", "b73", "bc", "bill",
            "cleanup", "cond", "cool", "doStuff", "done",
            "eat", "elseVar", "execVar", "exitVal", "fighter",
            "follows", "food", "gather", "good", "hell",
            "hungry", "im", "last", "lastProc", "modifies",
            "no", "notEmpty", "one", "P", "pacman", "paid", "pkgmgr",
            "program", "retVal", "sad", "sameName", "save",
            "sleep", "star", "state", "stuff", "tie", "tired",
            "true", "twoThree", "varHere", "x", "xid", "y"),
            stringSet);
    // procedure
    S = pkb->get_all_procs();
    stringSet = SetWrapper<string>(S);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "Xproc", "execVE",
            "oneTwoThree", "lastProc"),
            stringSet);
}

void Test_30_PKB::test_modifies_procedure_var()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    PKB *pkb = parser.get_pkb();
    set<int> intSet;
    SetWrapper<string> stringSet;

    // Modifies(procedure,var), get var
    stringSet = pkb->modifies_X_Y_get_string_Y_from_string_X(ENT_PROC,
            ENT_VAR, "pOne");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(24, "a", "all", "aone",
            "d3", "fire", "fol", "g2", "good", "h2", "haa", "harp",
            "hoho", "nn", "none", "onceOnly", "pe", "pfg", "t1",
            "this", "ue", "x", "x1", "xe", "y"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_string_X(ENT_PROC,
            ENT_VAR, "secProc");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(9, "a", "all", "harp",
            "nn", "none", "onceOnly", "pfg", "ue", "xe"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_string_X(ENT_PROC,
            ENT_VAR, "thirdProc");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "haa", "hoho"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_string_X(ENT_PROC,
            ENT_VAR, "procFOUR");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "pfg", "ue"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_string_X(ENT_PROC,
            ENT_VAR, "cleanUP");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "zzz"), stringSet);

    // Modifies(procedure,var), get procedure
    stringSet = pkb->modifies_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "a");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "pOne", "secProc"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "all");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "pOne", "secProc"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "aone");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "d3");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "fire");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "fol");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "g2");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "good");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "h2");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "haa");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "pOne", "thirdProc"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "harp");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "pOne", "secProc"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "hoho");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "pOne", "thirdProc"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "nn");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "pOne", "secProc"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "none");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "pOne", "secProc"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "onceOnly");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "pOne", "secProc"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "pe");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "pfg");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "pOne", "secProc",
            "procFOUR"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "t1");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "this");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "ue");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "pOne", "secProc",
            "procFOUR"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "x");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "x1");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "xe");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "pOne", "secProc"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "y");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "zzz");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "cleanUP"), stringSet);
}

void Test_30_PKB::test_modifies_assign_var()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    PKB *pkb = parser.get_pkb();
    set<int> intSet;
    SetWrapper<string> stringSet;

    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "aone"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "d3"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "this"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "x1"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "t1"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "h2"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "y"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "x"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "fire"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "xe"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "good"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pe"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "fol"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "g2"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "a"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "xe"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "onceOnly"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "all"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "none"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "harp"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "nn"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "hoho"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "haa"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pfg"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "ue"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "zzz"), stringSet);

    // Modifies(assign,var), get assign
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "a");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "23"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "all");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "28"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "aone");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "1"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "d3");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "2"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "fire");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "17"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "fol");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "21"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "g2");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "22"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "good");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "19"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "h2");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "9"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "haa");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "36"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "harp");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "32"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "hoho");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "35"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "nn");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "33"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "none");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "29"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "onceOnly");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "26"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "pe");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "20"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "pfg");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "37"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "t1");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "8"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "this");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "4"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "ue");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "39"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "x");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "15"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "x1");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "6"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "xe");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "18", "24"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "y");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "12"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "zzz");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "40"), stringSet);
}

void Test_30_PKB::test_modifies_call_var()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    PKB *pkb = parser.get_pkb();
    set<int> intSet;
    SetWrapper<string> stringSet;

    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 0);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(9, "a", "xe", "onceOnly",
            "all", "none", "harp", "nn", "pfg", "ue"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "hoho", "haa"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "pfg", "ue"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);

    // Modifies(call,var), get call
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "a");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "10"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "all");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "10"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "aone");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "d3");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "fire");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "fol");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "g2");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "good");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "h2");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "haa");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "16"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "harp");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "10"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "hoho");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "16"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "nn");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "10"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "none");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "10"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "onceOnly");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "10"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "pe");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "pfg");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "10", "34"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "t1");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "this");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "ue");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "10", "34"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "x");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "x1");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "xe");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "10"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "y");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "zzz");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
}

void Test_30_PKB::test_modifies_if_var()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    PKB *pkb = parser.get_pkb();
    set<int> intSet;
    SetWrapper<string> stringSet;

    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(16, "t1", "h2", "a", "xe",
            "onceOnly", "all", "none", "harp", "nn", "pfg", "ue",
            "y", "x", "hoho", "haa", "fire"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "x", "hoho", "haa",
            "fire"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "all", "none", "harp",
            "nn"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "harp", "nn"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);

    // Modifies(if,var), get if
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "a");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "all");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "7", "27"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "aone");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "d3");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "fire");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "7", "13"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "fol");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "g2");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "good");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "h2");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "haa");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "7", "13"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "harp");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "7", "27", "31"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "hoho");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "7", "13"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "nn");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "7", "27", "31"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "none");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "7", "27"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "onceOnly");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "pe");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "pfg");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "t1");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "this");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "ue");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "x");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "7", "13"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "x1");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "xe");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "y");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "zzz");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
}

void Test_30_PKB::test_modifies_while_var()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    PKB *pkb = parser.get_pkb();
    set<int> intSet;
    SetWrapper<string> stringSet;

    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(21, "this", "x1", "t1",
            "h2", "a", "xe", "onceOnly", "all", "none", "harp", "nn",
            "pfg", "ue", "y", "x", "hoho", "haa", "fire", "good", "pe",
            "fol"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(19, "x1", "t1", "h2", "a",
            "xe", "onceOnly", "all", "none", "harp", "nn", "pfg", "ue",
            "y", "x", "hoho", "haa", "fire", "good", "pe"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "y"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "x", "hoho", "haa"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "onceOnly", "all", "none",
            "harp", "nn"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "harp", "nn"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "ue"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);

    // Modifies(while,var), get while
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "a");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "5"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "all");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "25"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "aone");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "d3");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "fire");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "5"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "fol");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "g2");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "good");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "5"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "h2");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "5"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "haa");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "14"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "harp");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "3", "5", "25", "30"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "hoho");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "14"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "nn");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "3", "5", "25", "30"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "none");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "25"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "onceOnly");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "25"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "pe");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "5"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "pfg");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "5"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "t1");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "5"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "this");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "ue");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "38"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "x");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "14"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "x1");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "5"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "xe");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "5"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "y");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "11"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "zzz");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
}

void Test_30_PKB::test_modifies_stmt_var()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    PKB *pkb = parser.get_pkb();
    set<int> intSet;
    SetWrapper<string> stringSet;

    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "aone"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "d3"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(21, "this", "x1", "t1", "h2",
            "a", "xe", "onceOnly", "all", "none", "harp", "nn", "pfg",
            "ue", "y", "x", "hoho", "haa", "fire", "good", "pe", "fol"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "this"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(19, "x1", "t1", "h2", "a",
            "xe", "onceOnly", "all", "none", "harp", "nn", "pfg", "ue",
            "y", "x", "hoho", "haa", "fire", "good", "pe"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "x1"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(16, "t1", "h2", "a", "xe",
            "onceOnly", "all", "none", "harp", "nn", "pfg", "ue",
            "y", "x", "hoho", "haa", "fire"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "t1"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "h2"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(9, "a", "xe", "onceOnly",
            "all", "none", "harp", "nn", "pfg", "ue"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "y"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "y"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "x", "hoho", "haa",
            "fire"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "x", "hoho", "haa"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "x"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "hoho", "haa"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "fire"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "xe"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "good"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pe"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "fol"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "g2"), stringSet);

    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "a"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "xe"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "onceOnly", "all",
            "none", "harp", "nn"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "onceOnly"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "all", "none", "harp",
            "nn"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "all"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "none"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "harp", "nn"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "harp", "nn"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "harp"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "nn"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "pfg", "ue"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "hoho"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "haa"), stringSet);

    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pfg"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "ue"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "ue"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "zzz"), stringSet);

    // Modifies(stmt,var), get stmt
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "a");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "3", "5", "7", "10",
            "23"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "all");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "3", "5", "7", "10",
            "25", "27", "28"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "aone");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "1"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "d3");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "2"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "fire");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "3", "5", "7", "13",
            "17"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "fol");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "21"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "g2");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "22"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "good");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "19"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "h2");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "3", "5", "7", "9"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "haa");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "3", "5", "7", "13",
            "14", "16", "36"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "harp");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(9, "3", "5", "7", "10",
            "25", "27", "30", "31", "32"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "hoho");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "3", "5", "7", "13",
            "14", "16", "35"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "nn");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(9, "3", "5", "7", "10",
            "25", "27", "30", "31", "33"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "none");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "3", "5", "7", "10",
            "25", "27", "29"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "onceOnly");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "3", "5", "7", "10",
            "25", "26"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "pe");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "20"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "pfg");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "3", "5", "7", "10",
            "34", "37"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "t1");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "3", "5", "7", "8"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "this");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "4"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "ue");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "3", "5", "7", "10",
            "34", "38", "39"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "x");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "3", "5", "7", "13",
            "14", "15"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "x1");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "6"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "xe");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "3", "5", "7", "10",
            "18", "24"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "y");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "3", "5", "7", "11",
            "12"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "zzz");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "40"), stringSet);
}

void Test_30_PKB::test_modifies_progline_var()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    PKB *pkb = parser.get_pkb();
    set<int> intSet;
    SetWrapper<string> stringSet;

    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "aone"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "d3"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(21, "this", "x1", "t1", "h2",
            "a", "xe", "onceOnly", "all", "none", "harp", "nn", "pfg",
            "ue", "y", "x", "hoho", "haa", "fire", "good", "pe", "fol"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "this"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(19, "x1", "t1", "h2", "a",
            "xe", "onceOnly", "all", "none", "harp", "nn", "pfg", "ue",
            "y", "x", "hoho", "haa", "fire", "good", "pe"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "x1"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(16, "t1", "h2", "a", "xe",
            "onceOnly", "all", "none", "harp", "nn", "pfg", "ue",
            "y", "x", "hoho", "haa", "fire"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "t1"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "h2"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(9, "a", "xe", "onceOnly",
            "all", "none", "harp", "nn", "pfg", "ue"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "y"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "y"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "x", "hoho", "haa",
            "fire"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "x", "hoho", "haa"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "x"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "hoho", "haa"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "fire"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "xe"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "good"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pe"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "fol"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "g2"), stringSet);

    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "a"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "xe"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "onceOnly", "all",
            "none", "harp", "nn"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "onceOnly"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "all", "none", "harp",
            "nn"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "all"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "none"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "harp", "nn"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "harp", "nn"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "harp"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "nn"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "pfg", "ue"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "hoho"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "haa"), stringSet);

    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pfg"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "ue"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "ue"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "zzz"), stringSet);

    // Modifies(stmt,var), get stmt
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "a");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "3", "5", "7", "10",
            "23"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "all");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "3", "5", "7", "10",
            "25", "27", "28"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "aone");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "1"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "d3");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "2"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "fire");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "3", "5", "7", "13",
            "17"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "fol");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "21"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "g2");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "22"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "good");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "19"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "h2");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "3", "5", "7", "9"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "haa");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "3", "5", "7", "13",
            "14", "16", "36"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "harp");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(9, "3", "5", "7", "10",
            "25", "27", "30", "31", "32"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "hoho");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "3", "5", "7", "13",
            "14", "16", "35"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "nn");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(9, "3", "5", "7", "10",
            "25", "27", "30", "31", "33"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "none");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "3", "5", "7", "10",
            "25", "27", "29"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "onceOnly");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "3", "5", "7", "10",
            "25", "26"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "pe");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "20"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "pfg");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "3", "5", "7", "10",
            "34", "37"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "t1");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "3", "5", "7", "8"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "this");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "4"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "ue");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "3", "5", "7", "10",
            "34", "38", "39"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "x");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "3", "5", "7", "13",
            "14", "15"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "x1");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "6"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "xe");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "3", "5", "7", "10",
            "18", "24"), stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "y");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "3", "5", "7", "11",
            "12"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "zzz");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "40"), stringSet);
}

void Test_30_PKB::test_uses_procedure_var()
{
    const string& simpleProg = this->TEST_USES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    // Uses(Procedure,var), get vars
    stringSet = pkb->uses_X_Y_get_string_Y_from_string_X(ENT_PROC,
            ENT_VAR, "pOne");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(36, "a", "b", "ba1", "bab",
            "bba", "brave", "bx", "c", "cab", "christmas", "d3", "evil",
            "fire", "g", "g2", "ga", "gg", "ha", "haas", "merry", "no",
            "one", "p", "pf", "t", "ten", "tp", "true", "twice", "ue",
            "x", "xe", "xz", "y", "z", "zt1"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_string_X(ENT_PROC,
            ENT_VAR, "secProc");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(13, "b", "ba1", "bba", "c",
            "g", "gg", "no", "p", "pf", "true", "twice", "x", "xe"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_string_X(ENT_PROC,
            ENT_VAR, "thirdProc");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "christmas", "haas",
            "merry"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_string_X(ENT_PROC,
            ENT_VAR, "procFOUR");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "g", "no", "pf", "x"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_string_X(ENT_PROC,
            ENT_VAR, "execute");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_string_X(ENT_PROC,
            ENT_VAR, "useCall");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "g", "no", "pf", "x"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_string_X(ENT_PROC,
            ENT_VAR, "useOne");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "zzz"), stringSet);
    // Uses(Procedure,var), get procedure
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "a");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "b");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "pOne", "secProc"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "ba1");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "pOne", "secProc"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "bab");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "bba");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "pOne", "secProc"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "brave");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "bx");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "c");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "pOne", "secProc"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "cab");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "christmas");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "pOne", "thirdProc"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "d3");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "evil");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "fire");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "g");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "pOne", "secProc",
            "procFOUR", "useCall"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "g2");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "ga");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "gg");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "pOne", "secProc"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "ha");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "haas");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "pOne", "thirdProc"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "merry");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "pOne", "thirdProc"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "no");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "pOne", "secProc",
            "procFOUR", "useCall"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "one");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "p");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "pOne", "secProc"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "pf");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "pOne", "secProc",
            "procFOUR", "useCall"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "t");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "ten");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "tp");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "true");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "pOne", "secProc"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "twice");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "pOne", "secProc"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "ue");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "x");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "pOne", "secProc",
            "procFOUR", "useCall"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "xe");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "pOne", "secProc"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "xz");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "y");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "z");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "zt1");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pOne"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_X_from_string_Y(ENT_PROC,
            ENT_VAR, "zzz");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "useOne"), stringSet);
}

void Test_30_PKB::test_uses_assign_var()
{
    const string& simpleProg = this->TEST_USES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    // Uses(assign,var), get var
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "b", "c"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "bx", "d3"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "b", "ha"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "bab", "t"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "ga"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "ue", "y"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "y", "z"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "a", "fire"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "a", "cab"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "evil"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "zt1"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "g2", "y"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "brave", "xz"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "b", "c"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "true"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "bba"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "ba1"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "merry", "christmas"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "haas"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "g", "pf"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "no"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 43);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 44);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 45);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 46);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 47);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 48);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 49);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "zzz"), stringSet);

    // Uses(assign,var), get assign
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "a");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "17", "18"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "b");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "1", "6", "23"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "ba1");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "33"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "bab");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "8"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "bba");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "29"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "brave");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "22"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "bx");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "4"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "c");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "1", "23"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "cab");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "18"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "christmas");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "35"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "d3");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "4"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "evil");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "19"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "fire");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "17"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "g");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "37"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "g2");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "21"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "ga");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "9"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "gg");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "ha");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "6"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "haas");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "36"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "merry");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "35"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "no");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "39"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "one");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "p");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "pf");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "37"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "t");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "8"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "ten");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "tp");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "true");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "26"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "twice");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "ue");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "12"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "x");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "xe");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "xz");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "22"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "y");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "12", "15", "21"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "z");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "15"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "zt1");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "20"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_ASSIGN,
            ENT_VAR, "zzz");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "49"), stringSet);
}

void Test_30_PKB::test_uses_call_var()
{
    const string& simpleProg = this->TEST_USES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    // Uses(call,var), get var
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(13, "b", "ba1", "bba", "c",
            "g", "gg", "no", "p", "pf", "true", "twice", "x", "xe"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "christmas", "haas",
            "merry"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "g", "no", "pf", "x"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 43);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 44);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 45);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 46);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 47);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 48);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "g", "no", "pf", "x"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 49);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);

    // Uses(call,var), get call
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "a");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "b");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "10"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "ba1");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "10"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "bab");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "bba");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "10"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "brave");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "bx");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "c");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "10"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "cab");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "christmas");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "16"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "d3");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "evil");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "fire");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "g");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "10", "34", "48"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "g2");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "ga");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "gg");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "10"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "ha");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "haas");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "16"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "merry");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "16"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "no");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "10", "34", "48"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "one");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "p");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "10"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "pf");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "10", "34", "48"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "t");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "ten");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "tp");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "true");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "10"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "twice");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "10"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "ue");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "x");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "10", "34", "48"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "xe");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "10"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "xz");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "y");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "z");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "zt1");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_CALL,
            ENT_VAR, "zzz");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
}

void Test_30_PKB::test_uses_if_var()
{
    const string& simpleProg = this->TEST_USES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    // Uses(if,var), get var
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(29, "a", "b", "ba1", "bab",
            "bba", "c", "cab", "christmas", "fire", "g", "g2", "ga",
            "gg", "haas", "merry", "no", "one", "p", "pf", "t", "ten",
            "tp", "true", "twice", "ue", "x", "xe", "y", "z"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(9, "a", "christmas", "fire",
            "haas", "merry", "one", "tp", "y", "z"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "ba1", "bba", "p",
            "twice", "xe"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "ba1", "xe"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 43);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 44);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 45);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 46);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 47);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 48);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 49);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);

    // Uses(if,var), get if
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "a");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "7", "13"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "b");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "ba1");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "7", "27", "31"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "bab");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "bba");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "7", "27"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "brave");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "bx");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "c");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "cab");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "christmas");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "7", "13"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "d3");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "evil");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "fire");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "7", "13"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "g");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "g2");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "ga");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "gg");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "ha");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "haas");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "7", "13"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "merry");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "7", "13"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "no");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "one");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "7", "13"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "p");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "7", "27"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "pf");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "t");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "ten");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "tp");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "7", "13"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "true");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "twice");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "7", "27"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "ue");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "x");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "7"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "xe");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "7", "27", "31"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "xz");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "y");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "7", "13"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "z");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "7", "13"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "zt1");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_IF,
            ENT_VAR, "zzz");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
}

void Test_30_PKB::test_uses_while_var()
{
    const string& simpleProg = this->TEST_USES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    // Uses(while,var), get var
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(34, "a", "b", "ba1", "bab",
            "bba", "bx", "c", "cab", "christmas", "d3", "evil", "fire",
            "g", "g2", "ga", "gg", "ha", "haas", "merry", "no", "one",
            "p", "pf", "t", "ten", "tp", "true", "twice", "ue", "x",
            "xe", "y", "z", "zt1"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(32, "a", "b", "ba1", "bab",
            "bba", "c", "cab", "christmas", "evil", "fire", "g", "g2",
            "ga", "gg", "ha", "haas", "merry", "no", "one", "p", "pf",
            "t", "ten", "tp", "true", "twice", "ue", "x", "xe", "y",
            "z", "zt1"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "ten", "ue", "y"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "christmas", "haas",
            "merry", "one", "y", "z"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "ba1", "bba", "gg", "p",
            "true", "twice", "xe"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "ba1", "p", "xe"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "no", "x"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 43);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 44);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 45);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 46);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 47);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 48);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 49);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);

    // Uses(while,var), get while
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "a");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "5"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "b");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "5"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "ba1");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "3", "5", "25", "30"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "bab");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "5"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "bba");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "25"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "brave");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "bx");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "c");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "5"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "cab");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "5"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "christmas");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "14"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "d3");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "evil");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "5"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "fire");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "5"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "g");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "5"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "g2");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "5"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "ga");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "5"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "gg");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "25"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "ha");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "5"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "haas");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "14"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "merry");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "14"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "no");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "38"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "one");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "14"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "p");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "3", "5", "25", "30"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "pf");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "5"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "t");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "5"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "ten");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "11"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "tp");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "5"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "true");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "25"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "twice");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "25"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "ue");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "11"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "x");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "38"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "xe");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "3", "5", "25", "30"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "xz");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "y");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "3", "5", "11", "14"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "z");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "14"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "zt1");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "5"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_WHILE,
            ENT_VAR, "zzz");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
}

void Test_30_PKB::test_uses_stmt_var()
{
    const string& simpleProg = this->TEST_USES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    // Uses(stmt,var), get var
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "b", "c"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(34, "a", "b", "ba1", "bab",
            "bba", "bx", "c", "cab", "christmas", "d3", "evil", "fire",
            "g", "g2", "ga", "gg", "ha", "haas", "merry", "no", "one",
            "p", "pf", "t", "ten", "tp", "true", "twice", "ue", "x",
            "xe", "y", "z", "zt1"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "bx", "d3"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(32, "a", "b", "ba1", "bab",
            "bba", "c", "cab", "christmas", "evil", "fire", "g", "g2",
            "ga", "gg", "ha", "haas", "merry", "no", "one", "p", "pf",
            "t", "ten", "tp", "true", "twice", "ue", "x", "xe", "y",
            "z", "zt1"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "b", "ha"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(29, "a", "b", "ba1", "bab",
            "bba", "c", "cab", "christmas", "fire", "g", "g2", "ga",
            "gg", "haas", "merry", "no", "one", "p", "pf", "t", "ten",
            "tp", "true", "twice", "ue", "x", "xe", "y", "z"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "bab", "t"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "ga"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(13, "b", "ba1", "bba", "c",
            "g", "gg", "no", "p", "pf", "true", "twice", "x", "xe"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "ten", "ue", "y"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "ue", "y"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(9, "a", "christmas", "fire",
            "haas", "merry", "one", "tp", "y", "z"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "christmas", "haas",
            "merry", "one", "y", "z"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "y", "z"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "christmas", "haas",
            "merry"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "a", "fire"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "a", "cab"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "evil"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "zt1"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "g2", "y"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "brave", "xz"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "b", "c"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "ba1", "bba", "gg", "p",
            "true", "twice", "xe"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "true"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "ba1", "bba", "p",
            "twice", "xe"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "bba"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "ba1", "p", "xe"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "ba1", "xe"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "ba1"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "g", "no", "pf", "x"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "merry", "christmas"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "haas"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "g", "pf"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "no", "x"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "no"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 43);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 44);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 45);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 46);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 47);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 48);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "g", "no", "pf", "x"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_STMT,
            ENT_VAR, 49);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "zzz"), stringSet);

    // Uses(stmt,var), get stmt
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "a");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "3", "5", "7", "13",
            "17", "18"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "b");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "1", "3", "5", "6", "7",
            "10", "23"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "ba1");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(9, "3", "5", "7", "10",
            "25", "27", "30", "31", "33"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "bab");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "3", "5", "7", "8"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "bba");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "3", "5", "7", "10", "25",
            "27", "29"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "brave");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "22"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "bx");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "4"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "c");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "1", "3", "5", "7", "10",
            "23"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "cab");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "3", "5", "7", "18"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "christmas");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "3", "5", "7", "13",
            "14", "16", "35"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "d3");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "4"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "evil");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "19"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "fire");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "3", "5", "7", "13",
            "17"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "g");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "3", "5", "7", "10",
            "34", "37", "48"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "g2");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "3", "5", "7", "21"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "ga");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "3", "5", "7", "9"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "gg");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "3", "5", "7", "10",
            "25"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "ha");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "6"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "haas");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "3", "5", "7", "13",
            "14", "16", "36"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "merry");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "3", "5", "7", "13",
            "14", "16", "35"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "no");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(8, "3", "5", "7", "10",
            "34", "38", "39", "48"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "one");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "3", "5", "7", "13",
            "14"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "p");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "3", "5", "7", "10",
            "25", "27", "30"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "pf");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "3", "5", "7", "10",
            "34", "37", "48"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "t");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "3", "5", "7", "8"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "ten");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "3", "5", "7", "11"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "tp");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "3", "5", "7", "13"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "true");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "3", "5", "7", "10",
            "25", "26"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "twice");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "3", "5", "7", "10",
            "25", "27"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "ue");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "3", "5", "7", "11",
            "12"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "x");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "3", "5", "7", "10",
            "34", "38", "48"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "xe");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(8, "3", "5", "7", "10",
            "25", "27", "30", "31"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "xz");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "22"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "y");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(9, "3", "5", "7", "11",
            "12", "13", "14", "15", "21"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "z");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "3", "5", "7", "13",
            "14", "15"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "zt1");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "20"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_STMT,
            ENT_VAR, "zzz");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "49"), stringSet);
}

void Test_30_PKB::test_uses_progline_var()
{
    const string& simpleProg = this->TEST_USES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    // Uses(prog_line,var), get var
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "b", "c"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(34, "a", "b", "ba1", "bab",
            "bba", "bx", "c", "cab", "christmas", "d3", "evil", "fire",
            "g", "g2", "ga", "gg", "ha", "haas", "merry", "no", "one",
            "p", "pf", "t", "ten", "tp", "true", "twice", "ue", "x",
            "xe", "y", "z", "zt1"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "bx", "d3"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(32, "a", "b", "ba1", "bab",
            "bba", "c", "cab", "christmas", "evil", "fire", "g", "g2",
            "ga", "gg", "ha", "haas", "merry", "no", "one", "p", "pf",
            "t", "ten", "tp", "true", "twice", "ue", "x", "xe", "y",
            "z", "zt1"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "b", "ha"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(29, "a", "b", "ba1", "bab",
            "bba", "c", "cab", "christmas", "fire", "g", "g2", "ga",
            "gg", "haas", "merry", "no", "one", "p", "pf", "t", "ten",
            "tp", "true", "twice", "ue", "x", "xe", "y", "z"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "bab", "t"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "ga"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(13, "b", "ba1", "bba", "c",
            "g", "gg", "no", "p", "pf", "true", "twice", "x", "xe"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "ten", "ue", "y"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "ue", "y"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(9, "a", "christmas", "fire",
            "haas", "merry", "one", "tp", "y", "z"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "christmas", "haas",
            "merry", "one", "y", "z"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "y", "z"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "christmas", "haas",
            "merry"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 17);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "a", "fire"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 18);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "a", "cab"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "evil"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 20);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "zt1"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 21);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "g2", "y"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "brave", "xz"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "b", "c"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "ba1", "bba", "gg", "p",
            "true", "twice", "xe"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "true"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "ba1", "bba", "p",
            "twice", "xe"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "bba"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "ba1", "p", "xe"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "ba1", "xe"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "ba1"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "g", "no", "pf", "x"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "merry", "christmas"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "haas"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "g", "pf"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "no", "x"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "no"), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 40);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 41);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 42);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 43);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 44);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 45);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 46);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 47);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(), stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 48);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "g", "no", "pf", "x"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_string_Y_from_int_X(ENT_PROGLINE,
            ENT_VAR, 49);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "zzz"), stringSet);

    // Uses(prog_line,var), get prog_line
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "a");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "3", "5", "7", "13",
            "17", "18"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "b");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "1", "3", "5", "6", "7",
            "10", "23"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "ba1");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(9, "3", "5", "7", "10",
            "25", "27", "30", "31", "33"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "bab");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "3", "5", "7", "8"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "bba");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "3", "5", "7", "10", "25",
            "27", "29"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "brave");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "22"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "bx");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "4"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "c");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "1", "3", "5", "7", "10",
            "23"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "cab");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "3", "5", "7", "18"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "christmas");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "3", "5", "7", "13",
            "14", "16", "35"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "d3");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "3", "4"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "evil");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "19"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "fire");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "3", "5", "7", "13",
            "17"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "g");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "3", "5", "7", "10",
            "34", "37", "48"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "g2");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "3", "5", "7", "21"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "ga");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "3", "5", "7", "9"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "gg");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "3", "5", "7", "10",
            "25"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "ha");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "6"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "haas");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "3", "5", "7", "13",
            "14", "16", "36"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "merry");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "3", "5", "7", "13",
            "14", "16", "35"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "no");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(8, "3", "5", "7", "10",
            "34", "38", "39", "48"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "one");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "3", "5", "7", "13",
            "14"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "p");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "3", "5", "7", "10",
            "25", "27", "30"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "pf");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "3", "5", "7", "10",
            "34", "37", "48"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "t");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "3", "5", "7", "8"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "ten");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "3", "5", "7", "11"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "tp");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "3", "5", "7", "13"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "true");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "3", "5", "7", "10",
            "25", "26"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "twice");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "3", "5", "7", "10",
            "25", "27"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "ue");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "3", "5", "7", "11",
            "12"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "x");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "3", "5", "7", "10",
            "34", "38", "48"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "xe");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(8, "3", "5", "7", "10",
            "25", "27", "30", "31"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "xz");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "22"), stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "y");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(9, "3", "5", "7", "11",
            "12", "13", "14", "15", "21"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "z");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(6, "3", "5", "7", "13",
            "14", "15"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "zt1");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "3", "5", "20"),
            stringSet);
    stringSet = pkb->uses_X_Y_get_int_X_from_string_Y(ENT_PROGLINE,
            ENT_VAR, "zzz");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "49"), stringSet);
}


void Test_30_PKB::test_follows()
{
    const string& simpleProg = " procedure roses {\
                                    rose = red;\
                                    violet = blue;\
                                    call flower;\
                                    while love {\
                                        rose = 99;\
                                        if rose then {\
                                        rose = 999;}\
                                    else{\
                                        rose = 0;}\
                                    violet = 298;\
	                                call flower;\
	                                violet = 425;}\
                                    while choc {\
                                        choc = 0;\
	                                while rose {\
	                                    rose = 3;}\
	                                if red then {\
                                        green = 777;}\
                                    else{\
	                                    green = 888;}\
                                        if green then {\
                                        red = 123;}\
                                    else{\
	                                    red = 29384;}\
	                                while blue {\
	                                    blue = blue + 4;}\
	                                call flower;\
	                                call flower;\
	                                if blue then {\
                                        green = red;}\
                                    else{\
	                                    red = blue;}}}\
                                    procedure flower{\
                                        while green {\
	                                    red = 0;}\
                                        blue = 234;}";
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());

     CPPUNIT_ASSERT_EQUAL(true,pkb->follows_query_int_X_int_Y(ENT_ASSIGN,1,
        ENT_ASSIGN,2));
    stringSet = pkb->follows_X_Y_get_int_X_from_int_Y(ENT_ASSIGN,ENT_ASSIGN,2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "1"), stringSet);
    stringSet = pkb->follows_X_Y_get_int_Y_from_int_X(ENT_ASSIGN,ENT_ASSIGN,1);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "2"), stringSet);

    CPPUNIT_ASSERT_EQUAL(true,pkb->follows_query_int_X_int_Y(ENT_ASSIGN,2,
        ENT_CALL,3));
    stringSet = pkb->follows_X_Y_get_int_Y_from_int_X(ENT_ASSIGN,ENT_CALL,2);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"), stringSet);
    stringSet = pkb->follows_X_Y_get_int_X_from_int_Y(ENT_ASSIGN,ENT_CALL,3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "2"), stringSet);

    CPPUNIT_ASSERT_EQUAL(true,pkb->follows_query_int_X_int_Y(ENT_CALL,3,
        ENT_WHILE,4));
    stringSet = pkb->follows_X_Y_get_int_Y_from_int_X(ENT_CALL,ENT_WHILE,3);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "4"), stringSet);
    stringSet = pkb->follows_X_Y_get_int_X_from_int_Y(ENT_CALL,ENT_WHILE,4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "3"), stringSet);

    CPPUNIT_ASSERT_EQUAL(false,pkb->follows_query_int_X_int_Y(ENT_WHILE,4,
        ENT_ASSIGN,5));
    CPPUNIT_ASSERT_EQUAL(true,pkb->follows_query_int_X_int_Y(ENT_WHILE,4,
        ENT_WHILE,12));
    stringSet = pkb->follows_X_Y_get_int_Y_from_int_X(ENT_WHILE,ENT_WHILE,4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "12"), stringSet);
    stringSet = pkb->follows_X_Y_get_int_X_from_int_Y(ENT_WHILE,ENT_WHILE,12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "4"), stringSet);

    CPPUNIT_ASSERT_EQUAL(true,pkb->follows_query_int_X_int_Y(ENT_ASSIGN,5,
        ENT_IF,6));
    stringSet = pkb->follows_X_Y_get_int_Y_from_int_X(ENT_ASSIGN,ENT_IF,5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "6"), stringSet);
    stringSet = pkb->follows_X_Y_get_int_X_from_int_Y(ENT_ASSIGN,ENT_IF,6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "5"), stringSet);

    CPPUNIT_ASSERT_EQUAL(false,pkb->follows_query_int_X_int_Y(ENT_IF,6,
        ENT_ASSIGN,7));
    CPPUNIT_ASSERT_EQUAL(true,pkb->follows_query_int_X_int_Y(ENT_IF,6,
        ENT_ASSIGN,9));
    stringSet = pkb->follows_X_Y_get_int_Y_from_int_X(ENT_IF,ENT_ASSIGN,6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "9"), stringSet);
    stringSet = pkb->follows_X_Y_get_int_X_from_int_Y(ENT_IF,ENT_ASSIGN,9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "6"), stringSet);

    CPPUNIT_ASSERT_EQUAL(false,pkb->follows_query_int_X_int_Y(ENT_ASSIGN,7,
        ENT_ASSIGN,8));
    CPPUNIT_ASSERT_EQUAL(false,pkb->follows_query_int_X_int_Y(ENT_ASSIGN,8,
        ENT_ASSIGN,9));

    CPPUNIT_ASSERT_EQUAL(true,pkb->follows_query_int_X_int_Y(ENT_ASSIGN,9,
        ENT_CALL,10));
    stringSet = pkb->follows_X_Y_get_int_Y_from_int_X(ENT_ASSIGN,ENT_CALL,9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "10"), stringSet);
    stringSet = pkb->follows_X_Y_get_int_X_from_int_Y(ENT_ASSIGN,ENT_CALL,10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "9"), stringSet);

    CPPUNIT_ASSERT_EQUAL(true,pkb->follows_query_int_X_int_Y(ENT_CALL,10,
        ENT_ASSIGN,11));
    stringSet = pkb->follows_X_Y_get_int_Y_from_int_X(ENT_CALL,ENT_ASSIGN,10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "11"), stringSet);
    stringSet = pkb->follows_X_Y_get_int_X_from_int_Y(ENT_CALL,ENT_ASSIGN,11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "10"), stringSet);

    CPPUNIT_ASSERT_EQUAL(false,pkb->follows_query_int_X_int_Y(ENT_ASSIGN,11,
        ENT_WHILE,12));

    CPPUNIT_ASSERT_EQUAL(false,pkb->follows_query_int_X_int_Y(ENT_WHILE,12,
        ENT_ASSIGN,13));

    CPPUNIT_ASSERT_EQUAL(true,pkb->follows_query_int_X_int_Y(ENT_ASSIGN,13,
        ENT_WHILE,14));
    stringSet = pkb->follows_X_Y_get_int_Y_from_int_X(ENT_ASSIGN,ENT_WHILE,13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "14"), stringSet);
    stringSet = pkb->follows_X_Y_get_int_X_from_int_Y(ENT_ASSIGN,ENT_WHILE,14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "13"), stringSet);

    CPPUNIT_ASSERT_EQUAL(false,pkb->follows_query_int_X_int_Y(ENT_WHILE,14,
        ENT_ASSIGN,15));
    CPPUNIT_ASSERT_EQUAL(true,pkb->follows_query_int_X_int_Y(ENT_WHILE,14,
        ENT_IF,16));
    stringSet = pkb->follows_X_Y_get_int_Y_from_int_X(ENT_WHILE,ENT_IF,14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "16"), stringSet);
    stringSet = pkb->follows_X_Y_get_int_X_from_int_Y(ENT_WHILE,ENT_IF,16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "14"), stringSet);

    CPPUNIT_ASSERT_EQUAL(false,pkb->follows_query_int_X_int_Y(ENT_ASSIGN,15,
        ENT_IF,16));

    CPPUNIT_ASSERT_EQUAL(false,pkb->follows_query_int_X_int_Y(ENT_IF,16,
        ENT_ASSIGN,17));
    CPPUNIT_ASSERT_EQUAL(true,pkb->follows_query_int_X_int_Y(ENT_IF,16,
        ENT_IF,19));
    stringSet = pkb->follows_X_Y_get_int_Y_from_int_X(ENT_IF,ENT_IF,16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "19"), stringSet);
    stringSet = pkb->follows_X_Y_get_int_X_from_int_Y(ENT_IF,ENT_IF,19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "16"), stringSet);

    CPPUNIT_ASSERT_EQUAL(false,pkb->follows_query_int_X_int_Y(ENT_ASSIGN,17,
        ENT_ASSIGN,18));

    CPPUNIT_ASSERT_EQUAL(false,pkb->follows_query_int_X_int_Y(ENT_ASSIGN,18,
        ENT_IF,19));

    CPPUNIT_ASSERT_EQUAL(false,pkb->follows_query_int_X_int_Y(ENT_IF,19,
        ENT_ASSIGN,20));
    CPPUNIT_ASSERT_EQUAL(true,pkb->follows_query_int_X_int_Y(ENT_IF,19,
        ENT_WHILE,22));
    stringSet = pkb->follows_X_Y_get_int_Y_from_int_X(ENT_IF,ENT_WHILE,19);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "22"), stringSet);
    stringSet = pkb->follows_X_Y_get_int_X_from_int_Y(ENT_IF,ENT_WHILE,22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "19"), stringSet);

    CPPUNIT_ASSERT_EQUAL(false,pkb->follows_query_int_X_int_Y(ENT_ASSIGN,20,
        ENT_ASSIGN,21));

    CPPUNIT_ASSERT_EQUAL(false,pkb->follows_query_int_X_int_Y(ENT_ASSIGN,21,
        ENT_WHILE,22));

    CPPUNIT_ASSERT_EQUAL(false,pkb->follows_query_int_X_int_Y(ENT_WHILE,22,
        ENT_ASSIGN ,23));
    CPPUNIT_ASSERT_EQUAL(true,pkb->follows_query_int_X_int_Y(ENT_WHILE,22,
        ENT_CALL,24));
    stringSet = pkb->follows_X_Y_get_int_Y_from_int_X(ENT_WHILE,ENT_CALL,22);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "24"), stringSet);
    stringSet = pkb->follows_X_Y_get_int_X_from_int_Y(ENT_WHILE,ENT_CALL,24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "22"), stringSet);

    CPPUNIT_ASSERT_EQUAL(false,pkb->follows_query_int_X_int_Y(ENT_ASSIGN,23,
        ENT_CALL,24));

    CPPUNIT_ASSERT_EQUAL(true,pkb->follows_query_int_X_int_Y(ENT_CALL,24,
        ENT_CALL,25));
    stringSet = pkb->follows_X_Y_get_int_Y_from_int_X(ENT_CALL,ENT_CALL,24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "25"), stringSet);
    stringSet = pkb->follows_X_Y_get_int_X_from_int_Y(ENT_CALL,ENT_CALL,25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "24"), stringSet);

    CPPUNIT_ASSERT_EQUAL(true,pkb->follows_query_int_X_int_Y(ENT_CALL,25,
        ENT_IF,26));
    stringSet = pkb->follows_X_Y_get_int_Y_from_int_X(ENT_CALL,ENT_IF,25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "26"), stringSet);
    stringSet = pkb->follows_X_Y_get_int_X_from_int_Y(ENT_CALL,ENT_IF,26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "25"), stringSet);

    CPPUNIT_ASSERT_EQUAL(false,pkb->follows_query_int_X_int_Y(ENT_IF,26,
        ENT_ASSIGN,27));

    CPPUNIT_ASSERT_EQUAL(false,pkb->follows_query_int_X_int_Y(ENT_ASSIGN,27,
        ENT_ASSIGN,28));

    CPPUNIT_ASSERT_EQUAL(false,pkb->follows_query_int_X_int_Y(ENT_WHILE,29,
        ENT_ASSIGN,30));
    CPPUNIT_ASSERT_EQUAL(true,pkb->follows_query_int_X_int_Y(ENT_WHILE,29,
        ENT_ASSIGN,31));
    stringSet = pkb->follows_X_Y_get_int_Y_from_int_X(ENT_WHILE,ENT_ASSIGN,29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "31"), stringSet);
    stringSet = pkb->follows_X_Y_get_int_X_from_int_Y(ENT_WHILE,ENT_ASSIGN,31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "29"), stringSet);

    CPPUNIT_ASSERT_EQUAL(false,pkb->follows_query_int_X_int_Y(ENT_ASSIGN,27,
        ENT_ASSIGN,28));

    CPPUNIT_ASSERT_EQUAL(false,pkb->follows_query_int_X_int_Y(ENT_ASSIGN,30,
        ENT_ASSIGN,31));

}

void Test_30_PKB::test_has_assign()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(1));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(2));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(3));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(4));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(5));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(6));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(7));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(8));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(9));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(10));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(11));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(12));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(13));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(14));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(15));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(16));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(17));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(18));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(19));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(20));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(21));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(22));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(23));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(24));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(25));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(26));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(27));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(28));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(29));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(30));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(31));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(32));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(33));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(34));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(35));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(36));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(37));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(38));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(39));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_assign(40));
    // Out of range cases
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(0));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(-61));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(41));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_assign(50));
}

void Test_30_PKB::test_has_call()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(1));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(2));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(3));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(4));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(5));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(6));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(7));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(8));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(9));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_call(10));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(11));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(12));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(13));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(14));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(15));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_call(16));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(17));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(18));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(19));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(20));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(21));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(22));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(23));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(24));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(25));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(26));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(27));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(28));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(29));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(30));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(31));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(32));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(33));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_call(34));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(35));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(36));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(37));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(38));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(39));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(40));
    // Out of range cases
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(0));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(-61));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(41));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_call(50));
}

void Test_30_PKB::test_has_if()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(1));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(2));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(3));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(4));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(5));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(6));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_if(7));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(8));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(9));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(10));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(11));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(12));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_if(13));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(14));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(15));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(16));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(17));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(18));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(19));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(20));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(21));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(22));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(23));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(24));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(25));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(26));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_if(27));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(28));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(29));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(30));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_if(31));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(32));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(33));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(34));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(35));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(36));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(37));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(38));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(39));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(40));
    // Out of range cases
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(0));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(-61));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(41));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_if(50));
}

void Test_30_PKB::test_has_while()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(1));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(2));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_while(3));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(4));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_while(5));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(6));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(7));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(8));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(9));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(10));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_while(11));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(12));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(13));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_while(14));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(15));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(16));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(17));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(18));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(19));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(20));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(21));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(22));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(23));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(24));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_while(25));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(26));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(27));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(28));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(29));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_while(30));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(31));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(32));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(33));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(34));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(35));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(36));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(37));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_while(38));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(39));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(40));
    // Out of range cases
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(0));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(-61));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(41));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_while(50));
}

void Test_30_PKB::test_has_stmt()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(1));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(2));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(3));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(4));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(5));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(6));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(7));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(8));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(9));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(10));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(11));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(12));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(13));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(14));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(15));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(16));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(17));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(18));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(19));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(20));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(21));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(22));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(23));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(24));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(25));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(26));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(27));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(28));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(29));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(30));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(31));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(32));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(33));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(34));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(35));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(36));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(37));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(38));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(39));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmt(40));
    // Out of range cases
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmt(0));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmt(-61));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmt(41));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmt(50));
}

void Test_30_PKB::test_has_progline()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(1));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(2));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(3));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(4));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(5));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(6));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(7));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(8));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(9));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(10));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(11));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(12));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(13));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(14));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(15));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(16));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(17));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(18));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(19));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(20));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(21));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(22));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(23));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(24));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(25));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(26));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(27));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(28));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(29));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(30));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(31));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(32));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(33));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(34));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(35));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(36));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(37));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(38));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(39));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_progline(40));
    // Out of range cases
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_progline(0));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_progline(-61));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_progline(41));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_progline(50));
}

void Test_30_PKB::test_has_stmtLst()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(1));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(2));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(3));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(4));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(5));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(6));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(7));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(8));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(9));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(10));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(11));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(12));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(13));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(14));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(15));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(16));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(17));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(18));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(19));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(20));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(21));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(22));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(23));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(24));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(25));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(26));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(27));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(28));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(29));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(30));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(31));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(32));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(33));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(34));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(35));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(36));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(37));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(38));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(39));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_stmtLst(40));
    // Out of range cases
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(0));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(-61));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(41));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_stmtLst(50));
}

void Test_30_PKB::test_has_const()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_const(2));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_const(3));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_const(5));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_const(7));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_const(41));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_const(73));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_const(512));
    // negative tests
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_const(0));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_const(1000000));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_const(-15216));
}

void Test_30_PKB::test_has_variable()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());
    // variables: a, aone, all, b, ba1, bab, bba, brave, bx, c
    // cab, christmas, d3, evil, fire, fol, g, g2,
    // ga, gg, good, ha, haa, haas, harp, h2, hoho, merry
    // nn, no, none, onceOnly, one, p, pe, pf, pfg, t, t1, ten
    // this, tp, true, twice, ue, x, x1, xe, xz, y, z, zt1, zzz
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("a"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("aone"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("all"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("b"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("ba1"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("bab"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("bba"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("brave"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("bx"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("c"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("cab"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("christmas"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("d3"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("evil"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("fire"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("fol"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("g"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("g2"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("ga"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("gg"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("good"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("ha"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("haa"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("haas"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("harp"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("h2"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("hoho"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("merry"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("nn"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("no"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("none"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("onceOnly"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("one"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("p"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("pe"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("pf"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("pfg"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("t"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("t1"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("ten"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("this"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("tp"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("true"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("twice"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("ue"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("x"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("x1"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("xe"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("xz"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("y"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("z"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("zt1"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_variable("zzz"));
    // negative cases
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_variable("NOSUCHVAR"));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_variable("Phoenix"));
}

void Test_30_PKB::test_has_procedure()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());

    CPPUNIT_ASSERT_EQUAL(true, pkb->has_procedure("pOne"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_procedure("secProc"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_procedure("thirdProc"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_procedure("procFOUR"));
    CPPUNIT_ASSERT_EQUAL(true, pkb->has_procedure("cleanUP"));
    // negative tests
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_procedure("missingProc"));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_procedure("Pone"));
    CPPUNIT_ASSERT_EQUAL(false, pkb->has_procedure("main"));
}

void Test_30_PKB::test_modifies_query_string_X_string_Y()
{
    const string& simpleProg = this->TEST_MODIFIES_SIMPLE_PROG;
    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());

    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "pOne",
                    ENT_VAR, "a"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "pOne",
                    ENT_VAR, "all"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "pOne",
                    ENT_VAR, "aone"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "pOne",
                    ENT_VAR, "d3"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "pOne",
                    ENT_VAR, "fire"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "pOne",
                    ENT_VAR, "fol"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "pOne",
                    ENT_VAR, "g2"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "pOne",
                    ENT_VAR, "good"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "pOne",
                    ENT_VAR, "h2"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "pOne",
                    ENT_VAR, "haa"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "pOne",
                    ENT_VAR, "harp"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "pOne",
                    ENT_VAR, "hoho"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "pOne",
                    ENT_VAR, "nn"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "pOne",
                    ENT_VAR, "onceOnly"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "pOne",
                    ENT_VAR, "pe"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "pOne",
                    ENT_VAR, "pfg"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "pOne",
                    ENT_VAR, "t1"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "pOne",
                    ENT_VAR, "this"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "pOne",
                    ENT_VAR, "ue"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "pOne",
                    ENT_VAR, "x"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "pOne",
                    ENT_VAR, "x1"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "pOne",
                    ENT_VAR, "xe"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "pOne",
                    ENT_VAR, "y"));

    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "secProc",
                    ENT_VAR, "a"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "secProc",
                    ENT_VAR, "all"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "secProc",
                    ENT_VAR, "harp"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "secProc",
                    ENT_VAR, "nn"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "secProc",
                    ENT_VAR, "none"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "secProc",
                    ENT_VAR, "onceOnly"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "secProc",
                    ENT_VAR, "pfg"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "secProc",
                    ENT_VAR, "ue"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "secProc",
                    ENT_VAR, "xe"));

    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "thirdProc",
                    ENT_VAR, "haa"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "thirdProc",
                    ENT_VAR, "hoho"));

    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "procFOUR",
                    ENT_VAR, "pfg"));
    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "secProc",
                    ENT_VAR, "ue"));

    CPPUNIT_ASSERT_EQUAL(true,
            pkb->modifies_query_string_X_string_Y(ENT_PROC, "cleanUP",
                    ENT_VAR, "zzz"));
}