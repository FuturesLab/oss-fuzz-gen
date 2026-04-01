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

extern "C" int LLVMFuzzerTestOneInput_75(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t)) return 0;

    // Convert first 4 bytes of Data to uint32_t
    uint32_t logLuvValue;
    memcpy(&logLuvValue, Data, sizeof(uint32_t));

    // Prepare float array for XYZ output
    float xyz[3] = {0.0f, 0.0f, 0.0f};

    // Test LogLuv24toXYZ
    LogLuv24toXYZ(logLuvValue, xyz);

    // Test LogLuv32toXYZ
    LogLuv32toXYZ(logLuvValue, xyz);

    // Test LogLuv32fromXYZ
    uint32_t logLuv32 = LogLuv32fromXYZ(xyz, 3);

    // Test LogLuv24fromXYZ
    uint32_t logLuv24 = LogLuv24fromXYZ(xyz, 1);

    // Test TIFFSwabLong
    TIFFSwabLong(&logLuvValue);

    // Prepare float array for swapping
    float floatArray[3] = {xyz[0], xyz[1], xyz[2]};
    tmsize_t numFloats = 3;

    // Test TIFFSwabArrayOfFloat
    TIFFSwabArrayOfFloat(floatArray, numFloats);

    return 0;
}