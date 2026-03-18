#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_132(const uint8_t *data, size_t size) {
    z_stream stream;
    int ret;

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Set up the input data for the z_stream
    stream.next_in = (Bytef *)data;
    stream.avail_in = (uInt)size;

    // Initialize the inflate state
    ret = inflateInit(&stream);
    if (ret != Z_OK) {
        return 0;
    }

    // Call the function under test
    ret = inflateResetKeep(&stream);

    // Clean up
    inflateEnd(&stream);

    return 0;
}