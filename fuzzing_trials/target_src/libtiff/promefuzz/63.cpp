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
#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstring>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_63(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return 0;

    // Prepare a double for TIFFSwabDouble
    double singleDouble;
    memcpy(&singleDouble, Data, sizeof(double));
    TIFFSwabDouble(&singleDouble);

    // Prepare an array of doubles for TIFFSwabArrayOfDouble
    if (Size >= 2 * sizeof(double)) {
        size_t numDoubles = Size / sizeof(double);
        double *doubleArray = new double[numDoubles];
        memcpy(doubleArray, Data, numDoubles * sizeof(double));
        TIFFSwabArrayOfDouble(doubleArray, static_cast<tmsize_t>(numDoubles));
        delete[] doubleArray;
    }

    // Use uv_encode with two doubles and an int
    if (Size >= 2 * sizeof(double) + sizeof(int)) {
        double latitude, longitude;
        int precision;
        memcpy(&latitude, Data, sizeof(double));
        memcpy(&longitude, Data + sizeof(double), sizeof(double));
        memcpy(&precision, Data + 2 * sizeof(double), sizeof(int));
        uv_encode(latitude, longitude, precision);
    }
    
    // Use uv_decode with input and output arrays
    if (Size >= 2 * sizeof(double) + sizeof(int)) {
        int numDoubles = Size / sizeof(double);
        double *inputArray = new double[numDoubles];
        double *uArray = new double[numDoubles];
        double *vArray = new double[numDoubles];
        memcpy(inputArray, Data, numDoubles * sizeof(double));
        uv_decode(inputArray, uArray, numDoubles);
        delete[] inputArray;
        delete[] uArray;
        delete[] vArray;
    }

    // Prepare a dummy TIFF structure for TIFFIsByteSwapped and TIFFIsBigEndian
    // Since we can't directly allocate a TIFF struct, we simulate with a dummy file
    std::ofstream dummyFile("./dummy_file");
    if (dummyFile.is_open()) {
        dummyFile.write(reinterpret_cast<const char*>(Data), Size);
        dummyFile.close();

        TIFF* tiffStruct = TIFFOpen("./dummy_file", "r");
        if (tiffStruct) {
            TIFFIsByteSwapped(tiffStruct);
            TIFFIsBigEndian(tiffStruct);
            TIFFClose(tiffStruct);
        }
    }

    return 0;
}