#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

// Assume the function is declared in an external library
extern int janet_scan_number(const uint8_t *data, int32_t size, double *result);

int LLVMFuzzerTestOneInput_204(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0; // Ensure there's at least one byte to process
    }

    double result;
    int32_t dataSize = (int32_t)size; // Cast size to int32_t for the function call

    // Call the function-under-test
    janet_scan_number(data, dataSize, &result);

    return 0;
}