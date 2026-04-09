// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_smalloc at gc.c:706:7 in janet.h
// janet_gcpressure at gc.c:52:6 in janet.h
// janet_srealloc at gc.c:735:7 in janet.h
// janet_gcpressure at gc.c:52:6 in janet.h
// janet_smalloc at gc.c:706:7 in janet.h
// janet_srealloc at gc.c:735:7 in janet.h
// janet_gcpressure at gc.c:52:6 in janet.h
// janet_srealloc at gc.c:735:7 in janet.h
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

#define MAX_ALLOC_SIZE 1024

static void fuzz_janet_smalloc(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(size_t)) return;
    size_t alloc_size = *((size_t *)Data) % MAX_ALLOC_SIZE;
    void *ptr = janet_smalloc(alloc_size);
    if (ptr) {
        janet_gcpressure(alloc_size);
        // Properly release Janet's scratch memory instead of using free
        janet_srealloc(ptr, 0);
    }
}

static void fuzz_janet_calloc(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(size_t)) return;
    size_t nmemb = ((size_t *)Data)[0] % 10; // limit number of elements
    size_t elem_size = ((size_t *)Data)[1] % MAX_ALLOC_SIZE;
    void *ptr = janet_calloc(nmemb, elem_size);
    if (ptr) {
        janet_gcpressure(nmemb * elem_size);
        free(ptr);
    }
}

static void fuzz_janet_srealloc(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(size_t)) return;
    size_t alloc_size = *((size_t *)Data) % MAX_ALLOC_SIZE;
    void *ptr = janet_smalloc(alloc_size);
    if (ptr) {
        size_t new_size = (alloc_size + 1) % MAX_ALLOC_SIZE;
        void *new_ptr = janet_srealloc(ptr, new_size);
        if (new_ptr) {
            janet_gcpressure(new_size);
            janet_srealloc(new_ptr, 0); // Properly release Janet's scratch memory
        }
    }
}

static void fuzz_janet_realloc(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(size_t)) return;
    size_t alloc_size = *((size_t *)Data) % MAX_ALLOC_SIZE;
    void *ptr = malloc(alloc_size);
    if (ptr) {
        size_t new_size = (alloc_size + 1) % MAX_ALLOC_SIZE;
        void *new_ptr = janet_realloc(ptr, new_size);
        if (new_ptr) {
            janet_gcpressure(new_size);
            free(new_ptr);
        }
    }
}

int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size) {
    fuzz_janet_smalloc(Data, Size);
    fuzz_janet_calloc(Data, Size);
    fuzz_janet_srealloc(Data, Size);
    fuzz_janet_realloc(Data, Size);
    return 0;
}