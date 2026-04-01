#include <cstdint>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_198(const uint8_t *data, size_t size) {
    if (size < sizeof(uint32_t) + sizeof(TIFFDataType)) {
        return 0;
    }

    // Initialize TIFF structure
    TIFF *tiff = TIFFOpen("/dev/null", "r");
    if (!tiff) {
        return 0;
    }

    // Extract field_tag and data_type from the input data
    uint32_t field_tag = *(reinterpret_cast<const uint32_t*>(data));
    TIFFDataType data_type = *(reinterpret_cast<const TIFFDataType*>(data + sizeof(uint32_t)));

    // Call the function-under-test
    const TIFFField *field = TIFFFindField(tiff, field_tag, data_type);

    // Clean up
    TIFFClose(tiff);

    return 0;
}