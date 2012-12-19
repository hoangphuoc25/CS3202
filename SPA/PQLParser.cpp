#include <cstdio>
#include <cctype>
#include <cstdarg>
#include <string>
#include <map>
#include "PQLParser.h"
#include "StringBuffer.h"

using std::string;
using std::map;

PQLParser::PQLParser(): parseErrors(0)
{
    strToEnt[ENT_PROC_STR] = ENT_PROC;
    strToEnt[ENT_STMTLST_STR] = ENT_STMTLST;
    strToEnt[ENT_STMT_STR] = ENT_STMT;
    strToEnt[ENT_ASSIGN_STR] = ENT_ASSIGN;
    strToEnt[ENT_CALL_STR] = ENT_CALL;
    strToEnt[ENT_WHILE_STR] = ENT_WHILE;
    strToEnt[ENT_IF_STR] = ENT_IF;
    strToEnt[ENT_VAR_STR] = ENT_VAR;
    strToEnt[ENT_CONST_STR] = ENT_CONST;
    strToEnt[ENT_PROGLINE_STR] = ENT_PROGLINE;
}

int PQLParser::get_parse_errors() const
{
    return this->parseErrors;
}

map<string, DesignEnt> PQLParser::get_ent_table() const
{
    return this->entTable;
}

DesignEnt PQLParser::string_to_entity(const string &s)
{
    if (strToEnt.find(s) != strToEnt.end()) {
        return strToEnt[s];
    } else {
        return ENT_INVALID;
    }
}

const char *PQLParser::entity_type_to_string(DesignEnt entType)
{
    switch (entType) {
    case ENT_PROC:
        return ENT_PROC_STR;
    case ENT_STMTLST:
        return ENT_STMTLST_STR;
    case ENT_STMT:
        return ENT_STMT_STR;
    case ENT_ASSIGN:
        return ENT_ASSIGN_STR;
    case ENT_CALL:
        return ENT_CALL_STR;
    case ENT_WHILE:
        return ENT_WHILE_STR;
    case ENT_IF:
        return ENT_IF_STR;
    case ENT_VAR:
        return ENT_VAR_STR;
    case ENT_CONST:
        return ENT_CONST_STR;
    case ENT_PROGLINE:
        return ENT_PROGLINE_STR;
    case ENT_INVALID:
        return ENT_INVALID_STR;
    }
}

void PQLParser::error(const char *s, ...)
{
    this->parseErrors++;
    va_list ap;
    va_start(ap, s);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
    va_end(ap);
}

int PQLParser::eat_space()
{
    int spaces = 0;
    while (this->bufIdx < this->bufLen &&
            isspace(this->buf[this->bufIdx])) {
        this->bufIdx++;
        spaces++;
    }
    return spaces;
}

bool PQLParser::eat_one_char(char ch)
{
    if (this->bufIdx < this->bufLen &&
            this->buf[this->bufIdx] == ch) {
        this->bufIdx++;
        return true;
    } else {
        return false;
    }
}

bool PQLParser::eat_comma()
{
    return this->eat_one_char(',');
}

bool PQLParser::eat_semicolon()
{
    return this->eat_one_char(';');
}

void PQLParser::eat_nonws_token(StringBuffer &sb)
{
    sb.clear();
    while (this->bufIdx < this->bufLen &&
            !isspace(this->buf[this->bufIdx])) {
        sb.append(this->buf[this->bufIdx++]);
    }
}

bool PQLParser::eat_synonym(StringBuffer &sb)
{
    sb.clear();
    if (this->bufIdx < this->bufLen &&
            isalpha(this->buf[this->bufIdx])) {
        sb.append(this->buf[this->bufIdx++]);
    } else {
        return false;
    }
    while (this->bufIdx < this->bufLen &&
            (isalnum(this->buf[this->bufIdx]) ||
                        this->buf[this->bufIdx] == '#')) {
        sb.append(this->buf[this->bufIdx++]);
    }
    return true;
}

void PQLParser::eat_till_ws(StringBuffer &sb)
{
    while (this->bufIdx < this->bufLen &&
            !isspace(this->buf[this->bufIdx])) {
        sb.append(this->buf[this->bufIdx++]);
    }
}

bool PQLParser::insert_design_ent(DesignEnt entType, const std::string &s)
{
    if (s.size() <= 0) {
        this->error("Zero length entity of type %s",
            this->entity_type_to_string(entType));
        return false;
    }
    map<string, DesignEnt>::iterator it = this->entTable.find(s);
    if (it != this->entTable.end()) {
        const char *tmpS = s.c_str();
        this->error("design entity \"%s\" of type \"%s\" was"
            "previously declared (%s %s)",
            this->entity_type_to_string(entType),
            tmpS, this->entity_type_to_string(it->second), tmpS);
        return false;
    } else {
        this->entTable[s] = entType;
        return true;
    }
}

bool PQLParser::parse_decl_one()
{
    #define EAT_SYN() do {\
        ret = this->eat_synonym(sb);\
        s = sb.toString();\
        if (!ret) {\
            if (s.size() == 0) {\
                this->error("Missing design entity for \"%s\"",\
                    entStr.c_str());\
            } else {\
                this->eat_till_ws(sb);\
                this->error("Expected synonym, got \"%s\"",\
                    sb.toString().c_str());\
            }\
            return false;\
        }\
        if (!this->insert_design_ent(entType, s)) {\
            return false;\
        }\
    } while(0)

    StringBuffer sb;
    string s;
    bool ret;
    int saveIdx;
    this->eat_space();
    saveIdx = this->bufIdx;
    this->eat_nonws_token(sb);
    string entStr = sb.toString();
    DesignEnt entType = string_to_entity(entStr);
    if (entType == ENT_INVALID) {
        this->bufIdx = saveIdx;
        return false;
    }
    this->eat_space();
    EAT_SYN();
    while (1) {
        this->eat_space();
        if (!this->eat_comma()) {
            break;
        }
        this->eat_space();
        EAT_SYN();
    }
    this->eat_space();
    if (!this->eat_semicolon()) {
        this->error("Missing terminator ';'");
        return false;
    }
    return true;

    #undef EAT_SYN
}

PQLAst *PQLParser::parse(const string &s)
{
    this->bufIdx = 0;
    this->buf = s;
    this->bufLen = this->buf.size();
    this->entTable.clear();
    this->parseErrors = 0;
    if (!this->parse_decls()) {
        return NULL;
    }
    return NULL;
}

bool PQLParser::parse_decls()
{
    while (this->parse_decl_one()) {
        // nothing
    }
    return true;
}