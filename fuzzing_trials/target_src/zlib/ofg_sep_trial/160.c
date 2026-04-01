#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int LLVMFuzzerTestOneInput_160(const uint8_t *data, size_t size) {
    int fd;
    char mode[4]; // Buffer to hold the mode string

    // Ensure the mode string is null-terminated and not NULL
    if (size < 1) {
        return 0;
    }

    // Create a temporary file to get a valid file descriptor
    fd = open("/dev/null", O_WRONLY);
    if (fd == -1) {
        return 0;
    }

    // Copy a portion of data to mode ensuring it is null-terminated
    size_t mode_len = (size < 3) ? size : 3;
    memcpy(mode, data, mode_len);
    mode[mode_len] = '\0';

    // Call the function under test
    gzFile gz = gzdopen(fd, mode);

    // Clean up: close the gzFile if it was successfully opened
    if (gz != NULL) {
        gzclose(gz);
    } else {
        // If gzdopen fails, close the file descriptor manually
        close(fd);
    }

    return 0;
}