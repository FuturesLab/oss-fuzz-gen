#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    if (size == 0) return 0;

    // Allocate output buffer with a size larger than the input buffer
    uLongf destLen = compressBound(size);
    Bytef *dest = (Bytef *)malloc(destLen);
    if (dest == NULL) return 0;

    // Compression level (valid range is 0-9)
    int level = 6; // Default compression level

    // Call the function-under-test
    int result = compress2(dest, &destLen, data, size, level);

    // Free allocated memory
    free(dest);

    return 0;
}