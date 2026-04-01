// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFStripSize at tif_strip.c:204:10 in tiffio.h
// _TIFFmalloc at tif_unix.c:333:7 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFNumberOfStrips at tif_strip.c:65:10 in tiffio.h
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
extern "C" {
#include <tiffio.h>
}

#include <cstdint>
#include <cstdio>
#include <cstdlib>

static TIFF* openDummyTIFF(const char* filename) {
    TIFF* tif = TIFFOpen(filename, "r");
    return tif;
}

static void writeDummyFile(const uint8_t* data, size_t size) {
    FILE* file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t* Data, size_t Size) {
    // Write dummy file
    writeDummyFile(Data, Size);

    // Open the dummy TIFF file
    TIFF* tif = openDummyTIFF("./dummy_file");
    if (!tif) {
        return 0;
    }

    // Call TIFFStripSize
    tmsize_t stripSize = TIFFStripSize(tif);

    // Call _TIFFmalloc
    void* buffer = _TIFFmalloc(stripSize);
    if (!buffer) {
        TIFFClose(tif);
        return 0;
    }

    // Call TIFFNumberOfStrips
    uint32_t numStrips = TIFFNumberOfStrips(tif);

    // Iterate over strips if any
    for (uint32_t i = 0; i < numStrips; ++i) {
        // Call TIFFReadEncodedStrip
        TIFFReadEncodedStrip(tif, i, buffer, stripSize);
    }

    // Cleanup
    _TIFFfree(buffer);
    TIFFClose(tif);

    return 0;
}