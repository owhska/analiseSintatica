#include "token.h"

const char* tokenTypeToString(TokenType t) {
    switch (t) {
        case KW_PROGRAM: return "KW_PROGRAM";
        case KW_VAR: return "KW_VAR";
        case KW_INTEGER: return "KW_INTEGER";
        case KW_REAL: return "KW_REAL";
        case KW_BEGIN: return "KW_BEGIN";
        case KW_END: return "KW_END";
        case KW_IF: return "KW_IF";
        case KW_THEN: return "KW_THEN";
        case KW_ELSE: return "KW_ELSE";
        case KW_WHILE: return "KW_WHILE";
        case KW_DO: return "KW_DO";

        case ID: return "ID";

        case NUM_INT: return "NUM_INT";
        case NUM_REAL: return "NUM_REAL";

        case OP_ASS: return "OP_ASS";
        case OP_AD: return "OP_AD";
        case OP_MIN: return "OP_MIN";
        case OP_MUL: return "OP_MUL";
        case OP_DIV: return "OP_DIV";

        case OP_EQ: return "OP_EQ";
        case OP_NE: return "OP_NE";
        case OP_LT: return "OP_LT";
        case OP_LE: return "OP_LE";
        case OP_GT: return "OP_GT";
        case OP_GE: return "OP_GE";

        case SMB_SEM: return "SMB_SEM";
        case SMB_COM: return "SMB_COM";
        case SMB_OPA: return "SMB_OPA";
        case SMB_CPA: return "SMB_CPA";
        case SMB_COL: return "SMB_COL";
        case SMB_DOT: return "SMB_DOT";

        case ERRO: return "ERRO";

        default: return "UNKNOWN";
    }
}
