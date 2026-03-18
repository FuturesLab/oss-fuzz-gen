#include <stdint.h>
#include <stddef.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    // Initialize gzFile
    gzFile file = gzdopen(0, "wb"); // Using file descriptor 0 (stdin) for simplicity

    // Ensure that the file is not NULL
    if (file == NULL) {
        return 0;
    }

    // Initialize parameters for gzsetparams
    int compression_level = (size > 0) ? (data[0] % 10) : 6; // Valid range for compression level is 0-9
    int strategy = (size > 1) ? (data[1] % 5) : Z_DEFAULT_STRATEGY; // Valid strategies are 0-4

    // Call the function-under-test
    gzsetparams(file, compression_level, strategy);

    // Clean up
    gzclose(file);

    return 0;
}