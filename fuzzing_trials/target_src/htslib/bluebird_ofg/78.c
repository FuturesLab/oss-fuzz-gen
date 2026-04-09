#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Function prototype for the function-under-test
int hts_file_type(const char *);

// The 'extern "C"' linkage specification is not needed in C code, so we remove it
int LLVMFuzzerTestOneInput_78(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Failed to create a temporary file
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0; // Failed to write data to the file
    }

    // Close the file descriptor
    close(fd);

    // Call the function-under-test with the temporary file path
    hts_file_type(tmpl);

    // Clean up: remove the temporary file
    unlink(tmpl);

    return 0;
}