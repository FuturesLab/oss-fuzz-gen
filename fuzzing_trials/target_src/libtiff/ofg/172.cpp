#include <tiffio.h>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_172(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Create a temporary TIFF file in memory using libtiff's memory I/O functions
    TIFF *tiff = TIFFOpen("mem:", "w");

    if (tiff == nullptr) {
        return 0;
    }

    // Call the function-under-test
    TIFFCreateDirectory(tiff);

    // Clean up and close the TIFF file
    TIFFClose(tiff);

    return 0;
}