#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Function under test
long cmsfilelength(FILE *file);

// Fuzzer function
int LLVMFuzzerTestOneInput_443(const uint8_t *data, size_t size) {
    // Check if the input size is zero, which means there's nothing to write
    if (size == 0) {
        return 0;
    }

    // Create a temporary file
    FILE *tempFile = tmpfile();
    if (tempFile == NULL) {
        return 0;
    }

    // Write the input data to the temporary file
    fwrite(data, 1, size, tempFile);

    // Rewind the file to the beginning for reading
    rewind(tempFile);

    // Call the function under test
    long length = cmsfilelength(tempFile);

    // Check the length to ensure the function is being tested
    if (length != size) {
        fprintf(stderr, "Mismatch in file length: expected %zu, got %ld\n", size, length);
    }

    // Close the temporary file
    fclose(tempFile);

    return 0;
}