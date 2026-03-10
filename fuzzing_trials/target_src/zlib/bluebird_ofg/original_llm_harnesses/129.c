#include <stdint.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_129(const uint8_t *data, size_t size) {
    // Call the function-under-test
    uLong flags = zlibCompileFlags();

    // Use the flags in some way to ensure the call is not optimized away
    // For example, print the flags (in a real fuzzing environment, this might be logged)
    (void)flags; // Avoid unused variable warning

    // Utilize the input data in some way
    if (size > 0) {
        // For example, we could attempt to inflate the data using zlib functions
        // This is just an example and might not be meaningful without proper initialization
        z_stream stream;
        stream.zalloc = Z_NULL;
        stream.zfree = Z_NULL;
        stream.opaque = Z_NULL;
        stream.avail_in = size;
        stream.next_in = (Bytef *)data;

        if (inflateInit(&stream) == Z_OK) {
            inflate(&stream, Z_NO_FLUSH);
            inflateEnd(&stream);
        }
    }

    return 0;
}