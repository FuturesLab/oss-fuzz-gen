#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    z_stream stream;
    int bits;
    int value;
    int result;

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize the deflate operation
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0;
    }

    // Ensure that size is sufficient for extracting bits and value
    if (size < 2) {
        deflateEnd(&stream);
        return 0;
    }

    // Extract bits and value from the data
    bits = data[0] % 16;  // Limit bits to a valid range (0-15)
    value = data[1];

    // Call the function-under-test
    result = deflatePrime(&stream, bits, value);

    // Clean up
    deflateEnd(&stream);

    return 0;
}