// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFSwabDouble at tif_swab.c:201:6 in tiffio.h
// TIFFSwabArrayOfDouble at tif_swab.c:222:6 in tiffio.h
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFIsBigEndian at tif_open.c:904:5 in tiffio.h
// TIFFIsByteSwapped at tif_open.c:889:5 in tiffio.h
// uv_decode at tif_luv.c:997:5 in tiffio.h
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
#include <cstdlib>
#include <tiffio.h>
#include <iostream>

extern "C" int LLVMFuzzerTestOneInput_62(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double) * 2 + sizeof(int)) {
        return 0;
    }

    // Prepare a double for TIFFSwabDouble
    double swab_double;
    memcpy(&swab_double, Data, sizeof(double));
    TIFFSwabDouble(&swab_double);

    // Prepare an array of doubles for TIFFSwabArrayOfDouble
    double *array_of_doubles = reinterpret_cast<double *>(malloc(Size));
    if (!array_of_doubles) {
        return 0;
    }
    memcpy(array_of_doubles, Data, Size);
    tmsize_t num_doubles = Size / sizeof(double);
    TIFFSwabArrayOfDouble(array_of_doubles, num_doubles);

    // Prepare a dummy TIFF structure for TIFFIsBigEndian and TIFFIsByteSwapped
    TIFF *tiff = TIFFOpen("./dummy_file", "w");
    if (!tiff) {
        free(array_of_doubles);
        return 0;
    }
    TIFFIsBigEndian(tiff);
    TIFFIsByteSwapped(tiff);

    // Prepare data for uv_encode
    double lat, lon;
    int precision;
    memcpy(&lat, Data, sizeof(double));
    memcpy(&lon, Data + sizeof(double), sizeof(double));
    memcpy(&precision, Data + sizeof(double) * 2, sizeof(int));
    uv_encode(lat, lon, precision);

    // Prepare data for uv_decode
    double *u = reinterpret_cast<double *>(malloc(num_doubles * sizeof(double)));
    double *v = reinterpret_cast<double *>(malloc(num_doubles * sizeof(double)));
    if (u && v) {
        uv_decode(array_of_doubles, u, num_doubles);
    }

    // Cleanup
    free(array_of_doubles);
    TIFFClose(tiff);
    free(u);
    free(v);

    return 0;
}