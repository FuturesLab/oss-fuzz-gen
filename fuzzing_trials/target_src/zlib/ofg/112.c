#include <stdint.h>
#include <stdio.h>
#include <zlib.h>

// Remove the 'extern "C"' linkage specification, which is not needed in C
int LLVMFuzzerTestOneInput_112(const uint8_t *data, size_t size) {
    // Ensure there is enough data to use for gzseek parameters
    if (size < 3) return 0;

    // Create a temporary file to use with gzFile
    FILE *tempFile = tmpfile();
    if (tempFile == NULL) return 0;

    // Write the input data to the temporary file
    fwrite(data, 1, size, tempFile);
    rewind(tempFile);

    // Open the temporary file as a gzFile
    gzFile gzfile = gzdopen(fileno(tempFile), "rb");
    if (gzfile == NULL) {
        fclose(tempFile);
        return 0;
    }

    // Extract parameters for gzseek from the input data
    off_t offset = (off_t)data[0]; // Use the first byte as offset
    int whence = (int)data[1] % 3; // Use the second byte to determine whence (0, 1, or 2)

    // Call gzseek with the extracted parameters
    gzseek(gzfile, offset, whence);

    // Clean up
    gzclose(gzfile);
    fclose(tempFile);

    return 0;
}