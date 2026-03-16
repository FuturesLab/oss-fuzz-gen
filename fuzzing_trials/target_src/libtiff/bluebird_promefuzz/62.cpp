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
#include "tiffio.h"
#include <cmath>
#include "cstring"

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

extern "C" int LLVMFuzzerTestOneInput_62(const uint8_t *Data, size_t Size) {
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