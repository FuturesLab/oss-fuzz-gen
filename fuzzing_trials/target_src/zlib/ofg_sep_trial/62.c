#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_62(const uint8_t *data, size_t size) {
    // Ensure size is non-zero
    if (size == 0) {
        return 0;
    }

    // Create a temporary file to simulate a gzFile
    FILE *tempFile = tmpfile();
    if (tempFile == NULL) {
        return 0;
    }

    // Write the data to the temporary file
    fwrite(data, 1, size, tempFile);
    rewind(tempFile);

    // Open the temporary file as a gzFile
    gzFile gzfile = gzdopen(fileno(tempFile), "rb");
    if (gzfile == NULL) {
        fclose(tempFile);
        return 0;
    }

    // Initialize an integer to hold the error number
    int errnum = 0;

    // Call the function-under-test
    const char *error_msg = gzerror(gzfile, &errnum);

    // Clean up
    gzclose(gzfile);
    fclose(tempFile);

    return 0;
}