#include <stdint.h>
#include <stddef.h>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    TIFF *tiff = TIFFOpen("dummy.tiff", "r");
    uint32_t row = 0;
    uint16_t sample = 0;

    if (tiff == NULL) {
        return 0; // Exit if TIFFOpen fails
    }

    // Ensure that size is large enough to extract row and sample values
    if (size >= sizeof(uint32_t) + sizeof(uint16_t)) {
        // Extract row and sample values from data
        row = *(reinterpret_cast<const uint32_t*>(data));
        sample = *(reinterpret_cast<const uint16_t*>(data + sizeof(uint32_t)));
    }

    // Call the function-under-test
    uint32_t strip = TIFFComputeStrip(tiff, row, sample);

    // Clean up
    TIFFClose(tiff);

    return 0;
}