#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "/src/htslib/htslib/hfile.h"

int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    // Create a temporary file to use with hFILE
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0;
    }

    // Rewind the file descriptor to the beginning
    lseek(fd, 0, SEEK_SET);

    // Open the file using hFILE
    hFILE *hfile = hopen(tmpl, "r");
    if (hfile == NULL) {
        close(fd);
        return 0;
    }

    // Call the function-under-test
    hclose(hfile);

    // Clean up
    close(fd);
    unlink(tmpl);

    return 0;
}