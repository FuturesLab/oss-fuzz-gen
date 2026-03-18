#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_254(const uint8_t *data, size_t size) {
    if (size < sizeof(uint32_t) * 3 + sizeof(uint16_t)) {
        return 0;
    }

    // Initialize TIFF structure
    TIFF *tiff = TIFFOpen("dummy.tiff", "w");
    if (tiff == NULL) {
        return 0;
    }

    // Extract parameters from data
    uint32_t x = *reinterpret_cast<const uint32_t *>(data);
    uint32_t y = *reinterpret_cast<const uint32_t *>(data + sizeof(uint32_t));
    uint32_t z = *reinterpret_cast<const uint32_t *>(data + 2 * sizeof(uint32_t));
    uint16_t sample = *reinterpret_cast<const uint16_t *>(data + 3 * sizeof(uint32_t));

    // Call the function-under-test
    int result = TIFFCheckTile(tiff, x, y, z, sample);

    // Clean up
    TIFFClose(tiff);

    return 0;
}