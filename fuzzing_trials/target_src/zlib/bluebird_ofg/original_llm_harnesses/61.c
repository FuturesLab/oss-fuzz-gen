#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
    z_stream stream;
    int windowBits = 15; // Default windowBits for inflate
    int ret;

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = (uInt)size;
    stream.next_in = (Bytef *)data;

    // Initialize the inflate state
    ret = inflateInit2(&stream, windowBits);
    if (ret != Z_OK) {
        return 0;
    }

    // Call the function-under-test
    int undermine_result = inflateUndermine(&stream, 1);

    // Clean up
    inflateEnd(&stream);

    return 0;
}