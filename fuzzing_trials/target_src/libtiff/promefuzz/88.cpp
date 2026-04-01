// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFReadEncodedTile at tif_read.c:963:10 in tiffio.h
// TIFFRawStripSize at tif_strip.c:168:10 in tiffio.h
// TIFFVStripSize at tif_strip.c:142:10 in tiffio.h
// TIFFVTileSize at tif_tile.c:238:10 in tiffio.h
// TIFFStripSize at tif_strip.c:204:10 in tiffio.h
// TIFFTileRowSize at tif_tile.c:177:10 in tiffio.h
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

static TIFF* createDummyTIFF(const uint8_t *Data, size_t Size) {
    FILE* file = fopen("./dummy_file", "wb");
    if (!file) return nullptr;
    fwrite(Data, 1, Size, file);
    fclose(file);

    TIFF* tif = TIFFOpen("./dummy_file", "r");
    return tif;
}

extern "C" int LLVMFuzzerTestOneInput_88(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    TIFF* tif = createDummyTIFF(Data, Size);
    if (!tif) return 0;

    uint32_t index = Data[0] % 256; // Use the first byte for index
    tmsize_t bufferSize = 1024;
    void* buffer = malloc(bufferSize);
    if (!buffer) {
        TIFFClose(tif);
        return 0;
    }

    // Fuzz TIFFReadEncodedTile
    TIFFReadEncodedTile(tif, index, buffer, bufferSize);

    // Fuzz TIFFRawStripSize
    TIFFRawStripSize(tif, index);

    // Fuzz TIFFVStripSize
    TIFFVStripSize(tif, index);

    // Fuzz TIFFVTileSize
    TIFFVTileSize(tif, index);

    // Fuzz TIFFStripSize
    TIFFStripSize(tif);

    // Fuzz TIFFTileRowSize
    TIFFTileRowSize(tif);

    free(buffer);
    TIFFClose(tif);
    return 0;
}