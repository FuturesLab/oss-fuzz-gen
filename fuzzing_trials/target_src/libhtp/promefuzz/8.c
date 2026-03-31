// This fuzz driver is generated for library libhtp, aiming to fuzz the following functions:
// bstr_index_of_mem_nocase at bstr.c:310:5 in bstr.h
// bstr_index_of at bstr.c:290:5 in bstr.h
// bstr_util_mem_index_of_mem_nocasenorzero at bstr.c:539:5 in bstr.h
// bstr_util_mem_index_of_mem at bstr.c:493:5 in bstr.h
// bstr_util_mem_index_of_mem_nocase at bstr.c:516:5 in bstr.h
// bstr_index_of_mem at bstr.c:306:5 in bstr.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "bstr.h"

static void initialize_bstr(bstr *b, const uint8_t *data, size_t size) {
    b->len = size;
    b->size = size;
    b->realptr = (unsigned char *)malloc(size);
    if (b->realptr) {
        memcpy(b->realptr, data, size);
    }
}

static void cleanup_bstr(bstr *b) {
    if (b->realptr) {
        free(b->realptr);
        b->realptr = NULL;
    }
}

int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    // Split the input data for haystack and needle
    size_t half_size = Size / 2;
    const uint8_t *haystack_data = Data;
    const uint8_t *needle_data = Data + half_size;

    bstr bhaystack;
    bstr bneedle;
    initialize_bstr(&bhaystack, haystack_data, half_size);
    initialize_bstr(&bneedle, needle_data, Size - half_size);

    // Fuzz `bstr_index_of_mem_nocase`
    bstr_index_of_mem_nocase(&bhaystack, needle_data, Size - half_size);

    // Fuzz `bstr_index_of`
    bstr_index_of(&bhaystack, &bneedle);

    // Fuzz `bstr_util_mem_index_of_mem_nocasenorzero`
    bstr_util_mem_index_of_mem_nocasenorzero(haystack_data, half_size, needle_data, Size - half_size);

    // Fuzz `bstr_util_mem_index_of_mem`
    bstr_util_mem_index_of_mem(haystack_data, half_size, needle_data, Size - half_size);

    // Fuzz `bstr_util_mem_index_of_mem_nocase`
    bstr_util_mem_index_of_mem_nocase(haystack_data, half_size, needle_data, Size - half_size);

    // Fuzz `bstr_index_of_mem`
    bstr_index_of_mem(&bhaystack, needle_data, Size - half_size);

    cleanup_bstr(&bhaystack);
    cleanup_bstr(&bneedle);

    return 0;
}