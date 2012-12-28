#include "Parser.h"



Parser::Parser()
{

}

Parser::Parser(string s, ReadMode mode)
{
    tokenizer = *new Tokenizer(s.c_str(), mode);
    nextToken = tokenizer.get_token();
    stmtNo = 0;
    currNode = NULL;
    nextNode = NULL;
    printer[PROC_NAME] = "PROC_NAME";
    printer[VAR_NAME] = "VAR_NAME";
    printer[OPERATOR] = "OPERATOR";
    printer[EQUALSIGN] = "EQUALSIGN";
    printer[CONSTANT] = "CONSTANT";
    printer[BRACES] = "BRACES";
    printer[BRACKETS] = "BRACKETS";
    printer[KEYWORD] = "KEYWORD";
    printer[NONE] = "NONE";
    op_pre["+"] = 0;
    op_pre["-"] = 0;
    op_pre["*"] = 1;
    op_pre["("] = -1;
}


void Parser::init()
{
    program();
    tokenizer.closeInputFile();
}

Node *Parser::get_ast_root()
{
    return astRoot;
}

Node *Parser::get_proc_root()
{
    return procRoot;
}


/**** match functions ***/
//match token type
void Parser::match(tokenType type)
{
    if (nextToken.get_type() == type) {
        token_out();
        currToken = nextToken;
        nextToken = tokenizer.get_token();
    } else {
        error();
    }
}

//match with a string
void Parser::match(string str)
{
     if (!str.compare(nextToken.get_name())) {
         token_out(); 
         currToken = nextToken;
         nextToken = tokenizer.get_token();
     } else {
         error();
     }
}

//match against multiple token types
void Parser::match_mul(int amt, tokenType type, ...)
{
    va_list vl;
    va_start(vl,type);
    tokenType temp;
    bool flag = false;
    
    if (nextToken.get_type() == type) {
         token_out(); 
         currToken = nextToken;
         nextToken = tokenizer.get_token();
         flag = true;
    }
    
    for (int i = 1; i < amt; i++) {
        if (flag) {
            break;
        }
        temp = (tokenType)va_arg(vl,int);    
        if (nextToken.get_type() == temp) {
            token_out();
            currToken = nextToken;
            nextToken = tokenizer.get_token();
            flag = true;
        }
    }
    
    if (flag == false) {
        error();
    }
}

//match against multiple strings
void Parser::match_mul(int amt, char* str, ...)
{
     va_list vl;
     va_start(vl,str);
     string temp;
     bool flag = false;
     temp = str;
     if (!temp.compare(nextToken.get_name())) {
         token_out();
         currToken = nextToken;
         nextToken = tokenizer.get_token();
         flag = true;
     }
     
     for (int i = 1; i < amt; i++) {
        if (flag == true) {
            break;
        }
        temp = string(va_arg(vl,char*));
        if (!temp.compare(nextToken.get_name())) {
            token_out();
            currToken = nextToken;
            nextToken = tokenizer.get_token();
            flag = true;
        }
     }

     if (flag == false) {
         error();
     }
}



//For now just exit on error
void Parser::error()
{
     printf("Error!!!\n");
     token_out();
     getchar();
     exit(1);
}


/**** Grammer rules ***/

void Parser::program(){
// handle multiple procedure

    procedure();
}

void Parser::procedure(){
    match("procedure");
    match(PROC_NAME);
    nextNode = procRoot = new Node(currToken.get_name(), PROCEDURE, stmtNo);
    match("{");
    create_node("stmt_lst", STMTLST);
    currNode->add_leaf(nextNode);
    stmt_lst();
    match("}");
}

void Parser::stmt_lst(){
    stmt();
    while (nextToken.get_name().compare("}")) {
        stmt();
    }
    nextNode = nextNode->get_root();
}

void Parser::stmt(){
    stmtNo++;
    string s = nextToken.get_name();
    if (s == "call") {
        call_stmt();
    } else if (s == "while") {
        while_stmt();
    } else if (s == "if") {
        if_stmt();
    } else {
        assign();
    }
}

