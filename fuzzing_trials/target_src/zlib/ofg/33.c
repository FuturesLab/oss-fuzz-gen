#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    // Ensure there's enough data to extract the necessary parameters
    if (size < 2) {
        return 0;
    }

    // Initialize z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize the deflate process
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0;
    }

    // Extract parameters from data
    int bits = data[0] & 0x07;  // Use only the lower 3 bits (0-7)
    int value = data[1] & 0xFF; // Use the full byte

    // Call the function-under-test
    deflatePrime(&stream, bits, value);

    // Clean up
    deflateEnd(&stream);

    return 0;
}