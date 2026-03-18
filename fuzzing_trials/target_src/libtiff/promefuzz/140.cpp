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
#include "tiffio.h"

extern "C" int LLVMFuzzerTestOneInput_140(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t)) {
        return 0;
    }

    uint32_t logLuvValue;
    memcpy(&logLuvValue, Data, sizeof(uint32_t));

    float xyz[3] = {0.0f, 0.0f, 0.0f};
    LogLuv24toXYZ(logLuvValue, xyz);
    LogLuv32toXYZ(logLuvValue, xyz);

    uint32_t logLuv32FromXYZ = LogLuv32fromXYZ(xyz, 3);
    uint32_t logLuv24FromXYZ = LogLuv24fromXYZ(xyz, 3);

    TIFFSwabLong(&logLuvValue);
    TIFFSwabArrayOfFloat(xyz, 3);

    return 0;
}