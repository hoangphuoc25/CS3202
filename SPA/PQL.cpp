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

// silence Visual Studio
#define strdup _strdup

/// Global AttrRefCmp
struct AttrRefCmp glob__AttrRefCmp;

/// Global RefCmp
struct RefCmp glob__RefCmp;

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

const char *TYPE_ERROR_NEXTBIP[TYPE_ERROR_ARRAY_SZ] = {
    "NextBip: arg one must be a synonym of type" \
    " stmt, assign, call, while, if, prog_line;" \
    " or an integer;" \
    " or an underscore",

    "NextBip: arg two must be a synonym of type" \
    " stmt, assign, call, while, if, prog_line;" \
    " or an integer;" \
    " or an underscore",
};

const char *TYPE_ERROR_NEXTBIP_STAR[TYPE_ERROR_ARRAY_SZ] = {
    "NextBip*: arg one must be a synonym of type" \
    " stmt, assign, call, while, if, prog_line;" \
    " or an integer;" \
    " or an underscore",

    "NextBip*: arg two must be a synonym of type" \
    " stmt, assign, call, while, if, prog_line;" \
    " or an integer;" \
    " or an underscore",
};

const char *TYPE_ERROR_AFFECTSBIP[TYPE_ERROR_ARRAY_SZ] = {
    "AffectsBip: arg one must be a synonym of type" \
    " assign;" \
    " or an integer;" \
    " or an underscore",

    "AffectsBip: arg two must be a synonym of type" \
    " assign;" \
    " or an integer;" \
    " or an underscore"
};

