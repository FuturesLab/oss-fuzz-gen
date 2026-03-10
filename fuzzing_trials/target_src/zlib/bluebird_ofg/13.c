#include <stdint.h>
#include <stdlib.h>
#include "zlib.h"
#include <stdio.h>
#include <string.h>

int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    // Ensure that there is at least one byte of data to unget
    if (size < 1) {
        return 0;
    }

    // Create a temporary file to use with gzFile
    const char *filename = "temp.gz";
    FILE *file = fopen(filename, "wb");
    if (!file) {
        return 0;
    }

    // Write the input data to the file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the file with gzopen
    gzFile gzfile = gzopen(filename, "rb");
    if (!gzfile) {
        return 0;
    }

    // Use the first byte of data as the character to unget
    int c = data[0];

    // Call the function-under-test
    gzungetc(c, gzfile);

    // Clean up
    gzclose(gzfile);
    remove(filename);

    return 0;
}