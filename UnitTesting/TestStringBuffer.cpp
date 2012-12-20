#include <cstring>
#include <string>

#include "../SPA/StringBuffer.h"
#include "TestStringBuffer.h"

using std::string;

void TestStringBuffer::setUp() {}
void TestStringBuffer::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(TestStringBuffer);

void TestStringBuffer::testAppendChar()
{
    StringBuffer sb;
    string src, s;
    src = "";
    for (int i = 0; i < 10; i++) {
        for (int k = 0; k < 26; k++) {
            sb.append('a' + k);
            src += ('a' + k);
        }
    }
    s = sb.toString();
    CPPUNIT_ASSERT_EQUAL(src, s);
}

void TestStringBuffer::testAppendCString()
{
    const char *sArr[] = {
        "This is the first string",
        "there are many characters",
        "In short, this tests whether",
        "our string buffer is able to",
        "handle long strings"
    };
    int totalLen = 0;
    char *cat;
    for (int i = 0; i < 5; i++) {
        totalLen += strlen(sArr[i]);
    }
    cat = new char[totalLen+5];
    cat[0] = 0;
    for (int i = 0; i < 5; i++) {
        strcat(cat, sArr[i]);
    }
    StringBuffer sb;
    for (int i = 0; i < 5; i++) {
        sb.append(sArr[i]);
    }
    string src = string(cat);
    string s = sb.toString();
    CPPUNIT_ASSERT_EQUAL(src, s);
    delete[] cat;
}

void TestStringBuffer::testAppendString()
{
    string s, src;
    StringBuffer sb;
    src = "";
    for (int i = 0; i < 5; i++) {
        s = "";
        for (int k = 0; k < 26; k++) {
            s += ('a' + k);
        }
        sb.append(s);
        src += s;
    }
    CPPUNIT_ASSERT_EQUAL(src, sb.toString());
}

void TestStringBuffer::testAppendMixed()
{
    StringBuffer sb;
    string src = "";
    for (int i = 0; i < 10; i++) {
        for (int k = 0; k < 26; k++) {
            sb.append('a' + k);
            src += ('a' + k);
        }
    }
    const char *sArr[] = {
        "sunshine, flowers, trees, paths",
        "swords, fire, bricks, mortar, hay, horses",
        "torn, soul, asunder, fury, high, heaven",
        "beauty, peace, tranquility, green, water",
        "sticks, stones, bones, cast, iron"
    };
    for (int i = 0; i < 5; i++) {
        src += string(sArr[i]);
        sb.append(sArr[i]);
    }
    string s;
    for (int i = 0; i < 10; i++) {
        s = "";
        for (int k = 0; k < 10; k++) {
            s += '0' + k;
        }
        src += s;
        sb.append(s);
    }
    CPPUNIT_ASSERT_EQUAL(src, sb.toString());
}

void TestStringBuffer::testClear()
{
    string src = "";
    StringBuffer sb;
    for (int i = 0; i < 10; i++) {
        for (int k = 0; k < 26; k++) {
            src += 'a' + k;
            sb.append('a' + k);
        }
    }
    CPPUNIT_ASSERT_EQUAL(src, sb.toString());
    sb.clear();
    CPPUNIT_ASSERT_EQUAL(string(), sb.toString());
    src = "";
    for (int i = 0; i < 10; i++) {
        src += i + '0';
        sb.append(i + '0');
    }
    CPPUNIT_ASSERT_EQUAL(src, sb.toString());
}

void TestStringBuffer::testStrcmp()
{
    StringBuffer sb;
    for (int i = 0; i < 26; i++) {
        sb.append(i + 'a');
    }
    int ret = sb.strcmp("abcdefghijklmnopqrstuvwxyz");
    CPPUNIT_ASSERT_EQUAL(0, ret);
    ret = sb.strcmp("aye");
    CPPUNIT_ASSERT_EQUAL(-1, ret);
    ret = sb.strcmp("aaa");
    CPPUNIT_ASSERT_EQUAL(1, ret);
}