#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_90(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to extract necessary parameters
    if (size < sizeof(int)) {
        return 0;
    }

    // Initialize z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize the inflate state
    if (inflateInit(&stream) != Z_OK) {
        return 0;
    }

    // Extract an integer from the data for the windowBits parameter
    int windowBits = *((int*)data);

    // Call the function-under-test
    int result = inflateReset2(&stream, windowBits);

    // Clean up
    inflateEnd(&stream);

    return 0;
}