#include <tiffio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Include for write, close, and remove
#include <fcntl.h>   // Include for mkstemp

extern "C" {
    // Wrap the C library headers and functions in extern "C" to ensure proper linkage
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_318(const uint8_t *data, size_t size) {
    if (size < 4) {
        return 0; // Not enough data to proceed
    }

    // Create a temporary file to simulate a TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Failed to create a temporary file
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        remove(tmpl);
        return 0; // Failed to write all data
    }

    // Close the file descriptor
    close(fd);

    // Open the temporary file as a TIFF image
    TIFF* tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0; // Failed to open the TIFF file
    }

    // Allocate a buffer for the scanline
    tsize_t scanlineSize = TIFFScanlineSize(tiff);
    void* buf = _TIFFmalloc(scanlineSize);
    if (!buf) {
        TIFFClose(tiff);
        remove(tmpl);
        return 0; // Failed to allocate memory for the scanline buffer
    }

    // Define row and sample parameters
    uint32_t row = 0;
    uint16_t sample = 0;

    // Call the function under test
    TIFFReadScanline(tiff, buf, row, sample);

    // Clean up
    _TIFFfree(buf);
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}