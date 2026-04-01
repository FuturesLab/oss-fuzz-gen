#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_175(const uint8_t *data, size_t size) {
    // Initialize a TIFF structure
    TIFF *tiff = TIFFOpen("temp.tiff", "w");

    // Ensure TIFF structure is not NULL
    if (tiff == nullptr) {
        return 0;
    }

    // Call the function-under-test
    TIFFCreateDirectory(tiff);

    // Close the TIFF file
    TIFFClose(tiff);

    // Remove the temporary file
    remove("temp.tiff");

    return 0;
}