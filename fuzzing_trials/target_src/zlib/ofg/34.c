#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_34(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract two integers
    if (size < 2) {
        return 0;
    }

    // Initialize the z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize the deflate process
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0;
    }

    // Extract two integers from the data
    int bits = data[0] % 16; // Limit bits to a valid range (0-15)
    int value = data[1];

    // Call the function-under-test
    deflatePrime(&stream, bits, value);

    // Clean up
    deflateEnd(&stream);

    return 0;
}