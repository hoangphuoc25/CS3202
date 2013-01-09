#include <string>
#include <map>
#include "TestParser.h"
#include "../SPA/Parser.h"

using std::string;
using std::map;


void TestParser::setUp() {}
void TestParser::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(TestParser);

// Test shunting yard
void TestParser::test_one(){
    Parser p;
    p = Parser("TestParser\\test1\\proc1.txt",FROMFILE);
    p.init();
    Node* n = p.get_ast_root();
    n->out(0, "TestParser\\test1\\proc1_out.txt");
}

// TEST AST relationships
void TestParser::test_two(){

    Parser p;
    Node* n;
    /*
    p = Parser("TestParser\\test2\\Bill.txt",FROMFILE);
    p.init();
    n = p.get_proc_root();
    n->out_relationship("TestParser\\test2\\Bill_out.txt");

    p = Parser("TestParser\\test2\\Mary.txt",FROMFILE);
    p.init();
    n = p.get_proc_root();
    n->out_relationship("TestParser\\test2\\Mary_out.txt");
    
    p = Parser("TestParser\\test2\\Jane.txt",FROMFILE);
    p.init();
    n = p.get_proc_root();
    n->out_relationship("TestParser\\test2\\Jane_out.txt");

    p = Parser("TestParser\\test2\\John.txt",FROMFILE);
    p.init();
    n = p.get_proc_root();
    n->out_relationship("C:TestParser\\test2\\John_out.txt");*/
}

// TEST AST relationships for program
void TestParser::test_three(){
    Parser p;
    p = Parser("TestParser\\test3\\assign1.txt",FROMFILE);
    p.init();
    Node* n = p.get_ast_root();
    n->out(0, "TestParser\\test3\\assign1_out.txt");
    n->out_relationship("TestParser\\test3\\assign1_out_relationship.txt");
}
