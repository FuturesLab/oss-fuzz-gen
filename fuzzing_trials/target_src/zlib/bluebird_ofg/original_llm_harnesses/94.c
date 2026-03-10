#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_94(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the function parameters
    Bytef *dest;
    uLongf destLen = size * 2; // Initial destination buffer size
    const Bytef *source = data;
    uLong sourceLen = size;

    // Allocate memory for the destination buffer
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