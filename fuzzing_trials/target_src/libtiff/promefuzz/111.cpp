// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// _TIFFmemcpy at tif_unix.c:355:6 in tiffio.h
// TIFFGetBitRevTable at tif_swab.c:305:22 in tiffio.h
// TIFFReverseBits at tif_swab.c:310:6 in tiffio.h
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFReadEncodedStrip at tif_read.c:543:10 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFReadGPSDirectory at tif_dirread.c:5564:5 in tiffio.h
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
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_111(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Test _TIFFmemcpy
    if (Size >= 2) {
        size_t halfSize = Size / 2;
        void *dest = malloc(halfSize);
        const void *src = static_cast<const void*>(Data + halfSize);
        _TIFFmemcpy(dest, src, static_cast<tmsize_t>(halfSize));
        free(dest);
    }

    // Test TIFFGetBitRevTable
    int reversed = Data[0] % 2;
    const unsigned char *bitRevTable = TIFFGetBitRevTable(reversed);

    // Test TIFFReverseBits
    uint8_t *copyData = static_cast<uint8_t*>(malloc(Size));
    if (copyData) {
        memcpy(copyData, Data, Size);
        TIFFReverseBits(copyData, static_cast<tmsize_t>(Size));
        free(copyData);
    }

    // Test TIFFWriteScanline
    TIFF *tif = TIFFOpen("./dummy_file", "w");
    if (tif) {
        void *buf = malloc(Size);
        if (buf) {
            memcpy(buf, Data, Size);
            uint32_t row = 0;
            uint16_t sample = 0;
            TIFFWriteScanline(tif, buf, row, sample);
            free(buf);
        }
        TIFFClose(tif);
    }

    // Test TIFFReadEncodedStrip
    tif = TIFFOpen("./dummy_file", "r");
    if (tif) {
        void *buf = malloc(Size);
        if (buf) {
            TIFFReadEncodedStrip(tif, 0, buf, static_cast<tmsize_t>(Size));
            free(buf);
        }
        TIFFClose(tif);
    }

    // Test TIFFReadGPSDirectory
    tif = TIFFOpen("./dummy_file", "r");
    if (tif) {
        toff_t diroff = 0;
        TIFFReadGPSDirectory(tif, diroff);
        TIFFClose(tif);
    }

    return 0;
}