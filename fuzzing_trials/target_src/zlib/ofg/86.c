#include <zlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_86(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    FILE *tempFile = tmpfile();
    if (tempFile == NULL) {
        return 0;
    }

    // Write the input data to the temporary file
    fwrite(data, 1, size, tempFile);
    rewind(tempFile);

    // Open the temporary file as a gzFile
    gzFile gzfile = gzdopen(fileno(tempFile), "rb");
    if (gzfile == NULL) {
        fclose(tempFile);
        return 0;
    }

    // Allocate a buffer to read data into
    unsigned int bufferSize = 1024;
    void *buffer = malloc(bufferSize);
    if (buffer == NULL) {
        gzclose(gzfile);
        fclose(tempFile);
        return 0;
    }

    // Call the function-under-test
    gzread(gzfile, buffer, bufferSize);

    // Clean up
    free(buffer);
    gzclose(gzfile);
    fclose(tempFile);

    return 0;
}