#include <stdint.h>
#include <stdlib.h>
#include "zlib.h"
#include "unistd.h"
#include "fcntl.h"
#include <string.h>

int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for a valid null-terminated string
    if (size < 2) {
        return 0;
    }

    // Create a temporary file to use with gzdopen
    char filename[] = "/tmp/fuzz_gzXXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzzer data to the file
    write(fd, data, size);

    // Ensure the file descriptor is at the beginning
    lseek(fd, 0, SEEK_SET);

    // Prepare a mode string from the input data
    char mode[4];
    size_t mode_len = size < 3 ? size : 3; // Limit mode string length to 3
    memcpy(mode, data, mode_len);
    mode[mode_len] = '\0'; // Null-terminate the mode string

    // Call the function under test
    gzFile gz = gzdopen(fd, mode);

    // Clean up
    if (gz != NULL) {
        gzclose(gz);
    } else {
        close(fd); // Close the file descriptor if gzdopen fails
    }

    // Remove the temporary file
    unlink(filename);

    return 0;
}