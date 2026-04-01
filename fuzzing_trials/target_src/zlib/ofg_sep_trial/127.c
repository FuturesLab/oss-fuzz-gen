#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_127(const uint8_t *data, size_t size) {
    z_stream stream;
    int windowBits;
    const char *version;
    int stream_size;
    int result;

    // Initialize z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Ensure the input size is sufficient for our parameters
    if (size < 4) {
        return 0;
    }

    // Extract parameters from the data
    windowBits = (int)data[0]; // Use the first byte for windowBits
    version = (const char *)&data[1]; // Use the next bytes for version string
    stream_size = (int)data[2]; // Use another byte for stream_size

    // Call the function-under-test
    result = inflateInit2_(&stream, windowBits, version, stream_size);

    // Clean up
    inflateEnd(&stream);

    return 0;
}