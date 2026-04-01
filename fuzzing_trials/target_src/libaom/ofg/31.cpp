#include <cstddef>
#include <cstdint>
#include <aom/aom_decoder.h>
#include <aom/aomdx.h>

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    aom_codec_ctx_t codec;
    aom_codec_err_t res;
    aom_codec_iface_t *iface = aom_codec_av1_dx(); // Use AV1 decoder interface
    void *user_priv = (void*)1; // Non-NULL user private data

    // Initialize the codec context
    res = aom_codec_dec_init(&codec, iface, NULL, 0);
    if (res != AOM_CODEC_OK) {
        return 0; // Initialization failed
    }

    // Call the function-under-test
    res = aom_codec_decode(&codec, data, size, user_priv);

    // Destroy the codec context
    aom_codec_destroy(&codec);

    return 0;
}