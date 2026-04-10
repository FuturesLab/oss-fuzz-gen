// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_smalloc at gc.c:706:7 in janet.h
// janet_gcpressure at gc.c:52:6 in janet.h
// janet_gcpressure at gc.c:52:6 in janet.h
// janet_srealloc at gc.c:735:7 in janet.h
// janet_gcpressure at gc.c:52:6 in janet.h
// janet_gcpressure at gc.c:52:6 in janet.h
// janet_sfree at gc.c:759:6 in janet.h
// janet_sfree at gc.c:759:6 in janet.h
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

static size_t get_size_t_from_data(const uint8_t *Data, size_t Size, size_t *Index) {
    if (*Index + sizeof(size_t) > Size) {
        return 0;
    }
    size_t value;
    memcpy(&value, Data + *Index, sizeof(size_t));
    *Index += sizeof(size_t);
    return value;
}

static size_t sanitize_size(size_t size) {
    // Limit size to a reasonable value to prevent excessive allocation
    const size_t max_size = 1024 * 1024; // 1 MB
    return size > max_size ? max_size : size;
}

int LLVMFuzzerTestOneInput_373(const uint8_t *Data, size_t Size) {
    if (Size < 3 * sizeof(size_t)) {
        return 0;
    }

    size_t index = 0;
    size_t alloc_size = sanitize_size(get_size_t_from_data(Data, Size, &index));
    size_t nmemb = sanitize_size(get_size_t_from_data(Data, Size, &index));
    size_t realloc_size = sanitize_size(get_size_t_from_data(Data, Size, &index));

    // Test janet_smalloc
    void *smalloc_ptr = janet_smalloc(alloc_size);
    if (smalloc_ptr) {
        janet_gcpressure(alloc_size);
    }

    // Test janet_calloc
    void *calloc_ptr = janet_calloc(nmemb, alloc_size);
    if (calloc_ptr) {
        janet_gcpressure(nmemb * alloc_size);
    }

    // Test janet_srealloc
    void *srealloc_ptr = janet_srealloc(smalloc_ptr, realloc_size);
    if (srealloc_ptr) {
        janet_gcpressure(realloc_size);
    }

    // Test janet_realloc
    void *realloc_ptr = janet_realloc(calloc_ptr, realloc_size);
    if (realloc_ptr) {
        janet_gcpressure(realloc_size);
    }

    // Free allocated memory
    if (srealloc_ptr && srealloc_ptr != smalloc_ptr) {
        janet_sfree(srealloc_ptr);
    } else if (smalloc_ptr) {
        janet_sfree(smalloc_ptr);
    }

    if (realloc_ptr != calloc_ptr) {
        free(realloc_ptr); // Use free since janet_realloc does not use janet_smalloc
    } else if (calloc_ptr) {
        free(calloc_ptr);
    }

    return 0;
}