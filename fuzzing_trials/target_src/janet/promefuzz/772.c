// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_smalloc at gc.c:706:7 in janet.h
// janet_gcpressure at gc.c:52:6 in janet.h
// janet_gcpressure at gc.c:52:6 in janet.h
// janet_gcpressure at gc.c:52:6 in janet.h
// janet_smalloc at gc.c:706:7 in janet.h
// janet_srealloc at gc.c:735:7 in janet.h
// janet_gcpressure at gc.c:52:6 in janet.h
// janet_scalloc at gc.c:725:7 in janet.h
// janet_gcpressure at gc.c:52:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "janet.h"

static void fuzz_janet_smalloc(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(size_t)) return;
    size_t alloc_size = *((size_t *)Data);
    if (alloc_size == 0 || alloc_size > 1024 * 1024 * 10) return; // Limit allocation size
    void *ptr = janet_smalloc(alloc_size);
    if (ptr) {
        // Simulate some usage of the allocated memory
        janet_gcpressure(alloc_size);
        // Normally, janet's garbage collector would handle freeing
    }
}

static void fuzz_janet_malloc(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(size_t)) return;
    size_t alloc_size = *((size_t *)Data);
    if (alloc_size == 0 || alloc_size > 1024 * 1024 * 10) return; // Limit allocation size
    void *ptr = janet_malloc(alloc_size);
    if (ptr) {
        // Simulate some usage of the allocated memory
        janet_gcpressure(alloc_size);
        free(ptr);
    }
}

static void fuzz_janet_calloc(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(size_t)) return;
    size_t nmemb = ((size_t *)Data)[0];
    size_t elem_size = ((size_t *)Data)[1];
    if (nmemb == 0 || elem_size == 0 || nmemb > 1024 * 1024 || elem_size > 1024) return; // Limit allocation size
    void *ptr = janet_calloc(nmemb, elem_size);
    if (ptr) {
        // Simulate some usage of the allocated memory
        janet_gcpressure(nmemb * elem_size);
        free(ptr);
    }
}

static void fuzz_janet_srealloc(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(size_t)) return;
    size_t initial_size = ((size_t *)Data)[0];
    size_t new_size = ((size_t *)Data)[1];
    if (initial_size == 0 || initial_size > 1024 * 1024 * 10) return; // Limit allocation size
    if (new_size == 0 || new_size > 1024 * 1024 * 10) return; // Limit allocation size
    void *ptr = janet_smalloc(initial_size);
    if (ptr) {
        ptr = janet_srealloc(ptr, new_size);
        if (ptr) {
            // Simulate some usage of the reallocated memory
            janet_gcpressure(new_size);
            // Normally, janet's garbage collector would handle freeing
        }
    }
}

static void fuzz_janet_scalloc(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(size_t)) return;
    size_t nmemb = ((size_t *)Data)[0];
    size_t elem_size = ((size_t *)Data)[1];
    if (nmemb == 0 || elem_size == 0 || nmemb > 1024 * 1024 || elem_size > 1024) return; // Limit allocation size
    void *ptr = janet_scalloc(nmemb, elem_size);
    if (ptr) {
        // Simulate some usage of the allocated memory
        janet_gcpressure(nmemb * elem_size);
        // Normally, janet's garbage collector would handle freeing
    }
}

int LLVMFuzzerTestOneInput_772(const uint8_t *Data, size_t Size) {
    fuzz_janet_smalloc(Data, Size);
    fuzz_janet_malloc(Data, Size);
    fuzz_janet_calloc(Data, Size);
    fuzz_janet_srealloc(Data, Size);
    fuzz_janet_scalloc(Data, Size);
    return 0;
}