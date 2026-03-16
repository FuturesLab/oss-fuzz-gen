// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFWriteDirectory at tif_dirwrite.c:238:5 in tiffio.h
// TIFFRewriteDirectory at tif_dirwrite.c:483:5 in tiffio.h
// TIFFWriteCustomDirectory at tif_dirwrite.c:303:5 in tiffio.h
// TIFFCheckpointDirectory at tif_dirwrite.c:292:5 in tiffio.h
// TIFFForceStrileArrayWriting at tif_flush.c:76:5 in tiffio.h
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

static void writeDummyFile(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

static TIFF* openTiffFile() {
    return TIFFOpen("./dummy_file", "w+");
}

static void closeTiffFile(TIFF *tif) {
    if (tif) {
        TIFFClose(tif);
    }
}

extern "C" int LLVMFuzzerTestOneInput_130(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    writeDummyFile(Data, Size);

    TIFF *tif = openTiffFile();
    if (!tif) return 0;

    uint64_t offset = 0;
    uint32_t row = 0;
    uint16_t sample = 0;
    void *buf = malloc(1); // Minimal buffer allocation for TIFFWriteScanline
    if (!buf) {
        closeTiffFile(tif);
        return 0;
    }

    // Fuzz different functions
    TIFFWriteDirectory(tif);
    TIFFRewriteDirectory(tif);
    TIFFWriteCustomDirectory(tif, &offset);
    TIFFCheckpointDirectory(tif);
    TIFFForceStrileArrayWriting(tif);
    TIFFWriteScanline(tif, buf, row, sample);

    free(buf);
    closeTiffFile(tif);

    return 0;
}