// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFWriteDirectory at tif_dirwrite.c:238:5 in tiffio.h
// TIFFReverseBits at tif_swab.c:310:6 in tiffio.h
// TIFFReadGPSDirectory at tif_dirread.c:5564:5 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// _TIFFmemcpy at tif_unix.c:355:6 in tiffio.h
// TIFFGetBitRevTable at tif_swab.c:305:22 in tiffio.h
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
#include <cstdlib>
#include <cstring>
#include <cstdio>

static TIFF* create_dummy_tiff() {
    TIFF* tif = TIFFOpen("./dummy_file", "w+");
    if (tif) {
        // Set up a minimal TIFF directory for testing
        TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, 1);
        TIFFSetField(tif, TIFFTAG_IMAGELENGTH, 1);
        TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 1);
        TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);
        TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
        TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
        TIFFWriteDirectory(tif);
    }
    return tif;
}

extern "C" int LLVMFuzzerTestOneInput_132(const uint8_t *Data, size_t Size) {
    // Prepare dummy TIFF file
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }

    // TIFFReverseBits
    if (Size > 0) {
        uint8_t *buffer = static_cast<uint8_t *>(malloc(Size));
        if (buffer) {
            memcpy(buffer, Data, Size);
            TIFFReverseBits(buffer, static_cast<tmsize_t>(Size));
            free(buffer);
        }
    }

    // TIFFReadGPSDirectory
    TIFF *tif = create_dummy_tiff();
    if (tif) {
        toff_t diroff = 0;
        TIFFReadGPSDirectory(tif, diroff);
        TIFFClose(tif);
    }

    // TIFFWriteScanline
    tif = create_dummy_tiff();
    if (tif) {
        uint8_t *scanline = static_cast<uint8_t *>(malloc(Size));
        if (scanline) {
            memcpy(scanline, Data, Size);
            TIFFWriteScanline(tif, scanline, 0, 0);
            free(scanline);
        }
        TIFFClose(tif);
    }

    // _TIFFmemcpy
    if (Size > 0) {
        void *dest = malloc(Size);
        if (dest) {
            _TIFFmemcpy(dest, Data, static_cast<tmsize_t>(Size));
            free(dest);
        }
    }

    // TIFFGetBitRevTable
    const unsigned char *bitRevTable = TIFFGetBitRevTable(Size % 2);

    // TIFFReadEncodedStrip
    tif = create_dummy_tiff();
    if (tif) {
        uint8_t *buffer = static_cast<uint8_t *>(malloc(Size));
        if (buffer) {
            TIFFReadEncodedStrip(tif, 0, buffer, static_cast<tmsize_t>(Size));
            free(buffer);
        }
        TIFFClose(tif);
    }

    return 0;
}