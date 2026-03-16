#include <iostream>
#include "sstream"
#include <string>
#include <vector>
#include "cstring"
#include "cstdlib"
#include <cstdio>
#include "cstdint"
#include <cstddef>
#include "tiffio.h"
#include "cstdint"
#include <cstdio>
#include "cstdlib"
#include "cstring"

extern "C" int LLVMFuzzerTestOneInput_66(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Create a dummy TIFF file
    FILE *dummyFile = fopen("./dummy_file", "wb");
    if (!dummyFile) {
        return 0;
    }
    fwrite(Data, 1, Size, dummyFile);
    fclose(dummyFile);

    // Open the TIFF file
    TIFF *tif = TIFFOpen("./dummy_file", "r");
    if (!tif) {
        return 0;
    }

    // Variables for function calls
    uint32_t strile = 0;
    tmsize_t insize = static_cast<tmsize_t>(Size);
    tmsize_t outsize = static_cast<tmsize_t>(Size);
    void *inbuf = malloc(insize);
    void *outbuf = malloc(outsize);
    if (!inbuf || !outbuf) {
        TIFFClose(tif);
        free(inbuf);
        free(outbuf);
        return 0;
    }
    memcpy(inbuf, Data, insize);

    int pbErr = 0;
    
    // TIFFReadFromUserBuffer
    TIFFReadFromUserBuffer(tif, strile, inbuf, insize, outbuf, outsize);

    // TIFFClose
    TIFFClose(tif);
    tif = nullptr;

    // Reopen the TIFF file
    tif = TIFFOpen("./dummy_file", "r");
    if (!tif) {
        free(inbuf);
        free(outbuf);
        return 0;
    }

    // TIFFReadEncodedStrip
    TIFFReadEncodedStrip(tif, strile, outbuf, outsize);

    // TIFFClose
    TIFFClose(tif);
    tif = nullptr;

    // Reopen the TIFF file
    tif = TIFFOpen("./dummy_file", "r");
    if (!tif) {
        free(inbuf);
        free(outbuf);
        return 0;
    }

    // TIFFGetStrileOffsetWithErr

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of TIFFGetStrileOffsetWithErr
    TIFFGetStrileOffsetWithErr(tif, 1, &pbErr);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // TIFFGetStrileByteCountWithErr
    TIFFGetStrileByteCountWithErr(tif, strile, &pbErr);

    // TIFFClose
    TIFFClose(tif);

    // Cleanup
    free(inbuf);
    free(outbuf);

    return 0;
}