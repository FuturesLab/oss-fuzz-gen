// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFGetStrileByteCount at tif_dirread.c:8514:10 in tiffio.h
// TIFFGetStrileByteCountWithErr at tif_dirread.c:8521:10 in tiffio.h
// TIFFScanlineSize64 at tif_strip.c:257:10 in tiffio.h
// TIFFGetStrileOffset at tif_dirread.c:8497:10 in tiffio.h
// TIFFRawStripSize64 at tif_strip.c:153:10 in tiffio.h
// TIFFStripSize64 at tif_strip.c:196:10 in tiffio.h
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

static TIFF* initializeTIFF(const uint8_t* Data, size_t Size) {
    FILE* file = fopen("./dummy_file", "wb");
    if (!file) return nullptr;
    fwrite(Data, 1, Size, file);
    fclose(file);

    return TIFFOpen("./dummy_file", "r");
}

extern "C" int LLVMFuzzerTestOneInput_45(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t)) return 0;
    
    TIFF* tif = initializeTIFF(Data, Size);
    if (!tif) return 0;

    uint32_t strileIndex = *(reinterpret_cast<const uint32_t*>(Data));

    // Test TIFFGetStrileByteCount
    uint64_t byteCount = TIFFGetStrileByteCount(tif, strileIndex);

    // Test TIFFGetStrileByteCountWithErr
    int err = 0;
    uint64_t byteCountWithErr = TIFFGetStrileByteCountWithErr(tif, strileIndex, &err);

    // Test TIFFScanlineSize64
    uint64_t scanlineSize = TIFFScanlineSize64(tif);

    // Test TIFFGetStrileOffset
    uint64_t strileOffset = TIFFGetStrileOffset(tif, strileIndex);

    // Test TIFFRawStripSize64
    uint64_t rawStripSize = TIFFRawStripSize64(tif, strileIndex);

    // Test TIFFStripSize64
    uint64_t stripSize = TIFFStripSize64(tif);

    TIFFClose(tif);
    return 0;
}