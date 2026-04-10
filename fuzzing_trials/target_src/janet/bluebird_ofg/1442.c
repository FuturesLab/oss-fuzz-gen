#include <stdint.h>
#include <stddef.h>
#include "janet.h"

extern int janet_checkint64(Janet);

int LLVMFuzzerTestOneInput_1442(const uint8_t *data, size_t size) {
    if (size < sizeof(int64_t)) {
        return 0;
    }

    // Use the input data to construct a Janet integer
    int64_t value;
    memcpy(&value, data, sizeof(int64_t));
    Janet janet_value = janet_wrap_integer(value);

    // Call the function-under-test
    int result = janet_checkint64(janet_value);

    (void)result;  // Suppress unused variable warning

    return 0;
}