#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>  // Include for 'write' and 'close'
#include <sys/types.h>  // Include for 'ssize_t'

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_181(const uint8_t *data, size_t size) {
    TIFF *tiff;
    uint32_t *raster;
    uint32_t strip = 0;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);

    if (fd == -1) {
        return 0;
    }

    // Write the fuzzing data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the TIFF file
    tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        return 0;
    }

    // Allocate memory for the raster
    uint32_t width, height;
    if (TIFFGetField(tiff, TIFFTAG_IMAGEWIDTH, &width) && TIFFGetField(tiff, TIFFTAG_IMAGELENGTH, &height)) {
        raster = (uint32_t *)_TIFFmalloc(width * height * sizeof(uint32_t));
        if (raster) {
            // Call the function-under-test
            TIFFReadRGBAStrip(tiff, strip, raster);

            // Free the raster memory
            _TIFFfree(raster);
        }
    }

    // Close the TIFF file
    TIFFClose(tiff);

    // Remove the temporary file
    remove(tmpl);

    return 0;
}