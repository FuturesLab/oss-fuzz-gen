// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFFlushData at tif_flush.c:146:5 in tiffio.h
// TIFFForceStrileArrayWriting at tif_flush.c:76:5 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// LogL16toY at tif_luv.c:801:5 in tiffio.h
// LogL10toY at tif_luv.c:883:5 in tiffio.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_118(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double) + sizeof(int)) return 0;

    // Prepare data for LogL10fromY
    double Y = *reinterpret_cast<const double*>(Data);
    int param = *reinterpret_cast<const int*>(Data + sizeof(double));

    // Fuzz LogL10fromY
    if (Y > 0) {
        int logL10Result = LogL10fromY(Y, param);
        (void)logL10Result; // Suppress unused variable warning
    }

    // Prepare TIFF object for TIFFFlushData and TIFFForceStrileArrayWriting
    TIFF *tif = TIFFOpen("./dummy_file", "w+");
    if (tif) {
        // Fuzz TIFFFlushData
        int flushResult = TIFFFlushData(tif);
        (void)flushResult; // Suppress unused variable warning

        // Fuzz TIFFForceStrileArrayWriting
        int forceStrileResult = TIFFForceStrileArrayWriting(tif);
        (void)forceStrileResult; // Suppress unused variable warning

        TIFFClose(tif);
    }

    // Prepare data for LogL16toY
    if (Size >= sizeof(int)) {
        int logL16 = *reinterpret_cast<const int*>(Data);
        double logL16toYResult = LogL16toY(logL16);
        (void)logL16toYResult; // Suppress unused variable warning
    }

    // Prepare data for LogL16fromY
    if (Size >= sizeof(double) + sizeof(int)) {
        int logL16fromYResult = LogL16fromY(Y, param);
        (void)logL16fromYResult; // Suppress unused variable warning
    }

    // Prepare data for LogL10toY
    if (Size >= sizeof(int)) {
        int logL10 = *reinterpret_cast<const int*>(Data);
        double logL10toYResult = LogL10toY(logL10);
        (void)logL10toYResult; // Suppress unused variable warning
    }

    return 0;
}