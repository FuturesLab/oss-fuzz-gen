#include <stdint.h>
#include <stddef.h>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_146(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to extract a uint16_t value
    if (size < sizeof(uint16_t)) {
        return 0;
    }

    // Extract a uint16_t value from the input data
    uint16_t codec_id = *(const uint16_t *)data;

    // Call the function-under-test with the extracted codec_id
    const TIFFCodec *codec = TIFFFindCODEC(codec_id);

    // Optionally, perform additional operations with the codec
    // (e.g., checking its properties) if needed

    return 0;
}