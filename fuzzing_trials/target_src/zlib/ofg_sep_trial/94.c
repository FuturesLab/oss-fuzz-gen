#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <stdlib.h> // Include for malloc and free
#include <string.h> // Include for memcpy

int LLVMFuzzerTestOneInput_94(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0; // Return early if there's no data to process
    }

    // Use the fuzzer's input directly as the compressed data
    const Bytef *source = data;
    uLong sourceLen = size;

    // Assume a maximum decompressed size for the fuzzer input
    uLongf destLen = 1024; // Arbitrary large size for decompression buffer
    Bytef *dest = (Bytef *)malloc(destLen);
    if (dest == NULL) {
        return 0; // Return if memory allocation fails
    }

    // Call the function-under-test
    int result = uncompress(dest, &destLen, source, sourceLen);

    // Check if the decompression was successful
    if (result == Z_OK) {
        // Optionally, further process the decompressed data
        // For example, validate the decompressed content
    }

    // Free allocated memory
    free(dest);

    return 0; // Always return 0 to continue fuzzing
}