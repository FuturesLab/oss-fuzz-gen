#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput_318(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
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

    // Close the file descriptor
    close(fd);

    // Open the TIFF file using TIFFOpen
    const char *mode = "r"; // Open in read mode
    TIFF *tiff = TIFFOpen(tmpl, mode);

    // Perform some operations if TIFFOpen was successful
    if (tiff != nullptr) {
        // Example operation: retrieve image width and height
        uint32_t width, height;
        TIFFGetField(tiff, TIFFTAG_IMAGEWIDTH, &width);
        TIFFGetField(tiff, TIFFTAG_IMAGELENGTH, &height);

        // Close the TIFF file
        TIFFClose(tiff);
    }

    // Remove the temporary file
    unlink(tmpl);

    return 0;
}