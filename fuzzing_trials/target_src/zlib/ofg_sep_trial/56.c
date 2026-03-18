#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    z_stream stream;
    int bits;
    int value;

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize the inflate state
    if (inflateInit(&stream) != Z_OK) {
        return 0;
    }

    // Ensure that size is large enough to extract bits and value
    if (size < 2) {
        inflateEnd(&stream);
        return 0;
    }

    // Extract bits and value from the input data
    bits = data[0] % 16;  // Limit bits to a reasonable range (0-15)
    value = data[1];      // Use the second byte for the value

    // Call the function-under-test
    inflatePrime(&stream, bits, value);

    // Clean up
    inflateEnd(&stream);

    return 0;
}