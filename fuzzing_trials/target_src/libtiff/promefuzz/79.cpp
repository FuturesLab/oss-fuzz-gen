// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// LogLuv24toXYZ at tif_luv.c:1032:5 in tiffio.h
// TIFFSwabFloat at tif_swab.c:165:6 in tiffio.h
// TIFFCIELabToXYZ at tif_color.c:43:6 in tiffio.h
// XYZtoRGB24 at tif_luv.c:865:5 in tiffio.h
// TIFFXYZToRGB at tif_color.c:89:6 in tiffio.h
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
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_79(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t) + sizeof(float) * 3 + sizeof(uint8_t) * 3) {
        return 0;
    }

    // Prepare data for LogLuv24toXYZ
    uint32_t logLuvColor = *reinterpret_cast<const uint32_t*>(Data);
    float xyzOutput[3] = {0.0f, 0.0f, 0.0f};
    LogLuv24toXYZ(logLuvColor, xyzOutput);

    // Prepare data for TIFFSwabFloat
    float swabFloat = *reinterpret_cast<const float*>(Data + sizeof(uint32_t));
    TIFFSwabFloat(&swabFloat);

    // Prepare data for TIFFCIELabToXYZ
    TIFFCIELabToRGB labToRgb;
    uint32_t L = static_cast<uint32_t>(Data[sizeof(uint32_t) + sizeof(float)]);
    int32_t a = static_cast<int32_t>(Data[sizeof(uint32_t) + sizeof(float) + 1]);
    int32_t bVal = static_cast<int32_t>(Data[sizeof(uint32_t) + sizeof(float) + 2]);
    float cieX, cieY, cieZ;
    TIFFCIELabToXYZ(&labToRgb, L, a, bVal, &cieX, &cieY, &cieZ);

    // Prepare data for XYZtoRGB24
    float xyzInput[3] = {xyzOutput[0], xyzOutput[1], xyzOutput[2]};
    uint8_t rgbOutput[3];
    XYZtoRGB24(xyzInput, rgbOutput);

    // Prepare data for TIFFXYZToRGB
    uint32_t r, g, b;
    TIFFXYZToRGB(&labToRgb, cieX, cieY, cieZ, &r, &g, &b);

    // Prepare data for TIFFSwabArrayOfFloat
    float floatArray[3] = {xyzOutput[0], xyzOutput[1], xyzOutput[2]};
    tmsize_t numFloats = 3;
    TIFFSwabArrayOfFloat(floatArray, numFloats);

    return 0;
}