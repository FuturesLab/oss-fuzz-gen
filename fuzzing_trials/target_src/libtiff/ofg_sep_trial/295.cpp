#include <cstdint>
#include <cstdlib>
#include <cstring> // Include this header for memcpy

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_295(const uint8_t *data, size_t size) {
    if (size < sizeof(uint32_t)) {
        return 0; // Not enough data to extract uint32_t
    }

    // Initialize TIFF structure
    TIFF *tif = TIFFOpen("dummy.tif", "w");
    if (!tif) {
        return 0; // Failed to open TIFF
    }

    // Extract a uint32_t value from the input data
    uint32_t sampleValue;
    memcpy(&sampleValue, data, sizeof(uint32_t));

    // Call the function-under-test
    tmsize_t tileSize = TIFFVTileSize(tif, sampleValue);

    // Clean up
    TIFFClose(tif);

    return 0;
}