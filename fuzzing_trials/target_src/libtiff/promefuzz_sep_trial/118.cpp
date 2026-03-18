// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// LogLuv24toXYZ at tif_luv.c:1032:5 in tiffio.h
// LogLuv32toXYZ at tif_luv.c:1180:5 in tiffio.h
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

extern "C" int LLVMFuzzerTestOneInput_118(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0; // Ensure there is enough data for a uint32_t

    // Prepare data for LogLuv32fromXYZ and LogLuv24fromXYZ
    float xyz[3] = {0};
    int numComponents = 3;
    
    if (Size >= 12) {
        memcpy(xyz, Data, 12);
    }

    // Fuzz LogLuv32fromXYZ
    uint32_t logluv32 = LogLuv32fromXYZ(xyz, numComponents);

    // Fuzz LogLuv24fromXYZ
    uint32_t logluv24 = LogLuv24fromXYZ(xyz, numComponents);

    // Prepare data for LogLuv24toXYZ and LogLuv32toXYZ
    float xyzOutput[3] = {0};

    // Fuzz LogLuv24toXYZ
    LogLuv24toXYZ(logluv24, xyzOutput);

    // Fuzz LogLuv32toXYZ
    LogLuv32toXYZ(logluv32, xyzOutput);

    // Prepare data for TIFFSwabArrayOfFloat
    tmsize_t n = Size / sizeof(float);
    if (n > 0) {
        float* floatArray = (float*)malloc(n * sizeof(float));
        if (floatArray) {
            memcpy(floatArray, Data, n * sizeof(float));
            TIFFSwabArrayOfFloat(floatArray, n);
            free(floatArray);
        }
    }

    // Fuzz TIFFSwabLong
    uint32_t longValue;
    memcpy(&longValue, Data, sizeof(uint32_t));
    TIFFSwabLong(&longValue);

    return 0;
}