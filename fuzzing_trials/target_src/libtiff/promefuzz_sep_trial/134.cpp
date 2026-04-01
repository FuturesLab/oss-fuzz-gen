// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFWriteDirectory at tif_dirwrite.c:238:5 in tiffio.h
// TIFFRewriteDirectory at tif_dirwrite.c:483:5 in tiffio.h
// TIFFWriteCustomDirectory at tif_dirwrite.c:303:5 in tiffio.h
// TIFFCheckpointDirectory at tif_dirwrite.c:292:5 in tiffio.h
// TIFFForceStrileArrayWriting at tif_flush.c:76:5 in tiffio.h
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

static TIFF* initializeTIFF(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return nullptr;
    fwrite(Data, 1, Size, file);
    fclose(file);

    return TIFFOpen("./dummy_file", "r+");
}

extern "C" int LLVMFuzzerTestOneInput_134(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    TIFF *tif = initializeTIFF(Data, Size);
    if (!tif) return 0;

    uint64_t dir_offset;
    uint32_t row = 0;
    uint16_t sample = 0;

    TIFFWriteDirectory(tif);
    TIFFRewriteDirectory(tif);
    TIFFWriteCustomDirectory(tif, &dir_offset);
    TIFFCheckpointDirectory(tif);
    TIFFForceStrileArrayWriting(tif);

    if (Size > sizeof(uint32_t)) {
        void *buf = malloc(Size);
        if (buf) {
            memcpy(buf, Data, Size);
            TIFFWriteScanline(tif, buf, row, sample);
            free(buf);
        }
    }

    TIFFClose(tif);
    return 0;
}