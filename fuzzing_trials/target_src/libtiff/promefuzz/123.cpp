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

extern "C" int LLVMFuzzerTestOneInput_123(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(float) * 3) return 0; // Ensure there's enough data

    // Prepare input data for LogLuv32fromXYZ and LogLuv24fromXYZ
    float xyz[3];
    memcpy(xyz, Data, sizeof(float) * 3);
    int numComponents = 1; // Simplification for the fuzz target

    // Test LogLuv32fromXYZ
    uint32_t logluv32 = LogLuv32fromXYZ(xyz, numComponents);

    // Prepare input data for LogLuv24toXYZ and LogLuv32toXYZ
    if (Size < sizeof(uint32_t)) return 0; // Ensure there's enough data for uint32_t
    uint32_t logluv24 = *reinterpret_cast<const uint32_t*>(Data);

    // Test LogLuv24toXYZ
    float xyz_out24[3] = {0.0f, 0.0f, 0.0f};
    LogLuv24toXYZ(logluv24, xyz_out24);

    // Test LogLuv32toXYZ
    float xyz_out32[3] = {0.0f, 0.0f, 0.0f};
    LogLuv32toXYZ(logluv32, xyz_out32);

    // Test LogLuv24fromXYZ
    uint32_t logluv24_from_xyz = LogLuv24fromXYZ(xyz, numComponents);

    // Prepare input data for TIFFSwabArrayOfFloat
    size_t numFloats = Size / sizeof(float);
    if (numFloats > 0) {
        float* floatArray = (float*)malloc(sizeof(float) * numFloats);
        if (floatArray) {
            memcpy(floatArray, Data, sizeof(float) * numFloats);

            // Test TIFFSwabArrayOfFloat
            TIFFSwabArrayOfFloat(floatArray, (tmsize_t)numFloats);

            free(floatArray);
        }
    }

    // Test TIFFSwabLong
    uint32_t longValue = *reinterpret_cast<const uint32_t*>(Data);
    TIFFSwabLong(&longValue);

    return 0;
}