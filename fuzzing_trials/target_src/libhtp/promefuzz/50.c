// This fuzz driver is generated for library libhtp, aiming to fuzz the following functions:
// bstr_char_at at bstr.c:172:5 in bstr.h
// bstr_index_of_c at bstr.c:294:5 in bstr.h
// bstr_cmp_c at bstr.c:214:5 in bstr.h
// bstr_util_strdup_to_c at bstr.c:621:7 in bstr.h
// bstr_index_of_c_nocasenorzero at bstr.c:302:5 in bstr.h
// bstr_begins_with at bstr.c:114:5 in bstr.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "bstr.h"

static bstr *create_bstr(const uint8_t *Data, size_t Size) {
    bstr *b = (bstr *)malloc(sizeof(bstr));
    if (!b) return NULL;

    b->len = Size;
    b->size = Size;
    b->realptr = (unsigned char *)malloc(Size);
    if (!b->realptr) {
        free(b);
        return NULL;
    }

    memcpy(b->realptr, Data, Size);
    return b;
}

static void free_bstr(bstr *b) {
    if (b) {
        free(b->realptr);
        free(b);
    }
}

int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    bstr *b = create_bstr(Data, Size);
    if (!b) return 0;

    // Test bstr_char_at
    size_t pos = Data[0] % Size; // Ensure pos is within bounds
    int char_at = bstr_char_at(b, pos);

    // Test bstr_index_of_c
    const char *needle = "needle";
    int index_of_c = bstr_index_of_c(b, needle);

    // Test bstr_cmp_c
    const char *cstr = "compare";
    int cmp_c = bstr_cmp_c(b, cstr);

    // Test bstr_util_strdup_to_c
    char *dup_str = bstr_util_strdup_to_c(b);
    if (dup_str) free(dup_str);

    // Test bstr_index_of_c_nocasenorzero
    int index_of_c_nocasenorzero = bstr_index_of_c_nocasenorzero(b, needle);

    // Test bstr_begins_with
    bstr *bneedle = create_bstr((const uint8_t *)needle, strlen(needle));
    if (bneedle) {
        int begins_with = bstr_begins_with(b, bneedle);
        free_bstr(bneedle);
    }

    free_bstr(b);
    return 0;
}