// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpenOptionsAlloc at tif_open.c:80:18 in tiffio.h
// TIFFOpenOptionsSetMaxSingleMemAlloc at tif_open.c:94:6 in tiffio.h
// TIFFOpenOptionsFree at tif_open.c:87:6 in tiffio.h
// TIFFOpenExt at tif_unix.c:237:7 in tiffio.h
// TIFFOpenOptionsFree at tif_open.c:87:6 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFWriteDirectory at tif_dirwrite.c:238:5 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFOpenExt at tif_unix.c:237:7 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFSetField at tif_dir.c:1152:5 in tiffio.h
// TIFFWriteDirectory at tif_dirwrite.c:238:5 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
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
#include <cstdarg>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
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
        TIFFWriteDirectory(tif);

        // Close the TIFF handle
        TIFFClose(tif);
        tif = NULL; // Prevent further operations on freed memory
    }

    return 0;
}