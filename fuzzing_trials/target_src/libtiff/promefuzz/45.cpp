// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFCreateEXIFDirectory at tif_dir.c:1742:5 in tiffio.h
// TIFFCreateGPSDirectory at tif_dir.c:1752:5 in tiffio.h
// TIFFReadEXIFDirectory at tif_dirread.c:5556:5 in tiffio.h
// TIFFReadGPSDirectory at tif_dirread.c:5564:5 in tiffio.h
// TIFFLastDirectory at tif_dir.c:2239:5 in tiffio.h
// TIFFReadCustomDirectory at tif_dirread.c:5372:5 in tiffio.h
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
extern "C" {
#include <tiffio.h>
}

#include <cstdint>
#include <cstdio>

static TIFF* initializeTIFF(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return nullptr;
    fwrite(Data, 1, Size, file);
    fclose(file);

    TIFF *tif = TIFFOpen("./dummy_file", "r+");
    return tif;
}

extern "C" int LLVMFuzzerTestOneInput_45(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint64_t)) return 0; // Ensure enough data for offsets

    TIFF *tif = initializeTIFF(Data, Size);
    if (!tif) return 0;

    toff_t offset = *reinterpret_cast<const toff_t*>(Data);

    TIFFCreateEXIFDirectory(tif);
    TIFFCreateGPSDirectory(tif);
    TIFFReadEXIFDirectory(tif, offset);
    TIFFReadGPSDirectory(tif, offset);
    TIFFLastDirectory(tif);

    TIFFFieldArray *dummyInfoArray = nullptr; // Placeholder for actual info array
    TIFFReadCustomDirectory(tif, offset, dummyInfoArray);

    TIFFClose(tif);
    return 0;
}