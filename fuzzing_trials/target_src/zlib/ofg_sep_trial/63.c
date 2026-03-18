#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size) {
    gzFile file;
    z_off_t offset;
    int whence;

    // Create a temporary file to use with gzFile
    FILE *tempFile = tmpfile();
    if (tempFile == NULL) {
        return 0;
    }

    // Write the input data to the temporary file
    fwrite(data, 1, size, tempFile);
    rewind(tempFile);

    // Open the temporary file with gzdopen
    file = gzdopen(fileno(tempFile), "rb");
    if (file == NULL) {
        fclose(tempFile);
        return 0;
    }

    // Initialize offset and whence
    offset = (z_off_t)(size > 0 ? data[0] : 0); // Use the first byte of data as offset if available
    whence = (size > 1 ? data[1] % 3 : 0); // Use the second byte of data to determine whence

    // Call the function-under-test
    gzseek(file, offset, whence);

    // Clean up
    gzclose(file);
    fclose(tempFile);

    return 0;
}