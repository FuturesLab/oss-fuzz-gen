#include <cstdint>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_82(const uint8_t *data, size_t size) {
    // Initialize TIFF structure
    TIFF *tiff = TIFFOpen("/tmp/test.tiff", "w");
    if (tiff == nullptr) {
        return 0;
    }

    // Initialize width and height
    uint32_t width = 0;
    uint32_t height = 0;

    // Call the function-under-test
    TIFFDefaultTileSize(tiff, &width, &height);

    // Clean up
    TIFFClose(tiff);

    return 0;
}