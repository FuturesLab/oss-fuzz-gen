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

extern "C" int LLVMFuzzerTestOneInput_154(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t)) return 0;

    uint32_t logLuvColor;
    memcpy(&logLuvColor, Data, sizeof(uint32_t));
    
    float xyz[3] = {0.0, 0.0, 0.0};
    float xyzArray[3] = {0.0, 0.0, 0.0};

    // Fuzz LogLuv24toXYZ
    LogLuv24toXYZ(logLuvColor, xyz);

    // Fuzz LogLuv32toXYZ
    LogLuv32toXYZ(logLuvColor, xyz);

    // Fuzz LogLuv32fromXYZ
    uint32_t logLuv32 = LogLuv32fromXYZ(xyz, 3);

    // Fuzz TIFFSwabLong
    TIFFSwabLong(&logLuv32);

    // Fuzz TIFFSwabArrayOfFloat
    TIFFSwabArrayOfFloat(xyzArray, 3);

    // Fuzz LogLuv24fromXYZ
    uint32_t logLuv24 = LogLuv24fromXYZ(xyzArray, 3);

    return 0;
}