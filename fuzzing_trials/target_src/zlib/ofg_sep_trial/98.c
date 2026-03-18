#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <string.h>
#include <stdlib.h> // Include for malloc and free

int LLVMFuzzerTestOneInput_98(const uint8_t *data, size_t size) {
    // Initialize the input buffer
    const Bytef *source = data;
    uLong sourceLen = size;

    // Initialize the output buffer with a size larger than the input
    uLongf destLen = size * 2; // Assuming decompressed data is not more than twice the compressed size
    Bytef *dest = (Bytef *)malloc(destLen);

    if (dest == NULL) {
        // Handle memory allocation failure
        return 0;
    }

    // Call the function under test
    int result = uncompress(dest, &destLen, source, sourceLen);

    // Clean up
    free(dest);

    return 0;
}