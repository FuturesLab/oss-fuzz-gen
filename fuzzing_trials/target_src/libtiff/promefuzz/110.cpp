// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// _TIFFmalloc at tif_unix.c:333:7 in tiffio.h
// _TIFFfree at tif_unix.c:349:6 in tiffio.h
// _TIFFmalloc at tif_unix.c:333:7 in tiffio.h
// TIFFReadRGBAStrip at tif_getimage.c:3387:5 in tiffio.h
// _TIFFfree at tif_unix.c:349:6 in tiffio.h
// _TIFFmalloc at tif_unix.c:333:7 in tiffio.h
// TIFFReadRGBATile at tif_getimage.c:3462:5 in tiffio.h
// _TIFFfree at tif_unix.c:349:6 in tiffio.h
// _TIFFmalloc at tif_unix.c:333:7 in tiffio.h
// TIFFRGBAImageGet at tif_getimage.c:589:5 in tiffio.h
// _TIFFfree at tif_unix.c:349:6 in tiffio.h
// _TIFFmalloc at tif_unix.c:333:7 in tiffio.h
// _TIFFfree at tif_unix.c:349:6 in tiffio.h
// _TIFFmalloc at tif_unix.c:333:7 in tiffio.h
// TIFFReadRGBAStripExt at tif_getimage.c:3393:5 in tiffio.h
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
#include <cstdlib>
#include <cstdio>
#include <cstring>

static TIFF* setupTIFF(const uint8_t* data, size_t size) {
    FILE* file = fopen("./dummy_file", "wb");
    if (!file) return nullptr;
    fwrite(data, 1, size, file);
    fclose(file);

    return TIFFOpen("./dummy_file", "r");
}

static void fuzz_TIFFReadRGBAImageOriented(TIFF* tif) {
    uint32_t width = 100, height = 100;
    uint32_t* raster = (uint32_t*)_TIFFmalloc(width * height * sizeof(uint32_t));
    if (raster) {
        TIFFReadRGBAImageOriented(tif, width, height, raster, ORIENTATION_TOPLEFT, 0);
        _TIFFfree(raster);
    }
}

static void fuzz_TIFFReadRGBAStrip(TIFF* tif) {
    uint32_t* raster = (uint32_t*)_TIFFmalloc(100 * sizeof(uint32_t));
    if (raster) {
        TIFFReadRGBAStrip(tif, 0, raster);
        _TIFFfree(raster);
    }
}

static void fuzz_TIFFReadRGBATile(TIFF* tif) {
    uint32_t* raster = (uint32_t*)_TIFFmalloc(100 * sizeof(uint32_t));
    if (raster) {
        TIFFReadRGBATile(tif, 0, 0, raster);
        _TIFFfree(raster);
    }
}

static void fuzz_TIFFRGBAImageGet(TIFF* tif) {
    TIFFRGBAImage img;
    uint32_t width = 100, height = 100;
    uint32_t* raster = (uint32_t*)_TIFFmalloc(width * height * sizeof(uint32_t));
    if (raster) {
        TIFFRGBAImageGet(&img, raster, width, height);
        _TIFFfree(raster);
    }
}

static void fuzz_TIFFReadRGBAImage(TIFF* tif) {
    uint32_t width = 100, height = 100;
    uint32_t* raster = (uint32_t*)_TIFFmalloc(width * height * sizeof(uint32_t));
    if (raster) {
        TIFFReadRGBAImage(tif, width, height, raster, 0);
        _TIFFfree(raster);
    }
}

static void fuzz_TIFFReadRGBAStripExt(TIFF* tif) {
    uint32_t* raster = (uint32_t*)_TIFFmalloc(100 * sizeof(uint32_t));
    if (raster) {
        TIFFReadRGBAStripExt(tif, 0, raster, 0);
        _TIFFfree(raster);
    }
}

extern "C" int LLVMFuzzerTestOneInput_110(const uint8_t *Data, size_t Size) {
    TIFF* tif = setupTIFF(Data, Size);
    if (!tif) return 0;

    fuzz_TIFFReadRGBAImageOriented(tif);
    fuzz_TIFFReadRGBAStrip(tif);
    fuzz_TIFFReadRGBATile(tif);
    fuzz_TIFFRGBAImageGet(tif);
    fuzz_TIFFReadRGBAImage(tif);
    fuzz_TIFFReadRGBAStripExt(tif);

    TIFFClose(tif);
    return 0;
}