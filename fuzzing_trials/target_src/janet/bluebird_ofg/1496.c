#include <stdint.h>
#include <stddef.h>
#include "janet.h"

extern int janet_equals(Janet x, Janet y);

int LLVMFuzzerTestOneInput_1496(const uint8_t *data, size_t size) {
    if (size < 2 * sizeof(Janet)) {
        return 0;
    }

    // Assume the data is large enough to extract two Janet values
    Janet x, y;

    // Extract two Janet values from the input data
    x = *(Janet *)(data);
    y = *(Janet *)(data + sizeof(Janet));

    // Call the function-under-test
    int result = janet_equals(x, y);

    // Use the result somehow (e.g., print, log, etc.)
    // For fuzzing purposes, we typically do not need to do anything with the result
    (void)result;

    return 0;
}