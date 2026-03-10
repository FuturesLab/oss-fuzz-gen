#include <stdint.h>
#include <stdio.h>
#include "zlib.h"

// Define the fuzzer test function
int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    // Ensure that the size is non-zero to create a valid file
    if (size == 0) return 0;

    // Create a temporary file to simulate a gzFile
    FILE *tempFile = tmpfile();
    if (tempFile == NULL) return 0;

    // Write the data to the temporary file
    fwrite(data, 1, size, tempFile);

    // Rewind the file to the beginning
    rewind(tempFile);

    // Open the temporary file as a gzFile
    gzFile gzfile = gzdopen(fileno(tempFile), "rb");
    if (gzfile == NULL) {
        fclose(tempFile);
        return 0;
    }

    // Call the function-under-test
    gzclearerr(gzfile);

    // Close the gzFile and the temporary file
    gzclose(gzfile);
    fclose(tempFile);

    return 0;
}