#include <stdint.h>
#include <stddef.h>  // Include this for size_t
#include <zlib.h>
#include <stdio.h>   // Include for logging

// Define the function prototype for crc32_combine_gen64 if it's not declared in the included headers
uLong crc32_combine_gen64(int64_t value);

int LLVMFuzzerTestOneInput_79(const uint8_t *data, size_t size) {
    // Ensure that the input size is at least the size of int64_t
    if (size < sizeof(int64_t)) {
        return 0;
    }

    // Extract an int64_t value from the input data
    int64_t input_value = 0;
    for (size_t i = 0; i < sizeof(int64_t); ++i) {
        input_value |= ((int64_t)data[i]) << (i * 8);
    }

    // Log the input value to ensure it's varied
    printf("Input value: %lld\n", (long long)input_value);

    // Call the function-under-test
    uLong result = crc32_combine_gen64(input_value);

    // Use the result in some way to avoid compiler optimizations removing the call
    // In this case, we just return it as an int
    return (int)result;
}