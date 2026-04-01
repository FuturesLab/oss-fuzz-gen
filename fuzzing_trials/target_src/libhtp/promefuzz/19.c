// This fuzz driver is generated for library libhtp, aiming to fuzz the following functions:
// bstr_expand at bstr.c:266:7 in bstr.h
// bstr_dup_ex at bstr.c:246:7 in bstr.h
// bstr_add_mem at bstr.c:66:7 in bstr.h
// bstr_dup_mem at bstr.c:258:7 in bstr.h
// bstr_alloc at bstr.c:43:7 in bstr.h
// bstr_wrap_mem at bstr.c:630:7 in bstr.h
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

static bstr* create_random_bstr(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(bstr)) return NULL;
    bstr *b = (bstr *)malloc(sizeof(bstr));
    if (b == NULL) return NULL;

    b->len = Size / 2;
    b->size = Size;
    b->realptr = (unsigned char *)malloc(b->size);
    if (b->realptr == NULL) {
        free(b);
        return NULL;
    }
    memcpy(b->realptr, Data, b->len);
    return b;
}

int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    bstr *b = create_random_bstr(Data, Size);
    if (b == NULL) return 0;

    // Fuzz bstr_expand
    bstr *expanded_b = bstr_expand(b, Size * 2);
    if (expanded_b) {
        free(expanded_b->realptr);
        free(expanded_b);
    }

    // Fuzz bstr_dup_ex
    bstr *dup_ex_b = bstr_dup_ex(b, 0, b->len);
    if (dup_ex_b) {
        free(dup_ex_b->realptr);
        free(dup_ex_b);
    }

    // Fuzz bstr_add_mem
    bstr *add_mem_b = bstr_add_mem(b, Data, Size);
    if (add_mem_b) {
        free(add_mem_b->realptr);
        free(add_mem_b);
    }

    // Fuzz bstr_dup_mem
    bstr *dup_mem_b = bstr_dup_mem(Data, Size);
    if (dup_mem_b) {
        free(dup_mem_b->realptr);
        free(dup_mem_b);
    }

    // Fuzz bstr_alloc
    bstr *alloc_b = bstr_alloc(Size);
    if (alloc_b) {
        free(alloc_b->realptr);
        free(alloc_b);
    }

    // Fuzz bstr_wrap_mem
    bstr *wrap_mem_b = bstr_wrap_mem(Data, Size);
    if (wrap_mem_b) {
        free(wrap_mem_b);
    }

    free(b->realptr);
    free(b);
    return 0;
}