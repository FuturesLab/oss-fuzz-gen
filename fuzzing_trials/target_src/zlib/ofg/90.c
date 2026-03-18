#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_90(const uint8_t *data, size_t size) {
    z_stream stream;
    int windowBits;

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize the stream with inflateInit2 to set up the internal state
    if (inflateInit2(&stream, 15) != Z_OK) {
        return 0; // Exit if initialization fails
    }

    // Ensure size is non-zero to avoid division by zero
    if (size == 0) {
        inflateEnd(&stream);
        return 0;
    }

    // Use the first byte of data to determine the windowBits, ensuring it is within a valid range
    windowBits = (data[0] % 15) + 8; // Valid range for windowBits is 8-15

    // Call the function-under-test
    inflateReset2(&stream, windowBits);

    // Clean up
    inflateEnd(&stream);

    return 0;
}