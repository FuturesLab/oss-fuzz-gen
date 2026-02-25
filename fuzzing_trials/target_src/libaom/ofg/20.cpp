#include <aom/aom_codec.h>
#include <aom/aom_decoder.h>
#include <aom/aomdx.h> // Include the header for decoder interface

extern "C" {

int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    // Initialize the codec interface
    aom_codec_iface_t *codec_iface = aom_codec_av1_dx();
    if (codec_iface == nullptr) {
        return 0; // Fail gracefully if the codec interface is not available
    }

    // Prepare aom_codec_ctx_t structure
    aom_codec_ctx_t codec_ctx;
    aom_codec_err_t res;

    // Initialize the codec context
    res = aom_codec_dec_init(&codec_ctx, codec_iface, nullptr, 0);
    if (res != AOM_CODEC_OK) {
        return 0; // Fail gracefully if initialization fails
    }

    // Prepare the input data for decoding
    aom_codec_err_t decode_res;
    decode_res = aom_codec_decode(&codec_ctx, data, size, nullptr);
    if (decode_res != AOM_CODEC_OK) {
        aom_codec_destroy(&codec_ctx); // Clean up
        return 0; // Fail gracefully if decoding fails
    }

    // Clean up the codec context
    aom_codec_destroy(&codec_ctx);
    return 0;
}

}