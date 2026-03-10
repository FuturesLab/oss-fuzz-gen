#include <stdint.h>
#include <stdio.h>
#include <zlib.h>

// Fuzzer test function
int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    FILE *tempFile = tmpfile();
    if (tempFile == NULL) {
        return 0;
    }

    // Write the input data to the temporary file
    fwrite(data, 1, size, tempFile);

    // Rewind the file to the beginning
    rewind(tempFile);

    // Open the temporary file with gzdopen
    gzFile gzfile = gzdopen(fileno(tempFile), "rb");
    if (gzfile == NULL) {
        fclose(tempFile);
        return 0;
    }

    // Call the function-under-test
    gzclose_r(gzfile);

    // Close the temporary file
    fclose(tempFile);

    return 0;
}