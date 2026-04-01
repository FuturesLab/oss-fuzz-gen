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
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t)) {
        return 0;
    }

    uint32_t logluvValue;
    std::memcpy(&logluvValue, Data, sizeof(uint32_t));

    // Buffer for XYZ output
    float xyz[3] = {0.0f, 0.0f, 0.0f};

    // Fuzz LogLuv24toXYZ
    LogLuv24toXYZ(logluvValue, xyz);

    // Fuzz LogLuv32toXYZ
    LogLuv32toXYZ(logluvValue, xyz);

    // Prepare input for LogLuv24fromXYZ
    if (Size >= sizeof(float) * 3 + sizeof(int)) {
        float inputXYZ[3];
        std::memcpy(inputXYZ, Data, sizeof(float) * 3);
        int numPixels;
        std::memcpy(&numPixels, Data + sizeof(float) * 3, sizeof(int));

        // Fuzz LogLuv24fromXYZ
        LogLuv24fromXYZ(inputXYZ, numPixels);
    }

    // Prepare input for TIFFXYZToRGB
    if (Size >= sizeof(float) * 3 + sizeof(TIFFCIELabToRGB)) {
        TIFFCIELabToRGB cielabToRGB;
        float x, y, z;
        std::memcpy(&cielabToRGB, Data, sizeof(TIFFCIELabToRGB));
        std::memcpy(&x, Data, sizeof(float));
        std::memcpy(&y, Data + sizeof(float), sizeof(float));
        std::memcpy(&z, Data + sizeof(float) * 2, sizeof(float));

        uint32_t r, g, b;
        TIFFXYZToRGB(&cielabToRGB, x, y, z, &r, &g, &b);
    }

    // Prepare input for TIFFSwabArrayOfFloat
    if (Size >= sizeof(float)) {
        tmsize_t n = Size / sizeof(float);
        if (n > 0) {
            float *floatArray = new float[n];
            std::memcpy(floatArray, Data, n * sizeof(float));

            // Fuzz TIFFSwabArrayOfFloat
            TIFFSwabArrayOfFloat(floatArray, n);

            delete[] floatArray;
        }
    }

    // Fuzz TIFFSwabLong
    TIFFSwabLong(&logluvValue);

    return 0;
}