// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
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
extern "C" {
#include <tiffio.h>
}

#include <cstdint>
#include <cstdio>
#include <cstdlib>

static void writeDummyFile(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

extern "C" int LLVMFuzzerTestOneInput_150(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    writeDummyFile(Data, Size);

    TIFF *tif = TIFFOpen("./dummy_file", "r");
    if (!tif) return 0;

    uint32_t width = 100, height = 100;
    uint32_t *raster = (uint32_t *)_TIFFmalloc(width * height * sizeof(uint32_t));
    if (!raster) {
        TIFFClose(tif);
        return 0;
    }

    // Fuzz TIFFReadRGBAImageOriented
    TIFFReadRGBAImageOriented(tif, width, height, raster, ORIENTATION_TOPLEFT, 0);

    // Fuzz TIFFReadRGBAStrip
    TIFFReadRGBAStrip(tif, 0, raster);

    // Fuzz TIFFReadRGBATile
    TIFFReadRGBATile(tif, 0, 0, raster);

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