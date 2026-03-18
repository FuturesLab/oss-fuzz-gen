#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <stdlib.h> // Include for malloc and free

int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
    Bytef *dest = (Bytef *)malloc(size * 2); // Allocate space for compressed data
    if (dest == NULL) {
        return 0; // Handle allocation failure
    }
    uLongf destLen = size * 2; // Initial destination length
    const Bytef *source = data; // Source data
    uLong sourceLen = size; // Source length
    int level = Z_DEFAULT_COMPRESSION; // Compression level

    // Call the function-under-test
    int result = compress2(dest, &destLen, source, sourceLen, level);

    // Clean up allocated memory
    free(dest);

    return 0;
}