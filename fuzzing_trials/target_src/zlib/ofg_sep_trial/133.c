#include <stdio.h>
#include <zlib.h>
#include <inttypes.h>
#include <stddef.h>

// Function to be used by the fuzzer
int LLVMFuzzerTestOneInput_133(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    FILE *tempFile = tmpfile();
    if (tempFile == NULL) {
        return 0;
    }

    // Write the input data to the temporary file
    fwrite(data, 1, size, tempFile);
    rewind(tempFile);

    // Open the temporary file as a gzFile
    gzFile gzFile = gzdopen(fileno(tempFile), "rb");
    if (gzFile == NULL) {
        fclose(tempFile);
        return 0;
    }

    // Call the function-under-test
    int result = gzgetc(gzFile); // Corrected function name from gzgetc_ to gzgetc

    // Clean up
    gzclose(gzFile);
    fclose(tempFile);

    return 0;
}