#include <cassert>
#include <utility>
#include "PQL.h"
#include "SPAUtils.h"

using std::make_pair;
using std::map;
using std::pair;
using std::set;
using std::string;
using std::vector;

const char *TYPE_ERROR_EMPTY[TYPE_ERROR_ARRAY_SZ] = {
    "", ""
};

const char *TYPE_ERROR_MODIFIES[TYPE_ERROR_ARRAY_SZ] = {
    "Modifies: arg one must be a synonym of type" \
    " assign, stmt, if, while, procedure, call, prog_line;" \
    " or the name of a procedure enclosed in double quotes;" \
    " or an integer;" \
    " or an underscore",

    "Modifies: arg two must be a synonym of type" \
    " variable;" \
    " or the name of a variable enclosed in double quotes;" \
    " or an underscore"
};

const char *TYPE_ERROR_USES[TYPE_ERROR_ARRAY_SZ] = {
    "Uses: arg one must be a synonym of type" \
    " assign, stmt, if, while, procedure, call, prog_line;" \
    " or the name of a procedure enclosed in double quotes;" \
    " or an integer;" \
    " or an underscore",

    "Uses: arg two must be a synonym of type" \
    " variable;" \
    " or the name of a variable enclosed in double quotes;" \
    " or an underscore"
};

const char *TYPE_ERROR_CALLS[TYPE_ERROR_ARRAY_SZ] = {
    "Calls: arg one must be a synonym of type" \
    " procedure;" \
    " or the name of a procedure enclosed in double quotes;" \
    " or an underscore",

    "Calls: arg two must be a synonym of type" \
    " procedure;" \
    " or the name of a procedure enclosed in double quotes;" \
    " or an underscore"
};

const char *TYPE_ERROR_CALLS_STAR[TYPE_ERROR_ARRAY_SZ] = {
    "Calls*: arg one must be a synonym of type" \
    " procedure;" \
    " or the name of a procedure enclosed in double quotes;" \
    " or an underscore",

    "Calls*: arg two must be a synonym of type" \
    " procedure;" \
    " or the name of a procedure enclosed in double quotes;" \
    " or an underscore"
};

const char *TYPE_ERROR_PARENT[TYPE_ERROR_ARRAY_SZ] = {
    "Parent: arg one must be a synonym of type" \
    " stmt, while, if, prog_line;" \
    " or an integer;" \
    " or an underscore",

    "Parent: arg two must be a synonym of type" \
    " stmt, assign, call, while, if, prog_line;" \
    " or an integer;"\
    " or an underscore"
};

const char *TYPE_ERROR_PARENT_STAR[TYPE_ERROR_ARRAY_SZ] = {
    "Parent*: arg one must be a synonym of type" \
    " stmt, while, if, prog_line;" \
    " or an integer;" \
    " or an underscore",

    "Parent*: arg two must be a synonym of type" \
    " stmt, assign, call, while, if, prog_line;" \
    " or an integer;"\
    " or an underscore"
};

const char *TYPE_ERROR_FOLLOWS[TYPE_ERROR_ARRAY_SZ] = {
    "Follows: arg one must be a synonym of type" \
    " stmt, assign, call, while, if, prog_line;" \
    " or an integer;" \
    " or an underscore",

    "Follows: arg two must be a synonym of type" \
    " stmt, assign, call, while, if, prog_line;" \
    " or an integer;" \
    " or an underscore"
};

const char *TYPE_ERROR_FOLLOWS_STAR[TYPE_ERROR_ARRAY_SZ] = {
    "Follows*: arg one must be a synonym of type" \
    " stmt, assign, call, while, if, prog_line;" \
    " or an integer;" \
    " or an underscore",

    "Follows*: arg two must be a synonym of type" \
    " stmt, assign, call, while, if, prog_line;" \
    " or an integer;" \
    " or an underscore"
};

const char *TYPE_ERROR_NEXT[TYPE_ERROR_ARRAY_SZ] = {
    "Next: arg one must be a synonym of type" \
    " stmt, assign, call, while, if, prog_line;" \
    " or an integer;" \
    " or an underscore",

    "Next: arg two must be a synonym of type" \
    " stmt, assign, call, while, if, prog_line;" \
    " or an integer;" \
    " or an underscore"
};

const char *TYPE_ERROR_NEXT_STAR[TYPE_ERROR_ARRAY_SZ] = {
    "Next*: arg one must be a synonym of type" \
    " stmt, assign, call, while, if, prog_line;" \
    " or an integer;" \
    " or an underscore",

    "Next*: arg two must be a synonym of type" \
    " stmt, assign, call, while, if, prog_line;" \
    " or an integer;" \
    " or an underscore"
};

const char *TYPE_ERROR_AFFECTS[TYPE_ERROR_ARRAY_SZ] = {
    "Affects: arg one must be a synonym of type" \
    " assign;" \
    " or an integer;" \
    " or an underscore",

    "Affects: arg two must be a synonym of type" \
    " assign;" \
    " or an integer;" \
    " or an underscore"
};

const char *TYPE_ERROR_AFFECTS_STAR[TYPE_ERROR_ARRAY_SZ] = {
    "Affects*: arg one must be a synonym of type" \
    " assign;" \
    " or an integer;" \
    " or an underscore",

    "Affects*: arg two must be a synonym of type" \
    " assign;" \
    " or an integer;" \
    " or an underscore"
};

