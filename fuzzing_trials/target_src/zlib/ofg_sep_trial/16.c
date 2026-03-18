#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size) {
    z_stream stream;
    int level, method, windowBits, memLevel, strategy, version_len;
    const char *version;

    // Initialize z_stream
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Ensure size is sufficient for extracting parameters
    if (size < 6) {
        return 0;
    }

    // Extract parameters from the input data
    level = data[0] % 10; // Compression level 0-9
    method = data[1] % 2; // Method (0 or 1, as Z_DEFLATED is typically used)
    windowBits = (data[2] % 16) + 8; // Window size 8-15
    memLevel = (data[3] % 9) + 1; // Memory level 1-9
    strategy = data[4] % 5; // Strategy 0-4
    version_len = data[5] % 10; // Length of version string

    // Ensure version_len does not exceed remaining data size
    if (version_len > size - 6) {
        version_len = size - 6;
    }

    // Create a version string from the remaining data
    version = (const char *)(data + 6);

    // Call the function under test
    deflateInit2_(&stream, level, method, windowBits, memLevel, strategy, version, version_len);

    // Clean up
    deflateEnd(&stream);

    return 0;
}