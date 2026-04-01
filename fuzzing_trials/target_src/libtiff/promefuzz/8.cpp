// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFSetDirectory at tif_dir.c:2067:5 in tiffio.h
// TIFFCurrentDirOffset at tif_dir.c:2233:10 in tiffio.h
// TIFFNumberOfTiles at tif_tile.c:108:10 in tiffio.h
// TIFFTileSize64 at tif_tile.c:249:10 in tiffio.h
// TIFFReadEncodedTile at tif_read.c:963:10 in tiffio.h
// TIFFScanlineSize64 at tif_strip.c:257:10 in tiffio.h
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
#include <cstdlib>
#include <cstdio>
#include <cstring>

static void writeDummyFile(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Write the input data to a dummy file
    writeDummyFile(Data, Size);

    // Open the dummy TIFF file
    TIFF *tif = TIFFOpen("./dummy_file", "r");
    if (!tif) return 0;

    // Set directory
    tdir_t dirNum = Data[0] % 256; // Use the first byte of data as directory number
    TIFFSetDirectory(tif, dirNum);

    // Get current directory offset
    uint64_t dirOffset = TIFFCurrentDirOffset(tif);

    // Get number of tiles
    uint32_t numTiles = TIFFNumberOfTiles(tif);

    // Get tile size
    uint64_t tileSize = TIFFTileSize64(tif);

    // Prepare a buffer for reading tiles
    uint8_t *tileBuffer = (tileSize > 0) ? (uint8_t *)malloc(tileSize) : nullptr;

    // Read encoded tile
    if (tileBuffer) {
        for (uint32_t tile = 0; tile < numTiles; ++tile) {
            TIFFReadEncodedTile(tif, tile, tileBuffer, tileSize);
        }
        free(tileBuffer);
    }

    // Get scanline size
    uint64_t scanlineSize = TIFFScanlineSize64(tif);

    // Prepare a buffer for reading scanlines
    uint8_t *scanlineBuffer = (scanlineSize > 0) ? (uint8_t *)malloc(scanlineSize) : nullptr;

    // Read scanlines
    if (scanlineBuffer) {
        uint32_t rowsPerStrip = (uint32_t)TIFFNumberOfTiles(tif); // Using number of tiles as an arbitrary number of rows
        for (uint32_t row = 0; row < rowsPerStrip; ++row) {
            TIFFReadScanline(tif, scanlineBuffer, row, 0);
        }
        free(scanlineBuffer);
    }

    // Close the TIFF file
    TIFFClose(tif);

    return 0;
}