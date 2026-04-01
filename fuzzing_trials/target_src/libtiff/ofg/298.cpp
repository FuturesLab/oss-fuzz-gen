#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>  // Include this header for close, write, and unlink

extern "C" int LLVMFuzzerTestOneInput_298(const uint8_t *data, size_t size) {
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        unlink(tmpl);
        return 0;
    }

    // Use a non-zero toff_t value for testing
    toff_t offset = 1;

    // Call the function-under-test
    TIFFReadEXIFDirectory(tiff, offset);

    // Clean up
    TIFFClose(tiff);
    unlink(tmpl);

    return 0;
}