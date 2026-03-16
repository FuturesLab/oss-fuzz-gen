// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFSetSubDirectory at tif_dir.c:2163:5 in tiffio.h
// TIFFReadGPSDirectory at tif_dirread.c:5564:5 in tiffio.h
// TIFFReadDirectory at tif_dirread.c:4323:5 in tiffio.h
// TIFFCreateGPSDirectory at tif_dir.c:1752:5 in tiffio.h
// TIFFReadEXIFDirectory at tif_dirread.c:5556:5 in tiffio.h
// TIFFLastDirectory at tif_dir.c:2239:5 in tiffio.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <tiffio.h>

static TIFF* initializeTiff(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return nullptr;
    fwrite(Data, 1, Size, file);
    fclose(file);

    TIFF *tif = TIFFOpen("./dummy_file", "r+");
    return tif;
}

static void cleanupTiff(TIFF *tif) {
    if (tif) {
        TIFFClose(tif);
    }
}

extern "C" int LLVMFuzzerTestOneInput_74(const uint8_t *Data, size_t Size) {
    if (Size < 8) return 0; // Ensure enough data for meaningful offsets

    TIFF *tif = initializeTiff(Data, Size);
    if (!tif) return 0;

    uint64_t offset = *reinterpret_cast<const uint64_t*>(Data);
    toff_t toff = static_cast<toff_t>(offset);

    // Explore TIFFSetSubDirectory
    TIFFSetSubDirectory(tif, offset);

    // Explore TIFFReadGPSDirectory
    TIFFReadGPSDirectory(tif, toff);

    // Explore TIFFReadDirectory
    TIFFReadDirectory(tif);

    // Explore TIFFCreateGPSDirectory
    TIFFCreateGPSDirectory(tif);

    // Explore TIFFReadEXIFDirectory
    TIFFReadEXIFDirectory(tif, toff);

    // Explore TIFFLastDirectory
    TIFFLastDirectory(tif);

    cleanupTiff(tif);
    return 0;
}