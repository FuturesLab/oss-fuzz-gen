extern "C" {
#include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_168(const uint8_t *data, size_t size) {
    // Initialize TIFF structure
    TIFF *tiff = TIFFOpen("/tmp/fuzzfile.tiff", "w");
    if (tiff == NULL) {
        return 0;
    }

    // Ensure that the data size is sufficient for a valid strip size calculation
    if (size < sizeof(uint32_t)) {
        TIFFClose(tiff);
        return 0;
    }

    // Use the first four bytes of data as the uint32_t parameter
    uint32_t stripSizeParam = *(reinterpret_cast<const uint32_t*>(data));

    // Call the function-under-test
    tmsize_t stripSize = TIFFVStripSize(tiff, stripSizeParam);

    // Clean up
    TIFFClose(tiff);

    return 0;
}