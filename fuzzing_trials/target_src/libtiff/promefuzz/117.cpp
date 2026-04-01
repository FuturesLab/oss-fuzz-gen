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

extern "C" int LLVMFuzzerTestOneInput_117(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t)) return 0;

    // Prepare a uint32_t input for LogLuv functions and TIFFSwabLong
    uint32_t logluvInput;
    memcpy(&logluvInput, Data, sizeof(uint32_t));

    // Prepare a float array for XYZ color space
    float xyz[3] = {0.0f, 0.0f, 0.0f};

    // Fuzzing LogLuv24toXYZ
    LogLuv24toXYZ(logluvInput, xyz);

    // Fuzzing LogLuv32toXYZ
    LogLuv32toXYZ(logluvInput, xyz);

    // Fuzzing LogLuv32fromXYZ
    uint32_t logluv32Result = LogLuv32fromXYZ(xyz, 3);

    // Fuzzing TIFFSwabLong
    TIFFSwabLong(&logluvInput);

    // Prepare a float array for TIFFSwabArrayOfFloat
    float floatArray[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    if (Size >= sizeof(floatArray)) {
        memcpy(floatArray, Data, sizeof(floatArray));
    }

    // Fuzzing TIFFSwabArrayOfFloat
    TIFFSwabArrayOfFloat(floatArray, 4);

    // Fuzzing LogLuv24fromXYZ
    uint32_t logluv24Result = LogLuv24fromXYZ(xyz, 3);

    return 0;
}