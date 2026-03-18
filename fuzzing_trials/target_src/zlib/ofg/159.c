#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int LLVMFuzzerTestOneInput_159(const uint8_t *data, size_t size) {
    int fd;
    const char *mode;
    gzFile file;

    // Ensure data size is sufficient for mode string and file descriptor
    if (size < 2) {
        return 0;
    }

    // Create a temporary file to obtain a valid file descriptor
    fd = open("/tmp/fuzz_gzdopen_tmp", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        return 0;
    }

    // Use the first byte of data to determine the mode
    switch (data[0] % 3) {
        case 0:
            mode = "r";
            break;
        case 1:
            mode = "w";
            break;
        case 2:
            mode = "a";
            break;
        default:
            mode = "r"; // Default case, should not be reached
            break;
    }

    // Call the function under test
    file = gzdopen(fd, mode);

    // If the file was successfully opened, close it
    if (file != NULL) {
        gzclose(file);
    } else {
        // If gzdopen fails, close the file descriptor manually
        close(fd);
    }

    return 0;
}