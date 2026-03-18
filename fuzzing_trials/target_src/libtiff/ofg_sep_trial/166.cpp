#include <cstdint>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_166(const uint8_t *data, size_t size) {
    // Initialize TIFF structure
    TIFF *tiff = TIFFOpen("/tmp/fuzzfile.tiff", "r");
    if (tiff == nullptr) {
        return 0;
    }

    // Ensure size is large enough to extract a uint32_t
    if (size < sizeof(uint32_t)) {
        TIFFClose(tiff);
        return 0;
    }

    // Extract a uint32_t from the data
    uint32_t tileIndex = *(reinterpret_cast<const uint32_t*>(data));

    // Call the function-under-test
    uint64_t tileSize = TIFFVTileSize64(tiff, tileIndex);

    // Clean up
    TIFFClose(tiff);

    return 0;
}