void Parser::call_stmt(){
    match("call");
    if (nextToken.get_type() == VAR_NAME) {
        nextToken = Token(nextToken.get_name(), PROC_NAME);
    }
    match(PROC_NAME);
    create_node(currToken.get_name(), CALL_STMT);
    currNode->link_stmt(nextNode);
    pkb.add_node_entry(stmtNo, CALLTYPE, nextNode);
    /*directory[stmtNo] = CALLTYPE;
    callBank[stmtNo] = nextNode;*/
    match(";");
}

void Parser::while_stmt(){
    match("while");
    create_node(currToken.get_name(), WHILE_STMT);
    currNode->link_stmt(nextNode);
    pkb.add_node_entry(stmtNo, WHILETYPE, nextNode);
    /*directory[stmtNo] = WHILETYPE;
    whileBank[stmtNo] = nextNode;*/
    
    match(VAR_NAME);
    string varName = currToken.get_name();
    create_node(varName, VARIABLE_);
    currNode->add_leaf(nextNode);
    add_uses(currNode, varName);
    currNode->set_control_var(varName);

    match("{");
    create_node("while_stmtLst", STMTLST);
    currNode->get_root()->add_leaf(nextNode);
    stmt_lst();
    match("}");
    nextNode = nextNode->get_root();
}

void Parser::if_stmt(){
    match("if");
    create_node(currToken.get_name(), IF_STMT);
    currNode->link_stmt(nextNode);
    pkb.add_node_entry(stmtNo, IFTYPE, nextNode);
    /*directory[stmtNo] = IFTYPE;
    ifBank[stmtNo] = nextNode;*/

    match(VAR_NAME);
    string varName = currToken.get_name();
    create_node(varName, VARIABLE_);
    currNode->add_leaf(nextNode);
    add_uses(currNode, varName);
    currNode->set_control_var(varName);

    match("then");
    create_node("then", STMTLST);
    currNode->get_root()->add_leaf(nextNode);

    match("{");
    stmt_lst();
    match("}");
    match("else");
    create_node("else", STMTLST);
    currNode->get_root()->add_leaf(nextNode);

    match("{");
    stmt_lst();
    match("}");
    nextNode = nextNode->get_root();
}
void Parser::assign(){
    match(VAR_NAME);
    tempNode = new Node(currToken.get_name(), VARIABLE_, stmtNo);
    
    match("=");
    create_node("=", ASSIGN_STMT);
    currNode->link_stmt(nextNode);
    nextNode->add_leaf(tempNode);
    pkb.add_node_entry(stmtNo, ASSIGNTYPE, nextNode);
    /*directory[stmtNo] = ASSIGNTYPE;
    assignBank[stmtNo] = nextNode;*/
    add_modifies(nextNode, tempNode->get_name());

    assignNode = nextNode;
    expr();
    while (!opStack.empty()) {
        join();
    }
    assignNode->add_leaf(outStack.top());
    outStack.pop();
    match(";");
}

void Parser::expr(){
    term();
    string s = nextToken.get_name();
    if (s == "+") {
        match("+");
        tempNode = new Node("+", OPERATOR_, stmtNo);
        check_pre(tempNode);
        expr();
    } else if (s == "-") {
        match("-");
        tempNode = new Node("-", OPERATOR_, stmtNo);
        check_pre(tempNode);
        expr();
    }
}

void Parser::term(){
    factor();
    if (nextToken.get_name() == "*") {
        match("*");
        tempNode = new Node("*", OPERATOR_, stmtNo);
        check_pre(tempNode);
        term();
    }
}

