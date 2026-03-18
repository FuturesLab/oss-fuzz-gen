#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    // Initialize the z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize the deflate process
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0;
    }

    // Ensure that the size is sufficient for our needs
    if (size < 2) {
        deflateEnd(&stream);
        return 0;
    }

    // Use the first byte as the 'bits' parameter
    int bits = data[0] & 0xFF; // Ensure it's within 0-255

    // Use the second byte as the 'value' parameter
    int value = data[1] & 0xFF; // Ensure it's within 0-255

    // Call the function under test
    deflatePrime(&stream, bits, value);

    // Clean up
    deflateEnd(&stream);

    return 0;
}