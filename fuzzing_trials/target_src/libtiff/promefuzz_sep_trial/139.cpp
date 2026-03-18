// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// _TIFFmalloc at tif_unix.c:333:7 in tiffio.h
// TIFFScanlineSize at tif_strip.c:343:10 in tiffio.h
// TIFFNumberOfStrips at tif_strip.c:65:10 in tiffio.h
// TIFFClose at tif_close.c:155:6 in tiffio.h
// TIFFReadRGBAStrip at tif_getimage.c:3387:5 in tiffio.h
// TIFFReadRGBAStripExt at tif_getimage.c:3393:5 in tiffio.h
// TIFFReadRGBATile at tif_getimage.c:3462:5 in tiffio.h
// TIFFRGBAImageGet at tif_getimage.c:589:5 in tiffio.h
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

static TIFF* openDummyTIFF(const uint8_t* Data, size_t Size) {
    FILE* file = fopen("./dummy_file", "wb");
    if (!file) return nullptr;
    fwrite(Data, 1, Size, file);
    fclose(file);
    return TIFFOpen("./dummy_file", "r");
}

extern "C" int LLVMFuzzerTestOneInput_139(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    TIFF* tiff = openDummyTIFF(Data, Size);
    if (!tiff) return 0;

    uint32_t* raster = (uint32_t*)_TIFFmalloc(TIFFScanlineSize(tiff) * TIFFNumberOfStrips(tiff) * sizeof(uint32_t));
    if (!raster) {
        TIFFClose(tiff);
        return 0;
    }

    // Fuzz TIFFReadRGBAStrip
    TIFFReadRGBAStrip(tiff, 0, raster);

    // Fuzz TIFFReadRGBAImageOriented
    TIFFReadRGBAImageOriented(tiff, 100, 100, raster, ORIENTATION_TOPLEFT, 0);

    // Fuzz TIFFReadRGBAStripExt
    TIFFReadRGBAStripExt(tiff, 0, raster, 1);

    // Fuzz TIFFReadRGBAImage
    TIFFReadRGBAImage(tiff, 100, 100, raster, 0);

    // Fuzz TIFFReadRGBATile
    TIFFReadRGBATile(tiff, 0, 0, raster);

    // Prepare TIFFRGBAImage structure for TIFFRGBAImageGet
    TIFFRGBAImage img;
    memset(&img, 0, sizeof(TIFFRGBAImage));
    TIFFRGBAImageGet(&img, raster, 100, 100);

    _TIFFfree(raster);
    TIFFClose(tiff);
    return 0;
}