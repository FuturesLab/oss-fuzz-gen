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
#include <cstddef>
#include <cstdio>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_155(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t)) return 0;

    uint32_t logluv24 = 0;
    uint32_t logluv32 = 0;
    float xyz[3] = {0.0f, 0.0f, 0.0f};
    float xyzInput[3] = {0.0f, 0.0f, 0.0f};

    // Read the first 4 bytes as a uint32_t for LogLuv24toXYZ and LogLuv32toXYZ
    logluv24 = *reinterpret_cast<const uint32_t*>(Data);

    // Use the same 4 bytes for LogLuv32toXYZ to test different function states
    logluv32 = *reinterpret_cast<const uint32_t*>(Data);

    // Call LogLuv24toXYZ
    LogLuv24toXYZ(logluv24, xyz);

    // Call LogLuv32toXYZ
    LogLuv32toXYZ(logluv32, xyz);

    // Prepare xyzInput for LogLuv32fromXYZ and LogLuv24fromXYZ
    if (Size >= sizeof(uint32_t) + sizeof(float) * 3) {
        for (int i = 0; i < 3; ++i) {
            xyzInput[i] = *reinterpret_cast<const float*>(Data + sizeof(uint32_t) + i * sizeof(float));
        }
    }

    // Call LogLuv32fromXYZ
    uint32_t result32 = LogLuv32fromXYZ(xyzInput, 3);

    // Call LogLuv24fromXYZ
    uint32_t result24 = LogLuv24fromXYZ(xyzInput, 3);

    // Call TIFFSwabLong
    TIFFSwabLong(&logluv32);

    // Call TIFFSwabArrayOfFloat
    TIFFSwabArrayOfFloat(xyzInput, 3);

    return 0;
}