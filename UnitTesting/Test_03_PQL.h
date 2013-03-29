#ifndef T04_TEST_03_PQL_H
#define T04_TEST_03_PQL_H

#include <map>
#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test_03_PQL: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test_03_PQL);
CPPUNIT_TEST(test_relRefType_to_string);
CPPUNIT_TEST(test_entity_type_to_string);
CPPUNIT_TEST(test_attrType_to_string);
CPPUNIT_TEST(test_designEnt_to_relRefArgType);
CPPUNIT_TEST(test_refSynType_to_BaseType);
CPPUNIT_TEST(test_baseType_to_string);
CPPUNIT_TEST(test_attrRef_to_RefSynType);
CPPUNIT_TEST(test_withClause_normalize);
CPPUNIT_TEST(test_withClause_is_contradiction);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

private:
    void test_relRefType_to_string();
    void test_entity_type_to_string();
    void test_attrType_to_string();
    void test_designEnt_to_relRefArgType();
    void test_refSynType_to_BaseType();
    void test_baseType_to_string();
    void test_attrRef_to_RefSynType();
    void test_withClause_normalize();
    void test_withClause_is_contradiction();
};

#endif