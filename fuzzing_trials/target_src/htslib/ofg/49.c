#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

// Assuming the function is declared in a header file, include it here
// #include "htslib.h"

extern char **hts_readlines(const char *, int *);

int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Prepare to call the function-under-test
    int num_lines = 0;
    char **lines = hts_readlines(tmpl, &num_lines);

    // Clean up
    if (lines != NULL) {
        for (int i = 0; i < num_lines; i++) {
            free(lines[i]);
        }
        free(lines);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}