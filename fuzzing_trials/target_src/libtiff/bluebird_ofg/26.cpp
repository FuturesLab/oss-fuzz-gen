#include "cstdint"
#include <cstdio>
#include "cstdlib" // For mkstemp and remove
#include <unistd.h> // For close
#include "tiffio.h"

extern "C" {
    #include "tiffio.h"
}

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a TIFF file
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
    TIFF *tiff = TIFFOpen(tmpl, "r+");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Fuzz the TIFFUnlinkDirectory function
    tdir_t directory = 0; // Use a fixed directory number for fuzzing

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from TIFFOpen to TIFFRasterScanlineSize

    tmsize_t ret_TIFFRasterScanlineSize_oykjg = TIFFRasterScanlineSize(tiff);

    // End mutation: Producer.APPEND_MUTATOR

    TIFFUnlinkDirectory(tiff, directory);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}