const char *relRefType_to_string(RelRefType relType)
{
    switch (relType) {
    case REL_MODIFIES:
        return MODIFIES_STR;
    case REL_USES:
        return USES_STR;
    case REL_CALLS:
        return CALLS_STR;
    case REL_CALLS_STAR:
        return CALLS_STAR_STR;
    case REL_PARENT:
        return PARENT_STR;
    case REL_PARENT_STAR:
        return PARENT_STAR_STR;
    case REL_FOLLOWS:
        return FOLLOWS_STR;
    case REL_FOLLOWS_STAR:
        return FOLLOWS_STAR_STR;
    case REL_NEXT:
        return NEXT_STR;
    case REL_NEXT_STAR:
        return NEXT_STAR_STR;
    case REL_AFFECTS:
        return AFFECTS_STR;
    case REL_AFFECTS_STAR:
        return AFFECTS_STAR_STR;
    default:
        return INVALID_STR;
    }
}

const char *entity_type_to_string(DesignEnt entType)
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

const char *attrType_to_string(AttrType attrType)
{
    switch (attrType) {
    case ATTR_PROCNAME:
        return ATTR_PROCNAME_STR;
    case ATTR_VARNAME:
        return ATTR_VARNAME_STR;
    case ATTR_VALUE:
        return ATTR_VALUE_STR;
    case ATTR_STMTNO:
        return ATTR_STMTNO_STR;
    case ATTR_DEFAULT:
        return ATTR_DEFAULT_STR;
    default:
        return ATTR_INVALID_STR;
    }
}

RelRefArgType designEnt_to_relRefArgType(DesignEnt ent)
{
    switch (ent) {
    case ENT_PROC:
    case ENT_VAR:
        return RELARG_STRING;
        break;
    case ENT_STMTLST:
    case ENT_STMT:
    case ENT_ASSIGN:
    case ENT_CALL:
    case ENT_WHILE:
    case ENT_IF:
    case ENT_CONST:
    case ENT_PROGLINE:
        return RELARG_INT;
        break;
    default:
        return RELARG_INVALID;
        break;
    }
}

//////////////////////////////////////////////////////////////////////
// GenericRef
//////////////////////////////////////////////////////////////////////
void GenericRef::dummy() {}

//////////////////////////////////////////////////////////////////////
// AttrRef
//////////////////////////////////////////////////////////////////////

AttrRef::AttrRef(): syn(""), entType(ENT_INVALID), attr(ATTR_INVALID) {}

AttrRef::AttrRef(string s, DesignEnt et, AttrType a)
    : syn(s), entType(et), attr(a) {}

AttrRef::AttrRef(const AttrRef& o)
    : syn(o.syn), entType(o.entType), attr(o.attr) {}

AttrRef& AttrRef::operator=(const AttrRef &o)
{
    AttrRef tmp(o);
    this->swap(*this, tmp);
    return *this;
}

AttrRef::~AttrRef() {}

void AttrRef::swap(AttrRef& one, AttrRef& two)
{
    using std::swap;
    swap(one.syn, two.syn);
    swap(one.entType, two.entType);
    swap(one.attr, two.attr);
}

void AttrRef::dump_to_sb(StringBuffer &sb) const
{
    sb.append(entity_type_to_string(entType));
    sb.append(' ');
    sb.append(syn);
    if (attr != ATTR_DEFAULT) {
        sb.append(' ');
        sb.append(attrType_to_string(attr));
    }
}

string AttrRef::toPeriodString() const
{
    StringBuffer sb;
    sb.append(syn);
    sb.append('.');
    sb.append(attrType_to_string(attr));
    return sb.toString();
}

bool AttrRefCmp::operator()(const AttrRef &a, const AttrRef &b) const
{
    if (a.syn != b.syn) {
        return a.syn < b.syn;
    } else if (a.entType != b.entType) {
        return a.entType < b.entType;
    } else {
        return a.attr < b.attr;
    }
}

//////////////////////////////////////////////////////////////////////
// RelRef
//////////////////////////////////////////////////////////////////////

bool RelRef::valid(const struct RelRef &r) {
    return ((REL_INVALID != r.relType) &&
            (RELARG_INVALID != r.argOneType) &&
            (RELARG_INVALID != r.argTwoType));
}

RelRef::RelRef(): relType(REL_INVALID), argOneType(RELARG_INVALID),
    argOneSyn(ENT_INVALID), argOneString(), argOneInt(0),
    argTwoType(RELARG_INVALID), argTwoSyn(ENT_INVALID),
    argTwoString(), argTwoInt(0) {}

RelRef::RelRef(const RelRef &o)
    : relType(o.relType), argOneType(o.argOneType),
      argOneSyn(o.argOneSyn), argOneString(o.argOneString),
      argOneInt(o.argOneInt), argTwoType(o.argTwoType),
      argTwoSyn(o.argTwoSyn),  argTwoString(o.argTwoString),
      argTwoInt(o.argTwoInt) {}

RelRef& RelRef::operator=(const RelRef &o)
{
    RelRef tmp(o);
    this->swap(*this, tmp);
    return *this;
}

RelRef::~RelRef() {}

