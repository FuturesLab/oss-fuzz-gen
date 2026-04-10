// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_smalloc at gc.c:706:7 in janet.h
// janet_sfree at gc.c:759:6 in janet.h
// janet_smalloc at gc.c:706:7 in janet.h
// janet_srealloc at gc.c:735:7 in janet.h
// janet_sfree at gc.c:759:6 in janet.h
// janet_sfree at gc.c:759:6 in janet.h
// janet_cryptorand at janet.c:34711:5 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

static void fuzz_janet_smalloc(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(size_t)) return;
    size_t alloc_size;
    memcpy(&alloc_size, Data, sizeof(size_t));
    alloc_size = alloc_size % (1024 * 1024); // Limit allocation to 1MB for safety
    void *ptr = janet_smalloc(alloc_size);
    if (ptr) {
        janet_sfree(ptr);
    }
}

static void fuzz_janet_malloc(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(size_t)) return;
    size_t alloc_size;
    memcpy(&alloc_size, Data, sizeof(size_t));
    alloc_size = alloc_size % (1024 * 1024); // Limit allocation to 1MB for safety
    void *ptr = janet_malloc(alloc_size);
    if (ptr) {
        free(ptr);
    }
}

static void fuzz_janet_srealloc(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(size_t) * 2) return;
    size_t initial_size, realloc_size;
    memcpy(&initial_size, Data, sizeof(size_t));
    memcpy(&realloc_size, Data + sizeof(size_t), sizeof(size_t));
    initial_size = initial_size % (1024 * 1024); // Limit allocation to 1MB for safety
    realloc_size = realloc_size % (1024 * 1024); // Limit allocation to 1MB for safety

    void *ptr = janet_smalloc(initial_size);
    if (ptr) {
        void *new_ptr = janet_srealloc(ptr, realloc_size);
        if (new_ptr) {
            janet_sfree(new_ptr);
        } else {
            janet_sfree(ptr);
        }
    }
}

static void fuzz_janet_cryptorand(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(size_t)) return;
    size_t n;
    memcpy(&n, Data, sizeof(size_t));
    n = n % 256; // Limit to 256 bytes for buffer
    uint8_t *buffer = (uint8_t *)malloc(n);
    if (buffer) {
        janet_cryptorand(buffer, n);
        free(buffer);
    }
}

static void fuzz_janet_realloc(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(size_t) * 2) return;
    size_t initial_size, realloc_size;
    memcpy(&initial_size, Data, sizeof(size_t));
    memcpy(&realloc_size, Data + sizeof(size_t), sizeof(size_t));
    initial_size = initial_size % (1024 * 1024); // Limit allocation to 1MB for safety
    realloc_size = realloc_size % (1024 * 1024); // Limit allocation to 1MB for safety

    void *ptr = janet_malloc(initial_size);
    if (ptr) {
        void *new_ptr = janet_realloc(ptr, realloc_size);
        if (new_ptr) {
            free(new_ptr);
        } else if (realloc_size == 0) {
            // If realloc with size 0, it may return NULL but still free the memory
            ptr = NULL;
        }
    }
}

int LLVMFuzzerTestOneInput_417(const uint8_t *Data, size_t Size) {
    fuzz_janet_smalloc(Data, Size);
    fuzz_janet_malloc(Data, Size);
    fuzz_janet_srealloc(Data, Size);
    fuzz_janet_cryptorand(Data, Size);
    fuzz_janet_realloc(Data, Size);
    return 0;
}