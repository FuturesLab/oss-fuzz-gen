#include <cstdint>
#include <cstdlib>

extern "C" {
    #include <aom/aom_codec.h>
    #include <aom/aom_encoder.h>
    #include <aom/aomcx.h> // Include the correct header for aom_codec_av1_cx
}

extern "C" int LLVMFuzzerTestOneInput_59(const uint8_t *data, size_t size) {
    // Initialize the codec context
    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_cx(); // Use the correct function

    // Set up codec configuration
    aom_codec_enc_cfg_t cfg;
    if (aom_codec_enc_config_default(iface, &cfg, 0) != AOM_CODEC_OK) {
        return 0;
    }

    // Initialize the codec context with configuration
    if (aom_codec_enc_init(&codec_ctx, iface, &cfg, 0) != AOM_CODEC_OK) {
        return 0;
    }

    // Call the function under test
    const char *error_message = aom_codec_error(&codec_ctx);
    
    // Use the error message in some way to avoid compiler optimizations
    if (error_message != nullptr) {
        volatile char first_char = error_message[0];
        (void)first_char;
    }
    
    // Destroy the codec context
    aom_codec_destroy(&codec_ctx);

    return 0;
}