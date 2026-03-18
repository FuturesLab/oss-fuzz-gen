// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFScanlineSize at tif_strip.c:343:10 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
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
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

static void createDummyFile(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

extern "C" int LLVMFuzzerTestOneInput_109(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Create a dummy file with the provided data
    createDummyFile(Data, Size);

    // Open the TIFF file
    TIFF *tif = TIFFOpen("./dummy_file", "r+");
    if (!tif) {
        return 0;
    }

    // Prepare a buffer for scanline writing
    void *buf = malloc(TIFFScanlineSize(tif));
    if (!buf) {
        TIFFClose(tif);
        return 0;
    }

    // Attempt to write scanline
    TIFFWriteScanline(tif, buf, 0, 0);

    // Attempt to write the directory
    TIFFWriteDirectory(tif);

    // Attempt to rewrite the directory
    TIFFRewriteDirectory(tif);

    // Attempt to write a custom directory
    uint64_t dir_offset = 0;
    TIFFWriteCustomDirectory(tif, &dir_offset);

    // Attempt to checkpoint the directory
    TIFFCheckpointDirectory(tif);

    // Attempt to defer strile array writing
    TIFFDeferStrileArrayWriting(tif);

    // Clean up
    free(buf);
    TIFFClose(tif);

    return 0;
}