#include <cstdint>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_287(const uint8_t *data, size_t size) {
    // Initialize TIFF structure
    TIFF *tiff = TIFFOpen("/tmp/fuzzfile.tiff", "w");
    if (tiff == nullptr) {
        return 0; // If TIFFOpen fails, return early
    }

    // Ensure the size is non-zero to avoid division by zero
    uint32_t defaultSize = size > 0 ? size : 1;

    // Call the function-under-test
    uint32_t stripSize = TIFFDefaultStripSize(tiff, defaultSize);

    // Clean up
    TIFFClose(tiff);

    return 0;
}