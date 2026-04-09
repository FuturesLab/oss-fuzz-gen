#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "htslib/hfile.h"

int LLVMFuzzerTestOneInput_125(const uint8_t *data, size_t size) {
    int fd;
    char filename[] = "/tmp/fuzzfileXXXXXX";
    hFILE *file = NULL;

    // Create a temporary file and write the fuzz data to it
    fd = mkstemp(filename);
    if (fd == -1) {
        perror("mkstemp");
        return 0;
    }

    // Write data to the temporary file
    if (write(fd, data, size) != size) {
        perror("write");
        close(fd);
        unlink(filename);
        return 0;
    }

    // Close the file descriptor so it can be reopened with hdopen
    close(fd);

    // Open the file using hdopen
    file = hdopen(fd, "r");
    if (file == NULL) {
        perror("hdopen");
        unlink(filename);
        return 0;
    }

    // Perform any necessary operations on the hFILE object here

    // Close the hFILE object
    if (hclose(file) != 0) {
        perror("hclose");
    }

    // Clean up the temporary file
    unlink(filename);

    return 0;
}