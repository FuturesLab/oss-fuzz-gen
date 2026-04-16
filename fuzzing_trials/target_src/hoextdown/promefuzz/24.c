// This fuzz driver is generated for library hoextdown, aiming to fuzz the following functions:
// hoedown_malloc at buffer.c:9:1 in buffer.h
// hoedown_realloc at buffer.c:35:1 in buffer.h
// hoedown_buffer_init at buffer.c:48:1 in buffer.h
// hoedown_buffer_put at buffer.c:120:1 in buffer.h
// hoedown_buffer_slurp at buffer.c:210:1 in buffer.h
// hoedown_calloc at buffer.c:22:1 in buffer.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"

static void *custom_realloc(void *ptr, size_t size) {
    return realloc(ptr, size);
}

static void custom_free(void *ptr) {
    free(ptr);
}

int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Fuzz hoedown_malloc
    void *allocated_memory = hoedown_malloc(Size);
    if (!allocated_memory) return 0;

    // Fuzz hoedown_realloc
    void *reallocated_memory = hoedown_realloc(allocated_memory, Size / 2 + 1);
    if (!reallocated_memory) {
        free(allocated_memory);
        return 0;
    }

    // Initialize hoedown_buffer
    hoedown_buffer buffer;
    hoedown_buffer_init(&buffer, 64, custom_realloc, custom_free, custom_free);

    // Fuzz hoedown_buffer_put
    hoedown_buffer_put(&buffer, Data, Size);

    // Fuzz hoedown_buffer_slurp
    hoedown_buffer_slurp(&buffer, Size / 2);

    // Fuzz hoedown_calloc
    void *calloc_memory = hoedown_calloc(1, Size);
    if (!calloc_memory) {
        buffer.data_free(buffer.data);
        return 0;
    }

    // Cleanup
    buffer.data_free(buffer.data);
    free(calloc_memory);

    return 0;
}