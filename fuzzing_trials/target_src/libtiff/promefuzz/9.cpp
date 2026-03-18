// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFIsBigTIFF at tif_open.c:912:5 in tiffio.h
// TIFFGetSeekProc at tif_open.c:927:14 in tiffio.h
// TIFFGetReadProc at tif_open.c:917:19 in tiffio.h
// TIFFIsByteSwapped at tif_open.c:889:5 in tiffio.h
// TIFFSwabShort at tif_swab.c:33:6 in tiffio.h
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
#include <cstdlib>
#include <cstring>

static TIFF* initializeTIFF(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return nullptr;

    fwrite(Data, 1, Size, file);
    fclose(file);

    return TIFFOpen("./dummy_file", "r");
}

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint16_t)) {
        return 0;
    }

    TIFF *tiff = initializeTIFF(Data, Size);
    if (!tiff) {
        return 0;
    }

    // Test TIFFIsBigTIFF
    (void)TIFFIsBigTIFF(tiff);

    // Test TIFFGetSeekProc
    (void)TIFFGetSeekProc(tiff);

    // Test TIFFGetReadProc
    (void)TIFFGetReadProc(tiff);

    // Test TIFFIsByteSwapped
    (void)TIFFIsByteSwapped(tiff);

    // Test TIFFSwabShort
    uint16_t value;
    memcpy(&value, Data, sizeof(uint16_t));
    TIFFSwabShort(&value);

    TIFFClose(tiff);
    return 0;
}