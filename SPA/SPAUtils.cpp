#include "SPAUtils.h"

using std::string;

bool string_to_int(const string& s, int *res, char **errorMsg)
{
    int len = s.size();
    if (len <= 0) {
        if (errorMsg) {
            *errorMsg = strdup(S_TO_INT_EMPTY_STRING);
        }
        return false;
    }
    int idx = 0;
    while (idx < len && isspace(s[idx])) {
        idx++;
    }
    if (idx >= len) {
        if (errorMsg) {
            *errorMsg = strdup(S_TO_INT_WHITESPACE);
        }
        return false;
    }
    bool isNeg = false;
    if (s[idx] == '-') {
        isNeg = true;
        idx++;
    }
    if (len - idx > 10) {
        if (errorMsg) {
            *errorMsg = strdup(S_TO_INT_TOO_LONG);
        }
        return false;
    }
    long long tmp = 0;
    while (idx < len && isdigit(s[idx])) {
        tmp = tmp * 10 + (s[idx++] - '0');
    }
    if (!isNeg) {
        if (tmp > S_TO_INT_UPPER_BOUND) {
            if (errorMsg) {
                // TODO: Use StringBuffer to do this
                char *tmpBuf = new char[500];
                _snprintf(tmpBuf, 500, S_TO_INT_OVERFLOW, tmp);
                *errorMsg = strdup(tmpBuf);
                delete tmpBuf;
            }
            return false;
        }
    } else if (isNeg) {
        if (tmp > S_TO_INT_ABS_LOWER_BOUND) {
            if (errorMsg) {
                // TODO: Use StringBuffer to do this
                char *tmpBuf = new char[500];
                _snprintf(tmpBuf, 500, S_TO_INT_UNDERFLOW, tmp);
                *errorMsg = strdup(tmpBuf);
                delete tmpBuf;
            }
            return false;
        }
    }
    if (isNeg) {
        tmp = -tmp;
    }
    if (res) {
        *res = (int)tmp;
    }
    return true;
}