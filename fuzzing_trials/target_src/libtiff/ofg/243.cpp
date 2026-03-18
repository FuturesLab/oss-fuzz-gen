#include <tiffio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Include for close() and remove()

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_243(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == NULL) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file using the TIFF library
    TIFF *tif = TIFFOpen(tmpl, "r");
    if (tif == NULL) {
        remove(tmpl);
        return 0;
    }

    // Define parameters for the function
    uint32_t width = 1;  // Set to a non-zero value
    uint32_t height = 1; // Set to a non-zero value
    uint32_t *raster = (uint32_t *)malloc(width * height * sizeof(uint32_t));
    if (raster == NULL) {
        TIFFClose(tif);
        remove(tmpl);
        return 0;
    }
    int orientation = ORIENTATION_TOPLEFT; // Valid orientation value
    int stopOnError = 1; // Non-zero value

    // Call the function-under-test
    TIFFReadRGBAImageOriented(tif, width, height, raster, orientation, stopOnError);

    // Clean up
    free(raster);
    TIFFClose(tif);
    remove(tmpl);

    return 0;
}