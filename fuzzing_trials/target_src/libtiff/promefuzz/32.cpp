// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// LogLuv24toXYZ at tif_luv.c:1032:5 in tiffio.h
// LogLuv32toXYZ at tif_luv.c:1180:5 in tiffio.h
// TIFFXYZToRGB at tif_color.c:89:6 in tiffio.h
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
#include <fstream>
#include <iostream>
#include "tiffio.h"

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t)) {
        return 0;
    }

    // Prepare a float array for XYZ values
    float xyz[3] = {0.0f, 0.0f, 0.0f};

    // Extract a uint32_t value from the data
    uint32_t logLuv24 = *reinterpret_cast<const uint32_t*>(Data);

    // Call LogLuv24toXYZ
    LogLuv24toXYZ(logLuv24, xyz);

    // Call LogLuv32fromXYZ
    uint32_t logLuv32 = LogLuv32fromXYZ(xyz, 3);

    // Call LogLuv32toXYZ
    LogLuv32toXYZ(logLuv32, xyz);

    // Prepare TIFFCIELabToRGB structure
    TIFFCIELabToRGB cielabToRgb;
    uint32_t r, g, b;

    // Call TIFFXYZToRGB
    TIFFXYZToRGB(&cielabToRgb, xyz[0], xyz[1], xyz[2], &r, &g, &b);

    // Prepare a float array for byte swapping
    size_t numFloats = Size / sizeof(float);
    float* floatArray = new float[numFloats];
    std::memcpy(floatArray, Data, numFloats * sizeof(float));

    // Call TIFFSwabArrayOfFloat
    TIFFSwabArrayOfFloat(floatArray, numFloats);

    // Clean up
    delete[] floatArray;

    // Prepare uint32_t for byte swapping
    uint32_t swabLong = logLuv32;

    // Call TIFFSwabLong
    TIFFSwabLong(&swabLong);

    return 0;
}