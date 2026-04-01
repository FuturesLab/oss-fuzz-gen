#include <stdint.h>
#include <stddef.h>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_217(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to extract an integer for mode
    if (size < sizeof(int)) {
        return 0;
    }

    // Initialize TIFF structure
    TIFF *tiff = TIFFOpen("/tmp/fuzzfileXXXXXX", "w");
    if (tiff == NULL) {
        return 0;
    }

    // Extract an integer from the input data for the mode parameter
    int mode = *(reinterpret_cast<const int*>(data));

    // Call the function-under-test
    TIFFSetMode(tiff, mode);

    // Clean up
    TIFFClose(tiff);

    return 0;
}