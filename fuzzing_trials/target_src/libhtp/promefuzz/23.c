// This fuzz driver is generated for library libhtp, aiming to fuzz the following functions:
// bstr_add_c at bstr.c:58:7 in bstr.h
// bstr_chop at bstr.c:188:6 in bstr.h
// bstr_add_noex at bstr.c:98:7 in bstr.h
// bstr_add_c_noex at bstr.c:62:7 in bstr.h
// bstr_wrap_c at bstr.c:626:7 in bstr.h
// bstr_adjust_realptr at bstr.c:106:6 in bstr.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "bstr.h"

static bstr *create_bstr(size_t size) {
    bstr *b = (bstr *)malloc(sizeof(bstr));
    if (b) {
        b->len = 0;
        b->size = size;
        b->realptr = (unsigned char *)malloc(size);
        if (!b->realptr) {
            free(b);
            return NULL;
        }
    }
    return b;
}

static void free_bstr(bstr *b) {
    if (b) {
        free(b->realptr);
        free(b);
    }
}

int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Ensure there's at least one byte

    // Create a bstr with some initial size
    bstr *b = create_bstr(128);
    if (!b) return 0;

    // Create a null-terminated string from the input data
    char *cstr = (char *)malloc(Size + 1);
    if (!cstr) {
        free_bstr(b);
        return 0;
    }
    memcpy(cstr, Data, Size);
    cstr[Size] = '\0';

    // Test bstr_add_c
    bstr *result = bstr_add_c(b, cstr);
    if (result) {
        b = result;
    }

    // Test bstr_chop
    bstr_chop(b);

    // Create another bstr for testing
    bstr *b2 = create_bstr(64);
    if (b2) {
        // Test bstr_add_noex
        bstr_add_noex(b, b2);

        // Test bstr_add_c_noex
        bstr_add_c_noex(b, cstr);

        free_bstr(b2);
    }

    // Test bstr_wrap_c
    bstr *wrapped_bstr = bstr_wrap_c(cstr);
    if (wrapped_bstr) {
        // Test bstr_adjust_realptr
        bstr_adjust_realptr(wrapped_bstr, b->realptr);

        // Since wrapped_bstr shares the realptr with b, we should not free it twice
        free(wrapped_bstr); // Only free the wrapper, not the realptr
    }

    // Cleanup
    free(cstr);
    free_bstr(b);

    return 0;
}