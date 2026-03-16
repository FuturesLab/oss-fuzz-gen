// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// LogLuv24toXYZ at tif_luv.c:1032:5 in tiffio.h
// TIFFSwabArrayOfFloat at tif_swab.c:180:6 in tiffio.h
// XYZtoRGB24 at tif_luv.c:865:5 in tiffio.h
// TIFFCIELabToXYZ at tif_color.c:43:6 in tiffio.h
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
#include <cstdlib>
#include <cstring>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_65(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(float) * 3) {
        return 0;
    }

    // Prepare dummy file
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Prepare data for LogLuv24toXYZ
    uint32_t logluv24 = 0;
    if (Size >= sizeof(uint32_t)) {
        memcpy(&logluv24, Data, sizeof(uint32_t));
    }
    float xyz[3] = {0.0f, 0.0f, 0.0f};
    LogLuv24toXYZ(logluv24, xyz);

    // Prepare data for LogLuv32fromXYZ and LogLuv24fromXYZ
    float xyzInput[3];
    memcpy(xyzInput, Data, sizeof(float) * 3);
    uint32_t logluv32 = LogLuv32fromXYZ(xyzInput, 3);
    uint32_t logluv24FromXYZ = LogLuv24fromXYZ(xyzInput, 3);

    // Prepare data for TIFFSwabArrayOfFloat
    TIFFSwabArrayOfFloat(xyzInput, 3);

    // Prepare data for XYZtoRGB24
    uint8_t rgb[3] = {0, 0, 0};
    XYZtoRGB24(xyzInput, rgb);

    // Prepare data for TIFFCIELabToXYZ
    TIFFCIELabToRGB cielabToRGB;
    uint32_t L = static_cast<uint32_t>(Data[0]);
    int32_t a = static_cast<int32_t>(Data[1]);
    int32_t b = static_cast<int32_t>(Data[2]);
    float x, y, z;
    TIFFCIELabToXYZ(&cielabToRGB, L, a, b, &x, &y, &z);

    return 0;
}