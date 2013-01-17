#include "SPAUtils.h"

using std::string;

bool string_to_uint(const string& s, int *res, char **errorMsg)
{
    int len = s.size();
    if (len <= 0) {
        if (errorMsg) {
            *errorMsg = strdup(S_TO_UINT_EMPTY_STRING);
        }
        return false;
    }
    int idx = 0;
    while (idx < len && isspace(s[idx])) {
        idx++;
    }
    if (idx >= len) {
        if (errorMsg) {
            *errorMsg = strdup(S_TO_UINT_WHITESPACE);
        }
        return false;
    }
    if (len - idx > 10) {
        if (errorMsg) {
            *errorMsg = strdup(S_TO_UINT_TOO_LONG);
        }
        return false;
    }
    long long tmp = 0;
    while (idx < len && isdigit(s[idx])) {
        tmp = tmp * 10 + (s[idx++] - '0');
    }
    if (tmp > S_TO_UINT_MAX) {
        if (errorMsg) {
            *errorMsg = strdup(S_TO_UINT_OVERFLOW);
        }
        return false;
    }
    if (res) {
        *res = (int)tmp;
    }
    return true;
}