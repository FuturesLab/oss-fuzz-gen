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
#include "cstring"
#include <cstdio>

extern "C" int LLVMFuzzerTestOneInput_90(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t)) {
        return 0; // Not enough data to proceed
    }

    // Create a dummy file with the input data
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the dummy TIFF file
    TIFF *tif = TIFFOpen("./dummy_file", "r");
    if (!tif) {
        return 0;
    }

    // Use a portion of the input data to simulate a strip index or number of rows
    uint32_t stripOrRows = 0;
    memcpy(&stripOrRows, Data, sizeof(uint32_t));

    // Invoke the target API functions with the TIFF handle and simulated values

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of TIFFRawStripSize
    tmsize_t rawStripSize = TIFFRawStripSize(tif, FIELD_CUSTOM);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    tmsize_t rasterScanlineSize = TIFFRasterScanlineSize(tif);
    tmsize_t vStripSize = TIFFVStripSize(tif, stripOrRows);

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function TIFFScanlineSize with TIFFRasterScanlineSize
    tmsize_t scanlineSize = TIFFRasterScanlineSize(tif);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    tmsize_t stripSize = TIFFStripSize(tif);
    tmsize_t tileRowSize = TIFFTileRowSize(tif);

    // Handle the results (e.g., logging, further processing)
    // For fuzzing, typically we just want to ensure no crashes occur

    // Clean up
    TIFFClose(tif);

    return 0;
}