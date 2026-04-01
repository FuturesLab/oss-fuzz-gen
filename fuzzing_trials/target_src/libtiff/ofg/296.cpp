#include <tiffio.h>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_296(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract a uint32_t for the second parameter
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Create a TIFF structure
    TIFF *tiff = TIFFOpen("dummy.tiff", "w");
    if (tiff == nullptr) {
        return 0;
    }

    // Extract a uint32_t from the input data
    uint32_t tile = *reinterpret_cast<const uint32_t *>(data);

    // Call the function-under-test
    tmsize_t tileSize = TIFFVTileSize(tiff, tile);

    // Clean up
    TIFFClose(tiff);

    return 0;
}