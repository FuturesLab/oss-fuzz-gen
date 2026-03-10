#include <stdio.h>
#include <stdint.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_112(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a gzFile
    const char *temp_filename = "temp.gz";
    FILE *temp_file = fopen(temp_filename, "wb");
    if (temp_file == NULL) {
        return 0;
    }

    // Write the input data to the temporary file
    fwrite(data, 1, size, temp_file);
    fclose(temp_file);

    // Open the temporary file as a gzFile
    gzFile gz_file = gzopen(temp_filename, "rb");
    if (gz_file == NULL) {
        return 0;
    }

    // Prepare parameters for gzseek
    off_t offset = 0;  // Start seeking from the beginning
    int whence = SEEK_SET;  // Use SEEK_SET to seek from the start of the file

    // Call the function-under-test
    off_t result = gzseek(gz_file, offset, whence);

    // Close the gzFile
    gzclose(gz_file);

    // Remove the temporary file
    remove(temp_filename);

    return 0;
}