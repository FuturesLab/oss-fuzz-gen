// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// _TIFFfree at tif_unix.c:349:6 in tiffio.h
// TIFFReadEncodedStrip at tif_read.c:543:10 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// _TIFFfree at tif_unix.c:349:6 in tiffio.h
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFDeferStrileArrayWriting at tif_dirwrite.c:268:5 in tiffio.h
// TIFFWriteCheck at tif_write.c:605:5 in tiffio.h
// TIFFWriteDirectory at tif_dirwrite.c:238:5 in tiffio.h
// TIFFSetDirectory at tif_dir.c:2067:5 in tiffio.h
// TIFFForceStrileArrayWriting at tif_flush.c:76:5 in tiffio.h
// TIFFSetDirectory at tif_dir.c:2067:5 in tiffio.h
// TIFFForceStrileArrayWriting at tif_flush.c:76:5 in tiffio.h
// TIFFSetDirectory at tif_dir.c:2067:5 in tiffio.h
// TIFFTileSize at tif_tile.c:253:10 in tiffio.h
// _TIFFmalloc at tif_unix.c:333:7 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFWriteEncodedTile at tif_write.c:414:10 in tiffio.h
// TIFFWriteEncodedStrip at tif_write.c:215:10 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// _TIFFfree at tif_unix.c:349:6 in tiffio.h
// TIFFReadEncodedTile at tif_read.c:963:10 in tiffio.h
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

static void WriteDummyFile(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
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