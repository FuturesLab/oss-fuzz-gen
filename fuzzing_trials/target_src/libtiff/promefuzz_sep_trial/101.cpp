// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClientOpen at tif_open.c:289:7 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFWriteEncodedStrip at tif_write.c:215:10 in tiffio.h
// TIFFVStripSize at tif_strip.c:142:10 in tiffio.h
// TIFFReadRawStrip at tif_read.c:727:10 in tiffio.h
// TIFFStripSize at tif_strip.c:204:10 in tiffio.h
// TIFFWriteRawStrip at tif_write.c:328:10 in tiffio.h
// TIFFRawStripSize at tif_strip.c:168:10 in tiffio.h
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

static TIFF* createDummyTIFF() {
    FILE* file = fopen("./dummy_file", "wb+");
    if (!file) return nullptr;
    TIFF* tiff = TIFFClientOpen("dummy", "w+", (thandle_t)file,
                                [](thandle_t fd, void* buf, tmsize_t size) -> tmsize_t { return fread(buf, 1, size, (FILE*)fd); },
                                [](thandle_t fd, void* buf, tmsize_t size) -> tmsize_t { return fwrite(buf, 1, size, (FILE*)fd); },
                                [](thandle_t fd, toff_t off, int whence) -> toff_t { return fseek((FILE*)fd, off, whence); },
                                [](thandle_t fd) -> int { return fclose((FILE*)fd); },
                                [](thandle_t fd) -> toff_t { fseek((FILE*)fd, 0, SEEK_END); return ftell((FILE*)fd); },
                                nullptr, nullptr);
    return tiff;
}

static void destroyDummyTIFF(TIFF* tif) {
    if (tif) {
        TIFFClose(tif);
    }
}

extern "C" int LLVMFuzzerTestOneInput_101(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    TIFF* tiff = createDummyTIFF();
    if (!tiff) return 0;

    uint32_t stripIndex = Data[0] % 10;
    tmsize_t dataSize = Size - 1;
    void* dataBuffer = malloc(dataSize);
    if (!dataBuffer) {
        destroyDummyTIFF(tiff);
        return 0;
    }
    memcpy(dataBuffer, Data + 1, dataSize);

    // Test TIFFWriteEncodedStrip
    TIFFWriteEncodedStrip(tiff, stripIndex, dataBuffer, dataSize);

    // Test TIFFVStripSize
    TIFFVStripSize(tiff, stripIndex);

    // Prepare buffer for TIFFReadRawStrip
    void* readBuffer = malloc(dataSize);
    if (readBuffer) {
        // Test TIFFReadRawStrip
        TIFFReadRawStrip(tiff, stripIndex, readBuffer, dataSize);
        free(readBuffer);
    }

    // Test TIFFStripSize
    TIFFStripSize(tiff);

    // Test TIFFWriteRawStrip
    TIFFWriteRawStrip(tiff, stripIndex, dataBuffer, dataSize);

    // Test TIFFRawStripSize
    TIFFRawStripSize(tiff, stripIndex);

    free(dataBuffer);
    destroyDummyTIFF(tiff);
    return 0;
}