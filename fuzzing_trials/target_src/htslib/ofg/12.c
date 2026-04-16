#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

extern int hfile_has_plugin(const char *);

int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    // Check if the input size is non-zero to ensure meaningful input
    if (size == 0) {
        return 0;
    }

    // Create a temporary file to store the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // If file creation fails, exit the fuzzer
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0; // If writing fails, clean up and exit
    }

    // Close the file descriptor
    close(fd);

    // Call the function-under-test with the temporary file path
    hfile_has_plugin(tmpl);

    // Clean up the temporary file
    unlink(tmpl);

    return 0;
}