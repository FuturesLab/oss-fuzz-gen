#include <stdint.h>
#include <stdio.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size) {
    // Ensure the data size is large enough to simulate a valid gzFile
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

    // Buffer to read data into
    char buffer[1024];
    // Attempt to read from the gzFile
    while (gzread(gzfile, buffer, sizeof(buffer)) > 0) {
        // Process the buffer if needed
    }

    // Call the function-under-test
    int result = gzclose_r(gzfile);

    // Close the temporary file
    fclose(tempFile);

    return 0;
}