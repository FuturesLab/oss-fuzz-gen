// This fuzz driver is generated for library libhtp, aiming to fuzz the following functions:
// bstr_dup at bstr.c:238:7 in bstr.h
// bstr_free at bstr.c:285:6 in bstr.h
// bstr_dup_mem at bstr.c:258:7 in bstr.h
// bstr_free at bstr.c:285:6 in bstr.h
// bstr_dup_c at bstr.c:242:7 in bstr.h
// bstr_free at bstr.c:285:6 in bstr.h
// bstr_dup_lower at bstr.c:254:7 in bstr.h
// bstr_free at bstr.c:285:6 in bstr.h
// bstr_to_lowercase at bstr.c:334:7 in bstr.h
// bstr_free at bstr.c:285:6 in bstr.h
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
    bstr *new_bstr = (bstr *)malloc(sizeof(bstr));
    if (new_bstr == NULL) return NULL;

    new_bstr->len = Size;
    new_bstr->size = Size + 1; // Extra room for null terminator
    new_bstr->realptr = (unsigned char *)malloc(new_bstr->size);
    if (new_bstr->realptr == NULL) {
        free(new_bstr);
        return NULL;
    }

    memcpy(new_bstr->realptr, Data, Size);
    new_bstr->realptr[Size] = '\0'; // Ensure null termination

    return new_bstr;
}

int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Test bstr_dup
    bstr *original_bstr = create_bstr_from_data(Data, Size);
    if (original_bstr != NULL) {
        bstr *dup_bstr = bstr_dup(original_bstr);
        bstr_free(dup_bstr);
    }

    // Test bstr_dup_mem
    bstr *dup_mem_bstr = bstr_dup_mem(Data, Size);
    bstr_free(dup_mem_bstr);

    // Test bstr_dup_c
    char *cstr = (char *)malloc(Size + 1);
    if (cstr != NULL) {
        memcpy(cstr, Data, Size);
        cstr[Size] = '\0';
        bstr *dup_c_bstr = bstr_dup_c(cstr);
        bstr_free(dup_c_bstr);
        free(cstr);
    }

    // Test bstr_dup_lower
    if (original_bstr != NULL) {
        bstr *dup_lower_bstr = bstr_dup_lower(original_bstr);
        bstr_free(dup_lower_bstr);

        // Test bstr_to_lowercase
        bstr *lowercase_bstr = bstr_to_lowercase(original_bstr);
    }

    bstr_free(original_bstr);

    return 0;
}