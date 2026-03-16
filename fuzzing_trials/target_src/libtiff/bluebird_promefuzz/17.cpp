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
#include <cstdarg>
#include "cstdlib"
#include "cstring"

extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Step 1: Prepare the environment
    TIFFOpenOptions *opts = TIFFOpenOptionsAlloc();
    if (!opts) {
        return 0; // Allocation failed, exit early
    }

    // Set a reasonable max single memory allocation size
    tmsize_t max_single_mem_alloc = 1024 * 1024; // 1MB
    TIFFOpenOptionsSetMaxSingleMemAlloc(opts, max_single_mem_alloc);

    // Write input data to a dummy file
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        TIFFOpenOptionsFree(opts);
        return 0; // File open failed, exit early
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Step 2: Invoke the target functions
    TIFF *tif = TIFFOpenExt("./dummy_file", "r", opts);

    // Free the options as they are no longer needed
    TIFFOpenOptionsFree(opts);

    if (tif) {
        // Set some fields, using tags and values that are typical
        TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, 100);
        TIFFSetField(tif, TIFFTAG_IMAGELENGTH, 100);

        // Write the current directory
        TIFFWriteDirectory(tif);

        // Close the TIFF handle
        TIFFClose(tif);
        tif = NULL; // Prevent further operations on freed memory
    }

    // Attempt to open the file again in write mode
    tif = TIFFOpenExt("./dummy_file", "w", NULL);
    if (tif) {
        // Set some fields again
        TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, 200);
        TIFFSetField(tif, TIFFTAG_IMAGELENGTH, 200);

        // Write the current directory again

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from TIFFSetField to TIFFWriteRawStrip
        int ret_TIFFDeferStrileArrayWriting_ypaad = TIFFDeferStrileArrayWriting(tif);
        if (ret_TIFFDeferStrileArrayWriting_ypaad < 0){
        	return 0;
        }
        tmsize_t ret_TIFFStripSize_jxwkz = TIFFStripSize(tif);

        tmsize_t ret_TIFFWriteRawStrip_fkggz = TIFFWriteRawStrip(tif, LOGLUV_PUBLIC, (void *)tif, ret_TIFFStripSize_jxwkz);

        // End mutation: Producer.APPEND_MUTATOR

        TIFFWriteDirectory(tif);

        // Close the TIFF handle
        TIFFClose(tif);
        tif = NULL; // Prevent further operations on freed memory
    }
    return 0;
}