void Parser::factor(){
    tokenType t = nextToken.get_type();
    if (t == VAR_NAME) {
        match(VAR_NAME);
        tempNode = new Node(currToken.get_name(), VARIABLE_, stmtNo);
        add_uses(assignNode, tempNode->get_name());
        outStack.push(tempNode);
    } else if (t == CONSTANT) {
        match(CONSTANT);
        tempNode = new Node(currToken.get_name(), CONSTANT_, stmtNo);
        outStack.push(tempNode);
    } else {
        match("(");
        tempNode = new Node("(", BRACKETS_, stmtNo);
        check_pre(tempNode);
        expr();
        match(")");
        tempNode = new Node(")", BRACKETS_, stmtNo);
        check_pre(tempNode);
    }
}

// Helpers

void Parser::create_node(string name, NodeType type){
    currNode = nextNode;
    nextNode = new Node(name, type, stmtNo);
}

void Parser::add_modifies(Node* n, string var){
    int stmt = n->get_stmtNo();
    pkb.add_modifies(var, stmt);
    /*varTable.insert_var(var);
    varTable.add_modified_by(var, stmt);*/
    n->add_modifies(var);
}

void Parser::add_uses(Node* n, string var){
    int stmt = n->get_stmtNo();
    pkb.add_modifies(var, stmt);
    /*varTable.insert_var(var);
    varTable.add_used_by(var, stmt);*/
    n->add_uses(var);
}





// Shunting Yard

void Parser::join(){
    Node* right = outStack.top();
    outStack.pop();
    Node* left = outStack.top();
    outStack.pop();
    Node* op = opStack.top();
    opStack.pop();
    op->add_leaf(left);
    op->add_leaf(right);
    outStack.push(op);
}

void Parser::check_pre(Node *op){

    if(op->get_name() == ")") {
        while (opStack.top()->get_name() != "(") {
            join();
        }
        opStack.pop();
        return;
    }

    if(op->get_name() == "(") {
        opStack.push(op);
        return;
    }

    if (!opStack.empty()) {
        Node *op2 = opStack.top();
        while(op_pre[op->get_name()] <= op_pre[op2->get_name()]) {
            join();
            if(opStack.empty()) {
                break;
            }
            op2 = opStack.top();
        }
    }
     opStack.push(op);
}

Node* Parser::yard(){
    if (nextToken.get_type() == PROC_NAME) {
        nextToken = Token(nextToken.get_name(), VAR_NAME);
    }
    match(VAR_NAME);
    tempNode = new Node(currToken.get_name(), VARIABLE_, stmtNo);
    match("=");
    create_node("=", ASSIGN_STMT);
    nextNode->add_leaf(tempNode);
    expr();
    while (!opStack.empty()) {
        join();
    }
    nextNode->add_leaf(outStack.top());
    outStack.pop();
    return nextNode;
}

/**** Printer functions ***/

void Parser::token_out(){
    printf("Token parsed: (%s , %s)\n",nextToken.get_name().c_str(),printer[nextToken.get_type()].c_str());     

}

void Parser::dumpBank(){
    map<int,stmtType>::iterator it;

    printf("\n\n::::::::: Dumping Bank :::::::\n\n");

    for (it = directory.begin(); it!= directory.end(); it++) {
        switch (it->second) {
            case CALLTYPE:
                callBank[it->first]->dumpR();
                break;
            case WHILETYPE:
                whileBank[it->first]->dumpR();
                break;
            case IFTYPE:
                ifBank[it->first]->dumpR();;
                break;
            case ASSIGNTYPE:
                assignBank[it->first]->dumpR();
                break;
        }
    }
}

void Parser::dumpTable(){
    set<int>::iterator it;
    vector<string>:: iterator varIt;
    set<int> m;
    set<int> u;

    printf("\n\n::::::::: Dumping Table :::::::\n\n");

    vector<string> var = varTable.get_all_vars();
    for (varIt = var.begin(); varIt != var.end(); varIt++){
        printf("Variable: %s\n", varIt->c_str());
        m = varTable.get_modified_by(*varIt);
        for (it = m.begin(); it != m.end(); it++) {
            printf("Modified by: %d\n", *it);
        }
        u = varTable.get_used_by(*varIt);
        for (it = u.begin(); it != u.end(); it++) {
            printf("Used by: %d\n", *it);
        }
        putchar('\n');
    }

}


