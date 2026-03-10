#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_158(const uint8_t *data, size_t size) {
    // Initialize the z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize the deflate operation
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0;
    }

    // Ensure the dictionary is not NULL and has a non-zero size
    const Bytef *dictionary = data;
    uInt dictLength = (uInt)(size > 0 ? size : 1); // Ensure dictLength is non-zero

    // Call the function-under-test
    deflateSetDictionary(&stream, dictionary, dictLength);

    // Clean up
    deflateEnd(&stream);

    return 0;
}