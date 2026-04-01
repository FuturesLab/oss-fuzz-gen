// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// LogLuv24toXYZ at tif_luv.c:1032:5 in tiffio.h
// LogLuv32toXYZ at tif_luv.c:1180:5 in tiffio.h
// TIFFCIELabToXYZ at tif_color.c:43:6 in tiffio.h
// XYZtoRGB24 at tif_luv.c:865:5 in tiffio.h
// TIFFSwabArrayOfFloat at tif_swab.c:180:6 in tiffio.h
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
#include <cstring>
#include "tiffio.h"

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t)) {
        return 0;
    }

    uint32_t logLuvColor = 0;
    memcpy(&logLuvColor, Data, sizeof(uint32_t));

    // Prepare data for LogLuv24toXYZ and LogLuv32toXYZ
    float xyzArray[3] = {0.0f};

    // Fuzz LogLuv24toXYZ
    LogLuv24toXYZ(logLuvColor, xyzArray);

    // Fuzz LogLuv32toXYZ
    LogLuv32toXYZ(logLuvColor, xyzArray);

    // Prepare data for TIFFCIELabToXYZ
    TIFFCIELabToRGB cielabToRgb;
    uint32_t L = static_cast<uint32_t>(Data[0]);
    int32_t a = static_cast<int32_t>(Data[1]);
    int32_t b = static_cast<int32_t>(Data[2]);

    float X, Y, Z;
    TIFFCIELabToXYZ(&cielabToRgb, L, a, b, &X, &Y, &Z);

    // Prepare data for XYZtoRGB24
    uint8_t rgbArray[3] = {0};

    // Fuzz XYZtoRGB24
    XYZtoRGB24(xyzArray, rgbArray);

    // Prepare data for TIFFSwabArrayOfFloat
    float floatArray[3] = {X, Y, Z};

    // Fuzz TIFFSwabArrayOfFloat
    TIFFSwabArrayOfFloat(floatArray, 3);

    // Fuzz LogLuv24fromXYZ
    uint32_t logLuvResult = LogLuv24fromXYZ(floatArray, 1);

    return 0;
}