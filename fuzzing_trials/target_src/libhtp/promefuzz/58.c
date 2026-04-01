// This fuzz driver is generated for library libhtp, aiming to fuzz the following functions:
// bstr_dup at bstr.c:238:7 in bstr.h
// bstr_index_of at bstr.c:290:5 in bstr.h
// bstr_cmp_nocase at bstr.c:234:5 in bstr.h
// bstr_cmp_c_nocase at bstr.c:218:5 in bstr.h
// bstr_cmp at bstr.c:210:5 in bstr.h
// bstr_begins_with at bstr.c:114:5 in bstr.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "bstr.h"

static bstr *create_bstr_from_data(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(bstr)) return NULL;

    bstr *b = (bstr *)malloc(sizeof(bstr));
    if (!b) return NULL;

    b->len = Size - sizeof(bstr);
    b->size = Size - sizeof(bstr);
    b->realptr = (unsigned char *)malloc(b->len);
    if (!b->realptr) {
        free(b);
        return NULL;
    }
    memcpy(b->realptr, Data + sizeof(bstr), b->len);

    return b;
}

int LLVMFuzzerTestOneInput_58(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(bstr)) return 0;

    // Create bstr from input data
    bstr *b1 = create_bstr_from_data(Data, Size);
    bstr *b2 = create_bstr_from_data(Data, Size);

    if (!b1 || !b2) {
        free(b1);
        free(b2);
        return 0;
    }

    // Test bstr_dup
    bstr *dup = bstr_dup(b1);
    if (dup) {
        free(dup->realptr);
        free(dup);
    }

    // Test bstr_index_of
    int index = bstr_index_of(b1, b2);

    // Test bstr_cmp_nocase
    int cmp_nocase = bstr_cmp_nocase(b1, b2);

    // Test bstr_cmp_c_nocase
    char cstr[] = "test";
    int cmp_c_nocase = bstr_cmp_c_nocase(b1, cstr);

    // Test bstr_cmp
    int cmp = bstr_cmp(b1, b2);

    // Test bstr_begins_with
    int begins_with = bstr_begins_with(b1, b2);

    // Cleanup
    free(b1->realptr);
    free(b1);
    free(b2->realptr);
    free(b2);

    return 0;
}