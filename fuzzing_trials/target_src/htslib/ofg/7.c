#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

// Assume the function is declared in some header file
char **hts_readlist(const char *, int, int *);

int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Create a temporary file to store the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    ssize_t written = write(fd, data, size);
    if (written != size) {
        close(fd);
        return 0;
    }
    close(fd);

    int num_elements = 0;
    int *num_elements_ptr = &num_elements;

    // Call the function-under-test
    char **result = hts_readlist(tmpl, 1, num_elements_ptr);

    // Clean up: Free the result if it's not NULL
    if (result != NULL) {
        for (int i = 0; i < num_elements; i++) {
            free(result[i]);
        }
        free(result);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}