void RelRef::swap(RelRef& one, RelRef& two)
{
    using std::swap;
    swap(one.relType, two.relType);
    swap(one.argOneType, two.argOneType);
    swap(one.argOneSyn, two.argOneSyn);
    swap(one.argOneString, two.argOneString);
    swap(one.argOneInt, two.argOneInt);
    swap(one.argTwoType, two.argTwoType);
    swap(one.argTwoSyn, two.argTwoSyn);
    swap(one.argTwoString, two.argTwoString);
    swap(one.argTwoInt, two.argTwoInt);
}

ParseError RelRef::set_arg_one(RelRefArgType argType, StringBuffer &sb,
        char **errorMsg)
{
    return this->set_arg(1, argType, sb, errorMsg);
}

ParseError RelRef::set_arg_two(RelRefArgType argType, StringBuffer &sb,
        char **errorMsg)
{
    return this->set_arg(2, argType, sb, errorMsg);
}

ParseError RelRef::set_arg(int which, RelRefArgType argType, StringBuffer &sb,
        char **errorMsg)
{
    ParseError ret = PARSE_OK;
    assert(argType != RELARG_INVALID);
    switch (argType) {
    case RELARG_SYN:
        if (which == 1) {
            this->argOneSyn = ENT_INVALID;
        } else {
            this->argTwoSyn = ENT_INVALID;
        }
        // fall through
    case RELARG_STRING:
        if (which == 1) {
            this->argOneString = sb.toString();
        } else {
            this->argTwoString = sb.toString();
        }
        break;
    case RELARG_INT:
        if (which == 1) {
            if (!string_to_uint(sb.toString(), &argOneInt, errorMsg)) {
                ret = PARSE_REL_ARG_INT_INVALID;
            }
        } else {
            if (!string_to_uint(sb.toString(), &argTwoInt, errorMsg)) {
                ret = PARSE_REL_ARG_INT_INVALID;
            }
        }
        break;
    case RELARG_WILDCARD:
        if (which == 1) {
            this->argOneType = RELARG_WILDCARD;
        } else {
            this->argTwoType = RELARG_WILDCARD;
        }
        break;
    }
    if (ret == PARSE_OK) {
        if (which == 1) {
            this->argOneType = argType;
        } else {
            this->argTwoType = argType;
        }
    }
    return ret;
}

string RelRef::dump(void) const
{
    StringBuffer sb;
    sb.append(relRefType_to_string(this->relType));
    sb.append('(');
    switch (this->argOneType) {
    case RELARG_SYN:
        sb.append(this->argOneString);
        break;
    case RELARG_STRING:
        sb.append('"');
        sb.append(this->argOneString);
        sb.append('"');
        break;
    case RELARG_INT:
        sb.append_int(this->argOneInt);
        break;
    case RELARG_WILDCARD:
        sb.append('_');
        break;
    }
    sb.append(',');
    switch (this->argTwoType) {
    case RELARG_SYN:
        sb.append(this->argTwoString);
        break;
    case RELARG_STRING:
        sb.append('"');
        sb.append(this->argTwoString);
        sb.append('"');
        break;
    case RELARG_INT:
        sb.append_int(this->argTwoInt);
        break;
    case RELARG_WILDCARD:
        sb.append('_');
        break;
    }
    sb.append(')');
    return sb.toString();
}

void RelRef::dummy() {}

bool RelRefCmp::operator()(const RelRef &a, const RelRef &b) const
{
    #define RELREF_ARGTWO_CMP() do {\
        if (a.argTwoType == RELARG_SYN) {\
            if (a.argTwoSyn != b.argTwoSyn) {\
                return a.argTwoSyn < b.argTwoSyn;\
            }\
            return a.argTwoString < b.argTwoString;\
        } else if (a.argTwoType == RELARG_STRING) {\
            return a.argTwoString < b.argTwoString;\
        } else if (a.argTwoType == RELARG_INT) {\
            return a.argTwoInt < b.argTwoInt;\
        } else {\
            return false;\
        }\
    } while(0)

    int cmp;
    if (a.relType != b.relType) {
        return a.relType < b.relType;
    } else if (a.argOneType != b.argOneType) {
        return a.argOneType < b.argOneType;
    } else if (a.argTwoType != b.argTwoType) {
        return a.argTwoType < b.argTwoType;
    } else if (a.argOneType == RELARG_SYN) {
        if (a.argOneSyn != b.argOneSyn) {
            return a.argOneSyn < b.argOneSyn;
        }
        cmp = a.argOneString.compare(b.argOneString);
        if (cmp != 0) {
            return (cmp < 0);
        }
        RELREF_ARGTWO_CMP();

    } else if (a.argOneType == RELARG_STRING) {
        cmp = a.argOneString.compare(b.argOneString);
        if (cmp != 0) {
            return (cmp < 0);
        }
        RELREF_ARGTWO_CMP();
    } else if (a.argOneType == RELARG_INT) {
        if (a.argOneInt != b.argOneInt) {
            return a.argOneInt < b.argOneInt;
        }
        RELREF_ARGTWO_CMP();
    } else if (a.argOneType == RELARG_WILDCARD) {
        RELREF_ARGTWO_CMP();
    }

    #undef RELREF_ARGTWO_CMP
}

//////////////////////////////////////////////////////////////////////
// PatCl
//////////////////////////////////////////////////////////////////////

PatCl::PatCl():
    type(PATCL_INVALID), syn(),
    varRefType(PATVARREF_INVALID), varRefString(),
    exprType(PATEXPR_INVALID), exprString() {}

