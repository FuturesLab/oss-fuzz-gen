#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <tiffio.h>
#include <unistd.h>
#include <fcntl.h>

extern "C" int LLVMFuzzerTestOneInput_189(const uint8_t *data, size_t size) {
    // Create a temporary file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Ensure the file is flushed and the file descriptor is reset
    fsync(fd);
    lseek(fd, 0, SEEK_SET);

    // Define mode for opening the TIFF file
    const char *mode = "r";

    // Call the function-under-test
    TIFF *tiff = TIFFFdOpen(fd, tmpl, mode);

    // If the TIFF file is successfully opened, close it
    if (tiff != nullptr) {
        TIFFClose(tiff);
    }

    // Clean up: close file descriptor and remove the temporary file
    close(fd);
    unlink(tmpl);

    return 0;
}