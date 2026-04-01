#include <stdint.h>
#include <stddef.h>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_158(const uint8_t *data, size_t size) {
    // Initialize TIFF memory stream
    TIFF *tiff = TIFFOpen("temp.tiff", "w");
    if (tiff == NULL) {
        return 0; // Exit if TIFF cannot be opened
    }
    
    // Ensure size is enough to extract a uint32_t tag
    if (size < sizeof(uint32_t)) {
        TIFFClose(tiff);
        return 0;
    }

    // Extract a uint32_t tag from the input data
    uint32_t tag = *(const uint32_t *)data;

    // Call the function-under-test
    const TIFFField *field = TIFFFieldWithTag(tiff, tag);

    // Clean up
    TIFFClose(tiff);

    return 0;
}