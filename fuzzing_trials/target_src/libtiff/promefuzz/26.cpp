// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFSwabArrayOfDouble at tif_swab.c:222:6 in tiffio.h
// TIFFSwabDouble at tif_swab.c:201:6 in tiffio.h
// TIFFSwabArrayOfTriples at tif_swab.c:99:6 in tiffio.h
// TIFFSwabArrayOfLong at tif_swab.c:117:6 in tiffio.h
// TIFFSwabArrayOfShort at tif_swab.c:81:6 in tiffio.h
// TIFFSwabArrayOfFloat at tif_swab.c:180:6 in tiffio.h
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
#include <fstream>
#include <iostream>
#include <tiffio.h>

static void fuzz_TIFFSwabArrayOfDouble(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return;
    size_t num_doubles = Size / sizeof(double);
    double *doubles = new double[num_doubles];
    std::memcpy(doubles, Data, num_doubles * sizeof(double));
    TIFFSwabArrayOfDouble(doubles, num_doubles);
    delete[] doubles;
}

static void fuzz_TIFFSwabDouble(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return;
    double value;
    std::memcpy(&value, Data, sizeof(double));
    TIFFSwabDouble(&value);
}

static void fuzz_TIFFSwabArrayOfTriples(const uint8_t *Data, size_t Size) {
    if (Size < 3) return;
    size_t num_triples = Size / 3;
    uint8_t *triples = new uint8_t[num_triples * 3];
    std::memcpy(triples, Data, num_triples * 3);
    TIFFSwabArrayOfTriples(triples, num_triples);
    delete[] triples;
}

static void fuzz_TIFFSwabArrayOfLong(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t)) return;
    size_t num_longs = Size / sizeof(uint32_t);
    uint32_t *longs = new uint32_t[num_longs];
    std::memcpy(longs, Data, num_longs * sizeof(uint32_t));
    TIFFSwabArrayOfLong(longs, num_longs);
    delete[] longs;
}

static void fuzz_TIFFSwabArrayOfShort(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint16_t)) return;
    size_t num_shorts = Size / sizeof(uint16_t);
    uint16_t *shorts = new uint16_t[num_shorts];
    std::memcpy(shorts, Data, num_shorts * sizeof(uint16_t));
    TIFFSwabArrayOfShort(shorts, num_shorts);
    delete[] shorts;
}

static void fuzz_TIFFSwabArrayOfFloat(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(float)) return;
    size_t num_floats = Size / sizeof(float);
    float *floats = new float[num_floats];
    std::memcpy(floats, Data, num_floats * sizeof(float));
    TIFFSwabArrayOfFloat(floats, num_floats);
    delete[] floats;
}

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    fuzz_TIFFSwabArrayOfDouble(Data, Size);
    fuzz_TIFFSwabDouble(Data, Size);
    fuzz_TIFFSwabArrayOfTriples(Data, Size);
    fuzz_TIFFSwabArrayOfLong(Data, Size);
    fuzz_TIFFSwabArrayOfShort(Data, Size);
    fuzz_TIFFSwabArrayOfFloat(Data, Size);
    return 0;
}