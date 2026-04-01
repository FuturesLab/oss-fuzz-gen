#include <stdint.h>
#include <stdio.h>
#include <zlib.h>

// Fuzzing harness for the gzeof function
int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    // Create a temporary file to write the data to
    FILE *tempFile = tmpfile();
    if (tempFile == NULL) {
        return 0;
    }

    // Write the input data to the temporary file
    fwrite(data, 1, size, tempFile);
    rewind(tempFile);

    // Open the temporary file as a gzFile
    gzFile gzFilePtr = gzdopen(fileno(tempFile), "rb");
    if (gzFilePtr == NULL) {
        fclose(tempFile);
        return 0;
    }

    // Call the function-under-test
    int result = gzeof(gzFilePtr);

    // Clean up
    gzclose(gzFilePtr);
    fclose(tempFile);

    return 0;
}