PatCl::PatCl(const PatCl &o)
    : type(o.type), syn(o.syn), varRefType(o.varRefType),
      varRefString(o.varRefString), exprType(o.exprType),
      exprString(o.exprString)
{
}

PatCl& PatCl::operator=(const PatCl& o)
{
    PatCl tmp(o);
    swap(*this, tmp);
    return *this;
}

PatCl::~PatCl() {}

void PatCl::swap(PatCl &one, PatCl &two)
{
    using std::swap;
    swap(one.type, two.type);
    swap(one.syn, two.syn);
    swap(one.varRefType, two.varRefType);
    swap(one.varRefString, two.varRefString);
    swap(one.exprType, two.exprType);
    swap(one.exprString, two.exprString);
}

void PatCl::set_pat_assign(const string& syn_, enum PatClVarRefType vrType,
        const string& vr, enum PatClExprType exType,
        const string& ex)
{
    this->type = PATCL_ASSIGN;
    this->syn = syn_;
    this->varRefType = vrType;
    if (this->varRefType == PATVARREF_SYN ||
            this->varRefType == PATVARREF_STRING) {
        this->varRefString = vr;
    }
    this->exprType = exType;
    if (this->exprType == PATEXPR_EXPR ||
            this->exprType == PATEXPR_EXPR_WILDCARD) {
        // TODO: Use AST static method to construct actual tree
        //       and store actual tree
        StringBuffer sb;
        sb.append(ex);
        sb.remove_spaces();
        this->exprString = sb.toString();
    }
}

void PatCl::set_pat_if(const string& syn_, enum PatClVarRefType vrType,
        const string& vr)
{
    this->type = PATCL_IF;
    this->syn = syn_;
    this->varRefType = vrType;
    if (this->varRefType == PATVARREF_SYN ||
            this->varRefType == PATVARREF_STRING) {
        this->varRefString = vr;
    }
}

void PatCl::set_pat_while(const string &syn_, enum PatClVarRefType vrType,
        const string& vr)
{
    this->type = PATCL_WHILE;
    this->syn = syn_;
    this->varRefType = vrType;
    if (this->varRefType == PATVARREF_SYN ||
            this->varRefType == PATVARREF_STRING) {
        this->varRefString = vr;
    }
}

string PatCl::toString(bool showType) const
{
    StringBuffer sb;
    if (showType) {
        switch (this->type) {
        case PATCL_ASSIGN:
            sb.append("assign ");
            break;
        case PATCL_IF:
            sb.append("if ");
            break;
        case PATCL_WHILE:
            sb.append("while ");
            break;
        default:
            sb.append("invalid ");
            break;
        }
    }
    sb.append("pattern ");
    if (this->type != PATCL_INVALID) {
        sb.append(this->syn);
        sb.append('(');
        switch (this->varRefType) {
        case PATVARREF_SYN:
            sb.append(this->varRefString);
            break;
        case PATVARREF_STRING:
            sb.append('"');
            sb.append(this->varRefString);
            sb.append('"');
            break;
        case PATVARREF_WILDCARD:
            sb.append('_');
            break;
        }
        sb.append(',');
        if (this->type == PATCL_ASSIGN) {
            switch (this->exprType) {
            case PATEXPR_EXPR:
                sb.append('"');
                sb.append(this->exprString);
                sb.append('"');
                break;
            case PATEXPR_EXPR_WILDCARD:
                sb.append('_');
                sb.append('"');
                sb.append(this->exprString);
                sb.append('"');
                sb.append('_');
                break;
            case PATEXPR_WILDCARD:
                sb.append('_');
                break;
            default:
                break;
            }
        } else if (this->type == PATCL_IF) {
            sb.append("_,_");
        } else if (this->type == PATCL_WHILE) {
            sb.append('_');
        }
        sb.append(')');
    }
    return sb.toString();
}

bool PatCl::valid(const PatCl &p)
{
    return p.type != PATCL_INVALID;
}

void PatCl::dummy() {}

bool PatClCmp::operator()(const PatCl &a, const PatCl &b) const
{
    if (a.type != b.type) {
        return a.type < b.type;
    } else {
        if (a.syn != b.syn) {
            return a.syn < b.syn;
        } else if (a.varRefType != b.varRefType) {
            return a.varRefType < b.varRefType;
        } else {
            if (a.varRefType == PATVARREF_SYN ||
                    a.varRefType == PATVARREF_STRING) {
                if (a.varRefString != b.varRefString) {
                    return a.varRefString < b.varRefString;
                }
            }
            if (a.type == PATCL_ASSIGN) {
                if (a.exprType != b.exprType) {
                    return a.exprType < b.exprType;
                } else if (a.exprType == PATEXPR_EXPR ||
                        a.exprType == PATEXPR_EXPR_WILDCARD) {
                    return a.exprString < b.exprString;
                } else {
                    return false;
                }
            }
            return false;
        }
    }
}

/* class QueryInfo */

DesignEnt QueryInfo::MODIFIES_ARGONE_TYPES_ARR
                [MODIFIES_ARGONE_TYPES_ARR_SZ] = {
    ENT_ASSIGN, ENT_STMT, ENT_IF,
    ENT_WHILE, ENT_PROC, ENT_CALL,
    ENT_PROGLINE
};

DesignEnt QueryInfo::MODIFIES_ARGTWO_TYPES_ARR
                [MODIFIES_ARGTWO_TYPES_ARR_SZ] = {
    ENT_VAR
};

