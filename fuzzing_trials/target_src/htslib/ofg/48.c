#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

// Function-under-test declaration
char **hts_readlines(const char *, int *);

// Remove the 'extern "C"' linkage specification as it is not needed in C
int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }
    close(fd);

    // Prepare the output parameter for hts_readlines
    int num_lines = 0;

    // Call the function-under-test
    char **lines = hts_readlines(tmpl, &num_lines);

    // Clean up
    if (lines) {
        for (int i = 0; i < num_lines; ++i) {
            free(lines[i]);
        }
        free(lines);
    }
    unlink(tmpl);

    return 0;
}