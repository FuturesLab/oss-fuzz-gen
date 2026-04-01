// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpenOptionsAlloc at tif_open.c:80:18 in tiffio.h
// TIFFOpenOptionsSetWarnAboutUnknownTags at tif_open.c:115:6 in tiffio.h
// TIFFOpenOptionsSetMaxCumulatedMemAlloc at tif_open.c:106:6 in tiffio.h
// TIFFOpenExt at tif_unix.c:237:7 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFOpenOptionsFree at tif_open.c:87:6 in tiffio.h
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
#include <cstdio>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_77(const uint8_t *Data, size_t Size) {
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