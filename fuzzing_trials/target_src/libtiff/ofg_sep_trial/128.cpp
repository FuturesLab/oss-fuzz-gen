#include <cstdint>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <tiffio.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_128(const uint8_t *data, size_t size) {
    // Create a memory-mapped TIFF file from the input data
    if (size < 4) {
        return 0; // Not enough data to be a valid TIFF file
    }

    // Create a temporary file to store the input data
    char tmpl[] = "/tmp/fuzz-tiff-XXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Unable to create temporary file
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        return 0; // Unable to write to temporary file
    }

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        close(fd);
        return 0; // Unable to open TIFF file
    }

    // Initialize parameters for TIFFReadRGBATileExt
    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t raster[256]; // Example size, adjust as needed
    int stopOnError = 1;

    // Call the function under test
    TIFFReadRGBATileExt(tiff, x, y, raster, stopOnError);

    // Clean up
    TIFFClose(tiff);
    close(fd);
    unlink(tmpl); // Remove the temporary file

    return 0;
}