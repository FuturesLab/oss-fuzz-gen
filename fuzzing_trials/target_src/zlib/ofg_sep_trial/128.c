#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_128(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to extract required parameters
    if (size < 6) {
        return 0;
    }

    // Initialize z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Extract parameters from the input data
    int windowBits = (int)data[0] % 16; // Valid range for windowBits is -15 to 15
    int versionLength = (int)data[1] % 5 + 1; // Length of version string (1 to 5)
    const char *version = (const char *)(data + 2); // Pointer to version string
    int streamSize = (int)data[2 + versionLength]; // Stream size

    // Ensure version string does not exceed input size
    if (2 + versionLength > size) {
        return 0;
    }

    // Call the function under test
    int ret = inflateInit2_(&stream, windowBits, version, streamSize);

    // Clean up
    inflateEnd(&stream);

    return 0;
}