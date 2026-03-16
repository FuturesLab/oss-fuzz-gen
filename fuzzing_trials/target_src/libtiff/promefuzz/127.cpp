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
#include <cstdlib>
#include <cstring>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_127(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(float) * 3) return 0; // Ensure there's enough data for at least 3 floats

    // Prepare data for LogLuv32fromXYZ and LogLuv24fromXYZ
    float xyz[3];
    memcpy(xyz, Data, sizeof(float) * 3);
    int numComponents = 3;

    // Invoke LogLuv32fromXYZ
    uint32_t logLuv32 = LogLuv32fromXYZ(xyz, numComponents);

    // Invoke LogLuv24fromXYZ
    uint32_t logLuv24 = LogLuv24fromXYZ(xyz, numComponents);

    // Prepare data for LogLuv24toXYZ and LogLuv32toXYZ
    float outputXYZ[3];

    // Invoke LogLuv24toXYZ
    LogLuv24toXYZ(logLuv24, outputXYZ);

    // Invoke LogLuv32toXYZ
    LogLuv32toXYZ(logLuv32, outputXYZ);

    // Prepare data for TIFFSwabArrayOfFloat
    size_t numFloats = Size / sizeof(float);
    float *floatArray = (float *)malloc(numFloats * sizeof(float));
    if (floatArray) {
        memcpy(floatArray, Data, numFloats * sizeof(float));

        // Invoke TIFFSwabArrayOfFloat
        TIFFSwabArrayOfFloat(floatArray, numFloats);

        free(floatArray);
    }

    // Prepare data for TIFFSwabLong
    if (Size >= sizeof(uint32_t)) {
        uint32_t longValue;
        memcpy(&longValue, Data, sizeof(uint32_t));

        // Invoke TIFFSwabLong
        TIFFSwabLong(&longValue);
    }

    return 0;
}