DesignEnt QueryInfo::USES_ARGONE_TYPES_ARR[USES_ARGONE_TYPES_ARR_SZ] = {
    ENT_ASSIGN, ENT_IF, ENT_WHILE, ENT_PROC,
    ENT_CALL, ENT_STMT, ENT_PROGLINE
};

DesignEnt QueryInfo::USES_ARGTWO_TYPES_ARR[USES_ARGTWO_TYPES_ARR_SZ] = {
    ENT_VAR
};

DesignEnt QueryInfo::CALLS_ARGONE_TYPES_ARR[CALLS_ARGONE_TYPES_ARR_SZ] = {
    ENT_PROC
};

DesignEnt QueryInfo::CALLS_ARGTWO_TYPES_ARR[CALLS_ARGTWO_TYPES_ARR_SZ] = {
    ENT_PROC
};

DesignEnt QueryInfo::PARENT_ARGONE_TYPES_ARR[PARENT_ARGONE_TYPES_ARR_SZ] = {
    ENT_STMT, ENT_WHILE, ENT_IF, ENT_PROGLINE
};

DesignEnt QueryInfo::PARENT_ARGTWO_TYPES_ARR[PARENT_ARGTWO_TYPES_ARR_SZ] = {
    ENT_STMT, ENT_ASSIGN, ENT_CALL, ENT_WHILE, ENT_IF, ENT_PROGLINE
};

DesignEnt QueryInfo::FOLLOWS_ARGONE_TYPES_ARR[FOLLOWS_ARGONE_TYPES_ARR_SZ] = {
    ENT_STMT, ENT_ASSIGN, ENT_CALL, ENT_WHILE, ENT_IF, ENT_PROGLINE
};

DesignEnt QueryInfo::FOLLOWS_ARGTWO_TYPES_ARR[FOLLOWS_ARGTWO_TYPES_ARR_SZ] = {
    ENT_STMT, ENT_ASSIGN, ENT_CALL, ENT_WHILE, ENT_IF, ENT_PROGLINE
};

DesignEnt QueryInfo::NEXT_ARGONE_TYPES_ARR[NEXT_ARGONE_TYPES_ARR_SZ] = {
    ENT_STMT, ENT_ASSIGN, ENT_CALL, ENT_WHILE, ENT_IF, ENT_PROGLINE
};

DesignEnt QueryInfo::NEXT_ARGTWO_TYPES_ARR[NEXT_ARGTWO_TYPES_ARR_SZ] = {
    ENT_STMT, ENT_ASSIGN, ENT_CALL, ENT_WHILE, ENT_IF, ENT_PROGLINE
};

DesignEnt QueryInfo::AFFECTS_ARGONE_TYPES_ARR[AFFECTS_ARGONE_TYPES_ARR_SZ] = {
    ENT_ASSIGN
};

DesignEnt QueryInfo::AFFECTS_ARGTWO_TYPES_ARR[AFFECTS_ARGTWO_TYPES_ARR_SZ] = {
    ENT_ASSIGN
};

const set<DesignEnt> QueryInfo::MODIFIES_ARGONE_TYPES(
        QueryInfo::MODIFIES_ARGONE_TYPES_ARR,
        QueryInfo::MODIFIES_ARGONE_TYPES_ARR+MODIFIES_ARGONE_TYPES_ARR_SZ);

const set<DesignEnt> QueryInfo::MODIFIES_ARGTWO_TYPES(
        QueryInfo::MODIFIES_ARGTWO_TYPES_ARR,
        QueryInfo::MODIFIES_ARGTWO_TYPES_ARR+MODIFIES_ARGTWO_TYPES_ARR_SZ);

const set<DesignEnt> QueryInfo::USES_ARGONE_TYPES(
        QueryInfo::USES_ARGONE_TYPES_ARR,
        QueryInfo::USES_ARGONE_TYPES_ARR+USES_ARGONE_TYPES_ARR_SZ);

const set<DesignEnt> QueryInfo::USES_ARGTWO_TYPES(
        QueryInfo::USES_ARGTWO_TYPES_ARR,
        QueryInfo::USES_ARGTWO_TYPES_ARR+USES_ARGTWO_TYPES_ARR_SZ);

const set<DesignEnt> QueryInfo::CALLS_ARGONE_TYPES(
        QueryInfo::CALLS_ARGONE_TYPES_ARR,
        QueryInfo::CALLS_ARGONE_TYPES_ARR+CALLS_ARGONE_TYPES_ARR_SZ);

const set<DesignEnt> QueryInfo::CALLS_ARGTWO_TYPES(
        QueryInfo::CALLS_ARGTWO_TYPES_ARR,
        QueryInfo::CALLS_ARGTWO_TYPES_ARR+CALLS_ARGTWO_TYPES_ARR_SZ);

const set<DesignEnt> QueryInfo::PARENT_ARGONE_TYPES(
        QueryInfo::PARENT_ARGONE_TYPES_ARR,
        QueryInfo::PARENT_ARGONE_TYPES_ARR+PARENT_ARGONE_TYPES_ARR_SZ);

const set<DesignEnt> QueryInfo::PARENT_ARGTWO_TYPES(
        QueryInfo::PARENT_ARGTWO_TYPES_ARR,
        QueryInfo::PARENT_ARGTWO_TYPES_ARR+PARENT_ARGTWO_TYPES_ARR_SZ);

