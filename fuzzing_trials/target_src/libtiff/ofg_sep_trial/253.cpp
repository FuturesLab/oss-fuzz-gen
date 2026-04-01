#include <cstdint>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_253(const uint8_t *data, size_t size) {
    // Declare and initialize the variables needed for TIFFCheckTile
    TIFF *tif = nullptr;
    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t z = 0;
    uint16_t sample = 0;

    // Open a TIFF file in memory for reading
    tif = TIFFOpen("test.tiff", "r");
    if (tif == nullptr) {
        return 0; // If TIFFOpen fails, return early
    }

    // Ensure size is sufficient to extract values
    if (size >= sizeof(uint32_t) * 3 + sizeof(uint16_t)) {
        // Extract values from the data
        x = *(reinterpret_cast<const uint32_t*>(data));
        y = *(reinterpret_cast<const uint32_t*>(data + sizeof(uint32_t)));
        z = *(reinterpret_cast<const uint32_t*>(data + 2 * sizeof(uint32_t)));
        sample = *(reinterpret_cast<const uint16_t*>(data + 3 * sizeof(uint32_t)));
    }

    // Call the function-under-test
    int result = TIFFCheckTile(tif, x, y, z, sample);

    // Close the TIFF file
    TIFFClose(tif);

    return 0;
}