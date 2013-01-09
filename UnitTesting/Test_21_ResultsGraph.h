#ifndef T11_TEST_21_RESULTSGRAPH_H
#define T11_TEST_21_RESULTSGRAPH_H

#include <map>
#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test_21_ResultsGraph: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test_21_ResultsGraph);
CPPUNIT_TEST(test_empty_graph);
CPPUNIT_TEST(test_add_vertex);
CPPUNIT_TEST(test_add_edge);
CPPUNIT_TEST(test_prune_add_all);
CPPUNIT_TEST(test_prune_nonempty_death);
CPPUNIT_TEST(test_prune_1);
CPPUNIT_TEST(test_prune_2);
CPPUNIT_TEST(test_prune_3);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

private:
    void test_empty_graph();
    void test_add_vertex();
    void test_add_edge();
    void test_prune_add_all();
    void test_prune_nonempty_death();
    void test_prune_1();
    void test_prune_2();
    void test_prune_3();
};

#endif