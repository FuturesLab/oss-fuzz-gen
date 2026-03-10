#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_125(const uint8_t *data, size_t size) {
    if (data == NULL || size == 0) {
        return 0;
    }

    gzFile file;
    char filename[] = "temp.gz";
    FILE *fp = fopen(filename, "wb");
    
    if (fp == NULL) {
        return 0;
    }

    // Write data to file
    fwrite(data, 1, size, fp);
    fclose(fp);

    // Open the file with gzopen
    file = gzopen(filename, "rb");
    if (file == NULL) {
        return 0;
    }

    // Call the function-under-test
    gzclearerr(file);

    // Clean up
    gzclose(file);
    remove(filename);

    return 0;
}