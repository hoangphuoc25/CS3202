#include <cstdarg>
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
    set<int> intSet;
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
    CPPUNIT_ASSERT(pkb.has_const(3));
    CPPUNIT_ASSERT(pkb.has_const(1));
    CPPUNIT_ASSERT(!pkb.has_const(100));

    intSet = pkb.get_all_const();
    CPPUNIT_ASSERT_EQUAL(7, (int)intSet.size());
    CPPUNIT_ASSERT(intSet.find(10) != intSet.end());
    CPPUNIT_ASSERT(intSet.find(5) != intSet.end());
    CPPUNIT_ASSERT(intSet.find(4) != intSet.end());
    CPPUNIT_ASSERT(intSet.find(12) != intSet.end());
    CPPUNIT_ASSERT(intSet.find(1) != intSet.end());
    CPPUNIT_ASSERT(intSet.find(3) != intSet.end());
    CPPUNIT_ASSERT(intSet.find(2) != intSet.end());

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

void TestPKB::compare_int_set(const set<int>& S, int n, ...) const
{
    int expectedSize = S.size();
    CPPUNIT_ASSERT_EQUAL((int)S.size(), n);
    set<int> tmpSet;
    va_list ap;
    va_start(ap, n);
    for (int i = 0; i < n; i++) {
        int value = va_arg(ap, int);
        CPPUNIT_ASSERT_EQUAL(1, (int)S.count(value));
        CPPUNIT_ASSERT_EQUAL(0, (int)tmpSet.count(value));
        tmpSet.insert(value);
    }
    va_end(ap);
    CPPUNIT_ASSERT_EQUAL(expectedSize, (int)tmpSet.size());
}

void TestPKB::compare_string_set(const set<string>& S, int n, ...) const
{
    int expectedSize = S.size();
    CPPUNIT_ASSERT_EQUAL((int)S.size(), n);
    set<string> tmpSet;
    va_list ap;
    va_start(ap, n);
    for (int i = 0; i < n; i++) {
        char *apStr = va_arg(ap, char*);
        string str = string(apStr);
        CPPUNIT_ASSERT_EQUAL(1, (int)S.count(str));
        CPPUNIT_ASSERT_EQUAL(0, (int)tmpSet.count(str));
        tmpSet.insert(str);
    }
    va_end(ap);
    CPPUNIT_ASSERT_EQUAL(expectedSize, (int)tmpSet.size());
}

