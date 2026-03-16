// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFVGetField at tif_dir.c:1609:5 in tiffio.h
// TIFFFindField at tif_dirinfo.c:878:18 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFVSetField at tif_dir.c:1211:5 in tiffio.h
// TIFFGetFieldDefaulted at tif_aux.c:382:5 in tiffio.h
// TIFFVGetFieldDefaulted at tif_aux.c:217:5 in tiffio.h
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
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
#include <cstdarg>
#include <tiffio.h>

static void fuzz_TIFFVGetField(TIFF* tif, uint32_t tag, ...) {
    va_list args;
    va_start(args, tag);
    TIFFVGetField(tif, tag, args);
    va_end(args);
}

static void fuzz_TIFFFindField(TIFF* tif, uint32_t tag, TIFFDataType dataType) {
    TIFFFindField(tif, tag, dataType);
}

static void fuzz_TIFFGetField(TIFF* tif, uint32_t tag, ...) {
    va_list args;
    va_start(args, tag);
    TIFFGetField(tif, tag, args);
    va_end(args);
}

static void fuzz_TIFFVSetField(TIFF* tif, uint32_t tag, ...) {
    va_list args;
    va_start(args, tag);
    TIFFVSetField(tif, tag, args);
    va_end(args);
}

static void fuzz_TIFFGetFieldDefaulted(TIFF* tif, uint32_t tag, ...) {
    va_list args;
    va_start(args, tag);
    TIFFGetFieldDefaulted(tif, tag, args);
    va_end(args);
}

static void fuzz_TIFFVGetFieldDefaulted(TIFF* tif, uint32_t tag, ...) {
    va_list args;
    va_start(args, tag);
    TIFFVGetFieldDefaulted(tif, tag, args);
    va_end(args);
}

extern "C" int LLVMFuzzerTestOneInput_75(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t)) return 0;

    FILE* file = fopen("./dummy_file", "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    TIFF* tif = TIFFOpen("./dummy_file", "r");
    if (!tif) return 0;

    uint32_t tag = *reinterpret_cast<const uint32_t*>(Data);

    fuzz_TIFFVGetField(tif, tag);
    fuzz_TIFFFindField(tif, tag, TIFF_NOTYPE);
    fuzz_TIFFGetField(tif, tag);
    fuzz_TIFFVSetField(tif, tag);
    fuzz_TIFFGetFieldDefaulted(tif, tag);
    fuzz_TIFFVGetFieldDefaulted(tif, tag);

    TIFFClose(tif);
    return 0;
}