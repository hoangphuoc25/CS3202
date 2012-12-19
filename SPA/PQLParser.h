#ifndef T11_PQLPARSER_H
#define T11_PQLPARSER_H

#include <string>
#include <map>
#include "PQLAst.h"
#include "StringBuffer.h"

#define ENT_PROC_STR     "procedure"
#define ENT_STMTLST_STR  "stmtLst"
#define ENT_STMT_STR     "stmt"
#define ENT_ASSIGN_STR   "assign"
#define ENT_CALL_STR     "call"
#define ENT_WHILE_STR    "while"
#define ENT_IF_STR       "if"
#define ENT_VAR_STR      "variable"
#define ENT_CONST_STR    "constant"
#define ENT_PROGLINE_STR "prog_line"
#define ENT_INVALID_STR  "invalid"

enum DesignEnt {
    ENT_PROC, ENT_STMTLST, ENT_STMT, ENT_ASSIGN, ENT_CALL,
    ENT_WHILE, ENT_IF, ENT_VAR, ENT_CONST, ENT_PROGLINE,
    ENT_INVALID
};

class PQLParser {
public:
    PQLParser();
    PQLAst *parse(const std::string &s);

    // For testing purposes
    int get_parse_errors() const;
    std::map<std::string, DesignEnt> get_ent_table() const;

private:
    PQLParser(const PQLParser &o);
    PQLParser& operator=(const PQLParser &o);

    bool parse_decls();
    bool parse_decl_one();
    int eat_space();
    void eat_nonws_token(StringBuffer &sb);
    bool eat_one_char(char ch);
    bool eat_comma();
    bool eat_semicolon();
    void eat_till_ws(StringBuffer &sb);
    bool eat_synonym(StringBuffer &sb);
    bool insert_design_ent(DesignEnt ent, const std::string &s);
    DesignEnt string_to_entity(const std::string &s);
    const char *entity_type_to_string(DesignEnt ent);
    void error(const char *s, ...);

    int bufIdx;
    int bufLen;
    std::string buf;
    std::map<std::string, DesignEnt> entTable;
    int parseErrors;

    std::map<std::string, DesignEnt> strToEnt;
};

#endif