#include <iostream>
#include "sstream"
#include <string>
#include <vector>
#include "cstring"
#include "cstdlib"
#include <cstdio>
#include "cstdint"
#include <cstddef>
#include "tiffio.h"
#include "cstdint"
#include "cstdlib"
#include <cstdio>
#include "cstring"

static void WriteDummyFile(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare dummy file for TIFFOpen
    WriteDummyFile(Data, Size);

    // Open TIFF file
    TIFF *tif = TIFFOpen("./dummy_file", "w");
    if (!tif) return 0;

    // Set fields in TIFF
    TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, 256);
    TIFFSetField(tif, TIFFTAG_IMAGELENGTH, 256);
    TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);
    TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 1);
    TIFFSetField(tif, TIFFTAG_ROWSPERSTRIP, 16);
    TIFFSetField(tif, TIFFTAG_COMPRESSION, COMPRESSION_NONE);
    TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
    TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);

    // Defer strile array writing
    TIFFDeferStrileArrayWriting(tif);

    // Check writing capability
    TIFFWriteCheck(tif, 1, "WriteCheck");

    // Write directory
    TIFFWriteDirectory(tif);

    // Set directory
    TIFFSetDirectory(tif, 0);

    // Force strile array writing
    TIFFForceStrileArrayWriting(tif);

    // Set directory again
    TIFFSetDirectory(tif, 0);

    // Force strile array writing again
    TIFFForceStrileArrayWriting(tif);

    // Set directory again
    TIFFSetDirectory(tif, 0);

    // Prepare buffer for encoded tile/strip
    tmsize_t bufSize = TIFFTileSize(tif);
    void *buffer = _TIFFmalloc(bufSize);
    if (!buffer) {
        TIFFClose(tif);
        return 0;
    }
    memset(buffer, 0, bufSize);

    // Write encoded tile
    TIFFWriteEncodedTile(tif, 0, buffer, bufSize);

    // Write encoded strip
    TIFFWriteEncodedStrip(tif, 0, buffer, bufSize);

    // Close TIFF
    TIFFClose(tif);

    // Open TIFF file for reading
    tif = TIFFOpen("./dummy_file", "r");
    if (!tif) {
        _TIFFfree(buffer);
        return 0;
    }

    // Read encoded tile
    TIFFReadEncodedTile(tif, 0, buffer, bufSize);

    // Close TIFF
    TIFFClose(tif);

    // Open TIFF file again for reading
    tif = TIFFOpen("./dummy_file", "r");
    if (!tif) {
        _TIFFfree(buffer);
        return 0;
    }

    // Read encoded strip
    TIFFReadEncodedStrip(tif, 0, buffer, bufSize);

    // Final close
    TIFFClose(tif);

    // Free allocated buffer
    _TIFFfree(buffer);

    return 0;
}