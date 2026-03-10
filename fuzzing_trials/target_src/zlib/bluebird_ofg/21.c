#include <stdint.h>
#include <stdio.h>
#include "zlib.h"

int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    gzFile file;
    int level, strategy;

    // Ensure the input size is sufficient for extracting level and strategy
    if (size < 2) {
        return 0;
    }

    // Open a temporary file for gzFile operations
    file = gzopen("/dev/null", "wb");
    if (file == NULL) {
        return 0;
    }

    // Extract level and strategy from the input data
    level = (int)data[0] % 10;  // Compression level is typically between 0 and 9
    strategy = (int)data[1] % 4; // Strategy is typically between 0 and 3

    // Call the function-under-test
    gzsetparams(file, level, strategy);

    // Close the gzFile
    gzclose(file);

    return 0;
}