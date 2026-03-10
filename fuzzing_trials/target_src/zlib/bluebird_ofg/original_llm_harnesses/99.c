#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_99(const uint8_t *data, size_t size) {
    // Ensure the input size is not zero
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the destination buffer
    uLongf destLen = size * 2; // Start with an arbitrary size larger than the input
    Bytef *dest = (Bytef *)malloc(destLen);
    if (dest == NULL) {
        return 0;
    }

    // Call the function-under-test
    int result = uncompress(dest, &destLen, data, (uLong)size);

    // Free the allocated memory
    free(dest);

    return 0;
}