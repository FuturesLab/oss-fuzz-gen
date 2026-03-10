#include <stdint.h>
#include <stdlib.h>
#include "zlib.h"

int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    z_stream stream;
    // Increase the dictionary buffer size to avoid overflow
    Bytef dictionary[32768]; // 32KB buffer, assuming a larger dictionary size
    uInt dictLength = sizeof(dictionary);

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.next_in = (Bytef *)data;
    stream.avail_in = size;

    // Initialize the deflate state with dummy values
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0;
    }

    // Prepare output buffer
    uint8_t out[1024];
    stream.next_out = out;
    stream.avail_out = sizeof(out);

    // Perform deflate to ensure the stream is processed
    int deflateStatus = deflate(&stream, Z_FINISH);
    if (deflateStatus != Z_STREAM_END && deflateStatus != Z_OK) {
        deflateEnd(&stream);
        return 0;
    }

    // Check if the dictionary can be obtained
    if (deflateGetDictionary(&stream, dictionary, &dictLength) != Z_OK) {
        deflateEnd(&stream);
        return 0;
    }

    // Clean up
    deflateEnd(&stream);

    return 0; // Return 0 to indicate successful processing
}