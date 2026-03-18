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
#include <tiffio.h>

static void fuzzTIFFSwabDouble(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return;
    double value;
    memcpy(&value, Data, sizeof(double));
    TIFFSwabDouble(&value);
}

static void fuzzTIFFSwabArrayOfDouble(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return;
    size_t numDoubles = Size / sizeof(double);
    double *array = new double[numDoubles];
    memcpy(array, Data, numDoubles * sizeof(double));
    TIFFSwabArrayOfDouble(array, numDoubles);
    delete[] array;
}

static void fuzzUVEncode(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(double) + sizeof(int)) return;
    double latitude, longitude;
    int precision;
    memcpy(&latitude, Data, sizeof(double));
    memcpy(&longitude, Data + sizeof(double), sizeof(double));
    memcpy(&precision, Data + 2 * sizeof(double), sizeof(int));
    uv_encode(latitude, longitude, precision);
}

static void fuzzUVDecode(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int count;
    memcpy(&count, Data, sizeof(int));
    if (count <= 0) return;
    size_t requiredSize = count * sizeof(double);
    if (Size < 3 * requiredSize + sizeof(int)) return;
    double *input = new double[count];
    double *outputU = new double[count];
    double *outputV = new double[count];
    memcpy(input, Data + sizeof(int), requiredSize);
    uv_decode(input, outputU, count);
    uv_decode(input, outputV, count);
    delete[] input;
    delete[] outputU;
    delete[] outputV;
}

static void fuzzTIFFIsByteSwapped(const uint8_t *Data, size_t Size) {
    TIFF *tiff = TIFFOpen("./dummy_file", "w");
    if (!tiff) return;
    TIFFIsByteSwapped(tiff);
    TIFFClose(tiff);
}

static void fuzzTIFFIsBigEndian(const uint8_t *Data, size_t Size) {
    TIFF *tiff = TIFFOpen("./dummy_file", "w");
    if (!tiff) return;
    TIFFIsBigEndian(tiff);
    TIFFClose(tiff);
}

extern "C" int LLVMFuzzerTestOneInput_128(const uint8_t *Data, size_t Size) {
    fuzzTIFFSwabDouble(Data, Size);
    fuzzTIFFSwabArrayOfDouble(Data, Size);
    fuzzUVEncode(Data, Size);
    fuzzUVDecode(Data, Size);
    fuzzTIFFIsByteSwapped(Data, Size);
    fuzzTIFFIsBigEndian(Data, Size);
    return 0;
}