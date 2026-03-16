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
#include <cstdio>
#include "cstdint"
#include "cstdlib"
#include "cstring"

static TIFF* createDummyTIFF() {
    // Open a dummy TIFF file for reading and writing
    FILE *file = fopen("./dummy_file", "wb+");
    if (!file) return nullptr;

    // Close and reopen the file using TIFFOpen to get a TIFF handle
    fclose(file);
    return TIFFOpen("./dummy_file", "w+");
}

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    TIFF* tif = createDummyTIFF();
    if (!tif) return 0;

    // Create buffers for input and output
    void *inbuf = malloc(Size);
    void *outbuf = malloc(Size);
    if (!inbuf || !outbuf) {
        TIFFClose(tif);
        free(inbuf);
        free(outbuf);
        return 0;
    }

    // Copy data to input buffer
    memcpy(inbuf, Data, Size);

    // Test TIFFReadFromUserBuffer
    TIFFReadFromUserBuffer(tif, 0, inbuf, static_cast<tmsize_t>(Size), outbuf, static_cast<tmsize_t>(Size));

    // Test TIFFReadEncodedTile
    TIFFReadEncodedTile(tif, 0, outbuf, static_cast<tmsize_t>(Size));

    // Test TIFFPrintDirectory
    FILE *output = fopen("./dummy_output", "w");
    if (output) {
        TIFFPrintDirectory(tif, output, 0);
        fclose(output);
    }

    // Test TIFFWriteEncodedStrip
    TIFFWriteEncodedStrip(tif, 0, inbuf, static_cast<tmsize_t>(Size));

    // Test TIFFStripSize
    TIFFStripSize(tif);

    // Test TIFFReadEncodedStrip
    TIFFReadEncodedStrip(tif, 0, outbuf, static_cast<tmsize_t>(Size));

    // Cleanup
    TIFFClose(tif);
    free(inbuf);
    free(outbuf);

    return 0;
}