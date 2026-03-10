#include <stdint.h>
#include <stdlib.h>
#include "unistd.h"
#include "fcntl.h"
#include "zlib.h"

// Forward declaration of the function-under-test
int gzgetc_(gzFile file);

int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    // Check if the input size is valid for creating a temporary file
    if (size == 0) {
        return 0;
    }

    // Create a temporary file to write the input data
    char filename[] = "/tmp/fuzz_gzfile_XXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(filename);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the temporary file as a gzFile
    gzFile gzfile = gzopen(filename, "rb");
    if (gzfile == NULL) {
        unlink(filename);
        return 0;
    }

    // Call the function-under-test
    int result = gzgetc_(gzfile);

    // Clean up
    gzclose(gzfile);
    unlink(filename);

    return 0;
}