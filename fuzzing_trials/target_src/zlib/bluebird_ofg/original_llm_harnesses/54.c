#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <stdlib.h> // Include the standard library for malloc and free

int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
    // Initialize variables for compress2 function
    Bytef *dest;
    uLongf destLen;
    const Bytef *source = data;
    uLong sourceLen = (uLong)size;
    int level = Z_BEST_COMPRESSION;

    // Allocate memory for dest, ensuring it's not NULL
    destLen = compressBound(sourceLen);
    dest = (Bytef *)malloc(destLen);
    if (dest == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Call the function-under-test
    compress2(dest, &destLen, source, sourceLen, level);

    // Free allocated memory
    free(dest);

    return 0;
}