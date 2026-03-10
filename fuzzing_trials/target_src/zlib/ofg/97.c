#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size) {
    Bytef *dest;
    uLongf destLen;
    const Bytef *source = data;
    uLong sourceLen = (uLong)size;
    
    // Allocate a buffer for the uncompressed data with an arbitrary size
    destLen = sourceLen * 2; // Assume the uncompressed data is at most twice the size of the compressed data
    dest = (Bytef *)malloc(destLen);
    if (dest == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Call the function-under-test
    int result = uncompress(dest, &destLen, source, sourceLen);

    // Free allocated memory
    free(dest);

    return 0;
}