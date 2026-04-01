#include <cstdint>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract the necessary parameters
    if (size < sizeof(uint32_t) + sizeof(uint16_t)) {
        return 0;
    }

    // Initialize TIFF structure
    TIFF *tiff = TIFFOpen("/tmp/fuzzfileXXXXXX", "w");
    if (tiff == nullptr) {
        return 0;
    }

    // Extract parameters from the input data
    uint32_t row = *(reinterpret_cast<const uint32_t*>(data));
    uint16_t sample = *(reinterpret_cast<const uint16_t*>(data + sizeof(uint32_t)));

    // Call the function-under-test
    uint32_t strip = TIFFComputeStrip(tiff, row, sample);

    // Clean up
    TIFFClose(tiff);

    return 0;
}