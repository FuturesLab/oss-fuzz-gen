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
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "tiffio.h"

static void fuzzTIFFSwabDouble(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return;
    double value;
    memcpy(&value, Data, sizeof(double));
    TIFFSwabDouble(&value);
}

static void fuzzTIFFSwabArrayOfDouble(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(tmsize_t) + sizeof(double)) return;
    tmsize_t n = Size / sizeof(double);
    double *array = (double*)malloc(n * sizeof(double));
    if (!array) return;
    memcpy(array, Data, n * sizeof(double));
    TIFFSwabArrayOfDouble(array, n);
    free(array);
}

static void fuzzUVEncode(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(double) + sizeof(int)) return;
    double lat, lon;
    int precision;
    memcpy(&lat, Data, sizeof(double));
    memcpy(&lon, Data + sizeof(double), sizeof(double));
    memcpy(&precision, Data + 2 * sizeof(double), sizeof(int));
    uv_encode(lat, lon, precision);
}

static void fuzzUVDecode(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int count = *(int *)Data;
    if (count <= 0 || Size < sizeof(int) + 2 * count * sizeof(double)) return;
    double *input = (double *)(Data + sizeof(int));
    double *u = (double *)malloc(count * sizeof(double));
    double *v = (double *)malloc(count * sizeof(double));
    if (!u || !v) {
        free(u);
        free(v);
        return;
    }
    uv_decode(input, u, count);
    uv_decode(input, v, count);
    free(u);
    free(v);
}

static void fuzzTIFFIsByteSwapped(const uint8_t *Data, size_t Size) {
    // Cannot directly manipulate TIFF structure due to incomplete type
    // Instead, simulate the behavior by using TIFFOpen and TIFFClose
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return;
    fwrite(Data, 1, Size, file);
    fclose(file);

    TIFF *tif = TIFFOpen("./dummy_file", "r");
    if (tif) {
        TIFFIsByteSwapped(tif);
        TIFFClose(tif);
    }
}

static void fuzzTIFFIsBigEndian(const uint8_t *Data, size_t Size) {
    // Cannot directly manipulate TIFF structure due to incomplete type
    // Instead, simulate the behavior by using TIFFOpen and TIFFClose
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return;
    fwrite(Data, 1, Size, file);
    fclose(file);

    TIFF *tif = TIFFOpen("./dummy_file", "r");
    if (tif) {
        TIFFIsBigEndian(tif);
        TIFFClose(tif);
    }
}

extern "C" int LLVMFuzzerTestOneInput_147(const uint8_t *Data, size_t Size) {
    fuzzTIFFSwabDouble(Data, Size);
    fuzzTIFFSwabArrayOfDouble(Data, Size);
    fuzzUVEncode(Data, Size);
    fuzzUVDecode(Data, Size);
    fuzzTIFFIsByteSwapped(Data, Size);
    fuzzTIFFIsBigEndian(Data, Size);
    return 0;
}