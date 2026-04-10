#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// Function-under-test
int hfile_has_plugin(const char *);

// Fuzzing harness
int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    // Check if the input data is non-empty
    if (size == 0) {
        return 0;
    }

    // Ensure the input data is null-terminated
    char *null_terminated_data = (char *)malloc(size + 1);
    if (!null_terminated_data) {
        return 0;
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Create a temporary file to hold the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        free(null_terminated_data);
        return 0;
    }

    // Write the null-terminated fuzz data to the temporary file
    if (write(fd, null_terminated_data, size) != size) {
        close(fd);
        unlink(tmpl);
        free(null_terminated_data);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Call the function-under-test with the temporary file's name
    int result = hfile_has_plugin(tmpl);

    // Clean up the temporary file and allocated memory
    unlink(tmpl);
    free(null_terminated_data);

    return result;
}