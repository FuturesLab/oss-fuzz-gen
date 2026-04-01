extern "C" {
#include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_172(const uint8_t *data, size_t size) {
    // Initialize a TIFF structure
    TIFF *tiff = TIFFOpen("/tmp/fuzz.tiff", "w");
    if (!tiff) {
        return 0;
    }

    // Ensure that the size is non-zero to avoid division by zero in TIFFVStripSize
    uint32_t rows_per_strip = size > 0 ? static_cast<uint32_t>(data[0]) + 1 : 1;

    // Call the function under test
    tmsize_t strip_size = TIFFVStripSize(tiff, rows_per_strip);

    // Clean up
    TIFFClose(tiff);

    return 0;
}