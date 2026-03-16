#include "tiffio.h"
#include "cstdint"
#include "cstdlib"
#include <cstdio>
#include <unistd.h> // Include for close function

extern "C" {
    #include "tiffio.h" // Ensure TIFF library functions are wrapped in extern "C"
}

extern "C" int LLVMFuzzerTestOneInput_88(const uint8_t *data, size_t size) {
    if (size < 4) {
        return 0; // Not enough data to proceed
    }

    // Create a temporary file to store the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Could not create temporary file
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

    // Initialize parameters for TIFFReadRGBAImage
    uint32_t width = 1;
    uint32_t height = 1;
    uint32_t *raster = (uint32_t *)malloc(width * height * sizeof(uint32_t));
    if (!raster) {
        TIFFClose(tiff);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from TIFFClose to TIFFGetStrileByteCount
        double ret_LogL10toY_wzsoi = LogL10toY(LOGLUV_PUBLIC);
        if (ret_LogL10toY_wzsoi < 0){
        	return 0;
        }

        uint64_t ret_TIFFGetStrileByteCount_kfdzf = TIFFGetStrileByteCount(tiff, (uint32_t )ret_LogL10toY_wzsoi);
        if (ret_TIFFGetStrileByteCount_kfdzf < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        remove(tmpl);
        return 0;
    }
    int stopOnError = 1; // Non-zero to stop on error

    // Call the function-under-test
    TIFFReadRGBAImage(tiff, width, height, raster, stopOnError);

    // Clean up
    free(raster);
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}