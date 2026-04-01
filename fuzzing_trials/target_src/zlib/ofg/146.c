#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_146(const uint8_t *data, size_t size) {
    // Initialize the z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.next_in = (Bytef *)data;
    stream.avail_in = (uInt)size;

    // Initialize the inflate state
    if (inflateInit(&stream) != Z_OK) {
        return 0;
    }

    // Call the function-under-test
    int result = inflateSync(&stream);

    // Cleanup
    inflateEnd(&stream);

    return 0;
}