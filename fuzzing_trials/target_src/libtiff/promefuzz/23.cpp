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
// TIFFWriteDirectory at tif_dirwrite.c:238:5 in tiffio.h
// TIFFSetDirectory at tif_dir.c:2067:5 in tiffio.h
// TIFFCurrentDirOffset at tif_dir.c:2233:10 in tiffio.h
// TIFFSetDirectory at tif_dir.c:2067:5 in tiffio.h
// TIFFForceStrileArrayWriting at tif_flush.c:76:5 in tiffio.h
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
#include <cstdlib>
#include <cstdio>
#include <cstring>

static TIFF* createDummyTIFF(const char* filename) {
    TIFF* tif = TIFFOpen(filename, "w+");
    if (tif) {
        TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, 1);
        TIFFSetField(tif, TIFFTAG_IMAGELENGTH, 1);
        TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 1);
        TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);
        TIFFSetField(tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
        TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
        TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
        uint8_t buffer[1] = {0};
        TIFFWriteEncodedStrip(tif, 0, buffer, 1);
    }
    return tif;
}

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(tdir_t)) {
        return 0; // Not enough data to proceed
    }

    const char* filename = "./dummy_file";
    TIFF* tif = createDummyTIFF(filename);
    if (!tif) {
        return 0; // Failed to create a dummy TIFF
    }

    // Write the current directory to disk
    TIFFWriteDirectory(tif);

    // Set the directory using the first bytes of Data as the directory number
    tdir_t dirn = *reinterpret_cast<const tdir_t*>(Data);
    TIFFSetDirectory(tif, dirn);

    // Get the current directory offset
    TIFFCurrentDirOffset(tif);

    // Set the directory again
    TIFFSetDirectory(tif, dirn);

    // Force strile array writing
    TIFFForceStrileArrayWriting(tif);

    // Flush data to disk
    TIFFFlushData(tif);

    TIFFClose(tif);
    return 0;
}