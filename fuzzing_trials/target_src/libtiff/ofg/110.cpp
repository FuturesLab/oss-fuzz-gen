#include <cstdint>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_110(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for our needs
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Create a TIFF structure
    TIFF *tiff = TIFFOpen("temp.tiff", "w");
    if (!tiff) {
        return 0;
    }

    // Extract a uint32_t value from the input data
    uint32_t tag = *(reinterpret_cast<const uint32_t *>(data));

    // Call the function-under-test
    TIFFUnsetField(tiff, tag);

    // Close the TIFF structure
    TIFFClose(tiff);

    return 0;
}