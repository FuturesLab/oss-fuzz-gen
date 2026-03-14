#include <stdint.h>
#include <stddef.h>
#include <aom/aom_decoder.h>

extern "C" {
    // Function prototype for the function-under-test
    aom_codec_iface_t * aom_codec_av1_dx();
}

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    // Call the function-under-test
    aom_codec_iface_t *codec_iface = aom_codec_av1_dx();

    // Check if the returned codec interface is not NULL
    if (codec_iface != NULL) {
        // Use the codec interface in a meaningful way
        // For the purpose of this fuzzing harness, we'll just ensure the function is called
        // and the result is not NULL.
        // In a real fuzzing scenario, you might want to initialize a codec context and decode data.
    }

    return 0;
}