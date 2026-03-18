#include <tiffio.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_292(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient for our parameters
    if (size < sizeof(uint32_t) * 3 + sizeof(uint16_t)) {
        return 0;
    }

    // Initialize the TIFF structure
    TIFF *tiff = TIFFOpen("/tmp/fuzzfileXXXXXX", "w");
    if (tiff == NULL) {
        return 0;
    }

    // Extract parameters from the data
    uint32_t x = *(const uint32_t *)(data);
    uint32_t y = *(const uint32_t *)(data + sizeof(uint32_t));
    uint32_t z = *(const uint32_t *)(data + 2 * sizeof(uint32_t));
    uint16_t sample = *(const uint16_t *)(data + 3 * sizeof(uint32_t));

    // Call the function-under-test
    uint32_t tileIndex = TIFFComputeTile(tiff, x, y, z, sample);

    // Clean up
    TIFFClose(tiff);

    return 0;
}