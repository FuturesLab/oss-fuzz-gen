#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Include for close() and unlink()
#include <fcntl.h>  // Include for open() flags

// Function-under-test declaration
FILE *janet_dynfile(const char *filename, FILE *file);

int LLVMFuzzerTestOneInput_1478(const uint8_t *data, size_t size) {
    // Ensure there is enough data for a filename
    if (size < 1) {
        return 0;
    }

    // Create a temporary file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    FILE *fuzzFile = fdopen(fd, "wb");
    if (!fuzzFile) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, fuzzFile);
    fflush(fuzzFile);
    fclose(fuzzFile); // Close the file after writing

    // Reopen the file for reading
    FILE *inputFile = fopen(tmpl, "rb");
    if (!inputFile) {
        unlink(tmpl);
        return 0;
    }

    // Reset the file pointer to the beginning of the file
    fseek(inputFile, 0, SEEK_SET);

    // Call the function-under-test with the file containing fuzz data
    // Ensure the function is called with a valid file pointer
    FILE *result = janet_dynfile(tmpl, inputFile);

    // Check if the result is not NULL to ensure the function is utilized
    if (result && result != inputFile) {
        // Process the result if needed
        fclose(result);
    }

    // Clean up
    fclose(inputFile);
    unlink(tmpl);

    return 0;
}