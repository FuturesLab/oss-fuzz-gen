// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// TIFFReadRGBAStrip at tif_getimage.c:3387:5 in tiffio.h
// TIFFReadRGBATile at tif_getimage.c:3462:5 in tiffio.h
// TIFFReadRGBAStripExt at tif_getimage.c:3393:5 in tiffio.h
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
#include <cstring>
#include <fstream>

static TIFF* openDummyTIFFFile(const uint8_t *Data, size_t Size) {
    std::ofstream ofs("./dummy_file", std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(Data), Size);
    ofs.close();
    return TIFFOpen("./dummy_file", "r");
}

extern "C" int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t) * 4) {
        return 0;
    }

    TIFF* tif = openDummyTIFFFile(Data, Size);
    if (!tif) {
        return 0;
    }

    uint32_t width = *reinterpret_cast<const uint32_t*>(Data);
    uint32_t height = *reinterpret_cast<const uint32_t*>(Data + 4);
    uint32_t row = *reinterpret_cast<const uint32_t*>(Data + 8);
    uint32_t col = *reinterpret_cast<const uint32_t*>(Data + 12);
    uint32_t* raster = new uint32_t[width * height];

    int orientation = ORIENTATION_TOPLEFT;
    TIFFReadRGBAImageOriented(tif, width, height, raster, orientation, 0);
    TIFFReadRGBAStrip(tif, row, raster);
    TIFFReadRGBATile(tif, col, row, raster);
    TIFFReadScanline(tif, raster, row, 0);
    TIFFReadRGBAImage(tif, width, height, raster, 0);
    TIFFReadRGBAStripExt(tif, row, raster, 1);

    delete[] raster;
    TIFFClose(tif);
    return 0;
}