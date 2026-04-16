#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy
#include "janet.h"  // Include for Janet related functions and types

int LLVMFuzzerTestOneInput_1482(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet)) {
        return 0;
    }

    Janet janet_value;
    memcpy(&janet_value, data, sizeof(Janet));

    JanetIntType result = janet_is_int(janet_value);

    (void)result; // Suppress unused variable warning

    return 0;
}