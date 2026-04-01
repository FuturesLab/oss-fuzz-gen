// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// LogLuv24toXYZ at tif_luv.c:1032:5 in tiffio.h
// LogLuv32toXYZ at tif_luv.c:1180:5 in tiffio.h
// TIFFXYZToRGB at tif_color.c:89:6 in tiffio.h
// TIFFSwabArrayOfFloat at tif_swab.c:180:6 in tiffio.h
// TIFFSwabLong at tif_swab.c:45:6 in tiffio.h
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
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_39(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t) + sizeof(float) * 3 + sizeof(int)) {
        return 0;
    }

    // Prepare the environment for LogLuv24toXYZ and LogLuv32toXYZ
    uint32_t logluv24 = 0;
    float xyz24[3] = {0.0f, 0.0f, 0.0f};
    memcpy(&logluv24, Data, sizeof(uint32_t));
    LogLuv24toXYZ(logluv24, xyz24);

    uint32_t logluv32 = 0;
    float xyz32[3] = {0.0f, 0.0f, 0.0f};
    memcpy(&logluv32, Data, sizeof(uint32_t));
    LogLuv32toXYZ(logluv32, xyz32);

    // Prepare a copy of the input data for LogLuv24fromXYZ and TIFFSwabArrayOfFloat
    size_t floatArrayOffset = sizeof(uint32_t);
    size_t floatArraySize = (Size - floatArrayOffset) / sizeof(float);
    std::vector<float> xyzInput(floatArraySize);
    memcpy(xyzInput.data(), Data + floatArrayOffset, floatArraySize * sizeof(float));

    int pixelCount = static_cast<int>(*(Data + sizeof(uint32_t) + sizeof(float) * 3));
    uint32_t logluvOutput = LogLuv24fromXYZ(xyzInput.data(), pixelCount);

    // Prepare the environment for TIFFXYZToRGB
    TIFFCIELabToRGB cielabToRgb;
    uint32_t r = 0, g = 0, b = 0;
    if (Size >= sizeof(uint32_t) + sizeof(float) * 3 * 2 + sizeof(TIFFCIELabToRGB)) {
        float x = xyzInput[0];
        float y = xyzInput[1];
        float z = xyzInput[2];
        TIFFXYZToRGB(&cielabToRgb, x, y, z, &r, &g, &b);
    }

    // Prepare the environment for TIFFSwabArrayOfFloat
    tmsize_t n = static_cast<tmsize_t>(floatArraySize);
    if (n > 0) {
        TIFFSwabArrayOfFloat(xyzInput.data(), n);
    }

    // Prepare the environment for TIFFSwabLong
    uint32_t swabLongValue = logluv24;
    TIFFSwabLong(&swabLongValue);

    return 0;
}