#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>
#include <stdio.h> // Added to fix undeclared identifier error for FILE operations

int LLVMFuzzerTestOneInput_114(const uint8_t *data, size_t size) {
    gzFile file;
    char filename[] = "/tmp/fuzz_gzfile.gz";

    // Write the input data to a temporary file to simulate a gzFile
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) return 0;
    fwrite(data, 1, size, fp);
    fclose(fp);

    // Open the file as a gzFile
    file = gzopen(filename, "rb");
    if (file == NULL) return 0;

    // Call the function-under-test
    off_t offset = gzoffset(file);

    // Cleanup
    gzclose(file);
    remove(filename);

    return 0;
}