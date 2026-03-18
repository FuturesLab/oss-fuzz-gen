#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_349(const uint8_t *data, size_t size) {
    // Initialize TIFF structure
    TIFF *tiff = TIFFOpen("temp.tiff", "w");
    if (tiff == nullptr) {
        return 0;
    }

    // Ensure the size is sufficient to extract a uint32_t value
    if (size < sizeof(uint32_t)) {
        TIFFClose(tiff);
        return 0;
    }

    // Extract a uint32_t value from the data
    uint32_t tag = *reinterpret_cast<const uint32_t*>(data);

    // Prepare a dummy value for the field
    void* value = (void*)(data + sizeof(uint32_t));

    // Call the function-under-test
    TIFFSetField(tiff, tag, value);

    // Clean up
    TIFFClose(tiff);

    return 0;
}