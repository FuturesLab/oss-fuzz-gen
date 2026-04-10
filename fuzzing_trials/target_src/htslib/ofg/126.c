#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include "/src/htslib/htslib/hfile.h"

int LLVMFuzzerTestOneInput_126(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to contain a valid filename.
    if (size < 5) {
        return 0;
    }

    // Create a temporary file to use with hdopen.
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file.
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Reset the file offset to the beginning of the file.
    lseek(fd, 0, SEEK_SET);

    // Call the function-under-test with the file descriptor and a mode.
    const char *mode = "r"; // Open the file for reading.
    hFILE *file = hdopen(fd, mode);

    // Clean up: Close the file and remove the temporary file.
    if (file != NULL) {
        hclose(file);
    } else {
        close(fd); // Close the file descriptor if hdopen fails.
    }
    unlink(tmpl);

    return 0;
}