#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <unistd.h> // Include for close and unlink functions

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_129(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data to
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

    // Write the data to the temporary file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        unlink(tmpl); // Use unlink instead of remove for consistency with close
        return 0;
    }

    // Prepare parameters for TIFFReadRGBATile
    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t *raster = (uint32_t *)malloc(TIFFTileSize(tiff));
    if (!raster) {
        TIFFClose(tiff);
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFFReadRGBATile(tiff, x, y, raster);

    // Clean up
    free(raster);
    TIFFClose(tiff);
    unlink(tmpl);

    return 0;
}