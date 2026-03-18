// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// TIFFGetField at tif_dir.c:1592:5 in tiffio.h
// _TIFFmalloc at tif_unix.c:333:7 in tiffio.h
// TIFFReadRGBAStrip at tif_getimage.c:3387:5 in tiffio.h
// TIFFReadRGBATile at tif_getimage.c:3462:5 in tiffio.h
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

static TIFF* openDummyTIFF(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return nullptr;
    fwrite(Data, 1, Size, file);
    fclose(file);

    return TIFFOpen("./dummy_file", "r");
}

extern "C" int LLVMFuzzerTestOneInput_96(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0; // Ensure there's enough data for meaningful operations

    TIFF *tif = openDummyTIFF(Data, Size);
    if (!tif) return 0;

    uint32_t width, height;
    uint32_t *raster = nullptr;

    // Attempt to read image dimensions
    if (TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width) && TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &height)) {
        raster = (uint32_t*) _TIFFmalloc(width * height * sizeof(uint32_t));
        if (raster) {
            // 1. Test TIFFReadRGBAImageOriented
            TIFFReadRGBAImageOriented(tif, width, height, raster, ORIENTATION_TOPLEFT, 0);

            // 2. Test TIFFReadRGBAStrip
            TIFFReadRGBAStrip(tif, 0, raster);

            // 3. Test TIFFReadRGBATile
            TIFFReadRGBATile(tif, 0, 0, raster);

            // 4. Test TIFFReadScanline
            TIFFReadScanline(tif, raster, 0, 0);

            // 5. Test TIFFReadRGBAImage
            TIFFReadRGBAImage(tif, width, height, raster, 0);

            // 6. Test TIFFReadRGBAStripExt
            TIFFReadRGBAStripExt(tif, 0, raster, 0);

            _TIFFfree(raster);
        }
    }

    TIFFClose(tif);
    return 0;
}