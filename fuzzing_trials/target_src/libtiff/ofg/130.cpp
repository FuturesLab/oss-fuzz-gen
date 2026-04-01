#include <cstdint>
#include <cstdio>
#include <cstdlib> // Include for mkstemp and close
#include <unistd.h> // Include for mkstemp and close

extern "C" {
#include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_130(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }

    // Write the fuzz data to the temporary file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0;
    }

    // Initialize parameters for TIFFReadRGBATileExt
    uint32_t x = 0; // Starting x coordinate
    uint32_t y = 0; // Starting y coordinate
    uint32_t raster[256]; // Example raster buffer, size should be adjusted based on actual tile size
    int stopOnError = 1; // Example flag for stopping on error

    // Call the function-under-test
    TIFFReadRGBATileExt(tiff, x, y, raster, stopOnError);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}