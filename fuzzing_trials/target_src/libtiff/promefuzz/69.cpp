// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFRasterScanlineSize64 at tif_strip.c:357:10 in tiffio.h
// TIFFVStripSize64 at tif_strip.c:88:10 in tiffio.h
// TIFFVStripSize64 at tif_strip.c:88:10 in tiffio.h
// TIFFVTileSize64 at tif_tile.c:188:10 in tiffio.h
// TIFFVTileSize64 at tif_tile.c:188:10 in tiffio.h
// TIFFScanlineSize64 at tif_strip.c:257:10 in tiffio.h
// TIFFTileSize64 at tif_tile.c:249:10 in tiffio.h
// TIFFStripSize64 at tif_strip.c:196:10 in tiffio.h
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

static TIFF* createDummyTIFF(const uint8_t *Data, size_t Size) {
    FILE *file = std::fopen("./dummy_file", "wb");
    if (!file) return nullptr;
    if (fwrite(Data, 1, Size, file) != Size) {
        std::fclose(file);
        return nullptr;
    }
    std::fclose(file);

    TIFF *tif = TIFFOpen("./dummy_file", "r");
    return tif;
}

static void cleanupTIFF(TIFF *tif) {
    if (tif) {
        TIFFClose(tif);
    }
}

extern "C" int LLVMFuzzerTestOneInput_69(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    TIFF *tif = createDummyTIFF(Data, Size);
    if (!tif) return 0;

    uint64_t result;

    // Test TIFFRasterScanlineSize64
    result = TIFFRasterScanlineSize64(tif);
    (void)result; // Prevent unused variable warning

    // Test TIFFVStripSize64 with various nrows
    result = TIFFVStripSize64(tif, 1);
    (void)result;
    result = TIFFVStripSize64(tif, static_cast<uint32_t>(-1));
    (void)result;

    // Test TIFFVTileSize64 with various nrows
    result = TIFFVTileSize64(tif, 1);
    (void)result;
    result = TIFFVTileSize64(tif, static_cast<uint32_t>(-1));
    (void)result;

    // Test TIFFScanlineSize64
    result = TIFFScanlineSize64(tif);
    (void)result;

    // Test TIFFTileSize64
    result = TIFFTileSize64(tif);
    (void)result;

    // Test TIFFStripSize64
    result = TIFFStripSize64(tif);
    (void)result;

    cleanupTIFF(tif);
    return 0;
}