#include <stdint.h>
#include <stddef.h>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_114(const uint8_t *data, size_t size) {
    TIFF *tiff = nullptr;
    uint32_t tag;

    // Ensure the size is sufficient to extract a uint32_t value for the tag
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Extract a uint32_t value from the data for the tag
    tag = *(reinterpret_cast<const uint32_t*>(data));

    // Create a temporary TIFF file in memory
    tiff = TIFFOpen("temp.tiff", "w");
    if (tiff == nullptr) {
        return 0;
    }

    // Call the function-under-test
    TIFFUnsetField(tiff, tag);

    // Clean up
    TIFFClose(tiff);

    return 0;
}