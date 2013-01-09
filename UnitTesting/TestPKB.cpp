#include <string>
#include <map>
#include "TestPKB.h"
#include "../SPA/Parser.h"
#include "../SPA/PKB.h"

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

    set<string> s;
    set<int> s1;
    set<int>::iterator it;
    int i;

    // Variables
    CPPUNIT_ASSERT(pkb.get_control_var(9) == "i");
    CPPUNIT_ASSERT_EQUAL(string("i"), pkb.get_control_var(19));
    CPPUNIT_ASSERT_EQUAL(string("i"), pkb.get_control_var(28));

    s = pkb.get_all_vars();
    CPPUNIT_ASSERT_EQUAL(6, (int)s.size());
    CPPUNIT_ASSERT(s.find("d") != s.end());
    CPPUNIT_ASSERT(s.find("e") != s.end());
    CPPUNIT_ASSERT(s.find("i") != s.end());
    CPPUNIT_ASSERT(s.find("x") != s.end());
    CPPUNIT_ASSERT(s.find("y") != s.end());
    CPPUNIT_ASSERT(s.find("z") != s.end());
    CPPUNIT_ASSERT(s.find("r") == s.end());

    s = pkb.get_all_vars_by_proc("Bill");
    CPPUNIT_ASSERT_EQUAL(6, (int)s.size());
    CPPUNIT_ASSERT(s.find("d") != s.end());
    CPPUNIT_ASSERT(s.find("e") != s.end());
    CPPUNIT_ASSERT(s.find("i") != s.end());
    CPPUNIT_ASSERT(s.find("x") != s.end());
    CPPUNIT_ASSERT(s.find("y") != s.end());
    CPPUNIT_ASSERT(s.find("z") != s.end());

    s = pkb.get_all_vars_by_proc("Mary");
    CPPUNIT_ASSERT_EQUAL(6, (int)s.size());
    CPPUNIT_ASSERT(s.find("d") != s.end());
    CPPUNIT_ASSERT(s.find("e") != s.end());
    CPPUNIT_ASSERT(s.find("i") != s.end());
    CPPUNIT_ASSERT(s.find("x") != s.end());
    CPPUNIT_ASSERT(s.find("y") != s.end());
    CPPUNIT_ASSERT(s.find("z") != s.end());

    s = pkb.get_all_vars_by_proc("Jane");
    CPPUNIT_ASSERT_EQUAL(3, (int)s.size());
    CPPUNIT_ASSERT(s.find("d") != s.end());
    CPPUNIT_ASSERT(s.find("x") != s.end());
    CPPUNIT_ASSERT(s.find("z") != s.end());

    s = pkb.get_all_vars_by_proc("John");
    CPPUNIT_ASSERT_EQUAL(6, (int)s.size());
    CPPUNIT_ASSERT(s.find("d") != s.end());
    CPPUNIT_ASSERT(s.find("e") != s.end());
    CPPUNIT_ASSERT(s.find("i") != s.end());
    CPPUNIT_ASSERT(s.find("x") != s.end());
    CPPUNIT_ASSERT(s.find("y") != s.end());
    CPPUNIT_ASSERT(s.find("z") != s.end());
    
    // Calls 
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_calls("Mary", "John"));
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_calls("Bill", "Mary"));
    CPPUNIT_ASSERT_EQUAL(false, pkb.is_calls("Jane", "John"));

    CPPUNIT_ASSERT_EQUAL(true, pkb.is_calls_star("Bill", "John"));

    s = pkb.get_calls("Bill");
    CPPUNIT_ASSERT_EQUAL(3, (int)s.size());
    CPPUNIT_ASSERT(s.find("John") != s.end());
    CPPUNIT_ASSERT(s.find("Jane") != s.end());
    CPPUNIT_ASSERT(s.find("Mary") != s.end());

    s = pkb.get_calls_star("Bill");
    CPPUNIT_ASSERT_EQUAL(3, (int)s.size());
    CPPUNIT_ASSERT(s.find("John") != s.end());
    CPPUNIT_ASSERT(s.find("Jane") != s.end());
    CPPUNIT_ASSERT(s.find("Mary") != s.end());

    s = pkb.get_called_by("John");
    CPPUNIT_ASSERT_EQUAL(2, (int)s.size());
    CPPUNIT_ASSERT(s.find("Bill") != s.end());
    CPPUNIT_ASSERT(s.find("Jane") == s.end());
    CPPUNIT_ASSERT(s.find("Mary") != s.end());

    s = pkb.get_called_by_star("John");
    CPPUNIT_ASSERT_EQUAL(2, (int)s.size());
    CPPUNIT_ASSERT(s.find("Bill") != s.end());
    CPPUNIT_ASSERT(s.find("Jane") == s.end());
    CPPUNIT_ASSERT(s.find("Mary") != s.end());

    // Modifies
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_modifies("Mary", "z"));
    CPPUNIT_ASSERT_EQUAL(false, pkb.is_modifies("Mary", "x"));

    CPPUNIT_ASSERT_EQUAL(true, pkb.is_modifies(1, "z"));
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_modifies(30, "z"));

    s = pkb.get_proc_modifies("i");
    CPPUNIT_ASSERT_EQUAL(2, (int)s.size());
    CPPUNIT_ASSERT(s.find("Bill") != s.end());
    CPPUNIT_ASSERT(s.find("Jane") == s.end());
    CPPUNIT_ASSERT(s.find("Mary") != s.end());

    s1 = pkb.get_stmt_modifies("i");
    CPPUNIT_ASSERT_EQUAL(7, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(13) != s1.end());
    CPPUNIT_ASSERT(s1.find(16) != s1.end());
    CPPUNIT_ASSERT(s1.find(22) != s1.end());
    CPPUNIT_ASSERT(s1.find(9) != s1.end());
    CPPUNIT_ASSERT(s1.find(11) != s1.end());
    CPPUNIT_ASSERT(s1.find(19) != s1.end());
    CPPUNIT_ASSERT(s1.find(18) != s1.end());

    s = pkb.get_var_proc_modifies("Jane");
    CPPUNIT_ASSERT_EQUAL(2, (int)s.size());
    CPPUNIT_ASSERT(s.find("x") != s.end());
    CPPUNIT_ASSERT(s.find("z") != s.end());

    s = pkb.get_var_stmt_modifies(6);
    CPPUNIT_ASSERT_EQUAL(1, (int)s.size());
    CPPUNIT_ASSERT(s.find("d") != s.end());
    
    s = pkb.get_var_stmt_modifies(15);
    CPPUNIT_ASSERT_EQUAL(2, (int)s.size());

    s = pkb.get_var_stmt_modifies(9);
    CPPUNIT_ASSERT_EQUAL(5, (int)s.size());
    CPPUNIT_ASSERT(s.find("e") != s.end());
    CPPUNIT_ASSERT(s.find("i") != s.end());
    CPPUNIT_ASSERT(s.find("x") != s.end());
    CPPUNIT_ASSERT(s.find("y") != s.end());
    CPPUNIT_ASSERT(s.find("z") != s.end());

    // Uses
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_uses("Mary", "x"));
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_uses("Mary", "d"));

    CPPUNIT_ASSERT_EQUAL(true, pkb.is_uses(3, "z"));
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_uses(9, "y"));
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_uses(21, "i"));

    s = pkb.get_proc_uses("d");
    CPPUNIT_ASSERT_EQUAL(4, (int)s.size());
    CPPUNIT_ASSERT(s.find("Bill") != s.end());
    CPPUNIT_ASSERT(s.find("John") != s.end());
    CPPUNIT_ASSERT(s.find("Mary") != s.end());
    CPPUNIT_ASSERT(s.find("Jane") != s.end());

    s1 = pkb.get_stmt_uses("i");
    CPPUNIT_ASSERT_EQUAL(11, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(9) != s1.end());
    CPPUNIT_ASSERT(s1.find(11) != s1.end());
    CPPUNIT_ASSERT(s1.find(16) != s1.end());
    CPPUNIT_ASSERT(s1.find(19) != s1.end());
    CPPUNIT_ASSERT(s1.find(18) != s1.end());
    CPPUNIT_ASSERT(s1.find(22) != s1.end());
    CPPUNIT_ASSERT(s1.find(23) != s1.end());
    CPPUNIT_ASSERT(s1.find(28) != s1.end());
    CPPUNIT_ASSERT(s1.find(5) != s1.end());
    CPPUNIT_ASSERT(s1.find(21) != s1.end());
    CPPUNIT_ASSERT(s1.find(27) != s1.end());

    s = pkb.get_var_proc_uses("Jane");
    CPPUNIT_ASSERT_EQUAL(3, (int)s.size());
    CPPUNIT_ASSERT(s.find("d") != s.end());
    CPPUNIT_ASSERT(s.find("x") != s.end());
    CPPUNIT_ASSERT(s.find("z") != s.end());

    s = pkb.get_var_stmt_uses(9);
    CPPUNIT_ASSERT_EQUAL(5, (int)s.size());
    CPPUNIT_ASSERT(s.find("d") != s.end());
    CPPUNIT_ASSERT(s.find("i") != s.end());
    CPPUNIT_ASSERT(s.find("x") != s.end());
    CPPUNIT_ASSERT(s.find("y") != s.end());
    CPPUNIT_ASSERT(s.find("z") != s.end());

    // Parent

    CPPUNIT_ASSERT(pkb.is_parent(11, 15));
    CPPUNIT_ASSERT(pkb.is_parent(11, 15));

    CPPUNIT_ASSERT(pkb.is_parent_star(11, 15));
    CPPUNIT_ASSERT(pkb.is_parent_star(9, 15));

    CPPUNIT_ASSERT(11 == pkb.get_parent(15));

    s1 = pkb.get_parent_star(16);
    CPPUNIT_ASSERT_EQUAL(2, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(9) != s1.end());
    CPPUNIT_ASSERT(s1.find(11) != s1.end());

    s1 = pkb.get_children_star(9);
    CPPUNIT_ASSERT_EQUAL(8, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(10) != s1.end());
    CPPUNIT_ASSERT(s1.find(11) != s1.end());
    CPPUNIT_ASSERT(s1.find(12) != s1.end());
    CPPUNIT_ASSERT(s1.find(13) != s1.end());
    CPPUNIT_ASSERT(s1.find(14) != s1.end());
    CPPUNIT_ASSERT(s1.find(15) != s1.end());
    CPPUNIT_ASSERT(s1.find(16) != s1.end());
    CPPUNIT_ASSERT(s1.find(17) != s1.end());

    s1 = pkb.get_children(9);
    CPPUNIT_ASSERT_EQUAL(3, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(10) != s1.end());
    CPPUNIT_ASSERT(s1.find(11) != s1.end());
    CPPUNIT_ASSERT(s1.find(17) != s1.end());

    s1 = pkb.get_children_star(9);
    CPPUNIT_ASSERT_EQUAL(8, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(10) != s1.end());
    CPPUNIT_ASSERT(s1.find(11) != s1.end());
    CPPUNIT_ASSERT(s1.find(12) != s1.end());
    CPPUNIT_ASSERT(s1.find(13) != s1.end());
    CPPUNIT_ASSERT(s1.find(14) != s1.end());
    CPPUNIT_ASSERT(s1.find(15) != s1.end());
    CPPUNIT_ASSERT(s1.find(16) != s1.end());
    CPPUNIT_ASSERT(s1.find(17) != s1.end());

    // Follows
    CPPUNIT_ASSERT(pkb.is_follows(9, 18));
    CPPUNIT_ASSERT(!pkb.is_follows(11, 15));

    CPPUNIT_ASSERT(pkb.is_follows_star(3, 4));
    CPPUNIT_ASSERT(pkb.is_follows_star(3, 18));
    CPPUNIT_ASSERT(!pkb.is_follows_star(12, 15));

    CPPUNIT_ASSERT_EQUAL(23, pkb.get_successor(19));
    CPPUNIT_ASSERT_EQUAL(26, pkb.get_successor(24));

    s1 = pkb.get_successor_star(7);
    CPPUNIT_ASSERT_EQUAL(3, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(8) != s1.end());
    CPPUNIT_ASSERT(s1.find(9) != s1.end());
    CPPUNIT_ASSERT(s1.find(18) != s1.end());

    CPPUNIT_ASSERT_EQUAL(19, pkb.get_predecessor(23));
    CPPUNIT_ASSERT_EQUAL(24, pkb.get_predecessor(26));

    s1 = pkb.get_predecessor_star(6);
    CPPUNIT_ASSERT_EQUAL(5, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(2) != s1.end());
    CPPUNIT_ASSERT(s1.find(3) != s1.end());
    CPPUNIT_ASSERT(s1.find(4) != s1.end());
    CPPUNIT_ASSERT(s1.find(5) != s1.end());
    CPPUNIT_ASSERT(s1.find(1) != s1.end());

    // Constant
    CPPUNIT_ASSERT(pkb.is_const_exist("3"));
    CPPUNIT_ASSERT(pkb.is_const_exist("1"));
    CPPUNIT_ASSERT(!pkb.is_const_exist("100"));

    s = pkb.get_all_const();
    CPPUNIT_ASSERT_EQUAL(7, (int)s.size());
    CPPUNIT_ASSERT(s.find("10") != s.end());
    CPPUNIT_ASSERT(s.find("5") != s.end());
    CPPUNIT_ASSERT(s.find("4") != s.end());
    CPPUNIT_ASSERT(s.find("12") != s.end());
    CPPUNIT_ASSERT(s.find("1") != s.end());
    CPPUNIT_ASSERT(s.find("3") != s.end());
    CPPUNIT_ASSERT(s.find("2") != s.end());

    // Others
    s1 = pkb.get_all_stmt();
    CPPUNIT_ASSERT_EQUAL(30, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(2) != s1.end());
    CPPUNIT_ASSERT(s1.find(10) != s1.end());
    CPPUNIT_ASSERT(s1.find(15) != s1.end());
    CPPUNIT_ASSERT(s1.find(22) != s1.end());
    CPPUNIT_ASSERT(s1.find(30) != s1.end());

    s1 = pkb.get_all_stmt_by_proc("Mary");
    CPPUNIT_ASSERT_EQUAL(5, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(19) != s1.end());
    CPPUNIT_ASSERT(s1.find(20) != s1.end());
    CPPUNIT_ASSERT(s1.find(21) != s1.end());
    CPPUNIT_ASSERT(s1.find(22) != s1.end());
    CPPUNIT_ASSERT(s1.find(23) != s1.end());

    s1 = pkb.filter_by_proc("Mary", pkb.get_all_stmt());
    CPPUNIT_ASSERT_EQUAL(5, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(19) != s1.end());
    CPPUNIT_ASSERT(s1.find(20) != s1.end());
    CPPUNIT_ASSERT(s1.find(21) != s1.end());
    CPPUNIT_ASSERT(s1.find(22) != s1.end());
    CPPUNIT_ASSERT(s1.find(23) != s1.end());

    s1 = pkb.filter_by_stmtType(WHILETYPE, pkb.get_all_stmt());
    CPPUNIT_ASSERT_EQUAL(4, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(9) != s1.end());
    CPPUNIT_ASSERT(s1.find(19) != s1.end());
    CPPUNIT_ASSERT(s1.find(24) != s1.end());
    CPPUNIT_ASSERT(s1.find(27) != s1.end());

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
    CPPUNIT_ASSERT(s1.size() == 0);
    s1 = pkb.get_children(9);
    CPPUNIT_ASSERT(s1.size() == 3);
    CPPUNIT_ASSERT(s1.find(10) != s1.end());
    CPPUNIT_ASSERT(s1.find(11) != s1.end());
    CPPUNIT_ASSERT(s1.find(17) != s1.end());
    s1 = pkb.get_children(10);
    CPPUNIT_ASSERT(s1.size() == 0);
    s1 = pkb.get_children(11);
    CPPUNIT_ASSERT(s1.size() == 5);
    CPPUNIT_ASSERT(s1.find(12) != s1.end());
    CPPUNIT_ASSERT(s1.find(13) != s1.end());
    CPPUNIT_ASSERT(s1.find(14) != s1.end());
    CPPUNIT_ASSERT(s1.find(15) != s1.end());
    CPPUNIT_ASSERT(s1.find(16) != s1.end());

    // Q4
    s1 =pkb.get_parent_star(2);
    CPPUNIT_ASSERT(s1.size() == 0);
    s1 =pkb.get_parent_star(10);
    CPPUNIT_ASSERT(s1.size() == 1);
    CPPUNIT_ASSERT(s1.find(9) != s1.end());
    s1 =pkb.get_parent_star(15);
    CPPUNIT_ASSERT(s1.size() == 2);
    CPPUNIT_ASSERT(s1.find(9) != s1.end());
    CPPUNIT_ASSERT(s1.find(11) != s1.end());
    s1 =pkb.get_parent_star(21);
    CPPUNIT_ASSERT(s1.size() == 1);
    CPPUNIT_ASSERT(s1.find(19) != s1.end());

    // Q5
    s1 = pkb.filter_by_stmtType(WHILETYPE, pkb.get_parent_star(2));
    CPPUNIT_ASSERT(s1.size() == 0);
    s1 = pkb.filter_by_stmtType(WHILETYPE, pkb.get_parent_star(10));
    CPPUNIT_ASSERT(s1.size() == 1);
    CPPUNIT_ASSERT(s1.find(9) != s1.end());
    s1 = pkb.filter_by_stmtType(WHILETYPE, pkb.get_parent_star(13));
    CPPUNIT_ASSERT(s1.size() == 1);
    CPPUNIT_ASSERT(s1.find(9) != s1.end());
    s1 = pkb.filter_by_stmtType(WHILETYPE, pkb.get_parent_star(17));
    CPPUNIT_ASSERT(s1.size() == 1);
    CPPUNIT_ASSERT(s1.find(9) != s1.end());
    s1 = pkb.filter_by_stmtType(WHILETYPE, pkb.get_parent_star(22));
    CPPUNIT_ASSERT(s1.size() == 1);
    CPPUNIT_ASSERT(s1.find(19) != s1.end());

    // Q7
    CPPUNIT_ASSERT_EQUAL(-1, pkb.get_predecessor(1));
    CPPUNIT_ASSERT_EQUAL(2, pkb.get_predecessor(3));
    CPPUNIT_ASSERT_EQUAL(8, pkb.get_predecessor(9));
    CPPUNIT_ASSERT_EQUAL(-1, pkb.get_predecessor(10));
    CPPUNIT_ASSERT_EQUAL(-1, pkb.get_predecessor(19));

    // Q8
    CPPUNIT_ASSERT_EQUAL(-1, pkb.filter_by_stmtType(ASSIGNTYPE,
        pkb.get_predecessor(1)));
    CPPUNIT_ASSERT_EQUAL(2, pkb.filter_by_stmtType(ASSIGNTYPE,
        pkb.get_predecessor(3)));
    CPPUNIT_ASSERT_EQUAL(8, pkb.filter_by_stmtType(ASSIGNTYPE,
        pkb.get_predecessor(9)));
    CPPUNIT_ASSERT_EQUAL(-1, pkb.filter_by_stmtType(ASSIGNTYPE,
        pkb.get_predecessor(10)));
    CPPUNIT_ASSERT_EQUAL(-1, pkb.filter_by_stmtType(ASSIGNTYPE,
        pkb.get_predecessor(18)));

    // Q10
    s1 = pkb.get_predecessor_star(2);
    CPPUNIT_ASSERT(s1.size() == 1);
    CPPUNIT_ASSERT(s1.find(1) != s1.end());
    s1 = pkb.get_predecessor_star(10);
    CPPUNIT_ASSERT(s1.size() == 0);
    s1 = pkb.get_predecessor_star(11);
    CPPUNIT_ASSERT(s1.size() == 1);
    CPPUNIT_ASSERT(s1.find(10) != s1.end());
    s1 = pkb.get_predecessor_star(21);
    CPPUNIT_ASSERT(s1.size() == 1);
    CPPUNIT_ASSERT(s1.find(20) != s1.end());

    // Q11
    s1 = pkb.filter_by_stmtType(IFTYPE,pkb.get_predecessor_star(10));
    CPPUNIT_ASSERT(s1.size() == 0);
    s1 = pkb.filter_by_stmtType(IFTYPE,pkb.get_predecessor_star(17));
    CPPUNIT_ASSERT(s1.size() == 1);
    CPPUNIT_ASSERT(s1.find(11) != s1.end());

    // Q12
    s1 = pkb.filter_by_stmtType(ASSIGNTYPE,pkb.get_predecessor_star(4));
    CPPUNIT_ASSERT(s1.size() == 3);
    CPPUNIT_ASSERT(s1.find(1) != s1.end());
    CPPUNIT_ASSERT(s1.find(2) != s1.end());
    CPPUNIT_ASSERT(s1.find(3) != s1.end());
    s1 = pkb.filter_by_stmtType(ASSIGNTYPE,pkb.get_predecessor_star(5));
    CPPUNIT_ASSERT(s1.size() == 4);
    CPPUNIT_ASSERT(s1.find(1) != s1.end());
    CPPUNIT_ASSERT(s1.find(2) != s1.end());
    CPPUNIT_ASSERT(s1.find(3) != s1.end());
    CPPUNIT_ASSERT(s1.find(4) != s1.end());
    s1 = pkb.filter_by_stmtType(ASSIGNTYPE,pkb.get_predecessor_star(9));
    CPPUNIT_ASSERT(s1.size() == 6);
    CPPUNIT_ASSERT(s1.find(1) != s1.end());
    CPPUNIT_ASSERT(s1.find(2) != s1.end());
    CPPUNIT_ASSERT(s1.find(3) != s1.end());
    CPPUNIT_ASSERT(s1.find(4) != s1.end());
    CPPUNIT_ASSERT(s1.find(6) != s1.end());
    CPPUNIT_ASSERT(s1.find(8) != s1.end());
    s1 = pkb.filter_by_stmtType(ASSIGNTYPE,pkb.get_predecessor_star(17));
    CPPUNIT_ASSERT(s1.size() == 1);
    CPPUNIT_ASSERT(s1.find(10) != s1.end());
    s1 = pkb.filter_by_stmtType(ASSIGNTYPE,pkb.get_predecessor_star(22));
    CPPUNIT_ASSERT(s1.size() == 1);
    CPPUNIT_ASSERT(s1.find(20) != s1.end());

    // Q13
    s = pkb.get_var_stmt_modifies(3);
    CPPUNIT_ASSERT(s.size() == 1);
    CPPUNIT_ASSERT(s.find("y") != s.end());
    s = pkb.get_var_stmt_modifies(5);
    CPPUNIT_ASSERT(s.size() == 2);
    CPPUNIT_ASSERT(s.find("y") != s.end());
    CPPUNIT_ASSERT(s.find("z") != s.end());
    s = pkb.get_var_stmt_modifies(9);
    CPPUNIT_ASSERT(s.size() == 5);
    CPPUNIT_ASSERT(s.find("e") != s.end());
    CPPUNIT_ASSERT(s.find("i") != s.end());
    CPPUNIT_ASSERT(s.find("x") != s.end());
    CPPUNIT_ASSERT(s.find("y") != s.end());
    CPPUNIT_ASSERT(s.find("z") != s.end());
    s = pkb.get_var_stmt_modifies(11);
    CPPUNIT_ASSERT(s.size() == 4);
    CPPUNIT_ASSERT(s.find("i") != s.end());
    CPPUNIT_ASSERT(s.find("x") != s.end());
    CPPUNIT_ASSERT(s.find("y") != s.end());
    CPPUNIT_ASSERT(s.find("z") != s.end());

    // Q14
    s1 = pkb.filter_by_stmtType(WHILETYPE, pkb.get_stmt_modifies("i"));
    CPPUNIT_ASSERT(s1.size() == 2);
    CPPUNIT_ASSERT(s1.find(9) != s1.end());
    CPPUNIT_ASSERT(s1.find(19) != s1.end());
    s1 = pkb.filter_by_stmtType(WHILETYPE, pkb.get_stmt_modifies("y"));
    CPPUNIT_ASSERT(s1.size() == 3);
    CPPUNIT_ASSERT(s1.find(9) != s1.end());
    CPPUNIT_ASSERT(s1.find(19) != s1.end());
    CPPUNIT_ASSERT(s1.find(27) != s1.end());

    // Q15
    s = pkb.get_var_proc_modifies("Mary");
    CPPUNIT_ASSERT_EQUAL(3, (int)s.size());
    CPPUNIT_ASSERT(s.find("i") != s.end());
    CPPUNIT_ASSERT(s.find("y") != s.end());
    CPPUNIT_ASSERT(s.find("z") != s.end());

    // Q16
    s1 = pkb.get_stmt_uses("i");
    CPPUNIT_ASSERT_EQUAL(11, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(5) != s1.end());
    CPPUNIT_ASSERT(s1.find(9) != s1.end());
    CPPUNIT_ASSERT(s1.find(11) != s1.end());
    CPPUNIT_ASSERT(s1.find(16) != s1.end());
    CPPUNIT_ASSERT(s1.find(18) != s1.end());
    CPPUNIT_ASSERT(s1.find(19) != s1.end());
    CPPUNIT_ASSERT(s1.find(21) != s1.end());
    CPPUNIT_ASSERT(s1.find(22) != s1.end());
    CPPUNIT_ASSERT(s1.find(23) != s1.end());
    CPPUNIT_ASSERT(s1.find(27) != s1.end());
    CPPUNIT_ASSERT(s1.find(28) != s1.end());
    s1 = pkb.get_stmt_uses("y");
    CPPUNIT_ASSERT_EQUAL(17, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(4) != s1.end());
    CPPUNIT_ASSERT(s1.find(5) != s1.end());
    CPPUNIT_ASSERT(s1.find(9) != s1.end());
    CPPUNIT_ASSERT(s1.find(10) != s1.end());
    CPPUNIT_ASSERT(s1.find(11) != s1.end());
    CPPUNIT_ASSERT(s1.find(12) != s1.end());
    CPPUNIT_ASSERT(s1.find(13) != s1.end());
    CPPUNIT_ASSERT(s1.find(14) != s1.end());
    CPPUNIT_ASSERT(s1.find(17) != s1.end());
    CPPUNIT_ASSERT(s1.find(18) != s1.end());
    CPPUNIT_ASSERT(s1.find(19) != s1.end());
    CPPUNIT_ASSERT(s1.find(20) != s1.end());
    CPPUNIT_ASSERT(s1.find(21) != s1.end());
    CPPUNIT_ASSERT(s1.find(23) != s1.end());
    CPPUNIT_ASSERT(s1.find(27) != s1.end());
    CPPUNIT_ASSERT(s1.find(28) != s1.end());
    CPPUNIT_ASSERT(s1.find(30) != s1.end());

    // Q17
    s = pkb.get_var_stmt_uses(10);
    CPPUNIT_ASSERT_EQUAL(2, (int)s.size());
    CPPUNIT_ASSERT(s.find("x") != s.end());
    CPPUNIT_ASSERT(s.find("y") != s.end());
    s = pkb.get_var_stmt_uses(18);
    CPPUNIT_ASSERT_EQUAL(6, (int)s.size());
    CPPUNIT_ASSERT(s.find("d") != s.end());
    CPPUNIT_ASSERT(s.find("e") != s.end());
    CPPUNIT_ASSERT(s.find("i") != s.end());
    CPPUNIT_ASSERT(s.find("x") != s.end());
    CPPUNIT_ASSERT(s.find("y") != s.end());
    CPPUNIT_ASSERT(s.find("z") != s.end());

    // Q23
    s = pkb.get_called_by_star("John");
    CPPUNIT_ASSERT_EQUAL(2, (int)s.size());
    CPPUNIT_ASSERT(s.find("Bill") != s.end());
    CPPUNIT_ASSERT(s.find("Jane") == s.end());
    CPPUNIT_ASSERT(s.find("Mary") != s.end());

    // Q39
    s1 = pkb.get_after(1);
    CPPUNIT_ASSERT_EQUAL(1, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(2) != s1.end());
    s1 = pkb.get_after(9);
    CPPUNIT_ASSERT_EQUAL(2, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(10) != s1.end());
    CPPUNIT_ASSERT(s1.find(18) != s1.end());
    s1 = pkb.get_after(11);
    CPPUNIT_ASSERT_EQUAL(2, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(12) != s1.end());
    CPPUNIT_ASSERT(s1.find(14) != s1.end());
    s1 = pkb.get_after(13);
    CPPUNIT_ASSERT_EQUAL(1, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(17) != s1.end());
    s1 = pkb.get_after(15);
    CPPUNIT_ASSERT_EQUAL(1, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(16) != s1.end());
    s1 = pkb.get_after(17);
    CPPUNIT_ASSERT_EQUAL(1, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(9) != s1.end());
    s1 = pkb.get_after(18);
    CPPUNIT_ASSERT_EQUAL(0, (int)s1.size());

    // Q40
    s1 = pkb.get_before(1);
    CPPUNIT_ASSERT_EQUAL(0, (int)s1.size());
    s1 = pkb.get_before(9);
    CPPUNIT_ASSERT_EQUAL(2, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(8) != s1.end());
    CPPUNIT_ASSERT(s1.find(17) != s1.end());
    s1 = pkb.get_before(10);
    CPPUNIT_ASSERT_EQUAL(1, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(9) != s1.end());
    s1 = pkb.get_before(17);
    CPPUNIT_ASSERT_EQUAL(2, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(13) != s1.end());
    CPPUNIT_ASSERT(s1.find(16) != s1.end());
    s1 = pkb.get_before(18);
    CPPUNIT_ASSERT_EQUAL(1, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(9) != s1.end());
    s1 = pkb.get_before(19);
    CPPUNIT_ASSERT_EQUAL(1, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(22) != s1.end());

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
    CPPUNIT_ASSERT_EQUAL(0, (int)s1.size());
    s1 = pkb.get_affected_by(10);
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_affects(17, 10));
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_affects(12, 10));
    CPPUNIT_ASSERT_EQUAL(2, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(12) != s1.end());
    CPPUNIT_ASSERT(s1.find(17) != s1.end());

    // Q45
    s1 = pkb.get_affects(1);
    CPPUNIT_ASSERT_EQUAL(2, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(2) != s1.end());
    CPPUNIT_ASSERT(s1.find(3) != s1.end());
    s1 = pkb.get_affects(13);
    CPPUNIT_ASSERT_EQUAL(1, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(16) != s1.end());

    // Q46
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_affects_star(1, 2));
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_affects_star(1, 3));
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_affects_star(1, 6));
    CPPUNIT_ASSERT_EQUAL(true, pkb.is_affects_star(1, 8));
    CPPUNIT_ASSERT_EQUAL(false, pkb.is_affects_star(11, 14));
    CPPUNIT_ASSERT_EQUAL(false, pkb.is_affects_star(20, 20));

    // Q47
    s1 = pkb.get_affected_by_star(12);
    CPPUNIT_ASSERT_EQUAL(0, (int)s1.size());
    s1 = pkb.get_affected_by_star(26);
    CPPUNIT_ASSERT_EQUAL(1, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(25) != s1.end());

    // Q48
    s1 = pkb.get_affects_star(20);
    CPPUNIT_ASSERT_EQUAL(0, (int)s1.size());
    s1 = pkb.get_affects_star(6);
    CPPUNIT_ASSERT_EQUAL(1, (int)s1.size());
    CPPUNIT_ASSERT(s1.find(8) != s1.end());
}


// Test procTable
void TestPKB::test_two(){


}

void TestPKB::test_three(){

}

