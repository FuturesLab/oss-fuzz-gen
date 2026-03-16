// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// _TIFFcalloc at tif_unix.c:341:7 in tiffio.h
// _TIFFmemcpy at tif_unix.c:355:6 in tiffio.h
// TIFFWriteEncodedStrip at tif_write.c:215:10 in tiffio.h
// _TIFFmemset at tif_unix.c:353:6 in tiffio.h
// _TIFFfree at tif_unix.c:349:6 in tiffio.h
// _TIFFcalloc at tif_unix.c:341:7 in tiffio.h
// TIFFReadEncodedStrip at tif_read.c:543:10 in tiffio.h
// _TIFFfree at tif_unix.c:349:6 in tiffio.h
// _TIFFmemcmp at tif_unix.c:360:5 in tiffio.h
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

extern "C" int LLVMFuzzerTestOneInput_54(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Ensure there's at least some data to work with

    // Create a dummy TIFF file for testing
    FILE *dummyFile = fopen("./dummy_file", "wb+");
    if (!dummyFile) return 0;
    fwrite(Data, 1, Size, dummyFile);
    fclose(dummyFile);

    TIFF *tif = TIFFOpen("./dummy_file", "r+");
    if (!tif) return 0;

    // Fuzzing TIFFWriteEncodedStrip
    uint32_t strip = 0;
    tmsize_t dataSize = static_cast<tmsize_t>(Size);
    void *stripData = _TIFFcalloc(1, dataSize);
    if (stripData) {
        _TIFFmemcpy(stripData, Data, dataSize);
        TIFFWriteEncodedStrip(tif, strip, stripData, dataSize);
        _TIFFmemset(stripData, 0, dataSize);
        _TIFFfree(stripData);
    }

    // Fuzzing TIFFReadEncodedStrip
    void *readBuffer = _TIFFcalloc(1, dataSize);
    if (readBuffer) {
        TIFFReadEncodedStrip(tif, strip, readBuffer, dataSize);
        _TIFFfree(readBuffer);
    }

    // Fuzzing _TIFFmemcmp
    if (Size >= 2) {
        _TIFFmemcmp(Data, Data + 1, Size - 1);
    }

    TIFFClose(tif);

    return 0;
}