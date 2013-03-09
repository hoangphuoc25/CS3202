#ifndef T11_SPA_UTILS_H
#define T11_SPA_UTILS_H

#include <string>

#define S_TO_INT_UPPER_BOUND 2147483647L
#define S_TO_INT_ABS_LOWER_BOUND 2147483648L
#define S_TO_INT_EMPTY_STRING \
        "string_to_int - String is empty"
#define S_TO_INT_WHITESPACE \
        "string_to_int - String consists of whitespace"
#define S_TO_INT_TOO_LONG \
        "string_to_int - String is too long (max 10 char)"
#define S_TO_INT_OVERFLOW \
        "string_to_int - integer overflow. Max 2147483647, got %lld"
#define S_TO_INT_UNDERFLOW \
        "string_to_int - integer underflow. Min -2147483648, got -%lld"

/*
 * Contains helper functions that can be used across entire SPA
 */

/*
 * Converts a string to a 32-bit signed integer. The bounds of the signed
 * integer should be from -2147483647 to 2147483647 inclusive.
 * @return - true on successful conversion, false otherwise
 * @param s - string representing the signed integer
 * @param res - Returns the integer that is converted. Please supply
 *              a pointer to a 32-bit signed integer here.
 * @param errorMsg - upon error, an error message will be returned here.
 *                   Please supply a pointer to char * here. The caller
 *                   is expected to check whether the returned string is
 *                   NULL and call free() on it if it's not NULL.
 *
 * Errors checked for:
 * - String is empty
 * - String consists solely of whitespace
 * - String exceeds 10 characters after trimming off whitespace.
 *   Since our upper bound is 2147483647 (lower bound is -2147483648)
 *   which has 10 digits, we cannot convert anything above 10 digits.
 * - Overflow error. Overflows our upper bound (or lower bound).
 */
bool string_to_int(const std::string& s, int *res, char **errorMsg);

#endif