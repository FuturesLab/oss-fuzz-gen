#include <stdint.h>
#include <stddef.h>
#include <janet.h>

// Function prototype for the function-under-test
int janet_scan_numeric(const uint8_t *data, int32_t size, Janet *result);

int LLVMFuzzerTestOneInput_349(const uint8_t *data, size_t size) {
    // Ensure size is within the range of int32_t
    if (size > INT32_MAX) {
        return 0;
    }

    // Initialize a Janet variable to store the result
    Janet result;

    // Call the function-under-test
    int status = janet_scan_numeric(data, (int32_t)size, &result);

    // Optionally, handle the result or status if needed
    // For example, you might want to perform some checks or logging here

    return 0;
}