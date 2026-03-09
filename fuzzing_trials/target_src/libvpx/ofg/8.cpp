#include <stdint.h>
#include <stddef.h>
#include <vpx/vpx_encoder.h>
#include <vpx/vp8cx.h>

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // Declare and initialize variables needed for the function call
    vpx_codec_ctx_t codec_ctx;
    vpx_codec_iface_t *iface = vpx_codec_vp8_cx(); // Use VP8 encoder interface
    vpx_codec_enc_cfg_t cfg;
    vpx_codec_flags_t flags = 0;
    vpx_rational_t dsf = {1, 1}; // Default scaling factor
    int num_encoders = 1;
    int ver = VPX_ENCODER_ABI_VERSION;

    // Initialize the encoder configuration with default values
    if (vpx_codec_enc_config_default(iface, &cfg, 0) != VPX_CODEC_OK) {
        return 0; // Return if configuration initialization fails
    }

    // Adjust the configuration based on the input data
    if (size > 0) {
        cfg.g_w = data[0] % 256 + 1; // Set width based on input data
    }
    if (size > 1) {
        cfg.g_h = data[1] % 256 + 1; // Set height based on input data
    }

    // Call the function-under-test
    vpx_codec_err_t res = vpx_codec_enc_init_multi_ver(&codec_ctx, iface, &cfg, num_encoders, flags, &dsf, ver);

    // Clean up and return
    vpx_codec_destroy(&codec_ctx);
    return 0;
}