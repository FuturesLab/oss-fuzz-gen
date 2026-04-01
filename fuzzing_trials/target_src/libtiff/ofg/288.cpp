#include <cstdint>
#include <cstdio>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_288(const uint8_t *data, size_t size) {
    // Initialize TIFF structure
    TIFF *tiff = TIFFOpen("/tmp/fuzzfileXXXXXX", "w");
    if (tiff == nullptr) {
        return 0;
    }

    // Ensure the size is non-zero to provide a valid parameter
    uint32_t stripSize = size > 0 ? static_cast<uint32_t>(data[0]) : 1;

    // Call the function-under-test
    uint32_t result = TIFFDefaultStripSize(tiff, stripSize);

    // Clean up
    TIFFClose(tiff);

    return 0;
}