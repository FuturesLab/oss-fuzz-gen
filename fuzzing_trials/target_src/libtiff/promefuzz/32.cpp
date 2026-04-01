// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFGetStrileOffset at tif_dirread.c:8497:10 in tiffio.h
// TIFFGetStrileByteCountWithErr at tif_dirread.c:8521:10 in tiffio.h
// TIFFGetStrileByteCount at tif_dirread.c:8514:10 in tiffio.h
// TIFFScanlineSize64 at tif_strip.c:257:10 in tiffio.h
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
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t)) {
        return 0;
    }

    // Write the input data to a dummy file
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

    // Extract a strile index from the input data
    uint32_t strile = 0;
    memcpy(&strile, Data, sizeof(uint32_t));

    // Fuzz TIFFGetStrileOffset
    uint64_t offset = TIFFGetStrileOffset(tif, strile);

    // Fuzz TIFFGetStrileByteCountWithErr
    int err = 0;
    uint64_t byteCountWithErr = TIFFGetStrileByteCountWithErr(tif, strile, &err);

    // Fuzz TIFFGetStrileByteCount
    uint64_t byteCount = TIFFGetStrileByteCount(tif, strile);

    // Fuzz TIFFScanlineSize64
    uint64_t scanlineSize = TIFFScanlineSize64(tif);

    // Fuzz TIFFRawStripSize64
    uint64_t rawStripSize = TIFFRawStripSize64(tif, strile);

    // Fuzz TIFFStripSize64
    uint64_t stripSize = TIFFStripSize64(tif);

    // Cleanup
    TIFFClose(tif);

    return 0;
}