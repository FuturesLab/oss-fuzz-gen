#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "/src/htslib/htslib/hfile.h"

int LLVMFuzzerTestOneInput_206(const uint8_t *data, size_t size) {
    hFILE *file;
    off_t offset;
    int whence;
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

    // Close the file descriptor and reopen it with hopen
    close(fd);
    file = hopen(tmpl, "rb");

    if (file == NULL) {
        return 0;
    }

    // Initialize offset and whence with non-zero values
    offset = (off_t)(size / 2);  // Arbitrary non-zero offset
    whence = SEEK_SET;           // Use SEEK_SET as the whence value

    // Call the function-under-test
    off_t result = hseek(file, offset, whence);

    // Clean up
    hclose(file);
    remove(tmpl);

    return 0;
}