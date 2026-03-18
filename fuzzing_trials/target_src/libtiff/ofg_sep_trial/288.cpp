#include <cstdint>
#include <cstdlib>
#include <cstring>  // Include for memcpy

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_288(const uint8_t *data, size_t size) {
    // Ensure there is enough data to read a uint32_t
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Initialize a TIFF structure
    TIFF *tiff = TIFFOpen("/dev/null", "w");
    if (tiff == nullptr) {
        return 0;
    }

    // Extract a uint32_t value from the input data
    uint32_t value;
    memcpy(&value, data, sizeof(uint32_t));

    // Call the function-under-test
    uint32_t stripSize = TIFFDefaultStripSize(tiff, value);

    // Clean up
    TIFFClose(tiff);

    return 0;
}