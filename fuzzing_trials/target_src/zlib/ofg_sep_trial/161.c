#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int LLVMFuzzerTestOneInput_161(const uint8_t *data, size_t size) {
    // Ensure that data is large enough to contain a null-terminated string
    if (size < 2) {
        return 0;
    }

    // Create a temporary file to use with gzdopen
    char filename[] = "/tmp/fuzz_gzdopen_XXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the file
    write(fd, data, size);

    // Null-terminate the data to use as the mode string
    char mode[2];
    mode[0] = (char)data[0];
    mode[1] = '\0';

    // Call the function-under-test
    gzFile gz = gzdopen(fd, mode);

    // Clean up
    if (gz != NULL) {
        gzclose(gz);
    } else {
        close(fd);
    }
    unlink(filename);

    return 0;
}