// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFWriteCheck at tif_write.c:605:5 in tiffio.h
// TIFFForceStrileArrayWriting at tif_flush.c:76:5 in tiffio.h
// TIFFIsTiled at tif_open.c:864:5 in tiffio.h
// TIFFSetWriteOffset at tif_write.c:961:6 in tiffio.h
// TIFFGetStrileOffsetWithErr at tif_dirread.c:8504:10 in tiffio.h
// TIFFDeferStrileArrayWriting at tif_dirwrite.c:268:5 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
#include <iostream>
#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_51(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Create a dummy TIFF file
    const char *filename = "./dummy_file.tiff";
    FILE *file = fopen(filename, "wb");
    if (!file) {
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    TIFF *tif = TIFFOpen(filename, "r+");
    if (!tif) {
        remove(filename);
        return 0;
    }

    // Fuzz TIFFWriteCheck
    TIFFWriteCheck(tif, 1, "Test");

    // Fuzz TIFFForceStrileArrayWriting
    TIFFForceStrileArrayWriting(tif);

    // Fuzz TIFFIsTiled
    TIFFIsTiled(tif);

    // Fuzz TIFFSetWriteOffset
    if (Size >= sizeof(toff_t)) {
        toff_t offset;
        memcpy(&offset, Data, sizeof(toff_t));
        TIFFSetWriteOffset(tif, offset);
    }

    // Fuzz TIFFGetStrileOffsetWithErr
    int err = 0;
    if (Size >= sizeof(uint32_t)) {
        uint32_t strile;
        memcpy(&strile, Data, sizeof(uint32_t));
        TIFFGetStrileOffsetWithErr(tif, strile, &err);
    }

    // Fuzz TIFFDeferStrileArrayWriting
    TIFFDeferStrileArrayWriting(tif);

    TIFFClose(tif);
    remove(filename);

    return 0;
}