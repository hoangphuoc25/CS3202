#include <cstdarg>
#include <string>
#include <map>
#include <memory>
#include "TestPKB.h"
#include "../SPA/Parser.h"
#include "../SPA/PKB.h"
#include "../SPA/SetWrapper.h"

using std::auto_ptr;
using std::string;
using std::map;


void TestPKB::setUp() {}
void TestPKB::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(TestPKB);

// Test banks
void TestPKB::test_one(){
    
    Parser p;
    p = Parser("TestPKB\\assign1.txt",FROMFILE);
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
void TestPKB::test_two(){


}

void TestPKB::test_three(){

}

void TestPKB::test_retrieve_all_X()
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

void TestPKB::test_modifies()
{
    string simpleProg =
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
         }";
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    PKB *pkb = parser.get_pkb();
    set<int> intSet;
    set<string> S;
    SetWrapper<string> stringSet;

    // pOne modifies:
    // aone, d3, this, x1, t1, h2, a, xe, onceOnly, all, none, harp, nn
    // pfg, ue, y, x, hoho, haa, fire, good, pe, fol, g2
    //
    // secProc modifies:
    // a, xe, onceOnly, all, none, harp, nn, pfg, ue
    //
    // thirdProc modifies:
    // hoho, haa
    //
    // procFOUR modifies:
    // pfg, ue
    //
    // stmt 1 [assign] - aone
    // stmt 2 [assign] - d3
    // stmt 3 [while] - this, x1, t1, h2, a, xe, onceOnly, all, none,
    //                  harp, nn, pfg, ue, y, x, hoho, haa, fire, good,
    //                  pe, fol
    // stmt 4 [assign] - this
    // stmt 5 [while] - x1, t1, h2, a, xe, onceOnly, all, none, harp, nn,
    //                  pfg, ue, y, x, hoho, haa, fire, good, pe
    // stmt 6 [assign] - x1
    // stmt 7 [if] - t1, h2, a, xe, onceOnly, all, none, harp, nn, pfg, ue,
    //               y, x, hoho, haa, fire
    // stmt 8 [assign] - t1
    // stmt 9 [assign] - h2
    // stmt 10 [call] - a, xe, onceOnly, all, none, harp, nn, pfg, ue
    // stmt 11 [while] - y
    // stmt 12 [assign] - y
    // stmt 13 [if] - x, hoho, haa, fire
    // stmt 14 [while] - x, hoho, haa
    // stmt 15 [assign] - x
    // stmt 16 [call] - hoho, haa
    // stmt 17 [assign] - fire
    // stmt 18 [assign] - xe
    // stmt 19 [assign] - good
    // stmt 20 [assign] - pe
    // stmt 21 [assign] - fol
    // stmt 22 [assign] - g2

    // secProc
    // stmt 23 [assign] - a
    // stmt 24 [assign] - xe
    // stmt 25 [while] - onceOnly, all, none, harp, nn
    // stmt 26 [assign] - onceOnly
    // stmt 27 [if] - all, none, harp, nn
    // stmt 28 [assign] - all
    // stmt 29 [assign] - none
    // stmt 30 [while] - harp, nn
    // stmt 31 [if] - harp, nn
    // stmt 32 [assign] - harp
    // stmt 33 [assign] - nn
    // stmt 34 [call] - pfg, ue

    // thirdProc
    // stmt 35 [assign] - hoho
    // stmt 36 [assign] - haa

    // procFour
    // stmt 37 [assign] - pfg
    // stmt 38 [while] - ue
    // stmt 39 [assign] - ue
    S = pkb->get_var_proc_modifies("pOne");
    stringSet = SetWrapper<string>(S);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(24, "aone", "d3", "this",
            "x1", "t1", "h2", "a", "xe", "onceOnly", "all", "none",
            "harp", "nn", "pfg", "ue", "y", "x", "hoho", "haa", "fire",
            "good", "pe", "fol", "g2"),
            stringSet);
    S = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 1);
    stringSet = SetWrapper<string>(S);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "aone"), stringSet);
    S = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 2);
    stringSet = SetWrapper<string>(S);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "d3"), stringSet);
    S = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 3);
    stringSet = SetWrapper<string>(S);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(21, "this", "x1", "t1",
            "h2", "a", "xe", "onceOnly", "all", "none", "harp", "nn",
            "pfg", "ue", "y", "x", "hoho", "haa", "fire", "good", "pe",
            "fol"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 4);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "this"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 5);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(19, "x1", "t1", "h2", "a",
            "xe", "onceOnly", "all", "none", "harp", "nn", "pfg", "ue",
            "y", "x", "hoho", "haa", "fire", "good", "pe"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 6);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "x1"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 7);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(16, "t1", "h2", "a", "xe",
            "onceOnly", "all", "none", "harp", "nn", "pfg", "ue",
            "y", "x", "hoho", "haa", "fire"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 8);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "t1"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 9);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "h2"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 10);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(9, "a", "xe", "onceOnly",
            "all", "none", "harp", "nn", "pfg", "ue"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 11);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "y"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 12);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "y"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 13);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "x", "hoho", "haa",
            "fire"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 14);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "x", "hoho", "haa"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 15);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "x"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 16);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "hoho", "haa"), stringSet);
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

    stringSet = pkb->get_var_proc_modifies("secProc");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(9, "a", "xe", "onceOnly",
            "all", "none", "harp", "nn", "pfg", "ue"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 23);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "a"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 24);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "xe"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 25);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(5, "onceOnly", "all", "none",
            "harp", "nn"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 26);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "onceOnly"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 27);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "all", "none", "harp",
            "nn"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 28);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "all"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 29);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "none"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 30);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "harp", "nn"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_IF,
            ENT_VAR, 31);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "harp", "nn"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 32);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "harp"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 33);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "nn"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_CALL,
            ENT_VAR, 34);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "pfg", "ue"), stringSet);

    stringSet = pkb->get_var_proc_modifies("thirdProc");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "hoho", "haa"),
            stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 35);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "hoho"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 36);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "haa"), stringSet);

    stringSet = pkb->get_var_proc_modifies("procFOUR");
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(2, "pfg", "ue"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 37);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "pfg"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_WHILE,
            ENT_VAR, 38);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "ue"), stringSet);
    stringSet = pkb->modifies_X_Y_get_string_Y_from_int_X(ENT_ASSIGN,
            ENT_VAR, 39);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(1, "ue"), stringSet);

    //////////////////////////////////////////////////////////////////
    // same as above, but using stmt
    //////////////////////////////////////////////////////////////////
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
}

void TestPKB::test_uses()
{
    string simpleProg, queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;

    simpleProg =
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