#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>
#include <stdio.h> // Include the standard I/O library for file operations

int LLVMFuzzerTestOneInput_102(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char filename[] = "/tmp/fuzz_input.gz";
    FILE *file = fopen(filename, "wb");
    if (!file) {
        return 0;
    }

    // Write the data to the file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the file as a gzFile
    gzFile gzfile = gzopen(filename, "rb");
    if (!gzfile) {
        return 0;
    }

    // Allocate a buffer for gzgets
    int buf_size = 1024;
    char *buffer = (char *)malloc(buf_size);
    if (!buffer) {
        gzclose(gzfile);
        return 0;
    }

    // Call the function-under-test
    gzgets(gzfile, buffer, buf_size);

    // Clean up
    free(buffer);
    gzclose(gzfile);

    return 0;
}