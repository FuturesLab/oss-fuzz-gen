#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_98(const uint8_t *data, size_t size) {
    // Ensure the input size is large enough to avoid trivial cases
    if (size < 1) {
        return 0;
    }

    // Allocate a buffer for the uncompressed data
    uLongf uncompressedSize = size * 2; // Start with a buffer twice the size of the input
    Bytef *uncompressedData = (Bytef *)malloc(uncompressedSize);
    if (uncompressedData == NULL) {
        return 0;
    }

    // Call the function-under-test
    int result = uncompress(uncompressedData, &uncompressedSize, data, (uLong)size);

    // Free the allocated buffer
    free(uncompressedData);

    return 0;
}