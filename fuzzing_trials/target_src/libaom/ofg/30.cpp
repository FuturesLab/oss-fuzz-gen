#include <cstddef>
#include <cstdint>
#include <aom/aom_codec.h>
#include <aom/aom_decoder.h>
#include <aom/aomdx.h>

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    aom_codec_ctx_t codec;
    aom_codec_err_t res;
    aom_codec_iface_t *iface = aom_codec_av1_dx();

    // Initialize the codec context
    res = aom_codec_dec_init(&codec, iface, NULL, 0);
    if (res != AOM_CODEC_OK) {
        return 0; // Initialization failed, exit early
    }

    // Call the function-under-test
    res = aom_codec_decode(&codec, data, size, NULL);

    // Destroy the codec context to free resources
    aom_codec_destroy(&codec);

    return 0;
}