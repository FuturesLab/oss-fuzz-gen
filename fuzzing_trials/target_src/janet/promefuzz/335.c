// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_array_pop at janet.c:1631:7 in janet.h
// janet_array_peek at janet.c:1640:7 in janet.h
// janet_getarray at janet.c:4512:1 in janet.h
// janet_array_n at janet.c:1576:13 in janet.h
// janet_nanbox_from_pointer at janet.c:37686:7 in janet.h
// janet_nanbox_to_pointer at janet.c:37680:7 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

static void initialize_janet_array(JanetArray *array, int32_t count) {
    array->count = count;
    array->capacity = count;
    array->data = (Janet *)malloc(count * sizeof(Janet));
    for (int32_t i = 0; i < count; i++) {
        array->data[i].i64 = i; // Initialize with dummy values
    }
}

static void cleanup_janet_array(JanetArray *array) {
    free(array->data);
    array->data = NULL;
    array->count = 0;
    array->capacity = 0;
}

int LLVMFuzzerTestOneInput_335(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return 0;

    int32_t count = *(int32_t *)Data;
    Data += sizeof(int32_t);
    Size -= sizeof(int32_t);

    JanetArray array;
    initialize_janet_array(&array, count);

    // Fuzz janet_array_pop
    if (array.count > 0) {
        Janet popped = janet_array_pop(&array);
    }

    // Fuzz janet_array_peek
    Janet peeked = janet_array_peek(&array);

    // Fuzz janet_getarray
    if (Size >= sizeof(Janet) * count) {
        JanetArray *retrieved = janet_getarray((const Janet *)Data, 0);
    }

    // Fuzz janet_array_n
    JanetArray *new_array = janet_array_n((const Janet *)Data, count);

    // Fuzz janet_unwrap_array
    Janet wrapped = janet_wrap_array(&array);
    JanetArray *unwrapped = janet_unwrap_array(wrapped);

    cleanup_janet_array(&array);
    if (new_array) {
        cleanup_janet_array(new_array);
        free(new_array);
    }

    return 0;
}