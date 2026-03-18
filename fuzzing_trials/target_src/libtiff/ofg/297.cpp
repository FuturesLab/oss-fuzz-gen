#include <cstdint>
#include <tiffio.h>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_297(const uint8_t *data, size_t size) {
    TIFF *tiff = nullptr;
    uint32_t tile = 0;

    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Initialize the TIFF structure with dummy data to avoid NULL
    tiff = TIFFClientOpen("dummy", "r", (thandle_t)data, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    if (!tiff) {
        return 0;
    }

    // Extract a uint32_t value from the input data for the tile parameter
    tile = *(reinterpret_cast<const uint32_t*>(data));

    // Call the function under test
    tmsize_t tileSize = TIFFVTileSize(tiff, tile);

    // Clean up
    TIFFClose(tiff);

    return 0;
}