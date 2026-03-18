// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFSwabDouble at tif_swab.c:201:6 in tiffio.h
// TIFFSwabArrayOfDouble at tif_swab.c:222:6 in tiffio.h
// uv_decode at tif_luv.c:997:5 in tiffio.h
// uv_decode at tif_luv.c:997:5 in tiffio.h
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFIsByteSwapped at tif_open.c:889:5 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
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
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "tiffio.h"

static void fuzz_TIFFSwabDouble(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return;

    double value;
    memcpy(&value, Data, sizeof(double));
    TIFFSwabDouble(&value);
}

static void fuzz_TIFFSwabArrayOfDouble(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return;

    tmsize_t count = static_cast<tmsize_t>(Size / sizeof(double));
    double *array = new double[count];
    memcpy(array, Data, count * sizeof(double));
    TIFFSwabArrayOfDouble(array, count);
    delete[] array;
}

static void fuzz_uv_encode(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(double) + sizeof(int)) return;

    double lat, lon;
    int precision;
    memcpy(&lat, Data, sizeof(double));
    memcpy(&lon, Data + sizeof(double), sizeof(double));
    memcpy(&precision, Data + 2 * sizeof(double), sizeof(int));
    uv_encode(lat, lon, precision);
}

static void fuzz_uv_decode(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double) * 2 + sizeof(int)) return;

    int count = static_cast<int>((Size - sizeof(int)) / (2 * sizeof(double)));
    double *input = new double[count * 2];
    double *outputU = new double[count];
    double *outputV = new double[count];

    memcpy(input, Data, count * 2 * sizeof(double));
    uv_decode(input, outputU, count);
    uv_decode(input, outputV, count);

    delete[] input;
    delete[] outputU;
    delete[] outputV;
}

static void fuzz_TIFFIsByteSwapped() {
    // Create a dummy TIFF structure
    TIFF *tiff = TIFFOpen("./dummy_file", "r");
    if (tiff) {
        TIFFIsByteSwapped(tiff);
        TIFFClose(tiff);
    }
}

static void fuzz_TIFFIsBigEndian() {
    // Create a dummy TIFF structure
    TIFF *tiff = TIFFOpen("./dummy_file", "r");
    if (tiff) {
        TIFFIsBigEndian(tiff);
        TIFFClose(tiff);
    }
}

extern "C" int LLVMFuzzerTestOneInput_91(const uint8_t *Data, size_t Size) {
    fuzz_TIFFSwabDouble(Data, Size);
    fuzz_TIFFSwabArrayOfDouble(Data, Size);
    fuzz_uv_encode(Data, Size);
    fuzz_uv_decode(Data, Size);
    fuzz_TIFFIsByteSwapped();
    fuzz_TIFFIsBigEndian();

    return 0;
}