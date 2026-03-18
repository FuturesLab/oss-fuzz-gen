// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// LogLuv24toXYZ at tif_luv.c:1032:5 in tiffio.h
// LogLuv32toXYZ at tif_luv.c:1180:5 in tiffio.h
// TIFFSwabLong at tif_swab.c:45:6 in tiffio.h
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
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    // Prepare data for LogLuv24toXYZ and LogLuv32toXYZ
    uint32_t logluvColor;
    memcpy(&logluvColor, Data, sizeof(uint32_t));

    float xyzOutput[3] = {0.0f, 0.0f, 0.0f};

    // Fuzz LogLuv24toXYZ
    LogLuv24toXYZ(logluvColor, xyzOutput);

    // Fuzz LogLuv32toXYZ
    LogLuv32toXYZ(logluvColor, xyzOutput);

    // Prepare data for LogLuv32fromXYZ
    float xyzInput[3] = {0.0f, 0.0f, 0.0f};
    int numComponents = 3;
    if (Size >= 16) {
        memcpy(xyzInput, Data + 4, sizeof(float) * 3);
    }

    // Fuzz LogLuv32fromXYZ
    uint32_t logluv32 = LogLuv32fromXYZ(xyzInput, numComponents);

    // Fuzz TIFFSwabLong
    TIFFSwabLong(&logluvColor);

    // Prepare data for TIFFSwabArrayOfFloat
    tmsize_t numFloats = 3;
    if (Size >= 28) {
        memcpy(xyzInput, Data + 16, sizeof(float) * 3);
    }

    // Fuzz TIFFSwabArrayOfFloat
    TIFFSwabArrayOfFloat(xyzInput, numFloats);

    // Fuzz LogLuv24fromXYZ
    uint32_t logluv24 = LogLuv24fromXYZ(xyzInput, numComponents);

    return 0;
}