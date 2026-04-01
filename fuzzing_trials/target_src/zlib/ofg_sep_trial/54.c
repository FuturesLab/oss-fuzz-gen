#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
    // Define and initialize the parameters for compress2
    Bytef *dest; // Output buffer
    uLongf destLen = compressBound(size); // Maximum size of the compressed data
    const Bytef *source = data; // Input data
    uLong sourceLen = size; // Length of input data
    int level = Z_BEST_COMPRESSION; // Compression level

    // Allocate memory for the destination buffer
    dest = (Bytef *)malloc(destLen);
    if (dest == NULL) {
        return 0; // Memory allocation failed
    }

    // Call the function-under-test
    int result = compress2(dest, &destLen, source, sourceLen, level);

    // Free allocated memory
    free(dest);

    return 0;
}