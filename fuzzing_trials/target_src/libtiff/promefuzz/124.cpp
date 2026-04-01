// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFCurrentDirOffset at tif_dir.c:2233:10 in tiffio.h
// TIFFReadDirectory at tif_dirread.c:4323:5 in tiffio.h
// TIFFScanlineSize64 at tif_strip.c:257:10 in tiffio.h
// TIFFTileSize64 at tif_tile.c:249:10 in tiffio.h
// TIFFSwabLong8 at tif_swab.c:60:6 in tiffio.h
// TIFFSetSubDirectory at tif_dir.c:2163:5 in tiffio.h
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

static TIFF* initializeTIFF(const uint8_t* Data, size_t Size) {
    FILE* file = fopen("./dummy_file", "wb");
    if (!file) return nullptr;
    
    fwrite(Data, 1, Size, file);
    fclose(file);

    TIFF* tif = TIFFOpen("./dummy_file", "r");
    return tif;
}

extern "C" int LLVMFuzzerTestOneInput_124(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint64_t)) return 0;

    TIFF* tif = initializeTIFF(Data, Size);
    if (!tif) return 0;

    // Test TIFFCurrentDirOffset
    uint64_t dirOffset = TIFFCurrentDirOffset(tif);

    // Test TIFFReadDirectory
    int readDirResult = TIFFReadDirectory(tif);

    // Test TIFFScanlineSize64
    uint64_t scanlineSize = TIFFScanlineSize64(tif);

    // Test TIFFTileSize64
    uint64_t tileSize = TIFFTileSize64(tif);

    // Test TIFFSwabLong8
    uint64_t value;
    memcpy(&value, Data, sizeof(uint64_t));
    TIFFSwabLong8(&value);

    // Test TIFFSetSubDirectory
    uint64_t subDirOffset;
    memcpy(&subDirOffset, Data, sizeof(uint64_t));
    int setSubDirResult = TIFFSetSubDirectory(tif, subDirOffset);

    // Cleanup
    TIFFClose(tif);
    return 0;
}