// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_smalloc at gc.c:706:7 in janet.h
// janet_gcpressure at gc.c:52:6 in janet.h
// janet_gcpressure at gc.c:52:6 in janet.h
// janet_smalloc at gc.c:706:7 in janet.h
// janet_srealloc at gc.c:735:7 in janet.h
// janet_gcpressure at gc.c:52:6 in janet.h
// janet_gcpressure at gc.c:52:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "janet.h"

static void fuzz_janet_smalloc(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(size_t)) return;
    size_t alloc_size;
    memcpy(&alloc_size, Data, sizeof(size_t));
    
    // Limit the allocation size to avoid excessive memory requests
    if (alloc_size > 1024 * 1024) return; // Example limit: 1MB

    void *ptr = janet_smalloc(alloc_size);
    if (ptr) {
        janet_gcpressure(alloc_size);
    }
}

static void fuzz_janet_calloc(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(size_t)) return;
    size_t nmemb, elem_size;
    memcpy(&nmemb, Data, sizeof(size_t));
    memcpy(&elem_size, Data + sizeof(size_t), sizeof(size_t));

    // Limit the allocation size to avoid excessive memory requests
    if (nmemb > 1024 || elem_size > 1024) return; // Example limits

    void *ptr = janet_calloc(nmemb, elem_size);
    if (ptr) {
        janet_gcpressure(nmemb * elem_size);
    }
}

static void fuzz_janet_srealloc(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(size_t)) return;
    size_t realloc_size;
    memcpy(&realloc_size, Data, sizeof(size_t));

    // Limit the allocation size to avoid excessive memory requests
    if (realloc_size > 1024 * 1024) return; // Example limit: 1MB

    void *ptr = janet_smalloc(1); // Initial allocation
    if (ptr) {
        ptr = janet_srealloc(ptr, realloc_size);
        if (ptr) {
            janet_gcpressure(realloc_size);
        }
    }
}

static void fuzz_janet_realloc(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(size_t)) return;
    size_t realloc_size;
    memcpy(&realloc_size, Data, sizeof(size_t));

    // Limit the allocation size to avoid excessive memory requests
    if (realloc_size > 1024 * 1024) return; // Example limit: 1MB

    void *ptr = janet_realloc(NULL, 1); // Initial allocation
    if (ptr) {
        ptr = janet_realloc(ptr, realloc_size);
        if (ptr) {
            janet_gcpressure(realloc_size);
        }
    }
}

int LLVMFuzzerTestOneInput_531(const uint8_t *Data, size_t Size) {
    fuzz_janet_smalloc(Data, Size);
    fuzz_janet_calloc(Data, Size);
    fuzz_janet_srealloc(Data, Size);
    fuzz_janet_realloc(Data, Size);
    return 0;
}