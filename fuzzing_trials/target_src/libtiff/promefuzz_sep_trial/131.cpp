// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// LogLuv24toXYZ at tif_luv.c:1032:5 in tiffio.h
// _TIFFmalloc at tif_unix.c:333:7 in tiffio.h
// TIFFYCbCrToRGBInit at tif_color.c:251:5 in tiffio.h
// TIFFXYZToRGB at tif_color.c:89:6 in tiffio.h
// TIFFCIELabToRGBInit at tif_color.c:135:5 in tiffio.h
// XYZtoRGB24 at tif_luv.c:865:5 in tiffio.h
// TIFFCIELabToXYZ at tif_color.c:43:6 in tiffio.h
// _TIFFfree at tif_unix.c:349:6 in tiffio.h
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
#include <cstdio>
#include <cstdlib>
#include <tiffio.h>

static size_t roundup_32(size_t size, size_t align) {
    return (size + (align - 1)) & ~(align - 1);
}

extern "C" int LLVMFuzzerTestOneInput_131(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t) + 3 * sizeof(float)) {
        return 0;
    }

    // Fuzz LogLuv24toXYZ
    uint32_t logLuvColor = *(reinterpret_cast<const uint32_t *>(Data));
    float xyzOutput[3];
    LogLuv24toXYZ(logLuvColor, xyzOutput);

    // Allocate memory for TIFFYCbCrToRGB structure
    size_t ycbcrSize = roundup_32(sizeof(TIFFYCbCrToRGB), sizeof(long)) +
                       4 * 256 * sizeof(TIFFRGBValue) + 
                       2 * 256 * sizeof(int) + 
                       3 * 256 * sizeof(int32_t);
    TIFFYCbCrToRGB *ycbcr = (TIFFYCbCrToRGB *)_TIFFmalloc(ycbcrSize);
    if (!ycbcr) {
        return 0;
    }

    // Fuzz TIFFYCbCrToRGBInit
    float luma[3] = {0.0f, 0.0f, 0.0f};
    float refBlackWhite[6] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    TIFFYCbCrToRGBInit(ycbcr, luma, refBlackWhite);

    // Fuzz TIFFXYZToRGB
    TIFFCIELabToRGB cielabToRGB;
    uint32_t r, g, b;
    TIFFXYZToRGB(&cielabToRGB, xyzOutput[0], xyzOutput[1], xyzOutput[2], &r, &g, &b);

    // Fuzz TIFFCIELabToRGBInit
    TIFFDisplay display;
    float whitePoint[3] = {0.0f, 0.0f, 0.0f};
    TIFFCIELabToRGBInit(&cielabToRGB, &display, whitePoint);

    // Fuzz XYZtoRGB24
    uint8_t rgbOutput[3];
    XYZtoRGB24(xyzOutput, rgbOutput);

    // Fuzz TIFFCIELabToXYZ
    float x, y, z;
    TIFFCIELabToXYZ(&cielabToRGB, 50, 0, 0, &x, &y, &z);

    // Free allocated memory
    _TIFFfree(ycbcr);

    return 0;
}