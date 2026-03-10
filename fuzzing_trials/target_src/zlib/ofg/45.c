#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
    z_stream stream;
    int level;
    const char *version;
    int stream_size;
    
    // Initialize z_stream structure
    memset(&stream, 0, sizeof(z_stream));
    
    // Ensure there is enough data to extract parameters
    if (size < sizeof(int) + 1 + sizeof(int)) {
        return 0;
    }
    
    // Extract parameters from the input data
    level = (int)data[0];  // Use the first byte for compression level
    version = (const char *)(data + 1);  // Use the rest for version string
    stream_size = (int)data[size - 1];  // Use the last byte for stream size
    
    // Ensure version string is null-terminated
    char version_buffer[10];
    strncpy(version_buffer, version, sizeof(version_buffer) - 1);
    version_buffer[sizeof(version_buffer) - 1] = '\0';
    
    // Call the function-under-test
    deflateInit_(&stream, level, version_buffer, stream_size);
    
    // Clean up
    deflateEnd(&stream);
    
    return 0;
}