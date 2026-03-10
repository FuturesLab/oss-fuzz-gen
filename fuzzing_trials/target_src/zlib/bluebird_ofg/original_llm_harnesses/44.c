#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for required parameters
    if (size < 4) {
        return 0;
    }

    // Initialize z_stream structure
    z_stream stream;
    memset(&stream, 0, sizeof(stream));

    // Extract parameters from data
    int level = data[0] % 10;  // Compression level from 0 to 9
    const char *version = ZLIB_VERSION;
    int stream_size = (int)sizeof(z_stream);

    // Call the function-under-test
    int result = deflateInit_(&stream, level, version, stream_size);

    // Clean up
    deflateEnd(&stream);

    return 0;
}