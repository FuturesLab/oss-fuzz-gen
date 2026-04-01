// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetFieldDefaulted at tif_aux.c:382:5 in tiffio.h
// TIFFFindField at tif_dirinfo.c:878:18 in tiffio.h
// TIFFVGetFieldDefaulted at tif_aux.c:217:5 in tiffio.h
// TIFFVGetField at tif_dir.c:1609:5 in tiffio.h
// TIFFVSetField at tif_dir.c:1211:5 in tiffio.h
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
#include <cstdarg>
#include <cstdio>
#include <cstring>

static TIFF* openDummyTIFF(const uint8_t* data, size_t size) {
    FILE* file = fopen("./dummy_file", "wb");
    if (!file) return nullptr;
    fwrite(data, 1, size, file);
    fclose(file);

    return TIFFOpen("./dummy_file", "r");
}

static void fuzzTIFFGetField(TIFF* tif, uint32_t tag) {
    int result = TIFFGetField(tif, tag);
}

static void fuzzTIFFGetFieldDefaulted(TIFF* tif, uint32_t tag) {
    int result = TIFFGetFieldDefaulted(tif, tag);
}

static void fuzzTIFFFindField(TIFF* tif, uint32_t tag, TIFFDataType dataType) {
    const TIFFField* field = TIFFFindField(tif, tag, dataType);
}

static void fuzzTIFFVGetFieldDefaulted(TIFF* tif, uint32_t tag, ...) {
    va_list args;
    va_start(args, tag);
    int result = TIFFVGetFieldDefaulted(tif, tag, args);
    va_end(args);
}

static void fuzzTIFFVGetField(TIFF* tif, uint32_t tag, ...) {
    va_list args;
    va_start(args, tag);
    int result = TIFFVGetField(tif, tag, args);
    va_end(args);
}

static void fuzzTIFFVSetField(TIFF* tif, uint32_t tag, ...) {
    va_list args;
    va_start(args, tag);
    int result = TIFFVSetField(tif, tag, args);
    va_end(args);
}

extern "C" int LLVMFuzzerTestOneInput_94(const uint8_t* Data, size_t Size) {
    if (Size < sizeof(uint32_t) + sizeof(TIFFDataType)) return 0;

    TIFF* tif = openDummyTIFF(Data, Size);
    if (!tif) return 0;

    uint32_t tag = *reinterpret_cast<const uint32_t*>(Data);
    TIFFDataType dataType = static_cast<TIFFDataType>(*(Data + sizeof(uint32_t)));

    fuzzTIFFGetField(tif, tag);
    fuzzTIFFGetFieldDefaulted(tif, tag);
    fuzzTIFFFindField(tif, tag, dataType);
    fuzzTIFFVGetFieldDefaulted(tif, tag, nullptr);
    fuzzTIFFVGetField(tif, tag, nullptr);
    fuzzTIFFVSetField(tif, tag, nullptr);

    TIFFClose(tif);
    return 0;
}