// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFReadRGBATile at tif_getimage.c:3462:5 in tiffio.h
// TIFFIsBigTIFF at tif_open.c:912:5 in tiffio.h
// TIFFGetTagListEntry at tif_extension.c:42:10 in tiffio.h
// TIFFReadDirectory at tif_dirread.c:4323:5 in tiffio.h
// TIFFSetSubDirectory at tif_dir.c:2163:5 in tiffio.h
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// _TIFFmalloc at tif_unix.c:333:7 in tiffio.h
// TIFFTileSize at tif_tile.c:253:10 in tiffio.h
// _TIFFfree at tif_unix.c:349:6 in tiffio.h
// _TIFFmalloc at tif_unix.c:333:7 in tiffio.h
// TIFFScanlineSize at tif_strip.c:343:10 in tiffio.h
// _TIFFfree at tif_unix.c:349:6 in tiffio.h
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

static void handleTIFFReadRGBATile(TIFF* tif, uint32_t* raster) {
    uint32_t col = 0, row = 0;
    TIFFReadRGBATile(tif, col, row, raster);
}

static void handleTIFFReadScanline(TIFF* tif, void* buf) {
    uint32_t row = 0;
    uint16_t sample = 0;
    TIFFReadScanline(tif, buf, row, sample);
}

static void handleTIFFIsBigTIFF(TIFF* tif) {
    TIFFIsBigTIFF(tif);
}

static void handleTIFFGetTagListEntry(TIFF* tif) {
    int tag_index = 0;
    TIFFGetTagListEntry(tif, tag_index);
}

static void handleTIFFReadDirectory(TIFF* tif) {
    TIFFReadDirectory(tif);
}

static void handleTIFFSetSubDirectory(TIFF* tif) {
    uint64_t offset = 0;
    TIFFSetSubDirectory(tif, offset);
}

extern "C" int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    const char* filename = "./dummy_file";
    FILE* file = fopen(filename, "wb");
    if (!file) {
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    TIFF* tif = TIFFOpen(filename, "r");
    if (!tif) {
        return 0;
    }

    uint32_t* raster = (uint32_t*) _TIFFmalloc(TIFFTileSize(tif));
    if (raster) {
        handleTIFFReadRGBATile(tif, raster);
        _TIFFfree(raster);
    }

    void* buf = _TIFFmalloc(TIFFScanlineSize(tif));
    if (buf) {
        handleTIFFReadScanline(tif, buf);
        _TIFFfree(buf);
    }

    handleTIFFIsBigTIFF(tif);
    handleTIFFGetTagListEntry(tif);
    handleTIFFReadDirectory(tif);
    handleTIFFSetSubDirectory(tif);

    TIFFClose(tif);
    return 0;
}