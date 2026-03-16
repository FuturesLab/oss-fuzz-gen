#include <stdint.h>
#include <stddef.h>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_165(const uint8_t *data, size_t size) {
    // Ensure there's enough data to extract a uint32_t value for the second parameter
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Initialize TIFF structure
    TIFF *tiff = TIFFOpen("dummy.tif", "r");
    if (!tiff) {
        return 0;
    }

    // Extract a uint32_t value from the input data
    uint32_t tileIndex = *(reinterpret_cast<const uint32_t*>(data));

    // Call the function-under-test
    uint64_t tileSize = TIFFVTileSize64(tiff, tileIndex);

    // Clean up
    TIFFClose(tiff);

    return 0;
}