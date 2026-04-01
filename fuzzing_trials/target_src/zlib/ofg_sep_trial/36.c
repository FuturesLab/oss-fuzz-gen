#include <zlib.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    z_stream stream;
    Bytef dictionary[1024];
    uInt dictLength = sizeof(dictionary);

    // Initialize the z_stream structure
    memset(&stream, 0, sizeof(z_stream));

    // Initialize the stream for deflation
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0;
    }

    // Set the input data for the stream
    stream.next_in = (Bytef *)data;
    stream.avail_in = (uInt)size;

    // Call the function-under-test
    deflateGetDictionary(&stream, dictionary, &dictLength);

    // Clean up
    deflateEnd(&stream);

    return 0;
}