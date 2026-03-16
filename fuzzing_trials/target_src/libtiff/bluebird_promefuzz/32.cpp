#include <iostream>
#include "sstream"
#include <string>
#include <vector>
#include "cstring"
#include "cstdlib"
#include <cstdio>
#include "cstdint"
#include <cstddef>
#include "tiffio.h"
#include "cstdint"
#include <cstdio>
#include "cstdlib"
#include "cstring"

static TIFF* initializeTIFF(const char* filename) {
    TIFF* tif = TIFFOpen(filename, "w");
    if (!tif) return nullptr;

    // Setup basic TIFF fields (example setup, may vary based on requirements)
    TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, 1);
    TIFFSetField(tif, TIFFTAG_IMAGELENGTH, 1);
    TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 1);
    TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);
    TIFFSetField(tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
    TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
    TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);

    return tif;
}

static void cleanupTIFF(TIFF* tif) {
    if (tif) {
        TIFFClose(tif);
    }
}

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;  // Not enough data to process

    // Step 1: Prepare a dummy file
    const char* filename = "./dummy_file";
    FILE* file = fopen(filename, "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Step 2: Initialize TIFF structure
    TIFF* tif = initializeTIFF(filename);
    if (!tif) return 0;

    uint64_t dir_offset;

    // Step 3: Invoke target functions with diverse inputs
    TIFFWriteCustomDirectory(tif, &dir_offset);
    TIFFCheckpointDirectory(tif);
    TIFFWriteDirectory(tif);
    TIFFRewriteDirectory(tif);

    // Prepare buffer for TIFFWriteScanline
    uint8_t buf[1] = {0};  // Minimal buffer for testing
    TIFFWriteScanline(tif, buf, 0, 0);

    TIFFDeferStrileArrayWriting(tif);

    // Step 4: Cleanup
    cleanupTIFF(tif);

    return 0;
}