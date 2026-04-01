#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Include this for the 'close' function

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_127(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
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
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0;
    }

    // Initialize parameters for TIFFReadRGBATileExt
    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t *raster = (uint32_t *)malloc(sizeof(uint32_t) * TIFFTileSize(tiff));
    if (!raster) {
        TIFFClose(tiff);
        remove(tmpl);
        return 0;
    }
    int stopOnError = 1;

    // Call the function-under-test
    TIFFReadRGBATileExt(tiff, x, y, raster, stopOnError);

    // Clean up
    free(raster);
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}