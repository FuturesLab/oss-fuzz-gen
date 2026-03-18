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
#include <cstring>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_153(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t)) {
        return 0;
    }

    // Prepare a dummy file if needed
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }

    uint32_t logluv_color;
    memcpy(&logluv_color, Data, sizeof(uint32_t));

    float xyz_output[3] = {0.0f, 0.0f, 0.0f};

    // Fuzz LogLuv24toXYZ
    LogLuv24toXYZ(logluv_color, xyz_output);

    // Fuzz LogLuv32toXYZ
    LogLuv32toXYZ(logluv_color, xyz_output);

    // Fuzz LogLuv32fromXYZ
    uint32_t logluv32 = LogLuv32fromXYZ(xyz_output, 3);

    // Fuzz TIFFSwabLong
    TIFFSwabLong(&logluv_color);

    // Fuzz TIFFSwabArrayOfFloat
    TIFFSwabArrayOfFloat(xyz_output, 3);

    // Fuzz LogLuv24fromXYZ
    uint32_t logluv24 = LogLuv24fromXYZ(xyz_output, 3);

    return 0;
}