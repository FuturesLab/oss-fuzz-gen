#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Create a temporary file to use with gzFile
    const char *filename = "temp.gz";
    FILE *file = fopen(filename, "wb");
    if (!file) {
        return 0;
    }
    fclose(file);

    // Open the file with gzopen
    gzFile gzfile = gzopen(filename, "wb");
    if (!gzfile) {
        return 0;
    }

    // Use the first byte of data as the character to write
    int c = (int)data[0];

    // Call the function-under-test
    gzputc(gzfile, c);

    // Clean up
    gzclose(gzfile);
    remove(filename);

    return 0;
}