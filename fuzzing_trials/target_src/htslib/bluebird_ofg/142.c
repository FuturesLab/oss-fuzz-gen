#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// Function prototype for the function-under-test
int sam_index_build3(const char *fn, const char *fnidx, int min_shift, int n_threads);

int LLVMFuzzerTestOneInput_142(const uint8_t *data, size_t size) {
    // Check if the input size is too small to be meaningful
    if (size < 1) {
        return 0; // Exit if no data is provided
    }

    // Create temporary files to simulate filenames
    char tmpl1[] = "/tmp/fuzzfile1XXXXXX";
    char tmpl2[] = "/tmp/fuzzfile2XXXXXX";
    int fd1 = mkstemp(tmpl1);
    int fd2 = mkstemp(tmpl2);

    // Ensure the temporary files are created successfully
    if (fd1 == -1 || fd2 == -1) {
        if (fd1 != -1) {
                close(fd1);
        }
        if (fd2 != -1) {
                close(fd2);
        }
        return 0; // Exit if file creation fails
    }

    // Write fuzz data to the first temporary file
    ssize_t written = write(fd1, data, size);
    if (written == -1 || written != size) {
        close(fd1);
        close(fd2);
        unlink(tmpl1);
        unlink(tmpl2);
        return 0; // Exit if writing fails
    }
    close(fd1);

    // Initialize parameters for the function-under-test
    const char *fn = tmpl1;
    const char *fnidx = tmpl2;
    int min_shift = 1;  // Example value, can be varied
    int n_threads = 2;  // Example value, can be varied

    // Call the function-under-test
    int result = sam_index_build3(fn, fnidx, min_shift, n_threads);

    // Check the result of the function-under-test
    if (result != 0) {
        fprintf(stderr, "Function sam_index_build3 failed with error code: %d\n", result);
    }

    // Clean up temporary files

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_index_build3 to hts_reglist_free

    hts_reglist_free(NULL, result);

    // End mutation: Producer.APPEND_MUTATOR

    unlink(tmpl1);
    unlink(tmpl2);

    return 0;
}