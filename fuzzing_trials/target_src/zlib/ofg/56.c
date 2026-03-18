#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    z_stream stream;
    int bits = 0;
    int value = 0;

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = 0;
    stream.next_in = Z_NULL;

    // Initialize the inflate state
    if (inflateInit(&stream) != Z_OK) {
        return 0;
    }

    // Ensure size is sufficient to extract bits and value
    if (size >= 2) {
        bits = data[0] % 16; // Limit bits to a reasonable range
        value = data[1];
    }

    // Call the function-under-test
    inflatePrime(&stream, bits, value);

    // Clean up
    inflateEnd(&stream);

    return 0;
}