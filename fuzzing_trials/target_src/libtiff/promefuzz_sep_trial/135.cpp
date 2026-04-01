// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFWriteEncodedStrip at tif_write.c:215:10 in tiffio.h
// TIFFSetupStrips at tif_write.c:553:5 in tiffio.h
// TIFFComputeStrip at tif_strip.c:35:10 in tiffio.h
// TIFFIsTiled at tif_open.c:864:5 in tiffio.h
// TIFFDefaultStripSize at tif_strip.c:218:10 in tiffio.h
// TIFFFileName at tif_open.c:803:13 in tiffio.h
// TIFFDefaultTileSize at tif_tile.c:267:6 in tiffio.h
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
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "tiffio.h"

static TIFF* createDummyTIFF(const char* filename) {
    TIFF* tif = TIFFOpen(filename, "w");
    if (tif) {
        TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, 1);
        TIFFSetField(tif, TIFFTAG_IMAGELENGTH, 1);
        TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 1);
        TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);
        TIFFSetField(tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
        TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
        TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
        uint8_t data[1] = {0};
        TIFFWriteEncodedStrip(tif, 0, data, 1);
    }
    return tif;
}

extern "C" int LLVMFuzzerTestOneInput_135(const uint8_t *Data, size_t Size) {
    // Step 1: Prepare the environment
    FILE* file = fopen("./dummy_file", "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    TIFF* tif = createDummyTIFF("./dummy_file");
    if (!tif) return 0;

    // Step 2: Invoke TIFFSetupStrips
    TIFFSetupStrips(tif);

    // Step 3: Invoke TIFFComputeStrip
    uint32_t row = 0;
    uint16_t sample = 0;
    TIFFComputeStrip(tif, row, sample);

    // Step 4: Invoke TIFFIsTiled
    TIFFIsTiled(tif);

    // Step 5: Invoke TIFFDefaultStripSize
    uint32_t request = 0;
    TIFFDefaultStripSize(tif, request);

    // Step 6: Invoke TIFFFileName
    TIFFFileName(tif);

    // Step 7: Invoke TIFFDefaultTileSize
    uint32_t width = 0, height = 0;
    TIFFDefaultTileSize(tif, &width, &height);

    // Cleanup
    TIFFClose(tif);
    remove("./dummy_file");

    return 0;
}