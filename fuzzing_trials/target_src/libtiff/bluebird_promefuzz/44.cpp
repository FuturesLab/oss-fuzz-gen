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

extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size) {
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
        TIFFReadWriteProc ret_TIFFGetWriteProc_gbkfg = TIFFGetWriteProc(tif);
        int ret_TIFFFieldSetGetCountSize_ytelw = TIFFFieldSetGetCountSize(NULL);
        if (ret_TIFFFieldSetGetCountSize_ytelw < 0){
        	return 0;
        }
        tmsize_t ret_TIFFTileSize_ibfyr = TIFFTileSize(tif);

        tmsize_t ret_TIFFWriteRawStrip_afsmo = TIFFWriteRawStrip(tif, (uint32_t )ret_TIFFFieldSetGetCountSize_ytelw, (void *)tif, ret_TIFFTileSize_ibfyr);

        // End mutation: Producer.APPEND_MUTATOR

        TIFFWriteDirectory(tif);

        // Close the TIFF handle
        TIFFClose(tif);
        tif = NULL; // Prevent further operations on freed memory
    }
    return 0;
}