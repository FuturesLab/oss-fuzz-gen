#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    const char *filename = "temp.gz";
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        return 0;
    }

    // Write the input data to the file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the file with gzopen
    gzFile gz_file = gzopen(filename, "rb");
    if (gz_file == NULL) {
        return 0;
    }

    // Call the function-under-test
    int eof = gzeof(gz_file);

    // Close the gzFile
    gzclose(gz_file);

    // Remove the temporary file
    remove(filename);

    return 0;
}