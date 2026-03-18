// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFDeferStrileArrayWriting at tif_dirwrite.c:268:5 in tiffio.h
// LogL16toY at tif_luv.c:801:5 in tiffio.h
// LogL10toY at tif_luv.c:883:5 in tiffio.h
// TIFFFlushData at tif_flush.c:146:5 in tiffio.h
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

static TIFF* createDummyTIFF() {
    TIFF* tif = TIFFOpen("./dummy_file", "w+");
    if (tif) {
        TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, 1);
        TIFFSetField(tif, TIFFTAG_IMAGELENGTH, 1);
        TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 1);
        TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);
        TIFFSetField(tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
        TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
        TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
    }
    return tif;
}

extern "C" int LLVMFuzzerTestOneInput_142(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare a TIFF object
    TIFF* tif = createDummyTIFF();
    if (!tif) return 0;

    // Fuzz TIFFDeferStrileArrayWriting
    TIFFDeferStrileArrayWriting(tif);

    // Fuzz LogL16toY
    int logL16Value = static_cast<int>(Data[0]);
    LogL16toY(logL16Value);

    // Fuzz LogL10toY
    int logL10Value = static_cast<int>(Data[0]);
    LogL10toY(logL10Value);

    // Fuzz TIFFFlushData
    TIFFFlushData(tif);

    // Fuzz LogL16fromY
    double luminance = static_cast<double>(Data[0]) / 255.0;
    LogL16fromY(luminance, static_cast<int>(Data[0]));

    // Fuzz LogL10fromY
    LogL10fromY(luminance, static_cast<int>(Data[0]));

    // Clean up
    TIFFClose(tif);
    return 0;
}