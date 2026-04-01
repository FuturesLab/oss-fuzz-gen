#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_95(const uint8_t *data, size_t size) {
    // Initialize all variables
    Bytef *dest;
    uLongf destLen;
    const Bytef *source = data;
    uLong sourceLen = size;
    
    // Allocate memory for the destination buffer
    // Assume a maximum compression ratio of 4:1 for this example
    destLen = size * 4;
    dest = (Bytef *)malloc(destLen);
    if (dest == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Call the function-under-test
    uncompress(dest, &destLen, source, sourceLen);

    // Free allocated memory
    free(dest);

    return 0;
}