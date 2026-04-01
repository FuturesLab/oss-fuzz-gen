// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFMergeFieldInfo at tif_dirinfo.c:1238:5 in tiffio.h
// TIFFScanlineSize at tif_strip.c:343:10 in tiffio.h
// TIFFYCbCrtoRGB at tif_color.c:199:6 in tiffio.h
// TIFFScanlineSize at tif_strip.c:343:10 in tiffio.h
// TIFFReadEncodedStrip at tif_read.c:543:10 in tiffio.h
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
#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>

static TIFF* openDummyTIFF() {
    FILE* file = fopen("./dummy_file", "wb+");
    if (!file) return nullptr;
    fclose(file);
    return TIFFOpen("./dummy_file", "r+");
}

static void fuzzTIFFMergeFieldInfo(TIFF* tif, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(TIFFFieldInfo)) return;
    const TIFFFieldInfo* fieldInfo = reinterpret_cast<const TIFFFieldInfo*>(Data);
    TIFFMergeFieldInfo(tif, fieldInfo, 1);
}

static void fuzzTIFFReadScanline(TIFF* tif, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t) + sizeof(uint16_t)) return;
    uint32_t row = *reinterpret_cast<const uint32_t*>(Data);
    uint16_t sample = *reinterpret_cast<const uint16_t*>(Data + sizeof(uint32_t));
    void* buffer = malloc(TIFFScanlineSize(tif));
    TIFFReadScanline(tif, buffer, row, sample);
    free(buffer);
}

static void fuzzTIFFYCbCrtoRGB(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(TIFFYCbCrToRGB) + 3 * sizeof(int32_t) + 3 * sizeof(uint32_t)) return;
    TIFFYCbCrToRGB* ycbcr = reinterpret_cast<TIFFYCbCrToRGB*>(const_cast<uint8_t*>(Data));
    int32_t Y = *reinterpret_cast<const int32_t*>(Data + sizeof(TIFFYCbCrToRGB));
    int32_t Cb = *reinterpret_cast<const int32_t*>(Data + sizeof(TIFFYCbCrToRGB) + sizeof(int32_t));
    int32_t Cr = *reinterpret_cast<const int32_t*>(Data + sizeof(TIFFYCbCrToRGB) + 2 * sizeof(int32_t));
    uint32_t R, G, B;
    TIFFYCbCrtoRGB(ycbcr, Y, Cb, Cr, &R, &G, &B);
}

static void fuzzTIFFWriteScanline(TIFF* tif, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t) + sizeof(uint16_t)) return;
    uint32_t row = *reinterpret_cast<const uint32_t*>(Data);
    uint16_t sample = *reinterpret_cast<const uint16_t*>(Data + sizeof(uint32_t));
    void* buffer = malloc(TIFFScanlineSize(tif));
    TIFFWriteScanline(tif, buffer, row, sample);
    free(buffer);
}

static void fuzzTIFFReadEncodedStrip(TIFF* tif, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t) + sizeof(tmsize_t)) return;
    uint32_t strip = *reinterpret_cast<const uint32_t*>(Data);
    tmsize_t bufSize = *reinterpret_cast<const tmsize_t*>(Data + sizeof(uint32_t));
    void* buffer = malloc(bufSize);
    TIFFReadEncodedStrip(tif, strip, buffer, bufSize);
    free(buffer);
}

static void fuzzTIFFReadGPSDirectory(TIFF* tif, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(toff_t)) return;
    toff_t diroff = *reinterpret_cast<const toff_t*>(Data);
    TIFFReadGPSDirectory(tif, diroff);
}

extern "C" int LLVMFuzzerTestOneInput_106(const uint8_t *Data, size_t Size) {
    TIFF* tif = openDummyTIFF();
    if (!tif) return 0;

    fuzzTIFFMergeFieldInfo(tif, Data, Size);
    fuzzTIFFReadScanline(tif, Data, Size);
    fuzzTIFFYCbCrtoRGB(Data, Size);
    fuzzTIFFWriteScanline(tif, Data, Size);
    fuzzTIFFReadEncodedStrip(tif, Data, Size);
    fuzzTIFFReadGPSDirectory(tif, Data, Size);

    TIFFClose(tif);
    return 0;
}