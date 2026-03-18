#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int LLVMFuzzerTestOneInput_113(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char filename[] = "/tmp/fuzz_gzfile_XXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(filename);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the file with gzopen
    gzFile gz_file = gzopen(filename, "rb");
    if (gz_file == NULL) {
        unlink(filename);
        return 0;
    }

    // Call the function-under-test
    off_t offset = gzoffset(gz_file);

    // Print the offset for debugging purposes
    printf("Offset: %ld\n", (long)offset);

    // Close the gzFile
    gzclose(gz_file);

    // Remove the temporary file
    unlink(filename);

    return 0;
}