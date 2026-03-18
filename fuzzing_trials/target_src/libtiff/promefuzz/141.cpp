// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// _TIFFmalloc at tif_unix.c:333:7 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFReadRGBAStrip at tif_getimage.c:3387:5 in tiffio.h
// TIFFReadRGBATile at tif_getimage.c:3462:5 in tiffio.h
// TIFFRGBAImageGet at tif_getimage.c:589:5 in tiffio.h
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
#include <cstdio>
#include <cstdlib>
#include <cstring>

static TIFF *openDummyTiff(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return nullptr;
    fwrite(Data, 1, Size, file);
    fclose(file);
    return TIFFOpen("./dummy_file", "r");
}

extern "C" int LLVMFuzzerTestOneInput_141(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0; // Minimum size check for meaningful data

    TIFF *tif = openDummyTiff(Data, Size);
    if (!tif) return 0;

    uint32_t width = 0, height = 0;
    TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width);
    TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &height);

    uint32_t *raster = (uint32_t *)_TIFFmalloc(width * height * sizeof(uint32_t));
    if (!raster) {
        TIFFClose(tif);
        return 0;
    }

    // Fuzz TIFFReadRGBAImageOriented
    for (int orientation = 0; orientation <= 8; ++orientation) {
        TIFFReadRGBAImageOriented(tif, width, height, raster, orientation, 0);
    }

    // Fuzz TIFFReadRGBAStrip
    if (height > 0) {
        TIFFReadRGBAStrip(tif, 0, raster);
    }

    // Fuzz TIFFReadRGBATile
    if (width > 0 && height > 0) {
        TIFFReadRGBATile(tif, 0, 0, raster);
    }

    // Fuzz TIFFRGBAImageGet
    TIFFRGBAImage img;
    img.tif = tif;
    img.width = width;
    img.get = nullptr;
    TIFFRGBAImageGet(&img, raster, width, height);

    // Fuzz TIFFReadRGBAImage
    TIFFReadRGBAImage(tif, width, height, raster, 0);

    // Fuzz TIFFReadRGBAStripExt
    TIFFReadRGBAStripExt(tif, 0, raster, 0);

    _TIFFfree(raster);
    TIFFClose(tif);
    return 0;
}