#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <unistd.h> // Include for close, write, unlink
#include <fcntl.h>  // Include for mkstemp

extern "C" int LLVMFuzzerTestOneInput_170(const uint8_t *data, size_t size) {
    TIFF *tiff = nullptr;
    uint32_t strip = 0;
    void *buf = nullptr;
    tmsize_t bufsize = 1024; // Arbitrary buffer size for reading

    // Create a temporary file to hold the TIFF data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        unlink(tmpl); // Remove the temporary file
        return 0;
    }

    // Open the temporary file as a TIFF
    tiff = TIFFFdOpen(fd, tmpl, "r");
    if (!tiff) {
        close(fd);
        unlink(tmpl); // Remove the temporary file
        return 0;
    }

    // Allocate memory for the buffer
    buf = malloc(bufsize);
    if (!buf) {
        TIFFClose(tiff);
        close(fd);
        unlink(tmpl); // Remove the temporary file
        return 0;
    }

    // Call the function-under-test
    TIFFReadRawStrip(tiff, strip, buf, bufsize);

    // Clean up
    free(buf);
    TIFFClose(tiff);
    close(fd);
    unlink(tmpl); // Remove the temporary file

    return 0;
}