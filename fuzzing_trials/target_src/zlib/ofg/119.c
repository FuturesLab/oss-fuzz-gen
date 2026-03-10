#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int LLVMFuzzerTestOneInput_119(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char filename[] = "/tmp/fuzz_gzXXXXXX";
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
    close(fd);

    // Open the file with gzopen
    gzFile gz_file = gzopen(filename, "rb");
    if (gz_file == NULL) {
        unlink(filename);
        return 0;
    }

    // Buffer to read decompressed data
    char buffer[4096];
    int bytes_read;

    // Read from the gz file to ensure the function is exercised
    while ((bytes_read = gzread(gz_file, buffer, sizeof(buffer))) > 0) {
        // Process the decompressed data (if necessary)
    }

    // Call the function-under-test
    gzclose(gz_file);

    // Clean up the temporary file
    unlink(filename);

    return 0;
}