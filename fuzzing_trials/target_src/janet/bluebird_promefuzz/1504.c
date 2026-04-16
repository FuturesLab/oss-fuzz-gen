#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

static void fuzz_janet_smalloc(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(size_t)) return;
    size_t alloc_size = *(size_t *)Data;
    if (alloc_size > 1024 * 1024) return; // Limit allocation size to 1MB
    void *memory = janet_smalloc(alloc_size);
    if (memory) {
        janet_gcpressure(alloc_size);
    }
}

static void fuzz_janet_calloc(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(size_t)) return;
    size_t nmemb = *(size_t *)Data;
    size_t size = *(size_t *)(Data + sizeof(size_t));
    if (nmemb > 1024 || size > 1024) return; // Limit allocation size
    void *memory = janet_calloc(nmemb, size);
    if (memory) {
        janet_gcpressure(nmemb * size);
        free(memory);
    }
}

static void fuzz_janet_srealloc(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(size_t)) return;
    size_t alloc_size = *(size_t *)Data;
    if (alloc_size > 1024 * 1024) return; // Limit allocation size to 1MB
    void *memory = janet_smalloc(alloc_size);
    if (memory) {
        janet_gcpressure(alloc_size);
        if (Size >= 2 * sizeof(size_t)) {
            size_t new_size = *(size_t *)(Data + sizeof(size_t));
            if (new_size > 1024 * 1024) return; // Limit new allocation size to 1MB
            void *new_memory = janet_srealloc(memory, new_size);
            if (new_memory) {
                janet_gcpressure(new_size);
            }
        }
    }
}

static void fuzz_janet_scalloc(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(size_t)) return;
    size_t nmemb = *(size_t *)Data;
    size_t size = *(size_t *)(Data + sizeof(size_t));
    if (nmemb > 1024 || size > 1024) return; // Limit allocation size
    void *memory = janet_scalloc(nmemb, size);
    if (memory) {
        janet_gcpressure(nmemb * size);
    }
}

static void fuzz_janet_realloc(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(size_t)) return;
    size_t alloc_size = *(size_t *)Data;
    if (alloc_size > 1024 * 1024) return; // Limit allocation size to 1MB
    void *memory = malloc(alloc_size);
    if (memory) {
        if (Size >= 2 * sizeof(size_t)) {
            size_t new_size = *(size_t *)(Data + sizeof(size_t));
            if (new_size > 1024 * 1024) return; // Limit new allocation size to 1MB
            void *new_memory = janet_realloc(memory, new_size);
            if (new_memory) {
                free(new_memory);
            }
        }
    }
}

int LLVMFuzzerTestOneInput_1504(const uint8_t *Data, size_t Size) {
    fuzz_janet_smalloc(Data, Size);
    fuzz_janet_calloc(Data, Size);
    fuzz_janet_srealloc(Data, Size);
    fuzz_janet_scalloc(Data, Size);
    fuzz_janet_realloc(Data, Size);
    return 0;
}