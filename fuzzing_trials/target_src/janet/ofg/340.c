#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <inttypes.h>
#include <limits.h>

// Assuming the function is declared in some header file
int janet_scan_uint64(const uint8_t *data, int32_t size, uint64_t *output);

int LLVMFuzzerTestOneInput_340(const uint8_t *data, size_t size) {
    // Ensure size is within the range of int32_t
    if (size > INT32_MAX) {
        return 0;
    }

    // Initialize the output parameter
    uint64_t output = 0;

    // Call the function-under-test
    int result = janet_scan_uint64(data, (int32_t)size, &output);

    // Optionally, print the result and output for debugging
    // printf("Result: %d, Output: %" PRIu64 "\n", result, output);

    return 0;
}