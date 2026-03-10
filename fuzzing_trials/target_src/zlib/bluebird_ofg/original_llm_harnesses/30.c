#include <zlib.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    gzFile file;
    int level;
    int strategy;

    // Ensure the input size is sufficient to extract level and strategy
    if (size < 2) {
        return 0;
    }

    // Open a temporary file to create a gzFile
    FILE *tempFile = tmpfile();
    if (tempFile == NULL) {
        return 0;
    }

    file = gzdopen(fileno(tempFile), "wb");
    if (file == NULL) {
        fclose(tempFile);
        return 0;
    }

    // Extract level and strategy from the input data
    level = data[0] % 10;  // Compression level range: 0-9
    strategy = data[1] % 4; // Strategy range: 0-3 (Z_DEFAULT_STRATEGY, Z_FILTERED, Z_HUFFMAN_ONLY, Z_RLE)

    // Call the function-under-test
    gzsetparams(file, level, strategy);

    // Clean up
    gzclose(file);
    fclose(tempFile);

    return 0;
}