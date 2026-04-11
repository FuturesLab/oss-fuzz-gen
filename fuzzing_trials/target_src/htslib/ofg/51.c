#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// Function-under-test declaration
int hts_file_type(const char *);

// Remove the 'extern "C"' linkage specification for C++
// since this is a C file, not a C++ file.
int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    // Create a temporary file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // If file creation fails, return
    }

    // Write the fuzzing data to the file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0; // If write fails, clean up and return
    }

    // Close the file descriptor
    close(fd);

    // Call the function-under-test with the temporary filename
    hts_file_type(tmpl);

    // Clean up: remove the temporary file
    unlink(tmpl);

    return 0;
}