#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zlib.h"

int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    // Ensure that the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a temporary file to use with gzopen
    FILE *tempFile = tmpfile();
    if (tempFile == NULL) {
        return 0;
    }

    // Convert the FILE* to a file descriptor
    int fd = fileno(tempFile);

    // Open a gzFile using the file descriptor
    gzFile gzfile = gzdopen(fd, "wb");
    if (gzfile == NULL) {
        fclose(tempFile);
        return 0;
    }

    // Ensure that the data is null-terminated for gzputs
    char *inputString = (char *)malloc(size + 1);
    if (inputString == NULL) {
        gzclose(gzfile);
        fclose(tempFile);
        return 0;
    }
    memcpy(inputString, data, size);
    inputString[size] = '\0';

    // Call the function under test
    gzputs(gzfile, inputString);

    // Clean up
    free(inputString);
    gzclose(gzfile);
    fclose(tempFile);

    return 0;
}