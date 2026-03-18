#include <stdint.h>
#include <zlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int LLVMFuzzerTestOneInput_86(const uint8_t *data, size_t size) {
    gzFile file;
    voidp buffer;
    unsigned int len;
    char filename[] = "/tmp/fuzz_gzread.gz";

    // Create a temporary file with the input data
    FILE *tempFile = fopen(filename, "wb");
    if (tempFile == NULL) {
        return 0;
    }
    fwrite(data, 1, size, tempFile);
    fclose(tempFile);

    // Open the temporary file with gzopen
    file = gzopen(filename, "rb");
    if (file == NULL) {
        return 0;
    }

    // Allocate a buffer for reading
    len = 1024;  // Example buffer size
    buffer = malloc(len);
    if (buffer == NULL) {
        gzclose(file);
        return 0;
    }

    // Call the function-under-test
    gzread(file, buffer, len);

    // Clean up
    free(buffer);
    gzclose(file);
    remove(filename);

    return 0;
}