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

static TIFF* createDummyTIFF(const char* filename) {
    TIFF* tiff = TIFFOpen(filename, "w");
    if (!tiff) {
        fprintf(stderr, "Failed to open TIFF file for writing.\n");
        return nullptr;
    }
    return tiff;
}

extern "C" int LLVMFuzzerTestOneInput_82(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint64_t)) {
        return 0;
    }

    // Write dummy data to a file to simulate a TIFF file
    const char* dummyFilename = "./dummy_file";
    FILE* file = fopen(dummyFilename, "wb");
    if (!file) {
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the dummy TIFF file
    TIFF* tiff = createDummyTIFF(dummyFilename);
    if (!tiff) {
        return 0;
    }

    // Call TIFFCreateEXIFDirectory
    TIFFCreateEXIFDirectory(tiff);

    // Call TIFFFileName
    const char* filename = TIFFFileName(tiff);
    if (filename) {
        printf("TIFF file name: %s\n", filename);
    }

    // Call TIFFGetCloseProc
    TIFFCloseProc closeProc = TIFFGetCloseProc(tiff);
    if (closeProc) {
        printf("TIFF close procedure is set.\n");
    }

    // Call TIFFCreateGPSDirectory
    TIFFCreateGPSDirectory(tiff);

    // Use the first 8 bytes of Data as the offset for TIFFReadEXIFDirectory
    toff_t offset = *((const uint64_t*)Data);
    TIFFReadEXIFDirectory(tiff, offset);

    // Clean up
    TIFFFreeDirectory(tiff);
    TIFFClose(tiff);

    return 0;
}