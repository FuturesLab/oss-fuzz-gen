// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFWriteCustomDirectory at tif_dirwrite.c:303:5 in tiffio.h
// TIFFCreateEXIFDirectory at tif_dir.c:1742:5 in tiffio.h
// TIFFCreateGPSDirectory at tif_dir.c:1752:5 in tiffio.h
// TIFFWriteDirectory at tif_dirwrite.c:238:5 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstring>

static TIFF *createDummyTIFF(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) return nullptr;
    fclose(file);
    return TIFFOpen(filename, "r+");
}

extern "C" int LLVMFuzzerTestOneInput_67(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint64_t)) return 0;

    const char *filename = "./dummy_file";
    TIFF *tif = createDummyTIFF(filename);
    if (!tif) return 0;

    uint64_t dirOffset = 0;

    // Attempt to write a custom directory
    TIFFWriteCustomDirectory(tif, &dirOffset);

    // Attempt to create an EXIF directory
    TIFFCreateEXIFDirectory(tif);

    // Attempt to create a GPS directory
    TIFFCreateGPSDirectory(tif);

    // Attempt to write the current directory
    TIFFWriteDirectory(tif);

    // Cleanup
    TIFFClose(tif);
    return 0;
}