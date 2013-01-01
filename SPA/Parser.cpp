#include "Parser.h"



Parser::Parser()
{

}

Parser::Parser(string s, ReadMode mode)
{
    tokenizer = *new Tokenizer(s.c_str(), mode);
    nextToken = tokenizer.get_token();
    stmtNo = 0;

    varTable = new VarTable();
    stmtBank = new StmtBank();
    procTable = new ProcTable();

    procRoot = NULL;
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

Node* Parser::get_ast_root()
{
    return astRoot;
}

Node* Parser::get_proc_root()
{
    return procRoot;
}

void Parser::update_tables(){
    // Update the procedure uses and modifies
    procTable->update_table(varTable);
    // Update calls nodes
    update_calls();
    // Updates container nodes
    map<int, Node*>::iterator it;
    map<int, Node*> bank = stmtBank->get_whileBank();
    for (it = bank.begin(); it != bank.end(); it++) {
        update_nodes(it->second);
    }
    bank = stmtBank->get_ifBank();
    for (it = bank.begin(); it != bank.end(); it++) {
        update_nodes(it->second);
    }
}

void Parser::update_nodes(Node *n){
    int stmtNo = n->get_stmtNo();
    if (!n->is_updated()) {
        vector<Node*> v = n->get_children();
        int sz = v.size();
        for (int i = 0; i < sz; i++) {
            update_nodes(v[i]);
            combine_node_up(n, v[i]);
        }
        n->set_updated();
    }
}

void Parser::combine_node_up(Node *n1, Node *n2){
    set<string>::iterator it;
    set<string> s;
    int stmtNo = n1->get_stmtNo();

    s = n2->get_modifies();
    for (it = s.begin(); it != s.end(); it++) {
        n1->add_modifies(*it);
        varTable->add_modified_by(*it,stmtNo);
    }

    s = n2->get_uses();
    for (it = s.begin(); it != s.end(); it++) {
        n1->add_uses(*it);
        varTable->add_used_by(*it,stmtNo);
    }
}


void Parser::update_calls(){
    map<int, Node*>::iterator it;
    map<int, Node*> callBank = stmtBank->get_callBank(); 
    set<string> s;
    string name;
    for (it = callBank.begin(); it != callBank.end(); it++) {
        name = it->second->get_name();
        s = procTable->get_modifies(name);
        it->second->set_modifies(s);
        s = procTable->get_uses(name);
        it->second->set_uses(s);
    }
}

PKB* Parser::get_pkb(){
    update_tables();
    return new PKB(astRoot, procTable, varTable, stmtBank);
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
        error(type);
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
         error(str);
     }
}


//For now just exit on error
void Parser::error()
{
     printf("Error!!!\n");
     printf("State: %s\n",state.c_str());
     getchar();
     exit(1);
}



void Parser::error(tokenType t)
{
     printf("Error!!!\n");
     printf("State: %s\n",state.c_str()); 
     printf("Expecting tokenType: %s\n", printer[t].c_str()); 
     token_out();
     getchar();
     exit(1);
}


void Parser::error(string s)
{
     printf("Error!!!\n");
     printf("State: %s\n",state.c_str());
     printf("Expecting string: %s\n", s.c_str());
     token_out();
     getchar();
     exit(1);
}


/**** Grammer rules ***/

void Parser::program(){
    state = "program";
    astRoot = new Node("program", PROGRAM, stmtNo);
    while (!tokenizer.is_done()){
        procedure();
        procTable->set_end(procName, stmtNo);
    }
}

void Parser::procedure(){
    state = "procedure";
    match("procedure");
    if (nextToken.get_type() == VAR_NAME) {
        nextToken = Token(nextToken.get_name(), PROC_NAME);
    }

    match(PROC_NAME);
    procName = currToken.get_name();
    procRoot = new Node(procName, PROCEDURE, stmtNo);
    astRoot->add_leaf(procRoot);
    procTable->insert_proc(procName);
    procTable->set_proc_root(procName, procRoot);
    procTable->set_start(procName, stmtNo+1);

    match("{");
    nextNode = procRoot;
    create_node("stmt_lst", STMTLST);
    currNode->add_leaf(nextNode);
    stmt_lst();
    match("}");
}

void Parser::stmt_lst(){
    state = "stmt_lst";
    stmt();
    while (nextToken.get_name().compare("}")) {
        stmt();
    }
    nextNode = nextNode->get_root();
}

void Parser::stmt(){
    state = "stmt";
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
    state = "call";
    match("call");
    if (nextToken.get_type() == VAR_NAME) {
        nextToken = Token(nextToken.get_name(), PROC_NAME);
    }

    match(PROC_NAME);
    create_node(currToken.get_name(), CALL_STMT);
    currNode->link_stmt(nextNode);
    stmtBank->add_node_entry(stmtNo, CALLTYPE, nextNode);
    procTable->add_calls(procName, nextNode->get_name());

    match(";");
}

void Parser::while_stmt(){
    state = "while";
    match("while");
    create_node(currToken.get_name(), WHILE_STMT);
    currNode->link_stmt(nextNode);
    stmtBank->add_node_entry(stmtNo, WHILETYPE, nextNode);

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
    state = "if";
    match("if");
    create_node(currToken.get_name(), IF_STMT);
    currNode->link_stmt(nextNode);
    stmtBank->add_node_entry(stmtNo, IFTYPE, nextNode);

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
    state = "assign";
    match(VAR_NAME);
    tempNode = new Node(currToken.get_name(), VARIABLE_, stmtNo);
    
    match("=");
    create_node("=", ASSIGN_STMT);
    currNode->link_stmt(nextNode);
    nextNode->add_leaf(tempNode);
    stmtBank->add_node_entry(stmtNo, ASSIGNTYPE, nextNode);

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
    state = "expr";
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
    state = "term";
    factor();
    if (nextToken.get_name() == "*") {
        match("*");
        tempNode = new Node("*", OPERATOR_, stmtNo);
        check_pre(tempNode);
        term();
    }
}

void Parser::factor(){
    state = "factor";
    tokenType t = nextToken.get_type();
    if (t == VAR_NAME) {
        match(VAR_NAME);
        tempNode = new Node(currToken.get_name(), VARIABLE_, stmtNo);
        add_uses(assignNode, tempNode->get_name());
        outStack.push(tempNode);
    } else if (t == CONSTANT) {
        match(CONSTANT);
        stmtBank->add_constant(currToken.get_name());
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
    varTable->insert_var(var);
    varTable->add_modified_by(var, stmt);
    varTable->add_modified_by(var, procName);
    n->add_modifies(var);
    procTable->add_modifies(procName, var);
}

void Parser::add_uses(Node* n, string var){
    int stmt = n->get_stmtNo();
    varTable->insert_var(var);
    varTable->add_used_by(var, stmt);
    varTable->add_used_by(var, procName);
    n->add_uses(var);
    procTable->add_uses(procName, var);
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
    assignNode = nextNode;
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



void Parser::dumpTable(){
    set<int>::iterator it;
    vector<string>:: iterator varIt;
    set<int> m;
    set<int> u;

    printf("\n\n::::::::: Dumping Table :::::::\n\n");
/*
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
    */
}


