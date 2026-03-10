#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_156(const uint8_t *data, size_t size) {
    Bytef *dest;
    uLongf destLen;
    const Bytef *source = data;
    uLong sourceLen = (uLong)size;

    // Allocate memory for the destination buffer
    destLen = compressBound(sourceLen);
    dest = (Bytef *)malloc(destLen);
    if (dest == NULL) {
        return 0; // If allocation fails, exit early
    }

    // Call the function-under-test
    int result = compress(dest, &destLen, source, sourceLen);

    // Free allocated memory
    free(dest);

    return 0;
}