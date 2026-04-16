#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_227(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a file input for hts_open
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // If file creation fails, exit early
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        remove(tmpl);
        return 0; // If writing fails, exit early
    }

    // Close the file descriptor
    close(fd);

    // Open the temporary file using hts_open
    htsFile *file = hts_open(tmpl, "r");
    if (file == NULL) {
        remove(tmpl);
        return 0; // If opening fails, exit early
    }

    // Call the function-under-test
    int result = hts_close(file);

    // Clean up: remove the temporary file
    remove(tmpl);

    return 0;
}