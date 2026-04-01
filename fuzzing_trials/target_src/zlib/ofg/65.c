#include <stdint.h>
#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_65(const uint8_t *data, size_t size) {
    gzFile file;
    z_off_t offset;
    int whence;
    z_off_t result;
    char buffer[1024]; // Buffer to read data after seeking

    // Create a temporary file to use with gzFile
    const char *filename = "temp.gz";
    FILE *tempFile = fopen(filename, "wb");
    if (tempFile == NULL) {
        return 0;
    }

    // Write the input data to the temporary file
    fwrite(data, 1, size, tempFile);
    fclose(tempFile);

    // Open the temporary file with gzopen
    file = gzopen(filename, "rb");
    if (file == NULL) {
        return 0;
    }

    // Initialize offset and whence with non-NULL values
    offset = (z_off_t)size / 2; // Arbitrary offset within the file size
    whence = SEEK_SET; // Arbitrary choice for whence

    // Call the function-under-test
    result = gzseek(file, offset, whence);

    // Check if gzseek was successful
    if (result != -1) {
        // Read some data from the file after seeking
        gzread(file, buffer, sizeof(buffer));
    }

    // Clean up
    gzclose(file);
    remove(filename);

    return 0;
}