#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h> // Include for close function

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_242(const uint8_t *data, size_t size) {
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

    // Write the fuzz data to the temporary file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0;
    }

    // Prepare parameters for TIFFReadRGBAImageOriented
    uint32_t width = 1;
    uint32_t height = 1;
    uint32_t *raster = (uint32_t *)malloc(width * height * sizeof(uint32_t));
    int orientation = ORIENTATION_TOPLEFT;
    int stopOnError = 1;

    if (raster) {
        // Call the function-under-test
        TIFFReadRGBAImageOriented(tiff, width, height, raster, orientation, stopOnError);

        // Clean up
        free(raster);
    }

    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}