const set<DesignEnt> QueryInfo::FOLLOWS_ARGONE_TYPES(
        QueryInfo::FOLLOWS_ARGONE_TYPES_ARR,
        QueryInfo::FOLLOWS_ARGONE_TYPES_ARR+FOLLOWS_ARGONE_TYPES_ARR_SZ);

const set<DesignEnt> QueryInfo::FOLLOWS_ARGTWO_TYPES(
        QueryInfo::FOLLOWS_ARGTWO_TYPES_ARR,
        QueryInfo::FOLLOWS_ARGTWO_TYPES_ARR+FOLLOWS_ARGTWO_TYPES_ARR_SZ);

const set<DesignEnt> QueryInfo::NEXT_ARGONE_TYPES(
        QueryInfo::NEXT_ARGONE_TYPES_ARR,
        QueryInfo::NEXT_ARGONE_TYPES_ARR+NEXT_ARGONE_TYPES_ARR_SZ);

const set<DesignEnt> QueryInfo::NEXT_ARGTWO_TYPES(
        QueryInfo::NEXT_ARGTWO_TYPES_ARR,
        QueryInfo::NEXT_ARGTWO_TYPES_ARR+NEXT_ARGTWO_TYPES_ARR_SZ);

const set<DesignEnt> QueryInfo::AFFECTS_ARGONE_TYPES(
        QueryInfo::AFFECTS_ARGONE_TYPES_ARR,
        QueryInfo::AFFECTS_ARGONE_TYPES_ARR+AFFECTS_ARGONE_TYPES_ARR_SZ);

const set<DesignEnt> QueryInfo::AFFECTS_ARGTWO_TYPES(
        QueryInfo::AFFECTS_ARGTWO_TYPES_ARR,
        QueryInfo::AFFECTS_ARGTWO_TYPES_ARR+AFFECTS_ARGTWO_TYPES_ARR_SZ);

bool QueryInfo::is_valid_argOne_syn_type(RelRefType relType,
        DesignEnt entType)
{
    assert(relType != REL_INVALID);
    switch (relType) {
    case REL_MODIFIES:
        return (QueryInfo::MODIFIES_ARGONE_TYPES.find(entType) !=
                QueryInfo::MODIFIES_ARGONE_TYPES.end());
        break;
    case REL_USES:
        return (QueryInfo::USES_ARGONE_TYPES.find(entType) !=
                QueryInfo::USES_ARGONE_TYPES.end());
        break;
    case REL_CALLS: case REL_CALLS_STAR:
        return (QueryInfo::CALLS_ARGONE_TYPES.find(entType) !=
                QueryInfo::CALLS_ARGONE_TYPES.end());
        break;
    case REL_PARENT: case REL_PARENT_STAR:
        return (QueryInfo::PARENT_ARGONE_TYPES.find(entType) !=
                QueryInfo::PARENT_ARGONE_TYPES.end());
        break;
    case REL_FOLLOWS: case REL_FOLLOWS_STAR:
        return (QueryInfo::FOLLOWS_ARGONE_TYPES.find(entType) !=
                QueryInfo::FOLLOWS_ARGONE_TYPES.end());
        break;
    case REL_NEXT: case REL_NEXT_STAR:
        return (QueryInfo::NEXT_ARGONE_TYPES.find(entType) !=
                QueryInfo::NEXT_ARGONE_TYPES.end());
        break;
    case REL_AFFECTS: case REL_AFFECTS_STAR:
        return (QueryInfo::AFFECTS_ARGONE_TYPES.find(entType) !=
                QueryInfo::AFFECTS_ARGONE_TYPES.end());
        break;
    }
}

bool QueryInfo::is_valid_argTwo_syn_type(RelRefType relType,
        DesignEnt entType)
{
    assert(relType != REL_INVALID);
    switch (relType) {
    case REL_MODIFIES:
        return (QueryInfo::MODIFIES_ARGTWO_TYPES.find(entType) !=
                QueryInfo::MODIFIES_ARGTWO_TYPES.end());
        break;
    case REL_USES:
        return (QueryInfo::USES_ARGTWO_TYPES.find(entType) !=
                QueryInfo::USES_ARGTWO_TYPES.end());
        break;
    case REL_CALLS: case REL_CALLS_STAR:
        return (QueryInfo::CALLS_ARGTWO_TYPES.find(entType) !=
                QueryInfo::CALLS_ARGTWO_TYPES.end());
        break;
    case REL_PARENT: case REL_PARENT_STAR:
        return (QueryInfo::PARENT_ARGTWO_TYPES.find(entType) !=
                QueryInfo::PARENT_ARGTWO_TYPES.end());
        break;
    case REL_FOLLOWS: case REL_FOLLOWS_STAR:
        return (QueryInfo::FOLLOWS_ARGTWO_TYPES.find(entType) !=
                QueryInfo::FOLLOWS_ARGTWO_TYPES.end());
        break;
    case REL_NEXT: case REL_NEXT_STAR:
        return (QueryInfo::NEXT_ARGTWO_TYPES.find(entType) !=
                QueryInfo::NEXT_ARGTWO_TYPES.end());
        break;
    case REL_AFFECTS: case REL_AFFECTS_STAR:
        return (QueryInfo::AFFECTS_ARGTWO_TYPES.find(entType) !=
                QueryInfo::AFFECTS_ARGTWO_TYPES.end());
        break;
    }
}

