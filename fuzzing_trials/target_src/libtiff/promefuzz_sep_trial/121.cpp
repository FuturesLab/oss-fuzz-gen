// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClientOpen at tif_open.c:289:7 in tiffio.h
// TIFFSwabLong8 at tif_swab.c:60:6 in tiffio.h
// TIFFSetSubDirectory at tif_dir.c:2163:5 in tiffio.h
// TIFFScanlineSize64 at tif_strip.c:257:10 in tiffio.h
// TIFFReadDirectory at tif_dirread.c:4323:5 in tiffio.h
// TIFFTileSize64 at tif_tile.c:249:10 in tiffio.h
// TIFFCurrentDirOffset at tif_dir.c:2233:10 in tiffio.h
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

static tmsize_t tiffReadProc(thandle_t fd, void* buf, tmsize_t size) {
    return fread(buf, 1, size, (FILE*)fd);
}

static tmsize_t tiffWriteProc(thandle_t fd, void* buf, tmsize_t size) {
    return fwrite(buf, 1, size, (FILE*)fd);
}

static toff_t tiffSeekProc(thandle_t fd, toff_t off, int whence) {
    return fseek((FILE*)fd, off, whence);
}

static int tiffCloseProc(thandle_t fd) {
    return fclose((FILE*)fd);
}

static toff_t tiffSizeProc(thandle_t fd) {
    fseek((FILE*)fd, 0, SEEK_END);
    return ftell((FILE*)fd);
}

static TIFF* createDummyTIFF() {
    FILE* file = fopen("./dummy_file", "wb+");
    if (!file) return nullptr;
    TIFF* tiff = TIFFClientOpen("dummy", "w", (thandle_t)file,
                                tiffReadProc, tiffWriteProc,
                                tiffSeekProc, tiffCloseProc, tiffSizeProc,
                                nullptr, nullptr);
    if (!tiff) fclose(file);
    return tiff;
}

extern "C" int LLVMFuzzerTestOneInput_121(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint64_t)) return 0;

    uint64_t value;
    memcpy(&value, Data, sizeof(uint64_t));

    TIFFSwabLong8(&value);

    TIFF* tif = createDummyTIFF();
    if (tif) {
        TIFFSetSubDirectory(tif, value);
        TIFFScanlineSize64(tif);
        TIFFReadDirectory(tif);
        TIFFTileSize64(tif);
        TIFFCurrentDirOffset(tif);
        TIFFClose(tif);
    }

    return 0;
}