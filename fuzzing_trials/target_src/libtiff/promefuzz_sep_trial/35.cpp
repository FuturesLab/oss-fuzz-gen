// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFSwabDouble at tif_swab.c:201:6 in tiffio.h
// TIFFSwabArrayOfDouble at tif_swab.c:222:6 in tiffio.h
// TIFFSwabArrayOfFloat at tif_swab.c:180:6 in tiffio.h
// TIFFSwabArrayOfShort at tif_swab.c:81:6 in tiffio.h
// TIFFSwabArrayOfLong8 at tif_swab.c:138:6 in tiffio.h
// TIFFSwabArrayOfTriples at tif_swab.c:99:6 in tiffio.h
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

static void fuzzTIFFSwabDouble(const uint8_t *Data, size_t Size) {
    if (Size >= sizeof(double)) {
        double value;
        memcpy(&value, Data, sizeof(double));
        TIFFSwabDouble(&value);
    }
}

static void fuzzTIFFSwabArrayOfDouble(const uint8_t *Data, size_t Size) {
    if (Size >= sizeof(double)) {
        tmsize_t n = Size / sizeof(double);
        double *array = reinterpret_cast<double*>(malloc(n * sizeof(double)));
        if (array) {
            memcpy(array, Data, n * sizeof(double));
            TIFFSwabArrayOfDouble(array, n);
            free(array);
        }
    }
}

static void fuzzTIFFSwabArrayOfFloat(const uint8_t *Data, size_t Size) {
    if (Size >= sizeof(float)) {
        tmsize_t n = Size / sizeof(float);
        float *array = reinterpret_cast<float*>(malloc(n * sizeof(float)));
        if (array) {
            memcpy(array, Data, n * sizeof(float));
            TIFFSwabArrayOfFloat(array, n);
            free(array);
        }
    }
}

static void fuzzTIFFSwabArrayOfShort(const uint8_t *Data, size_t Size) {
    if (Size >= sizeof(uint16_t)) {
        tmsize_t n = Size / sizeof(uint16_t);
        uint16_t *array = reinterpret_cast<uint16_t*>(malloc(n * sizeof(uint16_t)));
        if (array) {
            memcpy(array, Data, n * sizeof(uint16_t));
            TIFFSwabArrayOfShort(array, n);
            free(array);
        }
    }
}

static void fuzzTIFFSwabArrayOfLong8(const uint8_t *Data, size_t Size) {
    if (Size >= sizeof(uint64_t)) {
        tmsize_t n = Size / sizeof(uint64_t);
        uint64_t *array = reinterpret_cast<uint64_t*>(malloc(n * sizeof(uint64_t)));
        if (array) {
            memcpy(array, Data, n * sizeof(uint64_t));
            TIFFSwabArrayOfLong8(array, n);
            free(array);
        }
    }
}

static void fuzzTIFFSwabArrayOfTriples(const uint8_t *Data, size_t Size) {
    if (Size >= 3) {
        tmsize_t n = Size / 3;
        uint8_t *array = reinterpret_cast<uint8_t*>(malloc(n * 3));
        if (array) {
            memcpy(array, Data, n * 3);
            TIFFSwabArrayOfTriples(array, n);
            free(array);
        }
    }
}

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
    fuzzTIFFSwabDouble(Data, Size);
    fuzzTIFFSwabArrayOfDouble(Data, Size);
    fuzzTIFFSwabArrayOfFloat(Data, Size);
    fuzzTIFFSwabArrayOfShort(Data, Size);
    fuzzTIFFSwabArrayOfLong8(Data, Size);
    fuzzTIFFSwabArrayOfTriples(Data, Size);
    return 0;
}