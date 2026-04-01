#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_83(const uint8_t *data, size_t size) {
    // Check if size is 0 to prevent empty input
    if (size == 0) {
        return 0;
    }

    // Create a temporary file to use with gzopen
    FILE *tempFile = tmpfile();
    if (tempFile == NULL) {
        return 0;
    }

    // Get the file descriptor and open it with gzopen
    int fd = fileno(tempFile);
    gzFile gzfile = gzdopen(fd, "w");
    if (gzfile == NULL) {
        fclose(tempFile);
        return 0;
    }

    // Ensure the data is null-terminated for gzputs
    char *nullTerminatedData = (char *)malloc(size + 1);
    if (nullTerminatedData == NULL) {
        gzclose(gzfile);
        fclose(tempFile);
        return 0;
    }
    memcpy(nullTerminatedData, data, size);
    nullTerminatedData[size] = '\0';

    // Call the function-under-test
    gzputs(gzfile, nullTerminatedData);

    // Clean up
    free(nullTerminatedData);
    gzclose(gzfile);
    fclose(tempFile);

    return 0;
}