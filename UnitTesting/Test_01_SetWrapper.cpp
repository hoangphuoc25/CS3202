#include "Test_01_SetWrapper.h"
#include "../SPA/SetWrapper.h"

#include <list>
#include <set>
#include <string>

using std::list;
using std::set;
using std::string;

void Test_01_SetWrapper::setUp() {}

void Test_01_SetWrapper::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test_01_SetWrapper);

void Test_01_SetWrapper::test_set_ctor()
{
    set<string> S;
    S.insert("well");
    S.insert("thats");
    S.insert("great");
    SetWrapper<string> stringSet(S);
    CPPUNIT_ASSERT_EQUAL(string("great thats well\n"),
            stringSet.toString());
}

void Test_01_SetWrapper::test_list_ctor()
{
    list<string> l;
    l.push_back("aa");
    l.push_back("bcd");
    l.push_back("dupstr");
    l.push_back("123");
    l.push_back("dupstr");
    l.push_back("find");
    SetWrapper<string> stringSet(l);
    CPPUNIT_ASSERT_EQUAL(string("123 aa bcd dupstr find\n"),
            stringSet.toString());
}

void Test_01_SetWrapper::test_copy_ctor()
{
    set<string> S;
    S.insert("5");
    S.insert("many");
    S.insert("peoples");
    S.insert("have");
    S.insert("died");
    S.insert("fire");
    SetWrapper<string> stringSet(S);
    SetWrapper<string> anotherSet(stringSet);
    CPPUNIT_ASSERT_EQUAL(string("5 died fire have many peoples\n"),
            stringSet.toString());
    CPPUNIT_ASSERT_EQUAL(string("5 died fire have many peoples\n"),
            anotherSet.toString());
    S.clear();
    S.insert("AA");
    anotherSet = SetWrapper<string>(S);
    CPPUNIT_ASSERT_EQUAL(string("5 died fire have many peoples\n"),
            stringSet.toString());
    CPPUNIT_ASSERT_EQUAL(string("AA\n"),
            anotherSet.toString());
}

void Test_01_SetWrapper::test_equality()
{
    set<string> S;
    S.insert("because");
    S.insert("of");
    S.insert("you");
    S.insert("I");
    S.insert("am");
    S.insert("afraid");
    S.insert("madamiamadam");
    SetWrapper<string> sw1, sw2, sw3;
    sw1 = SetWrapper<string>(S);
    sw2 = SetWrapper<string>(S);
    CPPUNIT_ASSERT_EQUAL(sw1, sw2);
    set<string> S2;
    S2.insert("you");
    S2.insert("of");
    S2.insert("I");
    S2.insert("am");
    S2.insert("because");
    S2.insert("madamiamadam");
    S2.insert("afraid");
    sw3 = SetWrapper<string>(S2);
    CPPUNIT_ASSERT_EQUAL(sw1, sw3);
}