void TestPKB::test_retrieve_all_X()
{
    string simpleProg, queryStr;
    set<int> intSet;
    set<string> stringSet;
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
    this->compare_int_set(intSet, 26, 1, 2, 4, 5, 6, 8, 11, 13, 14, 15, 16,
            17, 18, 19, 21, 22, 23, 24, 27, 28, 29, 30, 31, 32, 34, 35);
    // if
    intSet = pkb->get_all_if();
    this->compare_int_set(intSet, 3, 3, 9, 25);
    // while
    intSet = pkb->get_all_while();
    this->compare_int_set(intSet, 3, 7, 12, 33);
    // call
    intSet = pkb->get_all_call();
    this->compare_int_set(intSet, 3, 10, 20, 26);
    // const
    intSet = pkb->get_all_const();
    this->compare_int_set(intSet, 9, 3, 62, 2, 73, 156, 511,
                0, 675, 1);
    // stmt
    intSet = pkb->get_all_stmt();
    this->compare_int_set(intSet, 35, 1, 2, 3, 4, 5, 6, 7, 8,
                9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
                21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
                33, 34, 35);
    // variable
    stringSet = pkb->get_all_vars();
    this->compare_string_set(stringSet, 48, "a", "b73", "bc", "bill",
            "cleanup", "cond", "cool", "doStuff", "done",
            "eat", "elseVar", "execVar", "exitVal", "fighter",
            "follows", "food", "gather", "good", "hell",
            "hungry", "im", "last", "lastProc", "modifies",
            "no", "notEmpty", "one", "P", "pacman", "paid", "pkgmgr",
            "program", "retVal", "sad", "sameName", "save",
            "sleep", "star", "state", "stuff", "tie", "tired",
            "true", "twoThree", "varHere", "x", "xid", "y");
    // procedure
    stringSet = pkb->get_all_procs();
    this->compare_string_set(stringSet, 4, "Xproc", "execVE", "oneTwoThree",
            "lastProc");
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
    set<string> stringSet;

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
    stringSet = pkb->get_var_proc_modifies("pOne");
    this->compare_string_set(stringSet, 24, "aone", "d3", "this", "x1", "t1",
            "h2", "a", "xe", "onceOnly", "all", "none", "harp", "nn",
            "pfg", "ue", "y", "x", "hoho", "haa", "fire", "good", "pe",
            "fol", "g2");
    stringSet = pkb->get_all_vars_modified_by_assign(1);
    this->compare_string_set(stringSet, 1, "aone");
    stringSet = pkb->get_all_vars_modified_by_assign(2);
    this->compare_string_set(stringSet, 1, "d3");
    stringSet = pkb->get_all_vars_modified_by_while(3);
    this->compare_string_set(stringSet, 21, "this", "x1", "t1", "h2", "a",
            "xe", "onceOnly", "all", "none", "harp", "nn", "pfg", "ue",
            "y", "x", "hoho", "haa", "fire", "good", "pe", "fol");
    stringSet = pkb->get_all_vars_modified_by_assign(4);
    this->compare_string_set(stringSet, 1, "this");
    stringSet = pkb->get_all_vars_modified_by_while(5);
    this->compare_string_set(stringSet, 19, "x1", "t1", "h2", "a", "xe",
            "onceOnly", "all", "none", "harp", "nn", "pfg", "ue", "y",
            "x", "hoho", "haa", "fire", "good", "pe");
    stringSet = pkb->get_all_vars_modified_by_assign(6);
    this->compare_string_set(stringSet, 1, "x1");
    stringSet = pkb->get_all_vars_modified_by_if(7);
    this->compare_string_set(stringSet, 16, "t1", "h2", "a", "xe",
            "onceOnly", "all", "none", "harp", "nn", "pfg", "ue",
            "y", "x", "hoho", "haa", "fire");
    stringSet = pkb->get_all_vars_modified_by_assign(8);
    this->compare_string_set(stringSet, 1, "t1");
    stringSet = pkb->get_all_vars_modified_by_assign(9);
    this->compare_string_set(stringSet, 1, "h2");
    stringSet = pkb->get_all_vars_modified_by_call(10);
    this->compare_string_set(stringSet, 9, "a", "xe", "onceOnly", "all",
            "none", "harp", "nn", "pfg", "ue");
    stringSet = pkb->get_all_vars_modified_by_while(11);
    this->compare_string_set(stringSet, 1, "y");
    stringSet = pkb->get_all_vars_modified_by_assign(12);
    this->compare_string_set(stringSet, 1, "y");
    stringSet = pkb->get_all_vars_modified_by_if(13);
    this->compare_string_set(stringSet, 4, "x", "hoho", "haa", "fire");
    stringSet = pkb->get_all_vars_modified_by_while(14);
    this->compare_string_set(stringSet, 3, "x", "hoho", "haa");
    stringSet = pkb->get_all_vars_modified_by_assign(15);
    this->compare_string_set(stringSet, 1, "x");
    stringSet = pkb->get_all_vars_modified_by_call(16);
    this->compare_string_set(stringSet, 2, "hoho", "haa");
    stringSet = pkb->get_all_vars_modified_by_assign(17);
    this->compare_string_set(stringSet, 1, "fire");
    stringSet = pkb->get_all_vars_modified_by_assign(18);
    this->compare_string_set(stringSet, 1, "xe");
    stringSet = pkb->get_all_vars_modified_by_assign(19);
    this->compare_string_set(stringSet, 1, "good");
    stringSet = pkb->get_all_vars_modified_by_assign(20);
    this->compare_string_set(stringSet, 1, "pe");
    stringSet = pkb->get_all_vars_modified_by_assign(21);
    this->compare_string_set(stringSet, 1, "fol");
    stringSet = pkb->get_all_vars_modified_by_assign(22);
    this->compare_string_set(stringSet, 1, "g2");

    stringSet = pkb->get_var_proc_modifies("secProc");
    this->compare_string_set(stringSet, 9, "a", "xe", "onceOnly", "all",
            "none", "harp", "nn", "pfg", "ue");
    stringSet = pkb->get_all_vars_modified_by_assign(23);
    this->compare_string_set(stringSet, 1, "a");
    stringSet = pkb->get_all_vars_modified_by_assign(24);
    this->compare_string_set(stringSet, 1, "xe");
    stringSet = pkb->get_all_vars_modified_by_while(25);
    this->compare_string_set(stringSet, 5, "onceOnly", "all", "none",
            "harp", "nn");
    stringSet = pkb->get_all_vars_modified_by_assign(26);
    this->compare_string_set(stringSet, 1, "onceOnly");
    stringSet = pkb->get_all_vars_modified_by_if(27);
    this->compare_string_set(stringSet, 4, "all", "none", "harp", "nn");
    stringSet = pkb->get_all_vars_modified_by_assign(28);
    this->compare_string_set(stringSet, 1, "all");
    stringSet = pkb->get_all_vars_modified_by_assign(29);
    this->compare_string_set(stringSet, 1, "none");
    stringSet = pkb->get_all_vars_modified_by_while(30);
    this->compare_string_set(stringSet, 2, "harp", "nn");
    stringSet = pkb->get_all_vars_modified_by_if(31);
    this->compare_string_set(stringSet, 2, "harp", "nn");
    stringSet = pkb->get_all_vars_modified_by_assign(32);
    this->compare_string_set(stringSet, 1, "harp");
    stringSet = pkb->get_all_vars_modified_by_assign(33);
    this->compare_string_set(stringSet, 1, "nn");
    stringSet = pkb->get_all_vars_modified_by_call(34);
    this->compare_string_set(stringSet, 2, "pfg", "ue");

    stringSet = pkb->get_var_proc_modifies("thirdProc");
    this->compare_string_set(stringSet, 2, "hoho", "haa");
    stringSet = pkb->get_all_vars_modified_by_assign(35);
    this->compare_string_set(stringSet, 1, "hoho");
    stringSet = pkb->get_all_vars_modified_by_assign(36);
    this->compare_string_set(stringSet, 1, "haa");

    stringSet = pkb->get_var_proc_modifies("procFOUR");
    this->compare_string_set(stringSet, 2, "pfg", "ue");
    stringSet = pkb->get_all_vars_modified_by_assign(37);
    this->compare_string_set(stringSet, 1, "pfg");
    stringSet = pkb->get_all_vars_modified_by_while(38);
    this->compare_string_set(stringSet, 1, "ue");
    stringSet = pkb->get_all_vars_modified_by_assign(39);
    this->compare_string_set(stringSet, 1, "ue");

    //////////////////////////////////////////////////////////////////
    // same as above, but using stmt
    //////////////////////////////////////////////////////////////////
    stringSet = pkb->get_all_vars_modified_by_stmt(1);
    this->compare_string_set(stringSet, 1, "aone");
    stringSet = pkb->get_all_vars_modified_by_stmt(2);
    this->compare_string_set(stringSet, 1, "d3");
    stringSet = pkb->get_all_vars_modified_by_stmt(3);
    this->compare_string_set(stringSet, 21, "this", "x1", "t1", "h2", "a",
            "xe", "onceOnly", "all", "none", "harp", "nn", "pfg", "ue",
            "y", "x", "hoho", "haa", "fire", "good", "pe", "fol");
    stringSet = pkb->get_all_vars_modified_by_stmt(4);
    this->compare_string_set(stringSet, 1, "this");
    stringSet = pkb->get_all_vars_modified_by_stmt(5);
    this->compare_string_set(stringSet, 19, "x1", "t1", "h2", "a", "xe",
            "onceOnly", "all", "none", "harp", "nn", "pfg", "ue", "y",
            "x", "hoho", "haa", "fire", "good", "pe");
    stringSet = pkb->get_all_vars_modified_by_stmt(6);
    this->compare_string_set(stringSet, 1, "x1");
    stringSet = pkb->get_all_vars_modified_by_stmt(7);
    this->compare_string_set(stringSet, 16, "t1", "h2", "a", "xe",
            "onceOnly", "all", "none", "harp", "nn", "pfg", "ue",
            "y", "x", "hoho", "haa", "fire");
    stringSet = pkb->get_all_vars_modified_by_stmt(8);
    this->compare_string_set(stringSet, 1, "t1");
    stringSet = pkb->get_all_vars_modified_by_stmt(9);
    this->compare_string_set(stringSet, 1, "h2");
    stringSet = pkb->get_all_vars_modified_by_stmt(10);
    this->compare_string_set(stringSet, 9, "a", "xe", "onceOnly", "all",
            "none", "harp", "nn", "pfg", "ue");
    stringSet = pkb->get_all_vars_modified_by_stmt(11);
    this->compare_string_set(stringSet, 1, "y");
    stringSet = pkb->get_all_vars_modified_by_stmt(12);
    this->compare_string_set(stringSet, 1, "y");
    stringSet = pkb->get_all_vars_modified_by_stmt(13);
    this->compare_string_set(stringSet, 4, "x", "hoho", "haa", "fire");
    stringSet = pkb->get_all_vars_modified_by_stmt(14);
    this->compare_string_set(stringSet, 3, "x", "hoho", "haa");
    stringSet = pkb->get_all_vars_modified_by_stmt(15);
    this->compare_string_set(stringSet, 1, "x");
    stringSet = pkb->get_all_vars_modified_by_stmt(16);
    this->compare_string_set(stringSet, 2, "hoho", "haa");
    stringSet = pkb->get_all_vars_modified_by_stmt(17);
    this->compare_string_set(stringSet, 1, "fire");
    stringSet = pkb->get_all_vars_modified_by_stmt(18);
    this->compare_string_set(stringSet, 1, "xe");
    stringSet = pkb->get_all_vars_modified_by_stmt(19);
    this->compare_string_set(stringSet, 1, "good");
    stringSet = pkb->get_all_vars_modified_by_stmt(20);
    this->compare_string_set(stringSet, 1, "pe");
    stringSet = pkb->get_all_vars_modified_by_stmt(21);
    this->compare_string_set(stringSet, 1, "fol");
    stringSet = pkb->get_all_vars_modified_by_stmt(22);
    this->compare_string_set(stringSet, 1, "g2");

    stringSet = pkb->get_all_vars_modified_by_stmt(23);
    this->compare_string_set(stringSet, 1, "a");
    stringSet = pkb->get_all_vars_modified_by_stmt(24);
    this->compare_string_set(stringSet, 1, "xe");
    stringSet = pkb->get_all_vars_modified_by_stmt(25);
    this->compare_string_set(stringSet, 5, "onceOnly", "all", "none",
            "harp", "nn");
    stringSet = pkb->get_all_vars_modified_by_stmt(26);
    this->compare_string_set(stringSet, 1, "onceOnly");
    stringSet = pkb->get_all_vars_modified_by_stmt(27);
    this->compare_string_set(stringSet, 4, "all", "none", "harp", "nn");
    stringSet = pkb->get_all_vars_modified_by_stmt(28);
    this->compare_string_set(stringSet, 1, "all");
    stringSet = pkb->get_all_vars_modified_by_stmt(29);
    this->compare_string_set(stringSet, 1, "none");
    stringSet = pkb->get_all_vars_modified_by_stmt(30);
    this->compare_string_set(stringSet, 2, "harp", "nn");
    stringSet = pkb->get_all_vars_modified_by_stmt(31);
    this->compare_string_set(stringSet, 2, "harp", "nn");
    stringSet = pkb->get_all_vars_modified_by_stmt(32);
    this->compare_string_set(stringSet, 1, "harp");
    stringSet = pkb->get_all_vars_modified_by_stmt(33);
    this->compare_string_set(stringSet, 1, "nn");
    stringSet = pkb->get_all_vars_modified_by_stmt(34);
    this->compare_string_set(stringSet, 2, "pfg", "ue");

    stringSet = pkb->get_all_vars_modified_by_stmt(35);
    this->compare_string_set(stringSet, 1, "hoho");
    stringSet = pkb->get_all_vars_modified_by_stmt(36);
    this->compare_string_set(stringSet, 1, "haa");

    stringSet = pkb->get_all_vars_modified_by_stmt(37);
    this->compare_string_set(stringSet, 1, "pfg");
    stringSet = pkb->get_all_vars_modified_by_stmt(38);
    this->compare_string_set(stringSet, 1, "ue");
    stringSet = pkb->get_all_vars_modified_by_stmt(39);
    this->compare_string_set(stringSet, 1, "ue");
}