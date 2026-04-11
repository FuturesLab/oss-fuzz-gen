#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include this header for memcpy
#include <janet.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_254(const uint8_t *data, size_t size) {
    if (size < sizeof(double)) {
        return 0;
    }

    // Extract a double from the input data
    double value;
    memcpy(&value, data, sizeof(double));

    // Call the function-under-test
    Janet result = janet_nanbox_from_double(value);

    // Use the result in some way to prevent compiler optimizations
    (void)result;

    return 0;
}

#ifdef __cplusplus
}
#endif