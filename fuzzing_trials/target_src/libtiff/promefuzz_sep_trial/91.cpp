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
// TIFFWriteEncodedStrip at tif_write.c:215:10 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFReadFromUserBuffer at tif_read.c:1555:5 in tiffio.h
// TIFFStripSize at tif_strip.c:204:10 in tiffio.h
// TIFFReadEncodedTile at tif_read.c:963:10 in tiffio.h
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

static TIFF* createDummyTIFF(const char* filename) {
    TIFF* tif = TIFFOpen(filename, "w");
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

extern "C" int LLVMFuzzerTestOneInput_91(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    TIFF* tif = createDummyTIFF("./dummy_file");
    if (!tif) return 0;

    // Buffer for operations
    void* buffer = malloc(Size);
    if (!buffer) {
        TIFFClose(tif);
        return 0;
    }
    memcpy(buffer, Data, Size);

    // Fuzzing TIFFWriteEncodedStrip
    TIFFWriteEncodedStrip(tif, 0, buffer, Size);

    // Fuzzing TIFFReadFromUserBuffer
    if (TIFFSetField(tif, TIFFTAG_TILELENGTH, 1) && TIFFSetField(tif, TIFFTAG_TILEWIDTH, 1)) {
        TIFFReadFromUserBuffer(tif, 0, buffer, Size, buffer, Size);
    }

    // Fuzzing TIFFStripSize
    TIFFStripSize(tif);

    // Fuzzing TIFFReadEncodedTile
    TIFFReadEncodedTile(tif, 0, buffer, Size);

    // Fuzzing TIFFReadEncodedStrip
    TIFFReadEncodedStrip(tif, 0, buffer, Size);

    // Fuzzing TIFFPrintDirectory
    FILE* dummyOutput = fopen("/dev/null", "w");
    if (dummyOutput) {
        TIFFPrintDirectory(tif, dummyOutput, 0);
        fclose(dummyOutput);
    }

    free(buffer);
    TIFFClose(tif);

    return 0;
}