const char *TYPE_ERROR_AFFECTSBIP_STAR[TYPE_ERROR_ARRAY_SZ] = {
    "AffectsBip*: arg one must be a synonym of type" \
    " assign;" \
    " or an integer;" \
    " or an underscore",

    "AffectsBip*: arg two must be a synonym of type" \
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
    case REL_NEXTBIP:
        return NEXTBIP_STR;
    case REL_NEXTBIP_STAR:
        return NEXTBIP_STAR_STR;
    case REL_AFFECTSBIP:
        return AFFECTSBIP_STR;
    case REL_AFFECTSBIP_STAR:
        return AFFECTSBIP_STAR_STR;
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
    case ATTR_PROGLINE:
        return ATTR_PROGLINE_STR;
        break;
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

BaseType refSynType_to_BaseType(RefSynType refSynType)
{
    switch (refSynType) {
    case REFSYN_PROC:
    case REFSYN_CALL_PROCNAME:
    case REFSYN_VAR:
        return BASETYPE_STRING;
        break;
    case REFSYN_STMTLST:
    case REFSYN_STMT:
    case REFSYN_ASSIGN:
    case REFSYN_CALL:
    case REFSYN_WHILE:
    case REFSYN_IF:
    case REFSYN_CONST:
    case REFSYN_PROGLINE:
    case REFSYN_PROGLINE_PROGLINE_NO:
        return BASETYPE_INT;
        break;
    case REFSYN_INVALID:
    default:
        return BASETYPE_INVALID;
        break;
    }
}

const char *baseType_to_string(BaseType baseType)
{
    switch (baseType) {
    case BASETYPE_STRING:
        return BASETYPE_STRING_STR;
        break;
    case BASETYPE_INT:
        return BASETYPE_INT_STR;
        break;
    default:
        return INVALID_STR;
        break;
    }
}

RefSynType attrRef_to_RefSynType(const AttrRef& attrRef)
{
    switch (attrRef.entType) {
    case ENT_ASSIGN:
        if (ATTR_STMTNO == attrRef.attr) {
            return REFSYN_ASSIGN;
        }
        break;
    case ENT_CALL:
        if (ATTR_STMTNO == attrRef.attr) {
            return REFSYN_CALL;
        } else if (ATTR_PROCNAME == attrRef.attr) {
            return REFSYN_CALL_PROCNAME;
        }
        break;
    case ENT_IF:
        if (ATTR_STMTNO == attrRef.attr) {
            return REFSYN_IF;
        }
        break;
    case ENT_WHILE:
        if (ATTR_STMTNO == attrRef.attr) {
            return REFSYN_WHILE;
        }
        break;
    case ENT_STMT:
        if (ATTR_STMTNO == attrRef.attr) {
            return REFSYN_STMT;
        }
        break;
    case ENT_PROGLINE:
        if (ATTR_DEFAULT == attrRef.attr) {
            return REFSYN_PROGLINE;
        } else if (ATTR_PROGLINE == attrRef.attr) {
            return REFSYN_PROGLINE_PROGLINE_NO;
        }
        break;
    case ENT_STMTLST:
        if (ATTR_STMTNO == attrRef.attr) {
            return REFSYN_STMTLST;
        }
        break;
    case ENT_CONST:
        if (ATTR_VALUE == attrRef.attr) {
            return REFSYN_CONST;
        }
        break;
    case ENT_PROC:
        if (ATTR_PROCNAME == attrRef.attr) {
            return REFSYN_PROC;
        }
        break;
    case ENT_VAR:
        if (ATTR_VARNAME == attrRef.attr) {
            return REFSYN_VAR;
        }
        break;
    default:
        break;
    }
    return REFSYN_INVALID;
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
    using std::swap;
    AttrRef tmp(o);
    swap(*this, tmp);
    return *this;
}

AttrRef::~AttrRef() {}

bool AttrRef::operator==(const AttrRef& o) const
{
    return ((0 == this->syn.compare(o.syn)) &&
            (this->entType == o.entType) &&
            (this->attr == o.attr));
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
    using std::swap;
    RelRef tmp(o);
    swap(*this, tmp);
    return *this;
}

RelRef::~RelRef() {}

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
            if (!string_to_int(sb.toString(), &argOneInt, errorMsg)) {
                ret = PARSE_REL_ARG_INT_INVALID;
            }
        } else {
            if (!string_to_int(sb.toString(), &argTwoInt, errorMsg)) {
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
    using std::swap;
    PatCl tmp(o);
    swap(*this, tmp);
    return *this;
}

PatCl::~PatCl() {}

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

//////////////////////////////////////////////////////////////////////
// Ref
//////////////////////////////////////////////////////////////////////

Ref::Ref()
        : refType(REF_INVALID), refStringVal(), refIntVal(),
          refSynType(REFSYN_INVALID) {}

Ref::Ref(const Ref& o)
        : refType(o.refType), refStringVal(o.refStringVal),
          refIntVal(o.refIntVal), refSynType(o.refSynType) {}

Ref& Ref::operator=(const Ref& o)
{
    using std::swap;
    Ref tmp(o);
    swap(*this, tmp);
    return *this;
}

bool Ref::operator==(const Ref& o) const
{
    if (this->refType != o.refType) {
        return false;
    } else {
        switch (this->refType) {
        case REF_STRING:
            return (0 == this->refStringVal.compare(o.refStringVal));
            break;
        case REF_INT:
            return (this->refIntVal == o.refIntVal);
            break;
        case REF_ATTRREF:
            return (0 == this->refStringVal.compare(o.refStringVal) &&
                    this->refSynType == o.refSynType);
            break;
        default:
            // REF_INVALID
            return true;
            break;
        }
    }
}

string Ref::toString() const
{
    StringBuffer sb;
    switch (this->refType) {
    case REF_STRING:
        sb.append('"');
        sb.append(this->refStringVal);
        sb.append('"');
        break;
    case REF_INT:
        sb.append_int(this->refIntVal);
        break;
    case REF_ATTRREF:
        if (REFSYN_INVALID == this->refSynType) {
            sb.append("Invalid RefSynType");
        } else {
            sb.append(this->refStringVal);
            switch (this->refSynType) {
            case REFSYN_ASSIGN:
            case REFSYN_CALL:
            case REFSYN_IF:
            case REFSYN_WHILE:
            case REFSYN_STMT:
            case REFSYN_STMTLST:
                sb.append('.');
                sb.append(ATTR_STMTNO_STR);
                break;
            case REFSYN_PROGLINE:
                // nothing
                break;
            case REFSYN_PROGLINE_PROGLINE_NO:
                sb.append('.');
                sb.append(ATTR_PROGLINE_STR);
                break;
            case REFSYN_PROC:
            case REFSYN_CALL_PROCNAME:
                sb.append('.');
                sb.append(ATTR_PROCNAME_STR);
                break;
            case REFSYN_VAR:
                sb.append('.');
                sb.append(ATTR_VARNAME_STR);
                break;
            case REFSYN_CONST:
                sb.append('.');
                sb.append(ATTR_VALUE_STR);
                break;
            }
            break;
        }
    default:
        sb.append("Invalid Ref");
        break;
    }
    return sb.toString();
}

bool Ref::valid(const Ref& ref)
{
    if (REF_INVALID == ref.refType) {
        return false;
    } else if (REF_ATTRREF == ref.refType) {
        return REFSYN_INVALID != ref.refSynType;
    }
    return true;
}

BaseType Ref::get_BaseType(const Ref& ref)
{
    switch (ref.refType) {
    case REF_STRING:
        return BASETYPE_STRING;
        break;
    case REF_INT:
        return BASETYPE_INT;
        break;
    case REF_ATTRREF:
        return refSynType_to_BaseType(ref.refSynType);
        break;
    default:
        return BASETYPE_INVALID;
    }
}

bool RefCmp::operator()(const Ref& x, const Ref& y) const
{
    int cmp;
    if (x.refType != y.refType) {
        return x.refType < y.refType;
    } else {
        switch (x.refType) {
        case REF_STRING:
            return x.refStringVal < y.refStringVal;
            break;
        case REF_INT:
            return x.refIntVal < y.refIntVal;
            break;
        case REF_ATTRREF:
            cmp = x.refStringVal.compare(y.refStringVal);
            if (0 == cmp) {
                return x.refSynType < y.refSynType;
            } else if (cmp < 0) {
                // x.refStringVal < y.refStringVal
                return false;
            } else {
                // x.refStringVal > y.refStringVal
                return true;
            }
            break;
        default:
            // REF_INVALID and REF_INVALID, return false
            return false;
            break;
        }
    }
}

WithClause::WithClause()
        : leftRef(), rightRef() {}

WithClause::WithClause(const WithClause& o)
        : leftRef(o.leftRef), rightRef(o.rightRef) {}

WithClause& WithClause::operator=(const WithClause& o)
{
    using std::swap;
    WithClause tmp(o);
    swap(*this, tmp);
    return *this;
}

string WithClause::toString() const
{
    StringBuffer sb;
    sb.append(leftRef.toString());
    sb.append(" = ");
    sb.append(rightRef.toString());
    return sb.toString();
}

void WithClause::normalize()
{
    using std::swap;
    if (REF_ATTRREF == this->leftRef.refType &&
            REF_ATTRREF == this->rightRef.refType) {
        if (this->leftRef.refSynType == this->rightRef.refSynType) {
            // compare synonym strings and order lexicographically
            int cmp = this->leftRef.refStringVal.compare(
                              this->rightRef.refStringVal);
            if (cmp > 0) {
                swap(this->leftRef, this->rightRef);
            }
            // else cmp <= 0, do nothing
        } else if (this->leftRef.refSynType > this->rightRef.refSynType) {
            // swap left and right ref
            swap(this->leftRef, this->rightRef);
        }
        // else properly ordered
    } else if (REF_ATTRREF == this->rightRef.refType) {
        // swap left ref and right ref
        swap(this->leftRef, this->rightRef);
    }
    // else (a) left Ref is attrRef, rightRef is concrete and we're done
    // OR   (b) both side are concrete values, and we're done
}

void WithClause::dummy() {}

bool WithClause::is_contradiction() const
{
    if (REF_INVALID == this->leftRef.refType ||
            REF_INVALID == this->rightRef.refType) {
        return true;
    }

    if (REF_ATTRREF == this->leftRef.refType &&
            REF_ATTRREF == this->rightRef.refType) {
        BaseType leftBaseType =
                refSynType_to_BaseType(this->leftRef.refSynType);
        BaseType rightBaseType =
                refSynType_to_BaseType(this->rightRef.refSynType);
        if (BASETYPE_INVALID == leftBaseType ||
                BASETYPE_INVALID == rightBaseType) {
            return true;
        } else if (leftBaseType != rightBaseType) {
            return true;
        }
        // more intensive checks
        if (BASETYPE_INT == leftBaseType) {
            if (leftRef.refSynType == rightRef.refSynType) {
                // same RefSynType, possibly may be equal
                return false;
            }
            // Now, we have these few types remaining
            // - assign, call, if, while
            // - stmt, prog_line, prog_line.prog_line#, const, stmtLst
            // And we know that, assign, call, if, while can NEVER
            // occupy the same line.
            // So as long as one of the 2 RefSynType is:
            // - stmt, prog_line, prog_line.prog_line#, const, stmtLst
            // Then the 2 sides may possibly be equal.
            //
            // Otherwise, the 2 sides are of different RefSynType and
            // none of them is stmt, prog_line, prog_line.prog_line#,
            // const, stmtLst.
            // This means a contradiction.
            if (REFSYN_STMT == leftRef.refSynType ||
                    REFSYN_PROGLINE == leftRef.refSynType ||
                    REFSYN_PROGLINE_PROGLINE_NO == leftRef.refSynType ||
                    REFSYN_CONST == leftRef.refSynType ||
                    REFSYN_STMTLST == leftRef.refSynType ||

                    REFSYN_STMT == rightRef.refSynType ||
                    REFSYN_PROGLINE == rightRef.refSynType ||
                    REFSYN_PROGLINE_PROGLINE_NO == rightRef.refSynType ||
                    REFSYN_CONST == rightRef.refSynType ||
                    REFSYN_STMTLST == rightRef.refSynType) {
                return false;
            } else {
                return true;
            }
        } else {
            // both sides are some string type
            // this limits us to:
            // 1. procedure.procName
            // 2. call.procName
            // 3. variable.varName
            // And it is entirely possible that these may be equal
            // Hence, not definite contradiction
            return false;
        }
    } else if (REF_ATTRREF == this->leftRef.refType) {
        BaseType leftBaseType =
                refSynType_to_BaseType(this->leftRef.refSynType);
        switch (leftBaseType) {
        case BASETYPE_INT:
            return REF_INT != this->rightRef.refType;
            break;
        case BASETYPE_STRING:
            return REF_STRING != this->rightRef.refType;
            break;
        default:
            return true;
            break;
        }
    } else if (REF_ATTRREF == this->rightRef.refType) {
        BaseType rightBaseType =
                refSynType_to_BaseType(this->rightRef.refSynType);
        switch (rightBaseType) {
        case BASETYPE_INT:
            return REF_INT != this->leftRef.refType;
            break;
        case BASETYPE_STRING:
            return REF_STRING != this->leftRef.refType;
            break;
        default:
            return true;
            break;
        }
    } else if (REF_INT == this->leftRef.refType) {
        if (REF_INT != this->rightRef.refType) {
            return true;
        } else {
            return this->leftRef.refIntVal != this->rightRef.refIntVal;
        }
    } else if (REF_STRING == this->leftRef.refType) {
        if (REF_STRING != this->rightRef.refType) {
            return true;
        } else {
            if (0 != this->leftRef.refStringVal.compare(
                             this->rightRef.refStringVal)) {
                return true;
            } else {
                return false;
            }
        }
    } else {
        assert(false);
    }
}

bool WithClause::valid_refs(const WithClause& withClause)
{
    return Ref::valid(withClause.leftRef) &&
            Ref::valid(withClause.rightRef);
}

bool WithClause::valid_type(const WithClause& withClause)
{
    BaseType leftRefType = Ref::get_BaseType(withClause.leftRef);
    BaseType rightRefType = Ref::get_BaseType(withClause.rightRef);
    if (BASETYPE_INVALID == leftRefType ||
            BASETYPE_INVALID == rightRefType) {
        return false;
    }
    return leftRefType == rightRefType;
}

bool WithClauseCmp::operator()(const WithClause& x,
        const WithClause& y) const
{
    if (x.leftRef == y.leftRef) {
        return glob__RefCmp(x.rightRef, y.rightRef);
    } else {
        return glob__RefCmp(x.leftRef, y.leftRef);
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
    case REL_NEXT:
    case REL_NEXT_STAR:
    // NextBip and NextBip* have same arg 1 types as Next
    case REL_NEXTBIP:
    case REL_NEXTBIP_STAR:
        return (QueryInfo::NEXT_ARGONE_TYPES.find(entType) !=
                QueryInfo::NEXT_ARGONE_TYPES.end());
        break;
    case REL_AFFECTS:
    case REL_AFFECTS_STAR:
    // AffectsBip and AffectsBip* have same arg 1 types as Affects
    case REL_AFFECTSBIP:
    case REL_AFFECTSBIP_STAR:
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
    case REL_NEXT:
    case REL_NEXT_STAR:
    // NextBip and NextBip* have same arg 2 types as Next
    case REL_NEXTBIP:
    case REL_NEXTBIP_STAR:
        return (QueryInfo::NEXT_ARGTWO_TYPES.find(entType) !=
                QueryInfo::NEXT_ARGTWO_TYPES.end());
        break;
    case REL_AFFECTS:
    case REL_AFFECTS_STAR:
    // AffectsBip and AffectsBip* have same arg 2 types as Affects
    case REL_AFFECTSBIP:
    case REL_AFFECTSBIP_STAR:
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
    this->alive = true;
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
    this->withClauseVec.clear();
    this->withClauseSet.clear();
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
    // NextBip and NextBip* have same type of args as Next
    case REL_NEXTBIP:
    case REL_NEXTBIP_STAR:
        return this->add_next_relRef(relRef, errorMsg);
    case REL_AFFECTS:
    case REL_AFFECTS_STAR:
    // AffectsBip and AffectsBip* have same type of args as Affects
    case REL_AFFECTSBIP:
    case REL_AFFECTSBIP_STAR:
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

ParseError QueryInfo::add_withClause(const WithClause& withClause,
        char **errorMsg)
{
    bool insertClause = false;
    ParseError ret = PARSE_OK;
    WithClause newWithClause(withClause);
    newWithClause.normalize();
    if (this->withClauseSet.end() !=
            this->withClauseSet.find(newWithClause)) {
        if (errorMsg) {
            StringBuffer sb;
            sb.append("QueryInfo::add_withClause - repeated clause: ");
            sb.append(withClause.toString());
            *errorMsg = strdup(sb.c_str());
        }
    } else {
        if (newWithClause.leftRef.refType ==
                newWithClause.rightRef.refType) {
            switch (newWithClause.leftRef.refType) {
            case REF_STRING:
                // the two strings are different
                // this query should just fail
                if (0 != newWithClause.leftRef.refStringVal.compare(
                                 newWithClause.rightRef.refStringVal)) {
                    ret = PARSE_WITHCLAUSE_VALUE_MISMATCH;
                }
                // else string = string, tautology
                break;
            case REF_INT:
                // the two int are different
                // this query should just fail
                if (newWithClause.leftRef.refIntVal !=
                        newWithClause.rightRef.refIntVal) {
                    ret = PARSE_WITHCLAUSE_VALUE_MISMATCH;
                }
                // else int = int, tautology
                break;
            case REF_ATTRREF:
                if (newWithClause.leftRef.refSynType ==
                        newWithClause.rightRef.refSynType) {
                    if (0 != newWithClause.leftRef.refStringVal.compare(
                            newWithClause.rightRef.refStringVal)) {
                        // different synonym of same RefSynType, insert
                        // TODO: Simplify this step by rewriting and equating
                        //       the two synonyms through all clauses
                        insertClause = true;
                    }
                    // else same synonym, tautology
                } else {
                    // shortcircuit query evaluation if contradiction
                    if (newWithClause.is_contradiction()) {
                        ret = PARSE_WITHCLAUSE_CONTRADICTION;
                    } else {
                        insertClause = true;
                    }
                }
                break;
            default:
                assert(false);
            }
        } else {
            // different RefType
            assert(!newWithClause.is_contradiction());
            insertClause = true;
        }
    }
    if (insertClause) {
        this->insertOrder.push_back(
                make_pair(WITH_CLAUSE, this->withClauseVec.size()));
        this->withClauseSet.insert(newWithClause);
        this->withClauseVec.push_back(newWithClause);
        this->clauses.push_back(new WithClause(newWithClause));
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
    if (this->alive) {
        this->dump_clauses(sb);
    }
    return sb.toString();
}

void QueryInfo::dump_decl_select(StringBuffer &sb) const
{
    if (this->alive) {
        sb.append("ALIVE\n");
    } else {
        sb.append("DEAD\n");
        return;
    }
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
        case WITH_CLAUSE:
            sb.append(this->withClauseVec[it->second].toString());
            sb.append('\n');
            break;
        }
    }
}

int QueryInfo::get_nr_clauses() const
{
    return (int)this->insertOrder.size();
}

const GenericRef *QueryInfo::get_nth_clause(int n,
        ClauseType *clauseType) const
{
    int len = this->insertOrder.size();
    if (n >= 0 && n < len) {
        if (clauseType) {
            *clauseType = this->insertOrder[n].first;
        }
        return this->clauses[n];
    } else {
        if (clauseType) {
            *clauseType = INVALID_CLAUSE;
        }
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

bool QueryInfo::is_alive() const
{
    return this->alive;
}

void QueryInfo::kill()
{
    this->alive = false;
}