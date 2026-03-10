#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient for the test
    if (size < 1) {
        return 0;
    }

    // Create a temporary file to simulate a gzFile
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

    // Buffer to read the decompressed data
    char buffer[1024];
    int bytesRead;

    // Attempt to read from the gzFile to ensure the function under test is exercised
    while ((bytesRead = gzread(gzfile, buffer, sizeof(buffer))) > 0) {
        // Process the buffer if needed
    }

    // Call the function-under-test
    gzclose(gzfile);

    // Close the temporary file
    fclose(tempFile);

    return 0;
}