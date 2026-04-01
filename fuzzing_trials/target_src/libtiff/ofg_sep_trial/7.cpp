extern "C" {
    #include <tiffio.h>
    #include <stdint.h>
}

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for the parameters
    if (size < sizeof(uint32_t) + sizeof(uint16_t)) {
        return 0;
    }

    // Initialize TIFF structure with a dummy TIFF file in memory
    TIFF *tiff = TIFFOpen("dummy.tiff", "w");
    if (tiff == NULL) {
        return 0;
    }

    // Extract parameters from the input data
    uint32_t row = *(reinterpret_cast<const uint32_t*>(data));
    uint16_t sample = *(reinterpret_cast<const uint16_t*>(data + sizeof(uint32_t)));

    // Call the function-under-test
    uint32_t strip = TIFFComputeStrip(tiff, row, sample);

    // Clean up
    TIFFClose(tiff);

    return 0;
}