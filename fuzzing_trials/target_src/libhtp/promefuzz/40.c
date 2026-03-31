// This fuzz driver is generated for library libhtp, aiming to fuzz the following functions:
// bstr_begins_with_c_nocase at bstr.c:122:5 in bstr.h
// bstr_begins_with_c at bstr.c:118:5 in bstr.h
// bstr_index_of_c_nocase at bstr.c:298:5 in bstr.h
// bstr_cmp_c_nocase at bstr.c:218:5 in bstr.h
// bstr_begins_with_nocase at bstr.c:126:5 in bstr.h
// bstr_index_of_nocase at bstr.c:314:5 in bstr.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "bstr.h"

static bstr *create_bstr(const uint8_t *data, size_t size) {
    bstr *b = (bstr *)malloc(sizeof(bstr));
    if (b == NULL) return NULL;
    b->len = size;
    b->size = size;
    b->realptr = (unsigned char *)malloc(size);
    if (b->realptr == NULL) {
        free(b);
        return NULL;
    }
    memcpy(b->realptr, data, size);
    return b;
}

static void free_bstr(bstr *b) {
    if (b) {
        free(b->realptr);
        free(b);
    }
}

int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;  // Ensure there's enough data for meaningful fuzzing

    // Split the input data into two parts
    size_t half_size = Size / 2;
    const uint8_t *haystack_data = Data;
    size_t haystack_size = half_size;

    const uint8_t *needle_data = Data + half_size;
    size_t needle_size = Size - half_size;

    // Create bstr instances
    bstr *bhaystack = create_bstr(haystack_data, haystack_size);
    bstr *bneedle = create_bstr(needle_data, needle_size);
    if (bhaystack == NULL || bneedle == NULL) {
        free_bstr(bhaystack);
        free_bstr(bneedle);
        return 0;
    }

    // Ensure needle is NUL-terminated for C string functions
    char *cneedle = (char *)malloc(needle_size + 1);
    if (cneedle == NULL) {
        free_bstr(bhaystack);
        free_bstr(bneedle);
        return 0;
    }
    memcpy(cneedle, needle_data, needle_size);
    cneedle[needle_size] = '\0';

    // Call the target functions
    int res1 = bstr_begins_with_c_nocase(bhaystack, cneedle);
    int res2 = bstr_begins_with_c(bhaystack, cneedle);
    int res3 = bstr_index_of_c_nocase(bhaystack, cneedle);
    int res4 = bstr_cmp_c_nocase(bhaystack, cneedle);
    int res5 = bstr_begins_with_nocase(bhaystack, bneedle);
    int res6 = bstr_index_of_nocase(bhaystack, bneedle);

    // Clean up
    free(cneedle);
    free_bstr(bhaystack);
    free_bstr(bneedle);

    return 0;
}