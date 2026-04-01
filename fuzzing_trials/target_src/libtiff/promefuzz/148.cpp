// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFIsTiled at tif_open.c:864:5 in tiffio.h
// TIFFWriteCheck at tif_write.c:605:5 in tiffio.h
// TIFFWriteDirectory at tif_dirwrite.c:238:5 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFReadFromUserBuffer at tif_read.c:1555:5 in tiffio.h
// TIFFReadEncodedTile at tif_read.c:963:10 in tiffio.h
// TIFFScanlineSize at tif_strip.c:343:10 in tiffio.h
// TIFFStripSize at tif_strip.c:204:10 in tiffio.h
// TIFFReadEncodedStrip at tif_read.c:543:10 in tiffio.h
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
    if (tif) {
        TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, 1);
        TIFFSetField(tif, TIFFTAG_IMAGELENGTH, 1);
        TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 1);
        TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);
        TIFFSetField(tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
        TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
        TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
        TIFFWriteCheck(tif, TIFFIsTiled(tif), "initializeDummyTIFF");
        TIFFWriteDirectory(tif);
        TIFFClose(tif);
    }
    return TIFFOpen("./dummy_file", "r");
}

extern "C" int LLVMFuzzerTestOneInput_148(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    TIFF* tif = initializeDummyTIFF();
    if (!tif) return 0;

    uint32_t index = Data[0] % 10; // Arbitrary index for strip/tile
    tmsize_t bufferSize = 1024;
    void* buffer = malloc(bufferSize);
    if (!buffer) {
        TIFFClose(tif);
        return 0;
    }

    // Fuzz TIFFReadFromUserBuffer
    TIFFReadFromUserBuffer(tif, index, (void*)Data, Size, buffer, bufferSize);

    // Fuzz TIFFReadEncodedTile
    TIFFReadEncodedTile(tif, index, buffer, bufferSize);

    // Fuzz TIFFPrintDirectory
    FILE* dummyFile = fopen("./dummy_file", "w");
    if (dummyFile) {
        TIFFPrintDirectory(tif, dummyFile, 0);
        fclose(dummyFile);
    }

    // Fuzz TIFFScanlineSize
    TIFFScanlineSize(tif);

    // Fuzz TIFFStripSize
    TIFFStripSize(tif);

    // Fuzz TIFFReadEncodedStrip
    TIFFReadEncodedStrip(tif, index, buffer, bufferSize);

    free(buffer);
    TIFFClose(tif);
    return 0;
}