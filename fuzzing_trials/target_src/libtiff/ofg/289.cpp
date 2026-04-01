#include <stdint.h>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_289(const uint8_t *data, size_t size) {
    // Initialize the TIFF structure
    TIFF *tiff = TIFFOpen("/tmp/fuzzfileXXXXXX", "w");
    if (tiff == NULL) {
        return 0;
    }

    // Ensure the size is non-zero to avoid division by zero errors
    uint32_t defaultSize = (size > 0) ? static_cast<uint32_t>(data[0]) : 1;

    // Call the function-under-test
    uint32_t stripSize = TIFFDefaultStripSize(tiff, defaultSize);

    // Clean up and close the TIFF file
    TIFFClose(tiff);

    return 0;
}