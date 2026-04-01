#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    // Initialize TIFF structure
    TIFF *tif = TIFFOpen("/tmp/fuzzfile.tiff", "w");
    if (tif == nullptr) {
        return 0;
    }

    // Set up some basic TIFF fields
    TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, 1);
    TIFFSetField(tif, TIFFTAG_IMAGELENGTH, 1);
    TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 1);
    TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);
    TIFFSetField(tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
    TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
    TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);

    // Ensure the data size is not zero and allocate a buffer for the tile
    tmsize_t tileSize = static_cast<tmsize_t>(size);
    if (tileSize == 0) {
        tileSize = 1;
    }
    void *tileBuffer = _TIFFmalloc(tileSize);
    if (tileBuffer == nullptr) {
        TIFFClose(tif);
        return 0;
    }

    // Copy the data into the tile buffer
    memcpy(tileBuffer, data, tileSize);

    // Call the function-under-test
    uint32_t tileIndex = 0; // Assuming the first tile
    TIFFWriteEncodedTile(tif, tileIndex, tileBuffer, tileSize);

    // Clean up
    _TIFFfree(tileBuffer);
    TIFFClose(tif);

    return 0;
}