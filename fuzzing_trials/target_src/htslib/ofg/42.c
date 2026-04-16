#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/hts.h>
#include <unistd.h>

int LLVMFuzzerTestOneInput_42(const uint8_t *data, size_t size) {
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

    // Use a non-zero integer for the second parameter
    int flags = 1;

    // Call the function-under-test
    hts_idx_t *index = hts_idx_load(tmpl, flags);

    // Clean up
    if (index != NULL) {
        hts_idx_destroy(index);
    }
    unlink(tmpl);

    return 0;
}