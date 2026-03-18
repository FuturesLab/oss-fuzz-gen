// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFWriteCheck at tif_write.c:605:5 in tiffio.h
// TIFFWriteDirectory at tif_dirwrite.c:238:5 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFReadFromUserBuffer at tif_read.c:1555:5 in tiffio.h
// TIFFReadEncodedTile at tif_read.c:963:10 in tiffio.h
// TIFFWriteEncodedStrip at tif_write.c:215:10 in tiffio.h
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
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>

static TIFF* createDummyTIFF() {
    TIFF* tif = TIFFOpen("./dummy_file", "w+");
    if (tif) {
        // Create a minimal valid TIFF structure
        TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, 1);
        TIFFSetField(tif, TIFFTAG_IMAGELENGTH, 1);
        TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 1);
        TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);
        TIFFSetField(tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
        TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
        TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
        TIFFWriteCheck(tif, 0, "createDummyTIFF");
        TIFFWriteDirectory(tif);
    }
    return tif;
}

extern "C" int LLVMFuzzerTestOneInput_121(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy TIFF file
    TIFF* tif = createDummyTIFF();
    if (!tif) return 0;

    // Prepare buffers
    void* inbuf = malloc(Size);
    if (!inbuf) {
        TIFFClose(tif);
        return 0;
    }
    memcpy(inbuf, Data, Size);

    void* outbuf = malloc(Size);
    if (!outbuf) {
        free(inbuf);
        TIFFClose(tif);
        return 0;
    }

    // Fuzz TIFFReadFromUserBuffer
    TIFFReadFromUserBuffer(tif, 0, inbuf, static_cast<tmsize_t>(Size), outbuf, static_cast<tmsize_t>(Size));

    // Fuzz TIFFReadEncodedTile
    TIFFReadEncodedTile(tif, 0, outbuf, static_cast<tmsize_t>(Size));

    // Fuzz TIFFPrintDirectory
    FILE* dummyFile = fopen("./dummy_file", "w+");
    if (dummyFile) {
        TIFFPrintDirectory(tif, dummyFile, 0);
        fclose(dummyFile);
    }

    // Fuzz TIFFWriteEncodedStrip
    TIFFWriteEncodedStrip(tif, 0, inbuf, static_cast<tmsize_t>(Size));

    // Fuzz TIFFStripSize
    TIFFStripSize(tif);

    // Fuzz TIFFReadEncodedStrip
    TIFFReadEncodedStrip(tif, 0, outbuf, static_cast<tmsize_t>(Size));

    // Cleanup
    free(inbuf);
    free(outbuf);
    TIFFClose(tif);
    unlink("./dummy_file");

    return 0;
}