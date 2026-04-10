#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include string.h for memcpy
#include <janet.h> // Assuming Janet library provides this header

int LLVMFuzzerTestOneInput_255(const uint8_t *data, size_t size) {
    if (size < sizeof(double)) {
        return 0; // Not enough data to form a double
    }

    // Interpret the first 8 bytes of data as a double
    double input_double;
    memcpy(&input_double, data, sizeof(double));

    // Call the function-under-test
    Janet result = janet_nanbox_from_double(input_double);

    // Use the result in some way to avoid any compiler optimizations
    // that might skip the call if the result is unused
    (void)result;

    return 0;
}