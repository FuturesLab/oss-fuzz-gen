#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>   // Include this for mkstemp(), write(), close(), and unlink()

int LLVMFuzzerTestOneInput_101(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char filename[] = "/tmp/fuzz_gzXXXXXX";
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

    // Close the file descriptor as gzopen will open it again
    close(fd);

    // Open the file with gzopen
    gzFile gz_file = gzopen(filename, "rb");
    if (gz_file == NULL) {
        unlink(filename);
        return 0;
    }

    // Buffer to read data into
    char buffer[1024];
    int bytes_read;

    // Read the data using gzread
    while ((bytes_read = gzread(gz_file, buffer, sizeof(buffer))) > 0) {
        // Process the data if needed
    }

    // Clean up
    gzclose(gz_file);
    unlink(filename);

    return 0;
}