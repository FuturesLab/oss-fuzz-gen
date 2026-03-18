#include <stdint.h>
#include <zlib.h>
#include <stdlib.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
    gzFile file;
    int level = 0;
    int strategy = 0;

    // Ensure the size is sufficient to extract parameters
    if (size < 2) {
        return 0;
    }

    // Initialize the level and strategy from the input data
    level = (int)data[0];      // Use the first byte for level
    strategy = (int)data[1];   // Use the second byte for strategy

    // Create a temporary file to use with gzFile
    FILE *tempFile = tmpfile();
    if (tempFile == NULL) {
        return 0;
    }

    // Get the file descriptor and open it with gzopen
    int fd = fileno(tempFile);
    file = gzdopen(fd, "wb");
    if (file == NULL) {
        fclose(tempFile);
        return 0;
    }

    // Call the function-under-test
    gzsetparams(file, level, strategy);

    // Write some data to the gzFile
    gzwrite(file, data + 2, size - 2);

    // Close the gzFile and the temporary file
    gzclose(file);
    fclose(tempFile);

    return 0;
}