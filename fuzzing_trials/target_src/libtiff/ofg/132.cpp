#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <tiffio.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_132(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
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

    // Write the fuzz data to the file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0;
    }

    // Initialize parameters for TIFFReadRGBATile
    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t *raster = new uint32_t[TIFFTileSize(tiff) / sizeof(uint32_t)];

    // Call the function-under-test
    TIFFReadRGBATile(tiff, x, y, raster);

    // Clean up
    delete[] raster;
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}