#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
    // Ensure the size is large enough to extract two integers for the function parameters
    if (size < sizeof(int) * 2) {
        return 0;
    }

    // Initialize z_stream structure
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Initialize inflate state
    if (inflateInit(&stream) != Z_OK) {
        return 0;
    }

    // Extract two integers from the input data
    int bits = *(int *)(data);
    int value = *(int *)(data + sizeof(int));

    // Call the function-under-test
    inflatePrime(&stream, bits, value);

    // Clean up
    inflateEnd(&stream);

    return 0;
}