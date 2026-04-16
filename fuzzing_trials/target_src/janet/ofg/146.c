#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include string.h for memcpy
#include <janet.h>

int LLVMFuzzerTestOneInput_146(const uint8_t *data, size_t size) {
    // Ensure that the size of data is sufficient to extract a double value
    if (size < sizeof(double)) {
        return 0;
    }

    // Extract a double from the input data
    double num;
    // Copy the bytes from data into the double variable
    memcpy(&num, data, sizeof(double));

    // Call the function-under-test
    Janet result = janet_wrap_number(num);

    // Use the result to avoid any compiler optimizations that might remove the call
    (void)result;

    return 0;
}