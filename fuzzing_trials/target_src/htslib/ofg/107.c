#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>  // For close, lseek, and unlink
#include <fcntl.h>   // For mkstemp
#include "/src/htslib/htslib/hfile.h" // Correct path for hFILE and hpeek

int LLVMFuzzerTestOneInput_107(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Create a temporary file to simulate hFILE
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }

    // Rewind the file descriptor to the beginning
    lseek(fd, 0, SEEK_SET);

    // Open the file using hopen_fd equivalent function
    hFILE *hfile = hopen(tmpl, "r");
    if (hfile == NULL) {
        close(fd);
        return 0;
    }

    // Allocate a buffer to read into
    void *buffer = malloc(size);
    if (buffer == NULL) {
        hclose(hfile);
        close(fd);
        return 0;
    }

    // Call the function-under-test
    ssize_t result = hpeek(hfile, buffer, size);

    // Clean up
    free(buffer);
    hclose(hfile);
    close(fd);
    unlink(tmpl);

    return 0;
}