#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>
#include <unistd.h>  // Include this for close() and unlink()

int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size) {
    gzFile file;
    int flush_mode = Z_SYNC_FLUSH; // Use a valid flush mode

    // Create a temporary file to use with gzopen
    char filename[] = "/tmp/fuzz_gzfileXXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1) {
        return 0;
    }

    // Open the file with gzopen
    file = gzdopen(fd, "wb");
    if (file == NULL) {
        close(fd);
        return 0;
    }

    // Write the input data to the gzFile
    if (gzwrite(file, data, size) != (int)size) {
        gzclose(file);
        return 0;
    }

    // Call the function-under-test
    gzflush(file, flush_mode);

    // Clean up
    gzclose(file);
    unlink(filename);

    return 0;
}