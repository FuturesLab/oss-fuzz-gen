// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpenOptionsAlloc at tif_open.c:80:18 in tiffio.h
// TIFFOpenOptionsSetMaxSingleMemAlloc at tif_open.c:94:6 in tiffio.h
// TIFFOpenExt at tif_unix.c:237:7 in tiffio.h
// TIFFOpenOptionsFree at tif_open.c:87:6 in tiffio.h
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
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare a dummy file
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Allocate TIFFOpenOptions
    TIFFOpenOptions *options = TIFFOpenOptionsAlloc();
    if (!options) return 0;

    // Set maximum single memory allocation
    tmsize_t max_mem_alloc = static_cast<tmsize_t>(Data[0]);
    TIFFOpenOptionsSetMaxSingleMemAlloc(options, max_mem_alloc);

    // Open TIFF file with options
    TIFF *tif = TIFFOpenExt("./dummy_file", "r", options);

    // Free TIFFOpenOptions
    TIFFOpenOptionsFree(options);

    if (tif) {
        // Set fields using TIFFSetField, using arbitrary tag and values
        TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, 100);
        TIFFSetField(tif, TIFFTAG_IMAGELENGTH, 100);

        // Write directory
        TIFFWriteDirectory(tif);

        // Close TIFF file
        TIFFClose(tif);
    }

    // Remove the dummy file
    remove("./dummy_file");

    return 0;
}