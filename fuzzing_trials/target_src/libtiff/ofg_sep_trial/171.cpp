#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_171(const uint8_t *data, size_t size) {
    // Initialize a TIFF structure
    TIFF *tiff = TIFFOpen("temp.tiff", "w");
    if (tiff == nullptr) {
        return 0;
    }

    // Call the function-under-test
    int result = TIFFCreateDirectory(tiff);

    // Clean up
    TIFFClose(tiff);

    return 0;
}