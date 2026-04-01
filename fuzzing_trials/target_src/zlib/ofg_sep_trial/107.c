#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_107(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for the test
    if (size < 1) {
        return 0;
    }

    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Use the first byte of data to determine the version string length
    int version_length = data[0] % 5 + 1; // version_length between 1 and 5
    const char *version = "1.2.3"; // A valid version string for zlib

    // Ensure the version string length does not exceed the actual version string
    if (version_length > 5) {
        version_length = 5;
    }

    // Call the function-under-test
    int result = inflateInit_(&stream, version, version_length);

    // Clean up the stream
    inflateEnd(&stream);

    return 0;
}