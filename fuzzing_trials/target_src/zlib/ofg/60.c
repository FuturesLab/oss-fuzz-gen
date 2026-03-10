#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    z_stream stream;
    int ret;
    int undermine_value = 1; // Example value, can be varied for fuzzing

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = 0;
    stream.next_in = Z_NULL;

    // Initialize the inflate operation
    ret = inflateInit(&stream);
    if (ret != Z_OK) {
        return 0;
    }

    // Set the input data for the z_stream
    stream.next_in = (Bytef *)data;
    stream.avail_in = size;

    // Call the function-under-test
    ret = inflateUndermine(&stream, undermine_value);

    // Clean up
    inflateEnd(&stream);

    return 0;
}