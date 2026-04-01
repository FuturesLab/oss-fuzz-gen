#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <unistd.h>  // Include for close, write, and unlink functions

extern "C" int LLVMFuzzerTestOneInput_307(const uint8_t *data, size_t size) {
    // Create a temporary file to store the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the TIFF file from the temporary file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        return 0;
    }

    // Prepare parameters for TIFFReadRGBAStripExt
    uint32_t strip = 0; // Start with the first strip
    uint32_t *raster = (uint32_t *)malloc(TIFFStripSize(tiff) * sizeof(uint32_t));
    if (raster == nullptr) {
        TIFFClose(tiff);
        return 0;
    }
    int stopOnError = 1; // Example value for stopOnError

    // Call the function-under-test
    TIFFReadRGBAStripExt(tiff, strip, raster, stopOnError);

    // Clean up
    free(raster);
    TIFFClose(tiff);

    // Remove the temporary file
    unlink(tmpl);

    return 0;
}