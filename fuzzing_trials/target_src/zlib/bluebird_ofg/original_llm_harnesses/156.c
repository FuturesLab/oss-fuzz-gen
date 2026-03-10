#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_156(const uint8_t *data, size_t size) {
    // Define and initialize the parameters for the compress function
    Bytef *dest;
    uLongf destLen;
    const Bytef *source = data;
    uLong sourceLen = (uLong)size;

    // Allocate memory for the destination buffer
    // The maximum size of the compressed data is slightly larger than the source data
    destLen = compressBound(sourceLen);
    dest = (Bytef *)malloc(destLen);

    if (dest == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Call the function-under-test
    int result = compress(dest, &destLen, source, sourceLen);

    // Free the allocated memory
    free(dest);

    return 0;
}