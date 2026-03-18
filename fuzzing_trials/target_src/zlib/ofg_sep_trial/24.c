#include <stdint.h>
#include <stdio.h>
#include <zlib.h>

// Remove the extern "C" linkage specification as it is not needed in C
int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    // Ensure there is enough data to read from
    if (size < 1) {
        return 0;
    }

    // Create a temporary file to use with gzFile
    FILE *tempFile = tmpfile();
    if (!tempFile) {
        return 0;
    }

    // Open the temporary file with gzopen
    gzFile gzfile = gzdopen(fileno(tempFile), "wb");
    if (!gzfile) {
        fclose(tempFile);
        return 0;
    }

    // Use the first byte of data as the character to write
    int character = (int)data[0];

    // Call the function-under-test
    gzputc(gzfile, character);

    // Close the gzFile
    gzclose(gzfile);

    // Close the temporary file
    fclose(tempFile);

    return 0;
}