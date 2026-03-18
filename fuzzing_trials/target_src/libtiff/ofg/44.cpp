#include <cstdint>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
    // Check if the size is sufficient to extract a toff_t value
    if (size < sizeof(toff_t)) {
        return 0;
    }

    // Create a TIFF structure using TIFFOpen
    const char *filename = "/tmp/fuzzfile.tiff";
    TIFF *tiff = TIFFOpen(filename, "w");
    if (tiff == nullptr) {
        return 0;
    }

    // Extract a toff_t value from the input data
    toff_t offset = 0;
    for (size_t i = 0; i < sizeof(toff_t); ++i) {
        offset = (offset << 8) | data[i];
    }

    // Call the function-under-test
    TIFFSetWriteOffset(tiff, offset);

    // Close the TIFF structure
    TIFFClose(tiff);

    return 0;
}