#include "Test_20_PQLParser_DeadQuery.h"
#include "../SPA/PQLParser.h"
#include "../SPA/PQL.h"

#include <string>

using std::string;

void Test_20_PQLParser_DeadQuery::setUp() {}

void Test_20_PQLParser_DeadQuery::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test_20_PQLParser_DeadQuery);

void Test_20_PQLParser_DeadQuery::test_kill_qinfo()
{
    string queryStr, out;
    PQLParser pqlParser;
    QueryInfo *qinfo;
    queryStr = "assign a; Select a";
    pqlParser.parse(queryStr);
    qinfo = pqlParser.get_queryinfo();
    out = "ALIVE\nDECLARATIONS\n  assign a\nSELECT TUPLE\n  assign a\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
    qinfo->kill();
    out = "DEAD\n";
    CPPUNIT_ASSERT_EQUAL(out, qinfo->dump_to_string());
}