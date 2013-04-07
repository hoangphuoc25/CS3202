// disable warnings about using strcat
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstring>
#include <string>

#include "../SPA/StringBuffer.h"
#include "Test_00_StringBuffer.h"

using std::string;

void Test_00_StringBuffer::setUp() {}
void Test_00_StringBuffer::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test_00_StringBuffer);

void Test_00_StringBuffer::testAppendChar()
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

void Test_00_StringBuffer::testAppendCString()
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

void Test_00_StringBuffer::testAppendString()
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

void Test_00_StringBuffer::testAppendInt()
{
    StringBuffer sb;
    int cnt;
    sb.append_int(0);
    string s = "0";
    CPPUNIT_ASSERT_EQUAL(s, sb.toString());
    cnt = sb.append_int(5);
    s += "5";
    CPPUNIT_ASSERT_EQUAL(s, sb.toString());
    CPPUNIT_ASSERT_EQUAL(1, cnt);
    cnt = sb.append_int(0);
    s += "0";
    CPPUNIT_ASSERT_EQUAL(s, sb.toString());
    CPPUNIT_ASSERT_EQUAL(1, cnt);
    cnt = sb.append_int(74);
    s += "74";
    CPPUNIT_ASSERT_EQUAL(s, sb.toString());
    CPPUNIT_ASSERT_EQUAL(2, cnt);
    cnt = sb.append_int(100);
    s += "100";
    CPPUNIT_ASSERT_EQUAL(s, sb.toString());
    CPPUNIT_ASSERT_EQUAL(3, cnt);
    cnt = sb.append_int(999);
    s += "999";
    CPPUNIT_ASSERT_EQUAL(s, sb.toString());
    CPPUNIT_ASSERT_EQUAL(3, cnt);
    cnt = sb.append_int(524138);
    s += "524138";
    CPPUNIT_ASSERT_EQUAL(s, sb.toString());
    CPPUNIT_ASSERT_EQUAL(6, cnt);
}

void Test_00_StringBuffer::testAppendMixed()
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

void Test_00_StringBuffer::testClear()
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

void Test_00_StringBuffer::testStrcmp()
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

void Test_00_StringBuffer::testCstr()
{
    StringBuffer sb;
    sb.append('a');
    sb.append(" big brown fox jumps over a gray dog");
    const char *str = "a big brown fox jumps over a gray dog";
    int ret = strcmp(str, sb.c_str());
    CPPUNIT_ASSERT_EQUAL(0, ret);
}

void Test_00_StringBuffer::testSprintf()
{
    StringBuffer sb;
    const char *fmt = "this is %% just a %d %s%% %c";
    int cnt = sb.sprintf(fmt, 13, "test", '!');
    string s = "this is % just a 13 test% !";
    CPPUNIT_ASSERT_EQUAL(s, sb.toString());
    CPPUNIT_ASSERT_EQUAL(27, cnt);
    // invalid %v
    const char *fmt2 = "%s%d%s%d%s%d%c block%v%d";
    cnt += sb.sprintf(fmt2, " hi Agent ", 17, ", welcome ", 2,
                    " your new home. ", 25, 'C', 721);
    s += " hi Agent 17, welcome 2 your new home. 25C block%v721";
    CPPUNIT_ASSERT_EQUAL(s, sb.toString());
    CPPUNIT_ASSERT_EQUAL(80, cnt);
}

void Test_00_StringBuffer::testSubstitutef()
{
    StringBuffer sb;
    const char *fmt = "this is %s just %% a %d test %s%s\n";
    const char *sub = "wow";
    string out = "this is wow just %% a %d test wowwow\n";
    int ate = sb.substitutef(fmt, sub);
    CPPUNIT_ASSERT_EQUAL(37, ate);
    CPPUNIT_ASSERT_EQUAL(out, sb.toString());

    StringBuffer strbuf;
    const char *fmt2 = "this is %s %s %s %s %s %s %s";
    const char *sub2 = "hard or easy to dish of wash in bath it";
    ate = strbuf.substitutef(fmt2, sub2);
    CPPUNIT_ASSERT_EQUAL(287, ate);
    out = "this is";
    for (int i = 0; i < 7; i++) {
        out += " hard or easy to dish of wash in bath it";
    }
    CPPUNIT_ASSERT_EQUAL(out, strbuf.toString());
}

void Test_00_StringBuffer::testSubstitutefCppString()
{
    StringBuffer sb;
    const char *fmt = "this is %s so %e %d shit %% %s xors";
    string sub = "bleh";
    string out = "this is bleh so %e %d shit %% bleh xors";
    int ate = sb.substitutef(fmt, sub);
    CPPUNIT_ASSERT_EQUAL(39, ate);
    CPPUNIT_ASSERT_EQUAL(out, sb.toString());
}

void Test_00_StringBuffer::testRemovespaces()
{
    StringBuffer sb;
    string out;
    sb.append("  this is just a tt \t \n test   ");
    sb.remove_spaces();
    out = "thisisjustatttest";
    CPPUNIT_ASSERT_EQUAL(out, sb.toString());
    CPPUNIT_ASSERT_EQUAL((int)out.size(), sb.size());
    sb.append("merry go round 1 2 3 45");
    out += "merry go round 1 2 3 45";
    CPPUNIT_ASSERT_EQUAL(out, sb.toString());
    CPPUNIT_ASSERT_EQUAL((int)out.size(), sb.size());
    sb.remove_spaces();
    out = "thisisjustatttestmerrygoround12345";
    CPPUNIT_ASSERT_EQUAL(out, sb.toString());
    CPPUNIT_ASSERT_EQUAL((int)out.size(), sb.size());
}

void Test_00_StringBuffer::testSize()
{
    StringBuffer sb;
    CPPUNIT_ASSERT_EQUAL(0, sb.size());
    for (int i = 0; i < 26; i++) {
        sb.append(i + 'a');
    }
    CPPUNIT_ASSERT_EQUAL(26, sb.size());
    sb.append("sdrawkcab tleps si ecnetnes sihT");
    CPPUNIT_ASSERT_EQUAL(58, sb.size());
    sb.append(string("aloha "));
    CPPUNIT_ASSERT_EQUAL(64, sb.size());
    sb.clear();
    CPPUNIT_ASSERT_EQUAL(0, sb.size());
    sb.append('b');
    CPPUNIT_ASSERT_EQUAL(1, sb.size());
}