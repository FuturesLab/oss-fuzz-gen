#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_159(const uint8_t *data, size_t size) {
    // Initialize z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize the deflate stream
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0;
    }

    // Ensure the dictionary size is smaller than the input size
    uInt dictSize = (uInt)(size < 256 ? size : 256); // Use a smaller dictionary size for safety

    // Call the function under test
    deflateSetDictionary(&stream, data, dictSize);

    // Clean up
    deflateEnd(&stream);

    return 0;
}