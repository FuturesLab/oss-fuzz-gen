#include <cstdint>
#include <cstdlib>
#include <fcntl.h> // For O_RDONLY

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_292(const uint8_t *data, size_t size) {
    if (size < 3 * sizeof(uint32_t) + sizeof(uint16_t)) {
        return 0; // Ensure there's enough data for all parameters
    }

    // Initialize TIFF structure with non-null values
    TIFF *tiff = TIFFOpen("dummy", "r");
    if (!tiff) {
        return 0; // Failed to open a dummy TIFF
    }

    // Extract parameters from data
    uint32_t x = *(uint32_t *)(data);
    uint32_t y = *(uint32_t *)(data + sizeof(uint32_t));
    uint32_t z = *(uint32_t *)(data + 2 * sizeof(uint32_t));
    uint16_t sample = *(uint16_t *)(data + 3 * sizeof(uint32_t));

    // Call the function under test
    uint32_t tile = TIFFComputeTile(tiff, x, y, z, sample);

    // Clean up
    TIFFClose(tiff);

    return 0;
}