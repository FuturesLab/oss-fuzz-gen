#define _LARGEFILE64_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <zlib.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// Define the fuzzing function without extern "C"
int LLVMFuzzerTestOneInput_59(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    FILE *tempFile = tmpfile();
    if (tempFile == NULL) {
        return 0;
    }

    // Write the input data to the temporary file
    fwrite(data, 1, size, tempFile);
    rewind(tempFile);

    // Open the temporary file with gzopen
    gzFile gzfile = gzdopen(fileno(tempFile), "rb");
    if (gzfile == NULL) {
        fclose(tempFile);
        return 0;
    }

    // Call the function-under-test
    off64_t offset = gzoffset64(gzfile);

    // Clean up
    gzclose(gzfile);
    fclose(tempFile);

    return 0;
}