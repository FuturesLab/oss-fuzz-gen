#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
    // Ensure there is enough data for the parameters
    if (size < sizeof(int) + sizeof(int)) {
        return 0;
    }

    // Initialize z_stream structure
    z_stream stream;
    memset(&stream, 0, sizeof(stream));

    // Extract parameters from the input data
    int level = data[0] % 10; // Compression level should be between 0 and 9
    int version_length = (size - sizeof(int)) % 20; // Limit version string length
    const char *version = (const char *)(data + sizeof(int));

    // Ensure the version string is null-terminated
    char version_buffer[21];
    strncpy(version_buffer, version, version_length);
    version_buffer[version_length] = '\0';

    // Call the function-under-test
    int result = deflateInit_(&stream, level, version_buffer, sizeof(z_stream));

    // Clean up
    deflateEnd(&stream);

    return 0;
}