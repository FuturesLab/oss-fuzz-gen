// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFSwabArrayOfDouble at tif_swab.c:222:6 in tiffio.h
// TIFFSwabArrayOfLong8 at tif_swab.c:138:6 in tiffio.h
// TIFFSwabArrayOfTriples at tif_swab.c:99:6 in tiffio.h
// TIFFSwabArrayOfLong at tif_swab.c:117:6 in tiffio.h
// TIFFSwabArrayOfShort at tif_swab.c:81:6 in tiffio.h
// TIFFSwabLong8 at tif_swab.c:60:6 in tiffio.h
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
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_131(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double) && Size < sizeof(uint64_t) && Size < sizeof(uint32_t) && Size < sizeof(uint16_t)) {
        return 0;
    }

    // Prepare data for TIFFSwabArrayOfDouble
    if (Size >= sizeof(double)) {
        size_t numDoubles = Size / sizeof(double);
        double *doubleArray = new double[numDoubles];
        std::memcpy(doubleArray, Data, numDoubles * sizeof(double));
        TIFFSwabArrayOfDouble(doubleArray, numDoubles);
        delete[] doubleArray;
    }

    // Prepare data for TIFFSwabArrayOfLong8
    if (Size >= sizeof(uint64_t)) {
        size_t numLong8 = Size / sizeof(uint64_t);
        uint64_t *long8Array = new uint64_t[numLong8];
        std::memcpy(long8Array, Data, numLong8 * sizeof(uint64_t));
        TIFFSwabArrayOfLong8(long8Array, numLong8);
        delete[] long8Array;
    }

    // Prepare data for TIFFSwabArrayOfTriples
    if (Size >= 3) {
        size_t numTriples = Size / 3;
        uint8_t *triplesArray = new uint8_t[numTriples * 3];
        std::memcpy(triplesArray, Data, numTriples * 3);
        TIFFSwabArrayOfTriples(triplesArray, numTriples);
        delete[] triplesArray;
    }

    // Prepare data for TIFFSwabArrayOfLong
    if (Size >= sizeof(uint32_t)) {
        size_t numLongs = Size / sizeof(uint32_t);
        uint32_t *longArray = new uint32_t[numLongs];
        std::memcpy(longArray, Data, numLongs * sizeof(uint32_t));
        TIFFSwabArrayOfLong(longArray, numLongs);
        delete[] longArray;
    }

    // Prepare data for TIFFSwabArrayOfShort
    if (Size >= sizeof(uint16_t)) {
        size_t numShorts = Size / sizeof(uint16_t);
        uint16_t *shortArray = new uint16_t[numShorts];
        std::memcpy(shortArray, Data, numShorts * sizeof(uint16_t));
        TIFFSwabArrayOfShort(shortArray, numShorts);
        delete[] shortArray;
    }

    // Prepare data for TIFFSwabLong8
    if (Size >= sizeof(uint64_t)) {
        uint64_t long8;
        std::memcpy(&long8, Data, sizeof(uint64_t));
        TIFFSwabLong8(&long8);
    }

    return 0;
}