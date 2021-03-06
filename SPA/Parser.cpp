#include <cassert>
#include "Parser.h"
#include "SPAUtils.h"

Parser::Parser()
{

}

Parser::Parser(string s, ReadMode mode)
{
    tokenizer = *new Tokenizer(s.c_str(), mode);
    nextToken = tokenizer.get_token();
    stmtNo = 0;
    makeTree = false;
    treeError = false;

    varTable = new VarTable();
    stmtBank = new StmtBank();
    procTable = new ProcTable();
    CFG = new vector<CFGNode*>;

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

PKB* Parser::get_pkb()
{
    make_CFG();
    update_tables();
    return new PKB(astRoot, procTable, varTable, stmtBank, CFG);
}

// Updaters
void Parser::update_tables()
{
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

void Parser::update_nodes(Node *n)
{
    int stmtNo = n->get_stmtNo();
    if (!n->is_updated()) {
        const vector<Node*>& v = n->get_children();
        int sz = v.size();
        for (int i = 0; i < sz; i++) {
            update_nodes(v[i]);
            combine_node_up(n, v[i]);
        }
        n->set_updated();
    }
}

void Parser::combine_node_up(Node *topNode, Node *botNode)
{
    set<string>::iterator it;
    set<string> s;
    int stmtNo = topNode->get_stmtNo();
    NodeType topNodeType = topNode->get_type();
    assert(topNodeType == IF_STMT || topNodeType == WHILE_STMT);
    bool addIfMod = (topNodeType == IF_STMT);
    bool addWhileMod = (topNodeType == WHILE_STMT);
    s = botNode->get_modifies();
    for (it = s.begin(); it != s.end(); it++) {
        topNode->add_modifies(*it);
        if (addIfMod) {
            this->varTable->add_if_modifies_var(stmtNo, *it);
        }
        if (addWhileMod) {
            this->varTable->add_while_modifies_var(stmtNo, *it);
        }
        this->varTable->add_stmt_modifies_var(stmtNo, *it);
    }

    // if / while use the variables that its descendents use
    DesignEnt topNodeEntType = ENT_INVALID;
    switch (topNodeType) {
    case IF_STMT:
        topNodeEntType = ENT_IF;
        break;
    case WHILE_STMT:
        topNodeEntType = ENT_WHILE;
        break;
    }
    s = botNode->get_uses();
    for (it = s.begin(); it != s.end(); it++) {
        topNode->add_uses(*it);
        this->varTable->add_used_by(*it, topNodeEntType, stmtNo);
    }
}


void Parser::update_calls()
{
    map<int, Node*>::iterator it;
    map<int, Node*> callBank = stmtBank->get_callBank(); 
    set<string> s;
    set<string>::iterator sit;
    string name;
    CFGNode *call, *next;
    for (it = callBank.begin(); it != callBank.end(); it++) {
        Node *callNode = it->second;
        int callNodeStmtNo = callNode->get_stmtNo();
        name = callNode->get_name();
        s = procTable->get_modifies(name);
        callNode->set_modifies(s);
        for (sit = s.begin(); sit != s.end(); sit++) {
            varTable->add_call_modifies_var(callNodeStmtNo, *sit);
        }
        s = procTable->get_vars_used_by_proc(name);
        callNode->set_uses(s);
        // Set call stmt to use variable
        for (sit = s.begin(); sit != s.end(); sit++) {
            this->varTable->add_used_by(*sit, ENT_CALL, callNode->get_stmtNo());
        }
        // Update CFG with BIP links
        call = CFG->at(callNodeStmtNo);
        set_BIPedge(call,progHead[name]);
        call->set_caller();
        next = call->get_edge(OUT,1);
        assert(next != NULL);
        while (next->get_stmtNo() == DUMMY && !next->is_terminator()) {
                next = next->get_edge(OUT, 1);
        }
        set_BIPedge(progTail[name],next);
    }
}

// Match functions
void Parser::match(tokenType type)
{
    if (nextToken.get_type() == type) {
        //token_out();
        currToken = nextToken;
        nextToken = tokenizer.get_token();
    } else {
        if(makeTree) {
            treeError = true;
        } else {
            error(type);
        }
    }
}

void Parser::match(string str)
{
     if (!str.compare(nextToken.get_name())) {
         //token_out(); 
         currToken = nextToken;
         nextToken = tokenizer.get_token();
     } else {
        if(makeTree) {
            treeError = true;
        } else {
            error(str);
        }
     }
}

void Parser::error()
{
     printf("Error!!!\n");
     printf("State: %s\n",state.c_str());
     token_out();
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

// Grammer rules
void Parser::program()
{
    state = "program";
    astRoot = new Node("program", PROGRAM, -1);
    while (!tokenizer.is_done()){
        procedure();
        procTable->set_end(procName, stmtNo);
    }
}

void Parser::procedure()
{
    state = "procedure";
    match("procedure");
    /*if (nextToken.get_type() == VAR_NAME) {
        nextToken = Token(nextToken.get_name(), PROC_NAME);
    }*/
    match(PROC_NAME);
    procName = currToken.get_name();
    procRoot = new Node(procName, PROCEDURE, 0);
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

void Parser::stmt_lst()
{
    state = "stmt_lst";
    int stmtNo = stmt();
    this->stmtBank->add_stmtLst(stmtNo);
    while (nextToken.get_name().compare("}")) {
        stmt();
    }
    nextNode = nextNode->get_root();
}

int Parser::stmt()
{
    state = "stmt";
    stmtNo++;
    int retStmtNo = stmtNo;
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
    return retStmtNo;
}

void Parser::call_stmt()
{
    state = "call";
    match("call");
    if (nextToken.get_type() == VAR_NAME) {
        nextToken = Token(nextToken.get_name(), PROC_NAME);
    }

    match(PROC_NAME);
    create_node(currToken.get_name(), CALL_STMT);
    currNode->link_stmt(nextNode);
    stmtBank->add_node_entry(stmtNo, ENT_CALL, nextNode);
    procTable->add_calls(procName, nextNode->get_name());

    match(";");
}

void Parser::while_stmt()
{
    state = "while";
    match("while");
    create_node(currToken.get_name(), WHILE_STMT);
    currNode->link_stmt(nextNode);
    stmtBank->add_node_entry(stmtNo, ENT_WHILE, nextNode);

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

void Parser::if_stmt()
{
    state = "if";
    match("if");
    create_node(currToken.get_name(), IF_STMT);
    currNode->link_stmt(nextNode);
    stmtBank->add_node_entry(stmtNo, ENT_IF, nextNode);

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

void Parser::assign()
{
    state = "assign";
    match(VAR_NAME);
    tempNode = new Node(currToken.get_name(), VARIABLE_, stmtNo);
    
    match("=");
    create_node("=", ASSIGN_STMT);
    currNode->link_stmt(nextNode);
    nextNode->add_leaf(tempNode);
    stmtBank->add_node_entry(stmtNo, ENT_ASSIGN, nextNode);

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

void Parser::expr()
{
    state = "expr";
    term();
    if (treeError) {
        return;
    }
    string s = nextToken.get_name();
    if (s == "+") {
        match("+");
        if (treeError) {
            return;
        }
        tempNode = new Node("+", OPERATOR_, stmtNo);
        check_pre(tempNode);
        expr();
    } else if (s == "-") {
        match("-");
        if (treeError) {
            return;
        }
        tempNode = new Node("-", OPERATOR_, stmtNo);
        check_pre(tempNode);
        expr();
    }
}

void Parser::term()
{
    state = "term";
    factor();
    if (treeError) {
        return;
    }
    if (nextToken.get_name() == "*") {
        match("*");
        if (treeError) {
            return;
        }
        tempNode = new Node("*", OPERATOR_, stmtNo);
        check_pre(tempNode);
        term();
    }
}

void Parser::factor()
{
    state = "factor";
    tokenType t = nextToken.get_type();
    if (t == VAR_NAME) {
        match(VAR_NAME);
        if (treeError) {
            return;
        }
        tempNode = new Node(currToken.get_name(), VARIABLE_, stmtNo);
        if (!makeTree) {
            add_uses(assignNode, tempNode->get_name());
        }
        outStack.push(tempNode);
    } else if (t == CONSTANT) {
        char *errorMsg = NULL;
        bool ret;
        match(CONSTANT);
        if (treeError) {
            return;
        }
        ret = stmtBank->add_constant(currToken.get_name(), &errorMsg);
        if (!ret) {
            // TODO: error out and show error message??
            free(errorMsg);
        } else {
            tempNode = new Node(currToken.get_name(), CONSTANT_, stmtNo);
            outStack.push(tempNode);
        }
    } else {
        match("(");
        if (treeError) {
            return;
        }
        tempNode = new Node("(", BRACKETS_, stmtNo);
        check_pre(tempNode);
        expr();
        if (treeError) {
            return;
        }
        match(")");
        if (treeError) {
            return;
        }
        tempNode = new Node(")", BRACKETS_, stmtNo);
        check_pre(tempNode);
    }
}

// Shunting Yard
void Parser::join()
{
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

void Parser::check_pre(Node *op)
{
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

Node* Parser::yard()
{
    makeTree = true;
    treeError = false;
    expr();
    if (treeError) {
        return NULL;
    }
    while (!opStack.empty()) {
        join();
    }
    treeNode = outStack.top();
    outStack.pop();
    return treeNode;
}

// CFG builder
void Parser::init_CFG()
{
    CFG->resize(stmtNo+10);
    int sz = CFG->size();
    for (int i = 0; i < sz; i++) {
        CFG->at(i) = new CFGNode(i);
    }
}
/*
CFGNode* Parser::build_CFG(int stmtNo)
{
    Node *n, *branch;
    int next, if_succ;
    
    if (stmtBank->is_stmt_type(stmtNo, ENT_IF)) {
         n = stmtBank->get_node(stmtNo)->get_successor();
         if (n != NULL) {
             if_succ = n->get_stmtNo();
         } else {
             if_succ = -1;
         }
         
         n = stmtBank->get_node(stmtNo);
         
         branch = n->get_leaves()[1]->get_leaves()[0];
         next = branch->get_stmtNo();
         CFG[stmtNo]->set_edge(CFG[next], OUT, 1);
         CFG[next]->set_edge(CFG[stmtNo], IN, 1);
         next = build_CFG(next);
         CFG[0]->set_edge(CFG[next], IN, 1);

         branch = n->get_leaves()[2]->get_leaves()[0];
         next = branch->get_stmtNo();
         CFG[stmtNo]->set_edge(CFG[next], OUT, 2);
         CFG[next]->set_edge(CFG[stmtNo], IN, 1);
         next = build_CFG(next);
         CFG[0]->set_edge(CFG[next], IN, 2);

         if (if_succ != -1) {
            CFG[0]->get_edge(IN, 1)->set_edge(CFG[if_succ], OUT, 1);
            CFG[0]->get_edge(IN, 2)->set_edge(CFG[if_succ], OUT, 1);
            CFG[if_succ]->set_edge(CFG[0]->get_edge(IN, 1), IN, 1);
            CFG[if_succ]->set_edge(CFG[0]->get_edge(IN, 2), IN, 2);
            return build_CFG(if_succ);
         } else {
             return 0;
         }
    } else {
        if (stmtBank->is_stmt_type(stmtNo, ENT_WHILE)) {
            n = stmtBank->get_node(stmtNo)->get_children()[0];
            next = n->get_stmtNo();
            CFG[stmtNo]->set_edge(CFG[next], OUT, 2);
            CFG[next]->set_edge(CFG[stmtNo], IN, 1);
            next = build_CFG(next);
            if (next != 0) {
                CFG[stmtNo]->set_edge(CFG[next], IN, 2);
                CFG[next]->set_edge(CFG[stmtNo], OUT, 1);
            } else {
                CFG[0]->get_edge(IN, 1)->set_edge(CFG[stmtNo], OUT, 1);
                CFG[0]->get_edge(IN, 2)->set_edge(CFG[stmtNo], OUT, 1);
                CFG[stmtNo]->set_edge(CFG[0]->get_edge(IN, 1), IN, 2);
                CFG[stmtNo]->set_edge(CFG[0]->get_edge(IN, 2), IN, 3);
            }
        } 

        n = stmtBank->get_node(stmtNo)->get_successor();
        if (n != NULL) {
            next = n->get_stmtNo();
            CFG[stmtNo]->set_edge(CFG[next], OUT, 1);
            CFG[next]->set_edge(CFG[stmtNo], IN, 1);
            return build_CFG(next);
        }
    }
    return CFG[stmtNo];
}*/

CFGNode* Parser::build_CFG(int stmtNo){
    Node *succ, *child, *ifNode, *ifNodeChild2, *ifNodeGrandChild0;
    Node *whileNode, *stmtNode;
    int succNo, childNo, thenNo, elseNo;
    CFGNode *next, *thenNode, *elseNode;

    if (stmtBank->is_stmtType(stmtNo, ENT_IF)){
        thenNo = stmtNo + 1;
        set_edge(CFG->at(stmtNo), CFG->at(thenNo), 1, 1);
        thenNode = build_CFG(thenNo);
        ifNode = stmtBank->get_node(stmtNo);
        assert(ifNode != NULL);
        ifNodeChild2 = ifNode->get_leaves()[2];
        assert(ifNodeChild2 != NULL);
        ifNodeGrandChild0 = ifNodeChild2->get_leaves()[0];
        elseNo = ifNodeGrandChild0->get_stmtNo();
        set_edge(CFG->at(stmtNo), CFG->at(elseNo), 2, 1);
        elseNode = build_CFG(elseNo);

        succ = ifNode->get_successor();
            
        next = new CFGNode(-1);
        set_edge(thenNode, next, 1, 1);
        set_edge(elseNode, next, 1, 2);
        
        if (succ != NULL) {
            succNo = succ->get_stmtNo();
            set_edge(next, CFG->at(succNo), 1, 1);
            return build_CFG(succNo);
        } else {
            return next;
        }
    } else {
        if (stmtBank->is_stmtType(stmtNo, ENT_WHILE)){
            whileNode = stmtBank->get_node(stmtNo);
            assert(whileNode != NULL);
            child = whileNode->get_children()[0];
            assert(child != NULL);
            childNo = child->get_stmtNo();
            set_edge(CFG->at(stmtNo), CFG->at(childNo), 2, 1);
            next = build_CFG(childNo);
            set_edge(next, CFG->at(stmtNo), 1, 2);
        }
        stmtNode = stmtBank->get_node(stmtNo);
        assert(stmtNode != NULL);
        succ = stmtNode->get_successor();
        if (succ != NULL) {
            succNo = succ->get_stmtNo();
            set_edge(CFG->at(stmtNo), CFG->at(succNo), 1, 1);
            return build_CFG(succNo);
        } else {
            return CFG->at(stmtNo);
        }
    }
}

void Parser::make_CFG()
{
    set<string>::iterator it;
    set<string> s = procTable->get_all_procs();
    CFGNode *head, *tail, *end;
    int start;
    init_CFG();
    for (it = s.begin(); it != s.end(); it++) {
        start = procTable->get_start(*it);
        progHead[*it] = CFG->at(start);
        end = build_CFG(start);
        if (end->get_stmtNo() == DUMMY) {
            queue<CFGNode*> q;
            CFGNode* currNode;
            q.push(end->get_edge(IN,1));
            q.push(end->get_edge(IN,2));
            while(!q.empty()){
                currNode = q.front();
                q.pop();
                if (currNode != NULL) {
                    currNode->set_last();
                    if (currNode->get_stmtNo() == DUMMY) {
                        q.push(currNode->get_edge(IN,1));
                        q.push(currNode->get_edge(IN,2));
                    }
                }
            }
        }
        end->set_last();
        tail = new CFGNode(DUMMY);
        tail->set_terminator();
        set_edge(end,tail,1,1);
        progTail[*it] = tail;
    }
}

void Parser::set_edge(CFGNode* outNode, CFGNode* inNode, int out, int in)
{
    if (outNode != NULL) {
        outNode->set_edge(inNode, OUT, out);
    }
    if (inNode != NULL) {
        inNode->set_edge(outNode, IN, in);
    }
}

void Parser::set_BIPedge(CFGNode* outNode, CFGNode* inNode)
{
    outNode->set_BIPedge(inNode, OUT);
    inNode->set_BIPedge(outNode, IN);
}


// Helpers
void Parser::create_node(string name, NodeType type)
{
    currNode = nextNode;
    nextNode = new Node(name, type, stmtNo);
}

// Node n is an assign stmt. It modifies var
void Parser::add_modifies(Node* n, const string& var)
{
    int assignStmt = n->get_stmtNo();
    varTable->insert_var(var);
    varTable->add_assign_modifies_var(assignStmt, var);
    varTable->add_proc_modifies_var(procName, var);
    n->add_modifies(var);
    procTable->add_modifies(procName, var);
}

void Parser::add_uses(Node* n, string var)
{
    int stmt = n->get_stmtNo();
    varTable->insert_var(var);
    DesignEnt stmtEntType = ENT_INVALID;
    switch (n->get_type()) {
    case CALL_STMT:
        stmtEntType = ENT_CALL;
        break;
    case WHILE_STMT:
        stmtEntType = ENT_WHILE;
        break;
    case IF_STMT:
        stmtEntType = ENT_IF;
        break;
    case ASSIGN_STMT:
        stmtEntType = ENT_ASSIGN;
        break;
    }
    this->varTable->add_used_by(var, stmtEntType, stmt);
    this->varTable->add_used_by(var, ENT_PROC, procName);
    n->add_uses(var);
    procTable->add_uses(procName, var);
}

// Printer
void Parser::token_out()
{
    printf("Now at stmtNo %d\n",stmtNo);
    printf("Token parsed: %s , type: %s\n",nextToken.get_name().c_str(),printer[nextToken.get_type()].c_str());

}
