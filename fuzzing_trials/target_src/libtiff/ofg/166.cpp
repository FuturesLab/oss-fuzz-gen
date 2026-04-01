#include <cstdint>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_166(const uint8_t *data, size_t size) {
    // Initialize a TIFF structure
    TIFF *tiff = TIFFOpen("/tmp/fuzzfileXXXXXX", "w");

    if (tiff == nullptr) {
        return 0; // If TIFFOpen fails, exit early
    }

    // Call the function-under-test
    TIFFFreeDirectory(tiff);

    // Close the TIFF file to clean up
    TIFFClose(tiff);

    return 0;
}