QueryInfo::QueryInfo() {}

QueryInfo::QueryInfo(const map<string, DesignEnt>& etab,
        const vector<pair<DesignEnt, string> > &eVec)
{
    this->reset(etab, eVec);
}

QueryInfo::~QueryInfo()
{
    int sz = this->clauses.size();
    for (int i = 0; i < sz; i++) {
        delete (this->clauses[i]);
    }
}

void QueryInfo::reset(const map<string, DesignEnt>& etab,
        const vector<pair<DesignEnt, string> > &eVec)
{
    this->entTable.clear();
    for (map<string, DesignEnt>::const_iterator it = etab.begin();
            it != etab.end(); it++) {
        this->entTable[it->first] = it->second;
    }
    this->entVec.clear();
    for (vector<pair<DesignEnt, string> >::const_iterator it = eVec.begin();
            it != eVec.end(); it++) {
        this->entVec.push_back(*it);
    }
    this->insertOrder.clear();
    this->relRefs.clear();
    this->relRefsSet.clear();
    this->patCls.clear();
    this->patClSet.clear();
    this->clauses.clear();
}

void QueryInfo::set_select_boolean()
{
    this->selectType = SEL_BOOLEAN;
}

void QueryInfo::set_select_tuple()
{
    this->selectType = SEL_TUPLE;
    this->selectTuple.clear();
    this->selectTable.clear();
}

ParseError QueryInfo::add_select_tuple(AttrRef attrRef)
{
    const std::string& syn = attrRef.syn;
    if (this->entTable.find(syn) == this->entTable.end()) {
        return PARSE_SELECT_UNDECLARED;
    }
    this->selectTable.insert(attrRef);
    this->selectTuple.push_back(attrRef);
    return PARSE_OK;
}

DesignEnt QueryInfo::retrieve_syn_type(const string &s) const
{
    map<string, DesignEnt>::const_iterator it = this->entTable.find(s);
    if (it != this->entTable.end()) {
        return it->second;
    } else {
        return ENT_INVALID;
    }
}

void QueryInfo::insert_relRef(const RelRef &relRef, char **errorMsg)
{
    if (this->relRefsSet.find(relRef) == this->relRefsSet.end()) {
        this->insertOrder.push_back(
            make_pair(SUCHTHAT_CLAUSE, this->relRefs.size()));
        this->relRefsSet.insert(relRef);
        this->relRefs.push_back(relRef);
        this->clauses.push_back(new RelRef(relRef));
    } else {
        // else duplicate relRef, dont insert
        if (errorMsg) {
            _snprintf_s(this->errorBuf, QINFO_ERROR_LEN, QINFO_ERROR_LEN,
                "Repeated relRef \"%s\"", relRef.dump().c_str());
            *errorMsg = strdup(this->errorBuf);
        }
    }
}

ParseError QueryInfo::add_X_relRef(const set<DesignEnt>& argOneTypes,
        const set<DesignEnt>& argTwoTypes,
        RelRef &relRef, char **errorMsg)
{
    DesignEnt entType;
    if (relRef.argOneType == RELARG_SYN) {
        entType = this->retrieve_syn_type(relRef.argOneString);
        if (entType == ENT_INVALID) {
            return PARSE_REL_ARGONE_UNDECLARED;
        } else if (argOneTypes.find(entType) != argOneTypes.end()) {
            relRef.argOneSyn = entType;
        } else {
            return PARSE_REL_ARGONE_TYPE_ERROR;
        }
    }
    if (relRef.argTwoType == RELARG_SYN) {
        entType = this->retrieve_syn_type(relRef.argTwoString);
        if (entType == ENT_INVALID) {
            return PARSE_REL_ARGTWO_UNDECLARED;
        } else if (argTwoTypes.find(entType) != argTwoTypes.end()) {
            relRef.argTwoSyn = entType;
        } else {
            return PARSE_REL_ARGTWO_TYPE_ERROR;
        }
    }
    this->insert_relRef(relRef, errorMsg);
    return PARSE_OK;
}

ParseError QueryInfo::add_modifies_relRef(RelRef &relRef, char **errorMsg)
{
    return this->add_X_relRef(QueryInfo::MODIFIES_ARGONE_TYPES,
                    QueryInfo::MODIFIES_ARGTWO_TYPES, relRef, errorMsg);
}

ParseError QueryInfo::add_uses_relRef(RelRef &relRef, char **errorMsg)
{
    return this->add_X_relRef(QueryInfo::USES_ARGONE_TYPES,
                    QueryInfo::USES_ARGTWO_TYPES, relRef, errorMsg);
}

ParseError QueryInfo::add_calls_relRef(RelRef &relRef, char **errorMsg)
{
    return this->add_X_relRef(QueryInfo::CALLS_ARGONE_TYPES,
                   QueryInfo::CALLS_ARGTWO_TYPES, relRef, errorMsg);
}

ParseError QueryInfo::add_parent_relRef(RelRef &relRef, char **errorMsg)
{
    return this->add_X_relRef(QueryInfo::PARENT_ARGONE_TYPES,
                    QueryInfo::PARENT_ARGTWO_TYPES, relRef, errorMsg);
}

ParseError QueryInfo::add_follows_relRef(RelRef &relRef, char **errorMsg)
{
    return this->add_X_relRef(QueryInfo::FOLLOWS_ARGONE_TYPES,
                    QueryInfo::FOLLOWS_ARGTWO_TYPES, relRef, errorMsg);
}

