#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h> // Include unistd.h for the close() function
#include <tiffio.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_242(const uint8_t *data, size_t size) {
    // Create a temporary file to store the input data
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

    // Define parameters for TIFFReadRGBAImageOriented
    uint32_t width = 100;  // Example width
    uint32_t height = 100; // Example height
    uint32_t *raster = (uint32_t *)malloc(width * height * sizeof(uint32_t));
    int orientation = ORIENTATION_TOPLEFT; // Example orientation
    int stopOnError = 1; // Example flag to stop on error

    // Call the function-under-test
    TIFFReadRGBAImageOriented(tiff, width, height, raster, orientation, stopOnError);

    // Clean up
    free(raster);
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}