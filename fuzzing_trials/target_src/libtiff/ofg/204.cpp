#include <cstdint>
#include <cstring>  // Include for memcpy

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_204(const uint8_t *data, size_t size) {
    // Initialize the TIFF structure
    TIFF *tiff = TIFFOpen("/tmp/fuzzfile.tiff", "w");
    if (tiff == nullptr) {
        return 0;
    }

    // Ensure data is large enough to extract a tag and data type
    if (size < sizeof(uint32_t) + sizeof(TIFFDataType)) {
        TIFFClose(tiff);
        return 0;
    }

    // Extract a tag from the data
    uint32_t tag;
    memcpy(&tag, data, sizeof(uint32_t));

    // Extract a data type from the data
    TIFFDataType dataType;
    memcpy(&dataType, data + sizeof(uint32_t), sizeof(TIFFDataType));

    // Call the function-under-test
    const TIFFField *field = TIFFFindField(tiff, tag, dataType);

    // Clean up
    TIFFClose(tiff);

    return 0;
}