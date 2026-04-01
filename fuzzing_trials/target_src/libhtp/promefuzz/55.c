// This fuzz driver is generated for library libhtp, aiming to fuzz the following functions:
// bstr_index_of_mem at bstr.c:306:5 in bstr.h
// bstr_util_cmp_mem at bstr.c:349:5 in bstr.h
// bstr_add_mem at bstr.c:66:7 in bstr.h
// bstr_util_mem_index_of_mem at bstr.c:493:5 in bstr.h
// bstr_util_mem_to_pint at bstr.c:431:9 in bstr.h
// bstr_cmp_mem at bstr.c:226:5 in bstr.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bstr.h"

static void fuzz_bstr_util_cmp_mem(const uint8_t *Data, size_t Size) {
    if (Size < 2) return;

    const void *data1 = Data;
    size_t len1 = Size / 2;
    const void *data2 = Data + len1;
    size_t len2 = Size - len1;

    int result = bstr_util_cmp_mem(data1, len1, data2, len2);
    (void)result; // Suppress unused variable warning
}

static void fuzz_bstr_add_mem(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(bstr)) return;

    bstr *b = (bstr *)malloc(sizeof(bstr));
    if (!b) return;
    b->len = 0;
    b->size = 0;
    b->realptr = NULL;

    const void *data = Data;
    size_t len = Size;

    bstr *result = bstr_add_mem(b, data, len);
    if (result != NULL) {
        free(result->realptr);
        free(result);
    } else {
        free(b->realptr);
        free(b);
    }
}

static void fuzz_bstr_util_mem_index_of_mem(const uint8_t *Data, size_t Size) {
    if (Size < 2) return;

    const void *data1 = Data;
    size_t len1 = Size / 2;
    const void *data2 = Data + len1;
    size_t len2 = Size - len1;

    int result = bstr_util_mem_index_of_mem(data1, len1, data2, len2);
    (void)result; // Suppress unused variable warning
}

static void fuzz_bstr_util_mem_to_pint(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(size_t) + sizeof(int)) return;

    const void *data = Data;
    size_t len = Size - sizeof(size_t) - sizeof(int);
    int base = 10; // Default base for conversion
    size_t lastlen = 0;

    int64_t result = bstr_util_mem_to_pint(data, len, base, &lastlen);
    (void)result; // Suppress unused variable warning
}

static void fuzz_bstr_cmp_mem(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(bstr)) return;

    bstr *b = (bstr *)malloc(sizeof(bstr));
    if (!b) return;
    b->len = 0;
    b->size = 0;
    b->realptr = NULL;

    const void *data = Data;
    size_t len = Size;

    int result = bstr_cmp_mem(b, data, len);
    (void)result; // Suppress unused variable warning

    free(b->realptr);
    free(b);
}

static void fuzz_bstr_index_of_mem(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(bstr)) return;

    bstr *bhaystack = (bstr *)malloc(sizeof(bstr));
    if (!bhaystack) return;
    bhaystack->len = 0;
    bhaystack->size = 0;
    bhaystack->realptr = NULL;

    const void *data = Data;
    size_t len = Size;

    int result = bstr_index_of_mem(bhaystack, data, len);
    (void)result; // Suppress unused variable warning

    free(bhaystack->realptr);
    free(bhaystack);
}

int LLVMFuzzerTestOneInput_55(const uint8_t *Data, size_t Size) {
    fuzz_bstr_util_cmp_mem(Data, Size);
    fuzz_bstr_add_mem(Data, Size);
    fuzz_bstr_util_mem_index_of_mem(Data, Size);
    fuzz_bstr_util_mem_to_pint(Data, Size);
    fuzz_bstr_cmp_mem(Data, Size);
    fuzz_bstr_index_of_mem(Data, Size);
    return 0;
}