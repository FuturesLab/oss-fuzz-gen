// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFComputeStrip at tif_strip.c:35:10 in tiffio.h
// TIFFTileSize at tif_tile.c:253:10 in tiffio.h
// _TIFFmalloc at tif_unix.c:333:7 in tiffio.h
// TIFFReadTile at tif_read.c:950:10 in tiffio.h
// _TIFFfree at tif_unix.c:349:6 in tiffio.h
// TIFFCurrentTile at tif_open.c:884:10 in tiffio.h
// TIFFComputeTile at tif_tile.c:35:10 in tiffio.h
// TIFFDefaultTileSize at tif_tile.c:267:6 in tiffio.h
// TIFFNumberOfTiles at tif_tile.c:108:10 in tiffio.h
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

static TIFF* initializeDummyTIFF() {
    TIFF* tif = TIFFOpen("./dummy_file", "w");
    if (!tif) {
        return nullptr;
    }
    TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, 256);
    TIFFSetField(tif, TIFFTAG_IMAGELENGTH, 256);
    TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 3);
    TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);
    TIFFSetField(tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
    TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
    TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
    TIFFSetField(tif, TIFFTAG_ROWSPERSTRIP, 16);
    return tif;
}

extern "C" int LLVMFuzzerTestOneInput_70(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t) * 2 + sizeof(uint16_t)) {
        return 0;
    }

    TIFF* tif = initializeDummyTIFF();
    if (!tif) {
        return 0;
    }

    uint32_t x = *reinterpret_cast<const uint32_t*>(Data);
    uint32_t y = *reinterpret_cast<const uint32_t*>(Data + sizeof(uint32_t));
    uint32_t z = 0;
    uint16_t s = *reinterpret_cast<const uint16_t*>(Data + sizeof(uint32_t) * 2);

    // Fuzz TIFFComputeStrip
    TIFFComputeStrip(tif, y, s);

    // Fuzz TIFFReadTile
    tmsize_t tileSize = TIFFTileSize(tif);
    void* buffer = _TIFFmalloc(tileSize);
    if (buffer) {
        TIFFReadTile(tif, buffer, x, y, z, s);
        _TIFFfree(buffer);
    }

    // Fuzz TIFFCurrentTile
    TIFFCurrentTile(tif);

    // Fuzz TIFFComputeTile
    TIFFComputeTile(tif, x, y, z, s);

    // Fuzz TIFFDefaultTileSize
    uint32_t width = 0, height = 0;
    TIFFDefaultTileSize(tif, &width, &height);

    // Fuzz TIFFNumberOfTiles
    TIFFNumberOfTiles(tif);

    TIFFClose(tif);
    return 0;
}