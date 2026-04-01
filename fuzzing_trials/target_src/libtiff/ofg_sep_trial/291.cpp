#include <cstdint>
#include <cstdio>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_291(const uint8_t *data, size_t size) {
    if (size < sizeof(uint32_t) * 3 + sizeof(uint16_t)) {
        return 0; // Not enough data to extract required parameters
    }

    // Initialize TIFF structure
    TIFF *tiff = TIFFOpen("temp.tiff", "w");
    if (!tiff) {
        return 0;
    }

    // Extract parameters from the input data
    uint32_t x = *(reinterpret_cast<const uint32_t*>(data));
    uint32_t y = *(reinterpret_cast<const uint32_t*>(data + sizeof(uint32_t)));
    uint32_t z = *(reinterpret_cast<const uint32_t*>(data + 2 * sizeof(uint32_t)));
    uint16_t s = *(reinterpret_cast<const uint16_t*>(data + 3 * sizeof(uint32_t)));

    // Call the function-under-test
    uint32_t tile = TIFFComputeTile(tiff, x, y, z, s);

    // Clean up
    TIFFClose(tiff);

    return 0;
}