// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFScanlineSize at tif_strip.c:343:10 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFScanlineSize at tif_strip.c:343:10 in tiffio.h
// TIFFWriteDirectory at tif_dirwrite.c:238:5 in tiffio.h
// TIFFRewriteDirectory at tif_dirwrite.c:483:5 in tiffio.h
// TIFFWriteCustomDirectory at tif_dirwrite.c:303:5 in tiffio.h
// TIFFCheckpointDirectory at tif_dirwrite.c:292:5 in tiffio.h
// TIFFDeferStrileArrayWriting at tif_dirwrite.c:268:5 in tiffio.h
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

extern "C" int LLVMFuzzerTestOneInput_141(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0; // Not enough data to proceed
    }

    // Create a dummy file to work with
    FILE *file = fopen("./dummy_file", "wb+");
    if (!file) {
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the dummy file with libtiff
    TIFF *tif = TIFFOpen("./dummy_file", "r+");
    if (!tif) {
        return 0;
    }

    // Prepare a buffer for TIFFWriteScanline
    uint32_t row = 0;
    uint16_t sample = 0;
    void *buf = malloc(TIFFScanlineSize(tif));
    if (!buf) {
        TIFFClose(tif);
        return 0;
    }
    memcpy(buf, Data, TIFFScanlineSize(tif));

    // Declare a variable for TIFFWriteCustomDirectory
    uint64_t dir_offset = 0;

    // Call the target functions with the TIFF pointer
    TIFFWriteDirectory(tif);
    TIFFRewriteDirectory(tif);
    TIFFWriteCustomDirectory(tif, &dir_offset);
    TIFFCheckpointDirectory(tif);
    TIFFWriteScanline(tif, buf, row, sample);
    TIFFDeferStrileArrayWriting(tif);

    // Clean up
    free(buf);
    TIFFClose(tif);

    return 0;
}