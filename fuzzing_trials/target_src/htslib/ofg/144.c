#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/hts.h>
#include <unistd.h>

int LLVMFuzzerTestOneInput_144(const uint8_t *data, size_t size) {
    char tmpl1[] = "/tmp/fuzzfileXXXXXX";
    char tmpl2[] = "/tmp/fuzzfileXXXXXX";

    // Create temporary files for the input filenames
    int fd1 = mkstemp(tmpl1);
    int fd2 = mkstemp(tmpl2);

    if (fd1 == -1 || fd2 == -1) {
        if (fd1 != -1) close(fd1);
        if (fd2 != -1) close(fd2);
        return 0;
    }

    // Write the fuzz data to the first temporary file
    if (write(fd1, data, size) != size) {
        close(fd1);
        close(fd2);
        return 0;
    }

    // Close the file descriptors as they are not needed anymore
    close(fd1);
    close(fd2);

    // Use non-zero integers for the int parameters
    int flags = 1;
    int is_remote = 1;

    // Call the function-under-test
    hts_idx_t *index = hts_idx_load3(tmpl1, tmpl2, flags, is_remote);

    // Clean up
    if (index != NULL) {
        hts_idx_destroy(index);
    }

    // Remove the temporary files
    unlink(tmpl1);
    unlink(tmpl2);

    return 0;
}