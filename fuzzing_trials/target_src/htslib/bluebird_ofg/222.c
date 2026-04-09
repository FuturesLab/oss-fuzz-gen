#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// Ensure the function is declared correctly
extern int sam_index_build2(const char *, const char *, int);

int LLVMFuzzerTestOneInput_222(const uint8_t *data, size_t size) {
    // Ensure size is large enough for two filenames and an integer
    if (size < 3) {
        return 0;
    }

    char tmpl1[] = "/tmp/fuzzfile1XXXXXX";
    char tmpl2[] = "/tmp/fuzzfile2XXXXXX";
    int fd1 = mkstemp(tmpl1);
    int fd2 = mkstemp(tmpl2);

    if (fd1 == -1 || fd2 == -1) {
        if (fd1 != -1) {
                close(fd1);
        }
        if (fd2 != -1) {
                close(fd2);
        }
        return 0;
    }

    // Calculate half size for splitting data
    size_t half_size = size / 2;

    // Ensure half_size is not zero to avoid empty writes
    if (half_size == 0) {
        close(fd1);
        close(fd2);
        unlink(tmpl1);
        unlink(tmpl2);
        return 0;
    }

    // Write the data to the first temporary file
    if (write(fd1, data, half_size) != half_size) {
        close(fd1);
        close(fd2);
        unlink(tmpl1);
        unlink(tmpl2);
        return 0;
    }
    close(fd1);

    // Write the remaining data to the second temporary file
    if (write(fd2, data + half_size, size - half_size) != (size - half_size)) {
        close(fd2);
        unlink(tmpl1);
        unlink(tmpl2);
        return 0;
    }
    close(fd2);

    // Use the first byte of data as an integer for the options parameter
    int options = (int)data[0];

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of sam_index_build2
    if (sam_index_build2(tmpl1, (const char *)"r", options) != 0) {
    // End mutation: Producer.REPLACE_ARG_MUTATOR


        // Handle error if sam_index_build2 fails
        unlink(tmpl1);
        unlink(tmpl2);
        return 0;
    }

    // Clean up temporary files
    unlink(tmpl1);
    unlink(tmpl2);

    return 0;
}