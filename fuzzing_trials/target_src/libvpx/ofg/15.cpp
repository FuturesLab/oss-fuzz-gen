#include <cstdint>
#include <cstdlib>
#include <cstring>  // Include the header for memcpy

extern "C" {
    #include <vpx/vpx_encoder.h>
    #include <vpx/vp8cx.h>
}

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    // Initialize codec context and configuration structures
    vpx_codec_ctx_t codec_ctx;
    vpx_codec_enc_cfg_t cfg;

    // Ensure data size is sufficient for configuration
    if (size < sizeof(vpx_codec_enc_cfg_t)) {
        return 0;
    }

    // Initialize codec context with default configuration
    if (vpx_codec_enc_config_default(vpx_codec_vp8_cx(), &cfg, 0) != VPX_CODEC_OK) {
        return 0;
    }

    // Copy data into the configuration structure
    memcpy(&cfg, data, sizeof(vpx_codec_enc_cfg_t));

    // Initialize codec context with the modified configuration
    if (vpx_codec_enc_init(&codec_ctx, vpx_codec_vp8_cx(), &cfg, 0) != VPX_CODEC_OK) {
        return 0;
    }

    // Call the function-under-test
    vpx_codec_err_t result = vpx_codec_enc_config_set(&codec_ctx, &cfg);

    // Clean up codec context
    vpx_codec_destroy(&codec_ctx);

    return 0;
}