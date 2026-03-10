#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_117(const uint8_t *data, size_t size) {
    // Ensure the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a temporary file to simulate a gzFile
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

    // Rewind the file descriptor to the beginning
    lseek(fd, 0, SEEK_SET);

    // Open the file as a gzFile
    gzFile gzfile = gzdopen(fd, "rb");
    if (gzfile == NULL) {
        close(fd);
        unlink(filename);
        return 0;
    }

    // Call the function-under-test
    int result = gzdirect(gzfile);

    // Clean up
    gzclose(gzfile);
    unlink(filename);

    return 0;
}