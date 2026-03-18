#include <stdint.h>
#include <stddef.h>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_143(const uint8_t *data, size_t size) {
    if (size < sizeof(uint16_t)) {
        return 0;
    }

    // Extract a uint16_t value from the input data
    uint16_t codec_id = *(const uint16_t *)data;

    // Call the function-under-test
    const TIFFCodec *codec = TIFFFindCODEC(codec_id);

    // Optionally, you can add some checks or operations on the returned codec
    // For example, you can print the codec name if it's not NULL
    if (codec != NULL) {
        // In a real fuzzing scenario, you might want to do more with the codec
        // For now, we'll just ensure the function is called
    }

    return 0;
}