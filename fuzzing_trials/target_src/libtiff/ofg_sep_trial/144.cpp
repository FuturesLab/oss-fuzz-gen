#include <stdint.h>
#include <stddef.h>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_144(const uint8_t *data, size_t size) {
    // Initialize a TIFF structure
    TIFF *tiff = TIFFOpen("/tmp/fuzzfileXXXXXX", "w");
    if (tiff == NULL) {
        return 0;
    }

    // Call the function-under-test
    uint32_t strip = TIFFCurrentStrip(tiff);

    // Clean up
    TIFFClose(tiff);

    return 0;
}