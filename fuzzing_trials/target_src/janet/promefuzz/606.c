// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_array at janet.c:1562:13 in janet.h
// janet_array_push at janet.c:1620:6 in janet.h
// janet_array_pop at janet.c:1631:7 in janet.h
// janet_array_peek at janet.c:1640:7 in janet.h
// janet_array_n at janet.c:1576:13 in janet.h
// janet_array_push at janet.c:1620:6 in janet.h
// janet_nanbox_to_pointer at janet.c:37680:7 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

static Janet random_janet() {
    Janet j;
    switch (rand() % 4) {
    case 0:
        j.i64 = rand();
        break;
    case 1:
        j.number = (double)rand() / RAND_MAX;
        break;
    case 2:
        j.pointer = NULL;
        break;
    case 3:
        j.u64 = (uint64_t)rand();
        break;
    }
    return j;
}

int LLVMFuzzerTestOneInput_606(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return 0;

    janet_init();

    int32_t capacity = *(int32_t *)Data;
    Data += sizeof(int32_t);
    Size -= sizeof(int32_t);

    JanetArray *array = janet_array(capacity);

    for (size_t i = 0; i < Size / sizeof(Janet); i++) {
        janet_array_push(array, random_janet());
    }

    Janet popped = janet_array_pop(array);
    (void)popped;

    Janet peeked = janet_array_peek(array);
    (void)peeked;

    JanetArray *new_array = janet_array_n(array->data, array->count);
    janet_array_push(new_array, random_janet());

    Janet wrapped = { .pointer = new_array };
    JanetArray *unwrapped = janet_unwrap_array(wrapped);
    (void)unwrapped;

    janet_deinit();

    return 0;
}