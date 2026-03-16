// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// LogLuv24toXYZ at tif_luv.c:1032:5 in tiffio.h
// TIFFSwabFloat at tif_swab.c:165:6 in tiffio.h
// TIFFSwabArrayOfFloat at tif_swab.c:180:6 in tiffio.h
// XYZtoRGB24 at tif_luv.c:865:5 in tiffio.h
// TIFFCIELabToXYZ at tif_color.c:43:6 in tiffio.h
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
#include <cstring>
#include <cstdio>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_95(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t) + sizeof(float) * 6 + sizeof(int32_t) * 2 + sizeof(uint8_t) * 3) {
        return 0;
    }

    // Prepare input data for LogLuv24toXYZ
    uint32_t logLuvColor;
    std::memcpy(&logLuvColor, Data, sizeof(uint32_t));
    Data += sizeof(uint32_t);
    Size -= sizeof(uint32_t);

    float xyzOutput[3];
    LogLuv24toXYZ(logLuvColor, xyzOutput);

    // Prepare input data for LogLuv24fromXYZ
    float xyzInput[3];
    std::memcpy(xyzInput, Data, sizeof(float) * 3);
    Data += sizeof(float) * 3;
    Size -= sizeof(float) * 3;

    uint32_t logLuvOutput = LogLuv24fromXYZ(xyzInput, 1);

    // Prepare input data for TIFFSwabFloat
    float swabFloat;
    std::memcpy(&swabFloat, Data, sizeof(float));
    Data += sizeof(float);
    Size -= sizeof(float);

    TIFFSwabFloat(&swabFloat);

    // Prepare input data for TIFFSwabArrayOfFloat
    if (Size < sizeof(float) * 3) {
        return 0;
    }
    float swabFloatArray[3];
    std::memcpy(swabFloatArray, Data, sizeof(float) * 3);
    Data += sizeof(float) * 3;
    Size -= sizeof(float) * 3;

    TIFFSwabArrayOfFloat(swabFloatArray, 3);

    // Prepare input data for XYZtoRGB24
    if (Size < sizeof(float) * 3) {
        return 0;
    }
    float xyzToRgbInput[3];
    std::memcpy(xyzToRgbInput, Data, sizeof(float) * 3);
    Data += sizeof(float) * 3;
    Size -= sizeof(float) * 3;

    uint8_t rgbOutput[3];
    XYZtoRGB24(xyzToRgbInput, rgbOutput);

    // Prepare input data for TIFFCIELabToXYZ
    if (Size < sizeof(uint32_t) + sizeof(int32_t) * 2) {
        return 0;
    }
    TIFFCIELabToRGB cielabToRgb;
    uint32_t L = *reinterpret_cast<const uint32_t*>(Data);
    Data += sizeof(uint32_t);
    Size -= sizeof(uint32_t);

    int32_t a = *reinterpret_cast<const int32_t*>(Data);
    Data += sizeof(int32_t);
    Size -= sizeof(int32_t);

    int32_t b = *reinterpret_cast<const int32_t*>(Data);
    Data += sizeof(int32_t);
    Size -= sizeof(int32_t);

    float cielabX, cielabY, cielabZ;
    TIFFCIELabToXYZ(&cielabToRgb, L, a, b, &cielabX, &cielabY, &cielabZ);

    return 0;
}