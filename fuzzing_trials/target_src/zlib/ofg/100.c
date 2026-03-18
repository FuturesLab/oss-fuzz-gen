#include <stdio.h>
#include <stdint.h>
#include <zlib.h>

// Define a constant for the size of the input data
#define INPUT_SIZE 1024

int LLVMFuzzerTestOneInput_100(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    gzFile file;
    char filename[] = "fuzz_input.gz";
    FILE *fp;

    // Ensure the size is not zero and does not exceed INPUT_SIZE
    if (size == 0 || size > INPUT_SIZE) {
        return 0;
    }

    // Open a file to write the input data
    fp = fopen(filename, "wb");
    if (fp == NULL) {
        return 0;
    }

    // Write the input data to the file
    fwrite(data, 1, size, fp);
    fclose(fp);

    // Open the file with gzopen
    file = gzopen(filename, "rb");
    if (file == NULL) {
        return 0;
    }

    // Call the function-under-test
    off_t offset = gztell(file);

    // Close the gzFile
    gzclose(file);

    // Return 0 to indicate successful execution
    return 0;
}