#include <iostream>
#include "sstream"
#include <string>
#include <vector>
#include "cstring"
#include "cstdlib"
#include <cstdio>
#include "cstdint"
#include <cstddef>
#include <iostream>
#include <fstream>
#include "cstdint"
#include "cstring"
#include "tiffio.h"

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) {
        return 0;
    }

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

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from TIFFOpen to TIFFRewriteDirectory

        int ret_TIFFRewriteDirectory_ukcun = TIFFRewriteDirectory(tiffStruct);
        if (ret_TIFFRewriteDirectory_ukcun < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

            TIFFClose(tiffStruct);
        }    }

    return 0;
}