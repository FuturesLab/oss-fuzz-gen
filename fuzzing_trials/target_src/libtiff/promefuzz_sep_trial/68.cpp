// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFScanlineSize at tif_strip.c:343:10 in tiffio.h
// TIFFStripSize at tif_strip.c:204:10 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFReadFromUserBuffer at tif_read.c:1555:5 in tiffio.h
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
#include <fcntl.h>
#include <unistd.h>

static TIFF* openDummyTIFF(const uint8_t *Data, size_t Size) {
    FILE *file = std::fopen("./dummy_file", "wb");
    if (!file) {
        return nullptr;
    }
    std::fwrite(Data, 1, Size, file);
    std::fclose(file);

    TIFF *tif = TIFFOpen("./dummy_file", "r");
    return tif;
}

extern "C" int LLVMFuzzerTestOneInput_68(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    TIFF *tif = openDummyTIFF(Data, Size);
    if (!tif) {
        return 0;
    }

    // Fuzz TIFFScanlineSize
    tmsize_t scanlineSize = TIFFScanlineSize(tif);

    // Fuzz TIFFStripSize
    tmsize_t stripSize = TIFFStripSize(tif);

    // Prepare buffers for TIFFReadFromUserBuffer, TIFFReadEncodedTile, and TIFFReadEncodedStrip
    uint32_t strile = 0;
    tmsize_t bufferSize = 1024;
    void *inbuf = std::malloc(bufferSize);
    void *outbuf = std::malloc(bufferSize);
    if (!inbuf || !outbuf) {
        TIFFClose(tif);
        std::free(inbuf);
        std::free(outbuf);
        return 0;
    }

    // Fuzz TIFFReadFromUserBuffer
    TIFFReadFromUserBuffer(tif, strile, inbuf, bufferSize, outbuf, bufferSize);

    // Fuzz TIFFReadEncodedTile
    TIFFReadEncodedTile(tif, strile, outbuf, bufferSize);

    // Fuzz TIFFReadEncodedStrip
    TIFFReadEncodedStrip(tif, strile, outbuf, bufferSize);

    // Fuzz TIFFPrintDirectory
    FILE *dummyFile = std::fopen("./dummy_output", "w");
    if (dummyFile) {
        TIFFPrintDirectory(tif, dummyFile, 0);
        std::fclose(dummyFile);
    }

    TIFFClose(tif);
    std::free(inbuf);
    std::free(outbuf);

    return 0;
}