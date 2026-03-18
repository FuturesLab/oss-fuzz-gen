#include <cstdint>
#include <cstdio>
#include <cstdlib> // For mkstemp
#include <unistd.h> // For close and remove
#include <tiffio.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_133(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == nullptr) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Prepare parameters for TIFFReadRGBATile
    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t *raster = new uint32_t[256 * 256]; // Allocate memory for the raster

    // Call the function-under-test
    TIFFReadRGBATile(tiff, x, y, raster);

    // Clean up
    delete[] raster;
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}