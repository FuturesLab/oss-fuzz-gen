#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

// Assume this is the function-under-test
int64_t bam_auxB2i(const uint8_t *data, uint32_t length);

int LLVMFuzzerTestOneInput_176(const uint8_t *data, size_t size) {
    // Ensure the size is at least as large as the uint32_t length parameter
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Cast size to uint32_t for the function call
    uint32_t length = (uint32_t)size;

    // Call the function-under-test
    int64_t result = bam_auxB2i(data, length);

    // Optionally, print the result for debugging purposes
    // printf("Result: %lld\n", result);

    return 0;
}