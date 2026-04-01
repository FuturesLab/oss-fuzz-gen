#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_39(const uint8_t *data, size_t size) {
    // Initialize a z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize the stream for decompression
    int ret = inflateInit(&stream);
    if (ret != Z_OK) {
        return 0;
    }

    // Set the input data for the stream
    stream.next_in = (Bytef *)data;
    stream.avail_in = (uInt)size;

    // Allocate some output buffer
    unsigned char out[1024];
    stream.next_out = out;
    stream.avail_out = sizeof(out);

    // Call the function-under-test
    int inflateRet;
    do {
        inflateRet = inflate(&stream, Z_NO_FLUSH);
        if (inflateRet == Z_STREAM_ERROR || inflateRet == Z_DATA_ERROR || inflateRet == Z_MEM_ERROR) {
            break;
        }
    } while (stream.avail_out == 0);

    // Clean up and end the decompression
    inflateEnd(&stream);

    return 0;
}