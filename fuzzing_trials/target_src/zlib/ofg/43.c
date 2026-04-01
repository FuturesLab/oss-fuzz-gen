#include <stdint.h>
#include <zlib.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
    // Ensure the input size is not zero to avoid undefined behavior
    if (size == 0) {
        return 0;
    }

    // Use the input data to create a uLong value for compressBound
    uLong input_value = (uLong)size; // Use the size of the data for compressBound

    // Calculate the maximum compressed size
    uLong compressed_size = compressBound(input_value);

    // Allocate memory for the compressed data
    uint8_t *compressed_data = (uint8_t *)malloc(compressed_size);
    if (compressed_data == NULL) {
        return 0; // Memory allocation failed
    }

    // Compress the data
    int result = compress(compressed_data, &compressed_size, data, size);

    // Free the allocated memory
    free(compressed_data);

    // Check the result of the compression
    if (result != Z_OK) {
        return 0; // Compression failed
    }

    // Optionally, you can add some checks or assertions on the result
    // For fuzzing purposes, we generally don't need to check the result

    return 0;
}