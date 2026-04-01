// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFWriteCustomDirectory at tif_dirwrite.c:303:5 in tiffio.h
// TIFFCheckpointDirectory at tif_dirwrite.c:292:5 in tiffio.h
// TIFFWriteDirectory at tif_dirwrite.c:238:5 in tiffio.h
// TIFFRewriteDirectory at tif_dirwrite.c:483:5 in tiffio.h
// TIFFDeferStrileArrayWriting at tif_dirwrite.c:268:5 in tiffio.h
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
#include <iostream>

static TIFF* initializeTIFF() {
    // Open a TIFF file for writing
    TIFF *tif = TIFFOpen("./dummy_file", "w");
    if (!tif) {
        std::cerr << "Failed to open TIFF file.\n";
        return nullptr;
    }
    // Set some basic TIFF fields (dummy values for fuzzing)
    TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, 1);
    TIFFSetField(tif, TIFFTAG_IMAGELENGTH, 1);
    TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 1);
    TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);
    TIFFSetField(tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
    TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
    TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);

    return tif;
}

static void cleanupTIFF(TIFF* tif) {
    if (tif) {
        TIFFClose(tif);
    }
}

extern "C" int LLVMFuzzerTestOneInput_156(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    TIFF *tif = initializeTIFF();
    if (!tif) return 0;

    uint64_t offset = 0;
    void *buf = malloc(Size);
    if (!buf) {
        cleanupTIFF(tif);
        return 0;
    }
    memcpy(buf, Data, Size);

    // Fuzz TIFFWriteCustomDirectory
    if (Size > 0) {
        TIFFWriteCustomDirectory(tif, &offset);
    }

    // Fuzz TIFFCheckpointDirectory
    TIFFCheckpointDirectory(tif);

    // Fuzz TIFFWriteDirectory
    TIFFWriteDirectory(tif);

    // Fuzz TIFFRewriteDirectory
    TIFFRewriteDirectory(tif);

    // Fuzz TIFFWriteScanline
    TIFFWriteScanline(tif, buf, 0, 0);

    // Fuzz TIFFDeferStrileArrayWriting
    TIFFDeferStrileArrayWriting(tif);

    free(buf);
    cleanupTIFF(tif);

    return 0;
}