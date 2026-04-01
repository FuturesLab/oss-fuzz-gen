#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h> // Include for 'close'
#include <tiffio.h>

extern "C" {
    #include <tiffio.h> // Ensure TIFF functions are wrapped in extern "C"
}

extern "C" int LLVMFuzzerTestOneInput_180(const uint8_t *data, size_t size) {
    // Create a temporary file to hold the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Failed to create temp file
    }

    // Write the data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0; // Failed to open file stream
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0; // Failed to open TIFF
    }

    // Prepare parameters for TIFFReadRGBAStrip
    uint32_t row = 0; // Starting row
    uint32_t *raster = (uint32_t *)_TIFFmalloc(TIFFRasterScanlineSize(tiff) * sizeof(uint32_t));
    if (!raster) {
        TIFFClose(tiff);
        remove(tmpl);
        return 0; // Memory allocation failed
    }

    // Call the function-under-test
    TIFFReadRGBAStrip(tiff, row, raster);

    // Cleanup
    _TIFFfree(raster);
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}