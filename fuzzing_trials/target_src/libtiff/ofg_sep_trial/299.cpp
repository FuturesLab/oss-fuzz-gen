#include <tiffio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Include for close() and unlink()

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_299(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb");
    if (file == NULL) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == NULL) {
        unlink(tmpl); // Use unlink instead of remove for consistency with close
        return 0;
    }

    // Retrieve image dimensions
    uint32_t width, height;
    if (!TIFFGetField(tiff, TIFFTAG_IMAGEWIDTH, &width) ||
        !TIFFGetField(tiff, TIFFTAG_IMAGELENGTH, &height)) {
        TIFFClose(tiff);
        unlink(tmpl);
        return 0;
    }

    // Allocate memory for the RGBA buffer
    uint32_t *raster = (uint32_t *)malloc(width * height * sizeof(uint32_t));
    if (raster == NULL) {
        TIFFClose(tiff);
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFFReadRGBAImage(tiff, width, height, raster, 0);

    // Clean up
    free(raster);
    TIFFClose(tiff);
    unlink(tmpl);

    return 0;
}