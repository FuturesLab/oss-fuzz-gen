#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
    z_stream stream;
    int level;
    const char *version;
    int stream_size;
    int result;

    // Initialize z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Ensure data is large enough to extract meaningful values
    if (size < 4) {
        return 0;
    }

    // Extract values from data
    level = data[0] % 10;  // Compression level between 0-9
    version = (const char *)&data[1];  // Pointer to a string in data
    stream_size = (int)data[2];  // Stream size from data

    // Call the function-under-test
    result = deflateInit_(&stream, level, version, stream_size);

    // Cleanup
    deflateEnd(&stream);

    return 0;
}