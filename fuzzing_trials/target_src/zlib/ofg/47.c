#include <stdint.h>
#include <stdio.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
    gzFile file;
    char filename[] = "/tmp/fuzz_input.gz";
    FILE *fp;

    // Write the data to a temporary file
    fp = fopen(filename, "wb");
    if (fp == NULL) {
        return 0;
    }
    fwrite(data, 1, size, fp);
    fclose(fp);

    // Open the file with gzopen
    file = gzopen(filename, "rb");
    if (file == NULL) {
        return 0;
    }

    // Call the function-under-test
    gzclose(file);

    // Clean up
    remove(filename);

    return 0;
}