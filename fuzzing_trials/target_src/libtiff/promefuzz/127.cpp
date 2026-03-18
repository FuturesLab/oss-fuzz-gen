// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFWriteCustomDirectory at tif_dirwrite.c:303:5 in tiffio.h
// TIFFCheckpointDirectory at tif_dirwrite.c:292:5 in tiffio.h
// TIFFWriteDirectory at tif_dirwrite.c:238:5 in tiffio.h
// TIFFRewriteDirectory at tif_dirwrite.c:483:5 in tiffio.h
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
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_127(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Create a dummy TIFF file
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tif = TIFFOpen("./dummy_file", "r+");
    if (!tif) {
        return 0;
    }

    // Buffer for scanline data
    uint8_t buf[1024];
    memset(buf, 0, sizeof(buf));

    // Variables for use with target functions
    uint64_t dir_offset = 0;
    uint32_t row = 0;
    uint16_t sample = 0;

    // Invoke TIFFWriteCustomDirectory
    TIFFWriteCustomDirectory(tif, &dir_offset);

    // Invoke TIFFCheckpointDirectory
    TIFFCheckpointDirectory(tif);

    // Invoke TIFFWriteDirectory
    TIFFWriteDirectory(tif);

    // Invoke TIFFRewriteDirectory
    TIFFRewriteDirectory(tif);

    // Invoke TIFFWriteScanline
    TIFFWriteScanline(tif, buf, row, sample);

    // Invoke TIFFDeferStrileArrayWriting
    TIFFDeferStrileArrayWriting(tif);

    // Close the TIFF file
    TIFFClose(tif);

    return 0;
}