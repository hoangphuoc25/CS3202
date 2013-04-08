#include <string>
#include <set>
#include <list>
#include "Test00_QE_misc.h"
#include "../SPA/QueryEvaluator.h"

using std::string;
using std::set;
using std::list;

void Test00_QE_misc::setUp() {}

void Test00_QE_misc::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test00_QE_misc);

void Test00_QE_misc::test_readconfig()
{
    map<string, string> settings;
    QueryEvaluator evaluator(settings);
    // multithreaded off and nrThreads_ = QE_DEFAULT_NR_THREADS by default
    CPPUNIT_ASSERT_EQUAL(false, evaluator.is_multithreaded());
    CPPUNIT_ASSERT_EQUAL(QE_DEFAULT_NR_THREADS,
            evaluator.get_maxThreads());
    // threads on, nrThreads_ = -1
    settings[QE_THREADSON_STR] = YES_STR;
    evaluator.reset(settings);
    CPPUNIT_ASSERT_EQUAL(true, evaluator.is_multithreaded());
    CPPUNIT_ASSERT_EQUAL(QE_DEFAULT_NR_THREADS,
            evaluator.get_maxThreads());
    // threads off, nrThreads_ = 4
    settings.clear();
    settings[QE_MAXTHREADS_STR] = "4";
    evaluator.reset(settings);
    CPPUNIT_ASSERT_EQUAL(false, evaluator.is_multithreaded());
    CPPUNIT_ASSERT_EQUAL(4, evaluator.get_maxThreads());
    // threads on, nrThreads_ = QE_MAX_THREADS [exceed 8 threads here]
    settings.clear();
    settings[QE_THREADSON_STR] = YES_STR;
    settings[QE_MAXTHREADS_STR] = "16";
    evaluator.reset(settings);
    CPPUNIT_ASSERT_EQUAL(true, evaluator.is_multithreaded());
    CPPUNIT_ASSERT_EQUAL(QE_MAX_THREADS, evaluator.get_maxThreads());
    // threads on, nrThreads_ = QE_MIN_THREADS [1 thread specified]
    settings.clear();
    settings[QE_THREADSON_STR] = YES_STR;
    settings[QE_MAXTHREADS_STR] = "1";
    evaluator.reset(settings);
    CPPUNIT_ASSERT_EQUAL(true, evaluator.is_multithreaded());
    CPPUNIT_ASSERT_EQUAL(QE_MIN_THREADS, evaluator.get_maxThreads());
}