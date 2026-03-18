#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    gzFile file;
    unsigned int buffer_size;

    // Ensure size is at least large enough to extract a buffer size
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Create a temporary file to use with gzopen
    const char *filename = "temp.gz";
    FILE *fp = fopen(filename, "wb+");
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

    // Extract buffer size from the input data
    buffer_size = *((unsigned int *)data);

    // Call the function-under-test
    gzbuffer(file, buffer_size);

    // Clean up
    gzclose(file);
    remove(filename);

    return 0;
}