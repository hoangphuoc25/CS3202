#include <string>
#include <map>
#include "Test_20_Parser.h"
#include "../SPA/Parser.h"

using std::string;
using std::map;


void Test_20_Parser::setUp() {}
void Test_20_Parser::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test_20_Parser);

// Test shunting yard
void Test_20_Parser::test_one(){
    Parser p;
    p = Parser("Test_20_Parser\\test1\\proc1.txt",FROMFILE);
    p.init();
    Node* n = p.get_ast_root();
    n->out(0, "Test_20_Parser\\test1\\proc1_out.txt");
}

// TEST AST relationships
void Test_20_Parser::test_two(){

    Parser p;
    Node* n;
    /*
    p = Parser("Test_20_Parser\\test2\\Bill.txt",FROMFILE);
    p.init();
    n = p.get_proc_root();
    n->out_relationship("Test_20_Parser\\test2\\Bill_out.txt");

    p = Parser("Test_20_Parser\\test2\\Mary.txt",FROMFILE);
    p.init();
    n = p.get_proc_root();
    n->out_relationship("Test_20_Parser\\test2\\Mary_out.txt");
    
    p = Parser("Test_20_Parser\\test2\\Jane.txt",FROMFILE);
    p.init();
    n = p.get_proc_root();
    n->out_relationship("Test_20_Parser\\test2\\Jane_out.txt");

    p = Parser("Test_20_Parser\\test2\\John.txt",FROMFILE);
    p.init();
    n = p.get_proc_root();
    n->out_relationship("C:Test_20_Parser\\test2\\John_out.txt");*/
}

// TEST AST relationships for program
void Test_20_Parser::test_three(){
    Parser p;
    p = Parser("Test_20_Parser\\test3\\assign1.txt",FROMFILE);
    p.init();
    Node* n = p.get_ast_root();
    n->out(0, "Test_20_Parser\\test3\\assign1_out.txt");
    n->out_relationship("Test_20_Parser\\test3\\assign1_out_relationship.txt");
}
