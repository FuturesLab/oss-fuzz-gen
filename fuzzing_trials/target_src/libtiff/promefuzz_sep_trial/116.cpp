// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// _TIFFmalloc at tif_unix.c:333:7 in tiffio.h
// _TIFFmemcpy at tif_unix.c:355:6 in tiffio.h
// TIFFWriteEncodedStrip at tif_write.c:215:10 in tiffio.h
// _TIFFfree at tif_unix.c:349:6 in tiffio.h
// _TIFFmalloc at tif_unix.c:333:7 in tiffio.h
// _TIFFmemcpy at tif_unix.c:355:6 in tiffio.h
// TIFFReverseBits at tif_swab.c:310:6 in tiffio.h
// _TIFFfree at tif_unix.c:349:6 in tiffio.h
// TIFFStripSize at tif_strip.c:204:10 in tiffio.h
// _TIFFmalloc at tif_unix.c:333:7 in tiffio.h
// TIFFReadEncodedStrip at tif_read.c:543:10 in tiffio.h
// _TIFFfree at tif_unix.c:349:6 in tiffio.h
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

extern "C" int LLVMFuzzerTestOneInput_116(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t)) {
        return 0;
    }

    // Create a dummy TIFF file
    FILE *file = fopen("./dummy_file", "wb+");
    if (!file) {
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    TIFF *tif = TIFFOpen("./dummy_file", "r+");
    if (!tif) {
        return 0;
    }

    // Fuzz TIFFWriteEncodedStrip
    uint32_t strip = *reinterpret_cast<const uint32_t *>(Data);
    void *encodedData = _TIFFmalloc(Size);
    if (encodedData) {
        _TIFFmemcpy(encodedData, Data, Size);
        TIFFWriteEncodedStrip(tif, strip, encodedData, static_cast<tmsize_t>(Size));
        _TIFFfree(encodedData);
    }

    // Fuzz TIFFReverseBits
    uint8_t *bitData = static_cast<uint8_t *>(_TIFFmalloc(Size));
    if (bitData) {
        _TIFFmemcpy(bitData, Data, Size);
        TIFFReverseBits(bitData, static_cast<tmsize_t>(Size));
        _TIFFfree(bitData);
    }

    // Fuzz TIFFStripSize
    tmsize_t stripSize = TIFFStripSize(tif);

    // Fuzz TIFFReadEncodedStrip
    void *buffer = _TIFFmalloc(stripSize);
    if (buffer) {
        TIFFReadEncodedStrip(tif, strip, buffer, stripSize);
        _TIFFfree(buffer);
    }

    TIFFClose(tif);
    return 0;
}