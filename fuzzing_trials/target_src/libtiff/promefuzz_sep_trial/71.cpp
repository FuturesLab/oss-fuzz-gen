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
#include "tiffio.h"

extern "C" int LLVMFuzzerTestOneInput_71(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(float) * 3 + sizeof(uint32_t)) return 0;

    // Prepare float array for XYZ values
    float xyz[3];
    memcpy(xyz, Data, sizeof(float) * 3);
    
    // Prepare uint32_t for LogLuv values
    uint32_t logluv = 0;
    memcpy(&logluv, Data + sizeof(float) * 3, sizeof(uint32_t));

    // Test LogLuv32fromXYZ
    uint32_t result32fromXYZ = LogLuv32fromXYZ(xyz, 1);

    // Test LogLuv24fromXYZ
    uint32_t result24fromXYZ = LogLuv24fromXYZ(xyz, 1);

    // Test LogLuv24toXYZ
    float outputXYZ24[3] = {0};
    LogLuv24toXYZ(logluv, outputXYZ24);

    // Test LogLuv32toXYZ
    float outputXYZ32[3] = {0};
    LogLuv32toXYZ(logluv, outputXYZ32);

    // Test TIFFSwabArrayOfFloat
    TIFFSwabArrayOfFloat(xyz, 3);

    // Test TIFFSwabLong
    TIFFSwabLong(&logluv);
    
    return 0;
}