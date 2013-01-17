#ifndef T11_SPA_UTILS_H
#define T11_SPA_UTILS_H

#include <string>

#define S_TO_UINT_MAX 2147483647L
#define S_TO_UINT_EMPTY_STRING "string_to_uint - String is empty"
#define S_TO_UINT_WHITESPACE "string_to_uint - String consists of whitespace"
#define S_TO_UINT_TOO_LONG  "string_to_uint - String is too long (max 10 char)"
#define S_TO_UINT_OVERFLOW "string_to_uint - integer overflow. Max 2147483647"

/*
 * Contains helper functions that can be used across entire SPA
 */

/*
 * Converts a string to an unsigned integer. The bounds of the unsigned
 * integer should be from 0 to 2147483647 inclusive.
 * @return - true on successful conversion, false otherwise
 * @param s - string representing the unsigned integer
 * @param res - Returns the integer that is converted. Please supply
 *              a pointer to an integer here.
 * @param errorMsg - upon error, an error message will be returned here.
 *                   Please supply a pointer to char * here. The caller
 *                   is expected to check whether the returned string is
 *                   NULL and call free() on it if it's not NULL.
 *
 * Errors checked for:
 * - String is empty
 * - String consists solely of whitespace
 * - String exceeds 10 characters after trimming off whitespace.
 *   Since our upper bound is 2147483647 which has 10 digits, we cannot
 *   convert anything above 10 digits.
 * - Overflow error. Overflows our upper bound.
 */
bool string_to_uint(const std::string& s, int *res, char **errorMsg);

#endif