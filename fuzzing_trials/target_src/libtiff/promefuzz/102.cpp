// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFReadRawTile at tif_read.c:1186:10 in tiffio.h
// TIFFWriteEncodedTile at tif_write.c:414:10 in tiffio.h
// TIFFReadTile at tif_read.c:950:10 in tiffio.h
// TIFFWriteRawTile at tif_write.c:533:10 in tiffio.h
// TIFFReadEncodedStrip at tif_read.c:543:10 in tiffio.h
// TIFFWriteTile at tif_write.c:387:10 in tiffio.h
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

static TIFF* openDummyTIFF(const char* mode) {
    // Create a dummy TIFF file
    FILE* file = fopen("./dummy_file", mode);
    if (!file) return nullptr;
    fclose(file);

    // Open the TIFF file using libtiff
    return TIFFOpen("./dummy_file", mode);
}

static void fuzzTIFFReadRawTile(TIFF* tif, const uint8_t* Data, size_t Size) {
    if (Size < sizeof(uint32_t) + sizeof(tmsize_t)) return;

    uint32_t tile = *reinterpret_cast<const uint32_t*>(Data);
    tmsize_t bufferSize = *reinterpret_cast<const tmsize_t*>(Data + sizeof(uint32_t));
    void* buffer = malloc(bufferSize);
    if (!buffer) return;

    TIFFReadRawTile(tif, tile, buffer, bufferSize);

    free(buffer);
}

static void fuzzTIFFWriteEncodedTile(TIFF* tif, const uint8_t* Data, size_t Size) {
    if (Size < sizeof(uint32_t) + sizeof(tmsize_t)) return;

    uint32_t tile = *reinterpret_cast<const uint32_t*>(Data);
    tmsize_t dataSize = *reinterpret_cast<const tmsize_t*>(Data + sizeof(uint32_t));
    void* data = const_cast<uint8_t*>(Data + sizeof(uint32_t) + sizeof(tmsize_t));

    TIFFWriteEncodedTile(tif, tile, data, dataSize);
}

static void fuzzTIFFReadTile(TIFF* tif, const uint8_t* Data, size_t Size) {
    if (Size < sizeof(uint32_t) * 3 + sizeof(uint16_t)) return;

    uint32_t x = *reinterpret_cast<const uint32_t*>(Data);
    uint32_t y = *reinterpret_cast<const uint32_t*>(Data + sizeof(uint32_t));
    uint32_t z = *reinterpret_cast<const uint32_t*>(Data + sizeof(uint32_t) * 2);
    uint16_t s = *reinterpret_cast<const uint16_t*>(Data + sizeof(uint32_t) * 3);
    void* buffer = malloc(Size);
    if (!buffer) return;

    TIFFReadTile(tif, buffer, x, y, z, s);

    free(buffer);
}

static void fuzzTIFFWriteRawTile(TIFF* tif, const uint8_t* Data, size_t Size) {
    if (Size < sizeof(uint32_t) + sizeof(tmsize_t)) return;

    uint32_t tile = *reinterpret_cast<const uint32_t*>(Data);
    tmsize_t dataSize = *reinterpret_cast<const tmsize_t*>(Data + sizeof(uint32_t));
    void* data = const_cast<uint8_t*>(Data + sizeof(uint32_t) + sizeof(tmsize_t));

    TIFFWriteRawTile(tif, tile, data, dataSize);
}

static void fuzzTIFFReadEncodedStrip(TIFF* tif, const uint8_t* Data, size_t Size) {
    if (Size < sizeof(uint32_t) + sizeof(tmsize_t)) return;

    uint32_t strip = *reinterpret_cast<const uint32_t*>(Data);
    tmsize_t bufferSize = *reinterpret_cast<const tmsize_t*>(Data + sizeof(uint32_t));
    void* buffer = malloc(bufferSize);
    if (!buffer) return;

    TIFFReadEncodedStrip(tif, strip, buffer, bufferSize);

    free(buffer);
}

static void fuzzTIFFWriteTile(TIFF* tif, const uint8_t* Data, size_t Size) {
    if (Size < sizeof(uint32_t) * 3 + sizeof(uint16_t)) return;

    uint32_t x = *reinterpret_cast<const uint32_t*>(Data);
    uint32_t y = *reinterpret_cast<const uint32_t*>(Data + sizeof(uint32_t));
    uint32_t z = *reinterpret_cast<const uint32_t*>(Data + sizeof(uint32_t) * 2);
    uint16_t s = *reinterpret_cast<const uint16_t*>(Data + sizeof(uint32_t) * 3);
    void* buffer = const_cast<uint8_t*>(Data + sizeof(uint32_t) * 3 + sizeof(uint16_t));

    TIFFWriteTile(tif, buffer, x, y, z, s);
}

extern "C" int LLVMFuzzerTestOneInput_102(const uint8_t* Data, size_t Size) {
    TIFF* tif = openDummyTIFF("w+");
    if (!tif) return 0;

    fuzzTIFFReadRawTile(tif, Data, Size);
    fuzzTIFFWriteEncodedTile(tif, Data, Size);
    fuzzTIFFReadTile(tif, Data, Size);
    fuzzTIFFWriteRawTile(tif, Data, Size);
    fuzzTIFFReadEncodedStrip(tif, Data, Size);
    fuzzTIFFWriteTile(tif, Data, Size);

    TIFFClose(tif);
    return 0;
}