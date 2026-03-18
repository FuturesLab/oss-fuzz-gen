// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFWriteEncodedStrip at tif_write.c:215:10 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFIsMSB2LSB at tif_open.c:899:5 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// LogL16toY at tif_luv.c:801:5 in tiffio.h
// TIFFReadBufferSetup at tif_read.c:1385:5 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
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
#include <iostream>
#include <fstream>
#include <tiffio.h>
#include <cmath>
#include <cstring>

static TIFF* createDummyTIFF() {
    TIFF* tif = TIFFOpen("./dummy_file", "w");
    if (tif) {
        TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, 1);
        TIFFSetField(tif, TIFFTAG_IMAGELENGTH, 1);
        TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 1);
        TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);
        TIFFSetField(tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
        TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
        TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
        char buf[1] = {0};
        TIFFWriteEncodedStrip(tif, 0, buf, 1);
        TIFFClose(tif);
    }
    return TIFFOpen("./dummy_file", "r");
}

extern "C" int LLVMFuzzerTestOneInput_123(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double) + sizeof(int)) {
        return 0;
    }

    TIFF* tif = createDummyTIFF();
    if (tif) {
        int msb2lsb = TIFFIsMSB2LSB(tif);
        (void)msb2lsb; // Use the result to avoid unused variable warning
        TIFFClose(tif);
    }

    double y = 0;
    int param = 0;
    std::memcpy(&y, Data, sizeof(double));
    std::memcpy(&param, Data + sizeof(double), sizeof(int));

    if (y > 0) {
        int logL10FromY = LogL10fromY(y, param);
        (void)logL10FromY; // Use the result to avoid unused variable warning
    }

    double logL16ToY = LogL16toY(param);
    (void)logL16ToY; // Use the result to avoid unused variable warning

    if (Size > sizeof(double) + sizeof(int) + 1) {
        void* buffer = nullptr;
        tmsize_t bufferSize = static_cast<tmsize_t>(Data[sizeof(double) + sizeof(int)]);
        if (bufferSize > 0) {
            buffer = malloc(bufferSize);
        }
        TIFF* tif = createDummyTIFF();
        if (tif) {
            TIFFReadBufferSetup(tif, buffer, bufferSize);
            TIFFClose(tif);
        }
        free(buffer);
    }

    if (y > 0) {
        int logL16FromY = LogL16fromY(y, param);
        (void)logL16FromY; // Use the result to avoid unused variable warning
    }

    double logL10ToY = LogL10toY(param);
    (void)logL10ToY; // Use the result to avoid unused variable warning

    return 0;
}