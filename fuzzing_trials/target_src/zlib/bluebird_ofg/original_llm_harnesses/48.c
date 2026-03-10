#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
    // Ensure the size is large enough to extract four integers
    if (size < sizeof(int) * 4) {
        return 0;
    }

    // Initialize z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize the deflate stream
    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return 0;
    }

    // Extract four integers from the input data
    int good_length = *(int *)(data);
    int max_lazy = *(int *)(data + sizeof(int));
    int nice_length = *(int *)(data + 2 * sizeof(int));
    int max_chain = *(int *)(data + 3 * sizeof(int));

    // Call the function-under-test
    deflateTune(&stream, good_length, max_lazy, nice_length, max_chain);

    // Clean up
    deflateEnd(&stream);

    return 0;
}