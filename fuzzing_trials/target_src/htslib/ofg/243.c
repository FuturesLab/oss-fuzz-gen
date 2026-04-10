#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern int sam_index_build3(const char *fn, const char *prefix, int min_shift, int n_threads);

int LLVMFuzzerTestOneInput_243(const uint8_t *data, size_t size) {
    char tmpl1[] = "/tmp/fuzzfileXXXXXX";
    char tmpl2[] = "/tmp/prefixXXXXXX";
    int fd1, fd2;
    int result;

    // Ensure size is sufficient for meaningful data
    if (size < 2) {
        return 0;
    }

    // Create temporary files for fn and prefix
    fd1 = mkstemp(tmpl1);
    fd2 = mkstemp(tmpl2);

    // Write data to the temporary files
    write(fd1, data, size / 2);
    write(fd2, data + size / 2, size - size / 2);

    // Close file descriptors
    close(fd1);
    close(fd2);

    // Call the function-under-test with non-NULL parameters
    result = sam_index_build3(tmpl1, tmpl2, 1, 1);

    // Clean up temporary files
    unlink(tmpl1);
    unlink(tmpl2);

    return 0;
}