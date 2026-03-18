// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpen at tif_unix.c:232:7 in tiffio.h
// _TIFFmalloc at tif_unix.c:333:7 in tiffio.h
// TIFFReadRGBAStrip at tif_getimage.c:3387:5 in tiffio.h
// TIFFReadRGBATile at tif_getimage.c:3462:5 in tiffio.h
// _TIFFfree at tif_unix.c:349:6 in tiffio.h
// TIFFReadFromUserBuffer at tif_read.c:1555:5 in tiffio.h
// TIFFCheckTile at tif_tile.c:71:5 in tiffio.h
// TIFFComputeStrip at tif_strip.c:35:10 in tiffio.h
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

static TIFF* createTIFFFile(const char* filename) {
    FILE* file = fopen(filename, "wb+");
    if (!file) return nullptr;
    fclose(file);
    return TIFFOpen(filename, "r+");
}

static void writeDummyDataToFile(const char* filename, const uint8_t* data, size_t size) {
    FILE* file = fopen(filename, "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

extern "C" int LLVMFuzzerTestOneInput_157(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0; // Ensure there's enough data for basic operations

    const char* dummyFileName = "./dummy_file";
    writeDummyDataToFile(dummyFileName, Data, Size);

    TIFF* tif = createTIFFFile(dummyFileName);
    if (!tif) return 0;

    uint32_t width = 100, height = 100;
    uint32_t* raster = (uint32_t*) _TIFFmalloc(width * height * sizeof(uint32_t));
    if (raster) {
        // Fuzz TIFFReadRGBAImageOriented
        TIFFReadRGBAImageOriented(tif, width, height, raster, ORIENTATION_TOPLEFT, 0);

        // Fuzz TIFFReadRGBAStrip
        TIFFReadRGBAStrip(tif, 0, raster);

        // Fuzz TIFFReadRGBATile
        TIFFReadRGBATile(tif, 0, 0, raster);

        _TIFFfree(raster);
    }

    // Fuzz TIFFReadFromUserBuffer
    void* outbuf = malloc(Size);
    if (outbuf) {
        TIFFReadFromUserBuffer(tif, 0, (void*)Data, Size, outbuf, Size);
        free(outbuf);
    }

    // Fuzz TIFFCheckTile
    TIFFCheckTile(tif, 0, 0, 0, 0);

    // Fuzz TIFFComputeStrip
    TIFFComputeStrip(tif, 0, 0);

    TIFFClose(tif);
    return 0;
}