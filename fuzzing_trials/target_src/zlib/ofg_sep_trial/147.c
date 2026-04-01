#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_147(const uint8_t *data, size_t size) {
    z_stream stream;
    int ret;

    // Initialize the z_stream structure
    memset(&stream, 0, sizeof(stream));

    // Allocate inflate state
    ret = inflateInit(&stream);
    if (ret != Z_OK) {
        return 0;
    }

    // Set the input data for the z_stream
    stream.next_in = (Bytef *)data;
    stream.avail_in = (uInt)size;

    // Call the function-under-test
    ret = inflateSync(&stream);

    // Clean up
    inflateEnd(&stream);

    return 0;
}