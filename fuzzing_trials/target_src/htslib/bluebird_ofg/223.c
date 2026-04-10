#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "htslib/hts.h"

int LLVMFuzzerTestOneInput_223(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create two strings
    if (size < 2) {
        return 0;
    }

    // Create a temporary file to pass as the first argument
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Prepare the second argument, mode string
    char mode[3];
    mode[0] = (data[0] % 26) + 'a';  // Random character
    mode[1] = (data[1] % 26) + 'a';  // Random character
    mode[2] = '\0';  // Null-terminate the string

    // Call the function-under-test
    htsFile *file_handle = hts_open(tmpl, mode);

    // Clean up
    if (file_handle) {

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function hts_close with hts_flush
        hts_flush(file_handle);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


    }
    remove(tmpl);

    return 0;
}