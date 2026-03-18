#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    z_stream stream;
    Bytef dictionary[1024];
    uInt dictLength = sizeof(dictionary);

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.next_in = (Bytef *)data;
    stream.avail_in = size;

    // Initialize the inflate state
    if (inflateInit(&stream) != Z_OK) {
        return 0;
    }

    // Call the function-under-test
    int result = inflateGetDictionary(&stream, dictionary, &dictLength);

    // Clean up
    inflateEnd(&stream);

    return 0;
}