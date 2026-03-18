#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <zlib.h>

// Remove the 'extern "C"' as it is not valid in C code
int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const char *version = zlibVersion();

    // Print the version to ensure the function is called
    printf("Zlib Version: %s\n", version);

    // Utilize the input data to maximize fuzzing result
    if (data != NULL && size > 0) {
        // Example: Attempt to decompress the data using zlib
        unsigned char outbuffer[1024];
        z_stream strm = {0};
        strm.next_in = (Bytef *)data;
        strm.avail_in = size;
        strm.next_out = outbuffer;
        strm.avail_out = sizeof(outbuffer);

        // Initialize the zlib decompression
        if (inflateInit(&strm) == Z_OK) {
            // Perform the decompression
            inflate(&strm, Z_NO_FLUSH);
            // Clean up
            inflateEnd(&strm);
        }
    }

    return 0;
}