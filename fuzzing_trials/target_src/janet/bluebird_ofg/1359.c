#include <stdint.h>
#include <stddef.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1359(const uint8_t *data, size_t size) {
    Janet janet_value;

    if (size >= sizeof(Janet)) {
        // Initialize Janet value from input data
        janet_value = *(Janet *)data;

        // Call the function-under-test
        int result = janet_checksize(janet_value);

        // Use the result in some way to avoid compiler optimizations
        if (result == -1) {
            return 0;
        }
    }

    return 0;
}