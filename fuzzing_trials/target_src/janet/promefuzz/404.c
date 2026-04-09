// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_array_push at janet.c:1620:6 in janet.h
// janet_array_peek at janet.c:1640:7 in janet.h
// janet_array_pop at janet.c:1631:7 in janet.h
// janet_array_push at janet.c:1620:6 in janet.h
// janet_array_n at janet.c:1576:13 in janet.h
// janet_array_pop at janet.c:1631:7 in janet.h
// janet_array_peek at janet.c:1640:7 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_array at janet.c:1562:13 in janet.h
// janet_array_pop at janet.c:1631:7 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static void fuzz_janet_array_operations(JanetArray *array, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) return;

    Janet element;
    memcpy(&element, Data, sizeof(Janet));

    // Test janet_array_push
    janet_array_push(array, element);

    // Test janet_array_peek
    Janet peeked = janet_array_peek(array);

    // Test janet_array_pop
    Janet popped = janet_array_pop(array);

    // Re-push the element to test further
    janet_array_push(array, element);

    // Use the remaining data to test janet_array_n
    if (Size >= 2 * sizeof(Janet)) {
        int32_t n = *((int32_t *)(Data + sizeof(Janet)));
        if (n > 0 && n < INT32_MAX / sizeof(Janet)) {
            Janet *elements = (Janet *)(Data + sizeof(Janet) + sizeof(int32_t));
            if ((size_t)n <= (Size - sizeof(Janet) - sizeof(int32_t)) / sizeof(Janet)) {
                JanetArray *new_array = janet_array_n(elements, n);
                if (new_array) {
                    janet_array_pop(new_array);
                    janet_array_peek(new_array);
                }
            }
        }
    }
}

int LLVMFuzzerTestOneInput_404(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return 0;

    // Initialize Janet runtime
    janet_init();

    // Initialize a JanetArray
    int32_t capacity = *((int32_t *)Data);
    if (capacity < 0 || capacity > INT32_MAX / sizeof(Janet)) return 0;
    JanetArray *array = janet_array(capacity);

    // Fuzz operations on the array
    fuzz_janet_array_operations(array, Data + sizeof(int32_t), Size - sizeof(int32_t));

    // Clean up the array
    while (array->count > 0) {
        janet_array_pop(array);
    }

    // Deinitialize Janet runtime
    janet_deinit();

    return 0;
}