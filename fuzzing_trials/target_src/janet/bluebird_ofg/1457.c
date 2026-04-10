#include <stdint.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1457(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for a Janet value
    if (size < sizeof(Janet) || data == NULL) {
        return 0;
    }

    // Create a Janet value from the input data
    Janet janet_value = janet_wrap_number(*(const double *)data);

    // Call the function-under-test
    janet_mark(janet_value);

    return 0;
}