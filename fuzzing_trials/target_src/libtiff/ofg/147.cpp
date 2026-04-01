#include <cstdint>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_147(const uint8_t *data, size_t size) {
    // Ensure there's enough data to extract a uint16_t value
    if (size < sizeof(uint16_t)) {
        return 0;
    }

    // Extract a uint16_t value from the input data
    uint16_t codec_id = *reinterpret_cast<const uint16_t*>(data);

    // Call the function-under-test
    const TIFFCodec *codec = TIFFFindCODEC(codec_id);

    // Optionally, you can add additional checks or operations on the codec
    // For example, you could print or log the codec name if it's not null
    if (codec != nullptr) {
        // Example operation: printing the codec name
        // Note: In a real fuzzing environment, you might avoid printing to reduce noise
        // printf("Codec Name: %s\n", codec->name);
    }

    return 0;
}