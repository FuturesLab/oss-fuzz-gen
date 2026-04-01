#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_121(const uint8_t *data, size_t size) {
    int c = 0; // Initialize with a non-zero integer

    // Create a temporary file to write the data to
    FILE *tempFile = tmpfile();
    if (tempFile == NULL) {
        return 0; // If the temporary file couldn't be created, exit early
    }

    // Write the input data to the temporary file
    fwrite(data, 1, size, tempFile);
    rewind(tempFile); // Reset the file position to the beginning

    // Open a gzFile, using the temporary file descriptor
    gzFile file = gzdopen(dup(fileno(tempFile)), "rb");
    if (file == NULL) {
        fclose(tempFile);
        return 0; // If gzFile couldn't be opened, exit early
    }

    // Call the function-under-test with the initialized parameters
    gzungetc(c, file);

    gzclose(file); // Close the gzFile
    fclose(tempFile); // Close the temporary file
    return 0;
}