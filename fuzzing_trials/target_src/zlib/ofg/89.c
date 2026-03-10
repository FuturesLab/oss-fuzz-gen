#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_89(const uint8_t *data, size_t size) {
    z_stream stream;
    int windowBits;

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize the inflate state
    if (inflateInit(&stream) != Z_OK) {
        return 0;
    }

    // Ensure the size is sufficient to extract an integer for windowBits
    if (size < sizeof(int)) {
        inflateEnd(&stream);
        return 0;
    }

    // Use the first bytes of data to determine the windowBits
    windowBits = *((int*)data);

    // Call the function-under-test
    inflateReset2(&stream, windowBits);

    // Clean up
    inflateEnd(&stream);

    return 0;
}