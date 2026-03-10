#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_155(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for meaningful compression
    if (size < 1) {
        return 0;
    }

    // Allocate memory for the compressed output
    uLongf compressedSize = compressBound(size);
    Bytef *compressedData = (Bytef *)malloc(compressedSize);

    if (compressedData == NULL) {
        return 0;
    }

    // Call the function-under-test
    int result = compress(compressedData, &compressedSize, data, (uLong)size);

    // Free allocated memory
    free(compressedData);

    return 0;
}