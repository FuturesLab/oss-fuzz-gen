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

extern "C" int LLVMFuzzerTestOneInput_133(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(float) * 3 + sizeof(uint32_t)) {
        return 0;
    }

    // Prepare XYZ float array
    float xyz[3];
    memcpy(xyz, Data, sizeof(float) * 3);
    Data += sizeof(float) * 3;
    Size -= sizeof(float) * 3;

    // Prepare LogLuv uint32_t
    uint32_t logLuv;
    memcpy(&logLuv, Data, sizeof(uint32_t));
    Data += sizeof(uint32_t);
    Size -= sizeof(uint32_t);

    // Fuzz LogLuv32fromXYZ
    uint32_t logLuv32Result = LogLuv32fromXYZ(xyz, 1);

    // Fuzz LogLuv24toXYZ
    float xyzFrom24[3];
    LogLuv24toXYZ(logLuv, xyzFrom24);

    // Fuzz LogLuv32toXYZ
    float xyzFrom32[3];
    LogLuv32toXYZ(logLuv32Result, xyzFrom32);

    // Fuzz LogLuv24fromXYZ
    uint32_t logLuv24Result = LogLuv24fromXYZ(xyz, 1);

    // Fuzz TIFFSwabArrayOfFloat
    TIFFSwabArrayOfFloat(xyz, 3);

    // Fuzz TIFFSwabLong
    TIFFSwabLong(&logLuv);

    return 0;
}