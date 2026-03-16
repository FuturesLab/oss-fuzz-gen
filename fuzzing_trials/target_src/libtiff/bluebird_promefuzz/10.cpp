#include <iostream>
#include "sstream"
#include <string>
#include <vector>
#include "cstring"
#include "cstdlib"
#include <cstdio>
#include "cstdint"
#include <cstddef>
#include "cstdint"
#include "cstdlib"
#include <cstdio>
#include "tiffio.h"

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    // Write the input data to a dummy file
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Allocate TIFFOpenOptions
    TIFFOpenOptions *options = TIFFOpenOptionsAlloc();
    if (!options) {
        return 0;
    }

    // Set options with fuzzed data
    int warn_about_unknown_tags = (Size > 0) ? Data[0] % 2 : 0;
    TIFFOpenOptionsSetWarnAboutUnknownTags(options, warn_about_unknown_tags);

    // Ensure there is enough data to safely read a tmsize_t value
    tmsize_t max_cumulated_mem_alloc = 0;
    if (Size > sizeof(tmsize_t)) {
        memcpy(&max_cumulated_mem_alloc, Data + 1, sizeof(tmsize_t));
    }
    TIFFOpenOptionsSetMaxCumulatedMemAlloc(options, max_cumulated_mem_alloc);

    // Open the TIFF file with options
    TIFF *tiff = TIFFOpenExt("./dummy_file", "r", options);
    if (tiff) {
        // Close the TIFF file if it was opened
        TIFFClose(tiff);
    }

    // Free the TIFFOpenOptions
    TIFFOpenOptionsFree(options);

    return 0;
}