// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFScanlineSize at tif_strip.c:343:10 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFSetSubDirectory at tif_dir.c:2163:5 in tiffio.h
// TIFFIsBigTIFF at tif_open.c:912:5 in tiffio.h
// TIFFReadDirectory at tif_dirread.c:4323:5 in tiffio.h
// TIFFReadEXIFDirectory at tif_dirread.c:5556:5 in tiffio.h
// TIFFTileSize64 at tif_tile.c:249:10 in tiffio.h
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
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_87(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint64_t)) {
        return 0; // Not enough data to proceed
    }

    // Create a dummy file to work with
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tif = TIFFOpen("./dummy_file", "r");
    if (!tif) {
        return 0;
    }

    // Prepare a buffer for TIFFReadScanline
    uint32_t row = 0;
    uint16_t sample = 0;
    tmsize_t scanline_size = TIFFScanlineSize(tif);
    void *buf = malloc(scanline_size);
    if (!buf) {
        TIFFClose(tif);
        return 0;
    }

    // Extract an offset for TIFFSetSubDirectory and TIFFReadEXIFDirectory
    uint64_t offset;
    memcpy(&offset, Data, sizeof(uint64_t));

    // Fuzz TIFFSetSubDirectory
    TIFFSetSubDirectory(tif, offset);

    // Fuzz TIFFIsBigTIFF
    TIFFIsBigTIFF(tif);

    // Fuzz TIFFReadDirectory
    TIFFReadDirectory(tif);

    // Fuzz TIFFReadScanline
    TIFFReadScanline(tif, buf, row, sample);

    // Fuzz TIFFReadEXIFDirectory
    TIFFReadEXIFDirectory(tif, offset);

    // Fuzz TIFFTileSize64
    TIFFTileSize64(tif);

    // Cleanup
    free(buf);
    TIFFClose(tif);

    return 0;
}