// This fuzz driver is generated for library libhtp, aiming to fuzz the following functions:
// bstr_add_c at bstr.c:58:7 in bstr.h
// bstr_adjust_len at bstr.c:102:6 in bstr.h
// bstr_add_noex at bstr.c:98:7 in bstr.h
// bstr_add at bstr.c:54:7 in bstr.h
// bstr_add_mem_noex at bstr.c:81:7 in bstr.h
// bstr_adjust_size at bstr.c:110:6 in bstr.h
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "bstr.h"

static bstr *create_bstr_with_size(size_t size) {
    bstr *b = (bstr *)malloc(sizeof(bstr));
    if (b == NULL) return NULL;
    b->len = 0;
    b->size = size;
    b->realptr = (unsigned char *)malloc(size);
    if (b->realptr == NULL) {
        free(b);
        return NULL;
    }
    return b;
}

static void free_bstr(bstr *b) {
    if (b) {
        free(b->realptr);
        free(b);
    }
}

int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create bstr objects
    bstr *b1 = create_bstr_with_size(128);
    bstr *b2 = create_bstr_with_size(128);
    if (!b1 || !b2) {
        free_bstr(b1);
        free_bstr(b2);
        return 0;
    }

    // Ensure the data is null-terminated
    char *cstr = (char *)malloc(Size + 1);
    if (!cstr) {
        free_bstr(b1);
        free_bstr(b2);
        return 0;
    }
    memcpy(cstr, Data, Size);
    cstr[Size] = '\0';

    // Fuzz bstr_add_c
    b1 = bstr_add_c(b1, cstr);
    if (!b1) {
        free(cstr);
        free_bstr(b2);
        return 0;
    }

    // Fuzz bstr_adjust_len
    size_t new_len = Size % 128;
    bstr_adjust_len(b1, new_len);

    // Fuzz bstr_add_noex
    b1 = bstr_add_noex(b1, b2);

    // Fuzz bstr_add
    b1 = bstr_add(b1, b2);
    if (!b1) {
        free(cstr);
        free_bstr(b2);
        return 0;
    }

    // Fuzz bstr_add_mem_noex
    b1 = bstr_add_mem_noex(b1, Data, Size);

    // Fuzz bstr_adjust_size
    size_t new_size = (Size % 256) + 1;
    bstr_adjust_size(b1, new_size);

    // Clean up
    free(cstr);
    free_bstr(b1);
    free_bstr(b2);

    return 0;
}