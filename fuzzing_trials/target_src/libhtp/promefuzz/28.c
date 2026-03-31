// This fuzz driver is generated for library libhtp, aiming to fuzz the following functions:
// bstr_util_mem_index_of_c_nocase at bstr.c:489:5 in bstr.h
// bstr_util_mem_index_of_c at bstr.c:485:5 in bstr.h
// bstr_util_cmp_mem_nocasenorzero at bstr.c:399:5 in bstr.h
// bstr_util_cmp_mem at bstr.c:349:5 in bstr.h
// bstr_util_cmp_mem_nocase at bstr.c:374:5 in bstr.h
// bstr_begins_with_mem_nocase at bstr.c:151:5 in bstr.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "bstr.h"

// Mock implementations of the target functions to allow compilation.
// These should be replaced with actual implementations from libhtp.
// int bstr_util_cmp_mem(const void *data1, size_t len1, const void *data2, size_t len2) {
//     return memcmp(data1, data2, len1 < len2 ? len1 : len2);
// }

// int bstr_util_mem_index_of_c_nocase(const void *data, size_t len, const char *cstr) {
//     size_t cstr_len = strlen(cstr);
//     if (cstr_len == 0 || len < cstr_len) return -1;
//     for (size_t i = 0; i <= len - cstr_len; ++i) {
//         if (strncasecmp((const char *)data + i, cstr, cstr_len) == 0) {
//             return i;
//         }
//     }
//     return -1;
// }

// int bstr_util_cmp_mem_nocase(const void *data1, size_t len1, const void *data2, size_t len2) {
//     size_t min_len = len1 < len2 ? len1 : len2;
//     int cmp = strncasecmp((const char *)data1, (const char *)data2, min_len);
//     if (cmp != 0) return cmp;
//     return (len1 > len2) - (len1 < len2);
// }

// int bstr_util_mem_index_of_c(const void *data, size_t len, const char *cstr) {
//     size_t cstr_len = strlen(cstr);
//     if (cstr_len == 0 || len < cstr_len) return -1;
//     for (size_t i = 0; i <= len - cstr_len; ++i) {
//         if (strncmp((const char *)data + i, cstr, cstr_len) == 0) {
//             return i;
//         }
//     }
//     return -1;
// }

// int bstr_begins_with_mem_nocase(const bstr *bhaystack, const void *data, size_t len) {
//     if (bhaystack->len < len) return 0;
//     return strncasecmp((const char *)bhaystack->realptr, (const char *)data, len) == 0;
// }

// int bstr_util_cmp_mem_nocasenorzero(const void *data1, size_t len1, const void *data2, size_t len2) {
//     size_t i = 0, j = 0;
//     while (i < len1 && j < len2) {
//         while (i < len1 && ((const char *)data1)[i] == '\0') ++i;
//         while (j < len2 && ((const char *)data2)[j] == '\0') ++j;
//         if (i < len1 && j < len2) {
//             int cmp = tolower(((const char *)data1)[i]) - tolower(((const char *)data2)[j]);
//             if (cmp != 0) return cmp;
//             ++i;
//             ++j;
//         }
//     }
//     return (len1 - i) - (len2 - j);
// }

int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    size_t half_size = Size / 2;
    const void *data1 = Data;
    size_t len1 = half_size;
    const void *data2 = Data + half_size;
    size_t len2 = Size - half_size;

    // Test bstr_util_cmp_mem
    bstr_util_cmp_mem(data1, len1, data2, len2);

    // Test bstr_util_mem_index_of_c_nocase
    if (len1 > 0) {
        char cstr[] = "test";
        bstr_util_mem_index_of_c_nocase(data1, len1, cstr);
    }

    // Test bstr_util_cmp_mem_nocase
    bstr_util_cmp_mem_nocase(data1, len1, data2, len2);

    // Test bstr_util_mem_index_of_c
    if (len1 > 0) {
        char cstr[] = "test";
        bstr_util_mem_index_of_c(data1, len1, cstr);
    }

    // Test bstr_begins_with_mem_nocase
    bstr bhaystack;
    bhaystack.len = len1;
    bhaystack.size = len1;
    bhaystack.realptr = (unsigned char *)data1;
    bstr_begins_with_mem_nocase(&bhaystack, data2, len2);

    // Test bstr_util_cmp_mem_nocasenorzero
    bstr_util_cmp_mem_nocasenorzero(data1, len1, data2, len2);

    return 0;
}