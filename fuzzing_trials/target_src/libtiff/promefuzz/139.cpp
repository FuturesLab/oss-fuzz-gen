// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFSwabDouble at tif_swab.c:201:6 in tiffio.h
// TIFFSwabArrayOfDouble at tif_swab.c:222:6 in tiffio.h
// uv_decode at tif_luv.c:997:5 in tiffio.h
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFIsByteSwapped at tif_open.c:889:5 in tiffio.h
// TIFFIsBigEndian at tif_open.c:904:5 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
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
#include <cstring>
#include <cstdio>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_139(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return 0;

    // Prepare a double for TIFFSwabDouble
    double singleDouble;
    std::memcpy(&singleDouble, Data, sizeof(double));
    TIFFSwabDouble(&singleDouble);

    // Prepare an array of doubles for TIFFSwabArrayOfDouble
    size_t numDoubles = Size / sizeof(double);
    double *doubleArray = new double[numDoubles];
    std::memcpy(doubleArray, Data, numDoubles * sizeof(double));
    TIFFSwabArrayOfDouble(doubleArray, static_cast<tmsize_t>(numDoubles));

    // Prepare coordinates for uv_encode
    if (Size >= 2 * sizeof(double) + sizeof(int)) {
        double lat, lon;
        int precision;
        std::memcpy(&lat, Data, sizeof(double));
        std::memcpy(&lon, Data + sizeof(double), sizeof(double));
        std::memcpy(&precision, Data + 2 * sizeof(double), sizeof(int));
        uv_encode(lat, lon, precision);
    }

    // Prepare data for uv_decode
    if (Size >= sizeof(double) * 2) {
        double u, v;
        int count = static_cast<int>(Size / (2 * sizeof(double)));
        double *inputArray = new double[count * 2];
        std::memcpy(inputArray, Data, count * 2 * sizeof(double));
        uv_decode(inputArray, &u, count);
        delete[] inputArray;
    }

    // Dummy TIFF structure for TIFFIsByteSwapped and TIFFIsBigEndian
    TIFF *tiff = TIFFOpen("./dummy_file", "w");
    if (tiff) {
        TIFFIsByteSwapped(tiff);
        TIFFIsBigEndian(tiff);
        TIFFClose(tiff);
    }

    delete[] doubleArray;
    return 0;
}