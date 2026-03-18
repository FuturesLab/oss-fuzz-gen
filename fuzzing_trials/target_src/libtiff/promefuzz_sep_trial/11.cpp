// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFStripSize at tif_strip.c:204:10 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// _TIFFmalloc at tif_unix.c:333:7 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFNumberOfStrips at tif_strip.c:65:10 in tiffio.h
// _TIFFfree at tif_unix.c:349:6 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFReadEncodedStrip at tif_read.c:543:10 in tiffio.h
// _TIFFfree at tif_unix.c:349:6 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
#include <iostream>
#include <tiffio.h>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    // Step 1: Prepare the environment
    // Create a dummy file to use with the TIFF functions
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return 0;

    // Write the input data to the dummy file
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the dummy file as a TIFF
    TIFF *tif = TIFFOpen("./dummy_file", "r");
    if (!tif) return 0;

    // Step 2: Invoke the target functions
    // TIFFStripSize
    tmsize_t stripSize = TIFFStripSize(tif);
    if (stripSize <= 0) {
        TIFFClose(tif);
        return 0;
    }

    // _TIFFmalloc
    void *buffer = _TIFFmalloc(stripSize);
    if (!buffer) {
        TIFFClose(tif);
        return 0;
    }

    // TIFFNumberOfStrips
    uint32_t numStrips = TIFFNumberOfStrips(tif);
    if (numStrips == 0) {
        _TIFFfree(buffer);
        TIFFClose(tif);
        return 0;
    }

    // TIFFReadEncodedStrip
    for (uint32_t strip = 0; strip < numStrips; ++strip) {
        tmsize_t bytesRead = TIFFReadEncodedStrip(tif, strip, buffer, stripSize);
        if (bytesRead == -1) {
            break;
        }
    }

    // Step 3: Cleanup
    _TIFFfree(buffer);
    TIFFClose(tif);

    return 0;
}