// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_smalloc at gc.c:706:7 in janet.h
// janet_gcpressure at gc.c:52:6 in janet.h
// janet_srealloc at gc.c:735:7 in janet.h
// janet_gcpressure at gc.c:52:6 in janet.h
// janet_scalloc at gc.c:725:7 in janet.h
// janet_gcpressure at gc.c:52:6 in janet.h
// janet_srealloc at gc.c:735:7 in janet.h
// janet_smalloc at gc.c:706:7 in janet.h
// janet_gcpressure at gc.c:52:6 in janet.h
// janet_srealloc at gc.c:735:7 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

#define MAX_ALLOC_SIZE 1024 * 1024 * 10 // 10 MB limit for allocation

static void fuzz_janet_smalloc(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(size_t)) return;
    size_t alloc_size;
    memcpy(&alloc_size, Data, sizeof(size_t));
    alloc_size = alloc_size % MAX_ALLOC_SIZE; // Limit allocation size
    void *mem = janet_smalloc(alloc_size);
    if (mem) {
        janet_gcpressure(alloc_size);
        janet_srealloc(mem, alloc_size / 2); // Resize to half
    }
}

static void fuzz_janet_calloc(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(size_t)) return;
    size_t nmemb, size;
    memcpy(&nmemb, Data, sizeof(size_t));
    memcpy(&size, Data + sizeof(size_t), sizeof(size_t));
    nmemb = nmemb % 1000; // Limit number of elements
    size = size % MAX_ALLOC_SIZE; // Limit element size
    void *mem = janet_calloc(nmemb, size);
    if (mem) {
        janet_gcpressure(nmemb * size);
        janet_realloc(mem, nmemb * size * 2); // Resize to double
    }
}

static void fuzz_janet_scalloc(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(size_t)) return;
    size_t nmemb, size;
    memcpy(&nmemb, Data, sizeof(size_t));
    memcpy(&size, Data + sizeof(size_t), sizeof(size_t));
    nmemb = nmemb % 1000; // Limit number of elements
    size = size % MAX_ALLOC_SIZE; // Limit element size
    void *mem = janet_scalloc(nmemb, size);
    if (mem) {
        janet_gcpressure(nmemb * size);
        janet_srealloc(mem, nmemb * size * 2); // Resize to double
    }
}

static void fuzz_janet_srealloc(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(size_t)) return;
    size_t alloc_size;
    memcpy(&alloc_size, Data, sizeof(size_t));
    alloc_size = alloc_size % MAX_ALLOC_SIZE; // Limit allocation size
    void *mem = janet_smalloc(alloc_size);
    if (mem) {
        janet_gcpressure(alloc_size);
        janet_srealloc(mem, alloc_size * 2); // Resize to double
    }
}

int LLVMFuzzerTestOneInput_493(const uint8_t *Data, size_t Size) {
    fuzz_janet_smalloc(Data, Size);
    fuzz_janet_calloc(Data, Size);
    fuzz_janet_scalloc(Data, Size);
    fuzz_janet_srealloc(Data, Size);
    return 0;
}