ParseError QueryInfo::add_next_relRef(RelRef &relRef, char **errorMsg)
{
    return this->add_X_relRef(QueryInfo::NEXT_ARGONE_TYPES,
                    QueryInfo::NEXT_ARGTWO_TYPES, relRef, errorMsg);
}

ParseError QueryInfo::add_affects_relRef(RelRef &relRef, char **errorMsg)
{
    return this->add_X_relRef(QueryInfo::AFFECTS_ARGONE_TYPES,
                    QueryInfo::AFFECTS_ARGTWO_TYPES, relRef, errorMsg);
}

ParseError QueryInfo::add_relRef(RelRef &relRef, char **errorMsg)
{
    switch (relRef.relType) {
    case REL_MODIFIES:
        return this->add_modifies_relRef(relRef, errorMsg);
    case REL_USES:
        return this->add_uses_relRef(relRef, errorMsg);
    case REL_CALLS:
    case REL_CALLS_STAR:
        return this->add_calls_relRef(relRef, errorMsg);
    case REL_PARENT:
    case REL_PARENT_STAR:
        return this->add_parent_relRef(relRef, errorMsg);
    case REL_FOLLOWS:
    case REL_FOLLOWS_STAR:
        return this->add_follows_relRef(relRef, errorMsg);
    case REL_NEXT:
    case REL_NEXT_STAR:
        return this->add_next_relRef(relRef, errorMsg);
    case REL_AFFECTS:
    case REL_AFFECTS_STAR:
        return this->add_affects_relRef(relRef, errorMsg);
    default:
        if (errorMsg) {
            *errorMsg = strdup("add_relRef - trying to add invalid rel ref");
        }
        return PARSE_QINFO_INSERT_INVALID_RELREF;
    }
}

ParseError QueryInfo::add_patCl(const PatCl &p, char **errorMsg)
{
    ParseError ret = PARSE_OK;
    assert(p.type != PATCL_INVALID && p.varRefType != PATVARREF_INVALID &&
            ((p.type == PATCL_ASSIGN && p.exprType != PATEXPR_INVALID) ||
             (p.type != PATCL_ASSIGN)));
    if (this->patClSet.find(p) != this->patClSet.end()) {
        if (errorMsg) {
            StringBuffer sb;
            sb.append("QueryInfo::add_patCl - repeated clause: ");
            sb.append(p.toString());
            *errorMsg = strdup(sb.c_str());
        }
    } else {
        this->insertOrder.push_back(
                make_pair(PATTERN_CLAUSE, this->patCls.size()));
        this->patClSet.insert(p);
        this->patCls.push_back(p);
        this->clauses.push_back(new PatCl(p));
    }
    return ret;
}

void QueryInfo::dump(void) const
{
    this->dump(stdout);
}

void QueryInfo::dump(FILE *f) const
{
    fprintf(f, "%s", this->dump_to_string().c_str());
}

std::string QueryInfo::dump_to_string() const
{
    StringBuffer sb;
    this->dump_decl_select(sb);
    this->dump_clauses(sb);
    return sb.toString();
}

void QueryInfo::dump_decl_select(StringBuffer &sb) const
{
    sb.append("DECLARATIONS\n");
    for (vector<pair<DesignEnt, string> >::const_iterator it =
            this->entVec.begin(); it != this->entVec.end(); it++) {
        sb.append("  ");
        sb.append(entity_type_to_string(it->first));
        sb.append(' ');
        sb.append(it->second.c_str());
        sb.append('\n');
    }
    sb.append("SELECT ");
    if (this->selectType == SEL_TUPLE) {
        sb.append("TUPLE\n");
        for (vector<AttrRef>::const_iterator kt =
                this->selectTuple.begin(); kt != this->selectTuple.end();
                kt++) {
            const AttrRef& attrRef = *kt;
            sb.append("  ");
            attrRef.dump_to_sb(sb);
            sb.append('\n');
        }
    } else {
        sb.append("BOOLEAN\n");
    }
}

void QueryInfo::dump_clauses(StringBuffer &sb) const
{
    for (vector<pair<ClauseType, int> >::const_iterator it =
            this->insertOrder.begin(); it != this->insertOrder.end();
            it++) {
        switch (it->first) {
        case SUCHTHAT_CLAUSE:
            sb.append(this->relRefs[it->second].dump());
            sb.append('\n');
            break;
        case PATTERN_CLAUSE:
            sb.append(this->patCls[it->second].toString(true));
            sb.append('\n');
            break;
        }
    }
}

int QueryInfo::get_nr_clauses() const
{
    return (int)this->insertOrder.size();
}

ClauseType QueryInfo::get_nth_clause_type(int n) const
{
    int len = this->insertOrder.size();
    ClauseType ret = INVALID_CLAUSE;
    if (n >= 0 && n < len) {
        return this->insertOrder[n].first;
    } else {
        return INVALID_CLAUSE;
    }
}

GenericRef *QueryInfo::get_nth_clause(int n)
{
    int len = this->insertOrder.size();
    if (n >= 0 && n < len) {
        return this->clauses[n];
    } else {
        return NULL;
    }
}

SelectType QueryInfo::get_selectType() const
{
    return this->selectType;
}

const vector<AttrRef>& QueryInfo::get_selectTuple() const
{
    return this->selectTuple;
}