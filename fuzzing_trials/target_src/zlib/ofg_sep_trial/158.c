#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_158(const uint8_t *data, size_t size) {
    z_stream stream;
    int ret;
    const Bytef *dictionary;
    uInt dictLength;

    // Initialize the z_stream structure
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    ret = deflateInit(&stream, Z_DEFAULT_COMPRESSION);
    if (ret != Z_OK) {
        return 0;
    }

    // Ensure the dictionary is not NULL and has a valid length
    dictionary = data;
    dictLength = (uInt)(size > 0 ? size : 1); // Ensure dictLength is at least 1

    // Call the function-under-test
    deflateSetDictionary(&stream, dictionary, dictLength);

    // Clean up
    deflateEnd(&stream);

    return 0;
}