#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>
#include <string.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_101(const uint8_t *data, size_t size) {
    // Prepare a temporary file to write the input data
    const char *filename = "temp.gz";
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        return 0;
    }

    // Write the input data to the file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the file with gzopen
    gzFile gzfile = gzopen(filename, "rb");
    if (gzfile == NULL) {
        return 0;
    }

    // Allocate a buffer to read data
    int buffer_size = 256;
    char *buffer = (char *)malloc(buffer_size);
    if (buffer == NULL) {
        gzclose(gzfile);
        return 0;
    }

    // Call the function-under-test
    gzgets(gzfile, buffer, buffer_size);

    // Clean up
    gzclose(gzfile);
    free(buffer);

    // Remove the temporary file
    remove(filename);

    return 0;
}