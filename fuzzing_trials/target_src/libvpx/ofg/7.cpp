#include <stdint.h>
#include <stddef.h>
#include <vpx/vpx_encoder.h>
#include <vpx/vp8cx.h>

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
    // Declare and initialize the parameters for the function-under-test
    vpx_codec_ctx_t codec_ctx;
    vpx_codec_iface_t *iface = vpx_codec_vp8_cx();
    vpx_codec_enc_cfg_t cfg;
    int num_encoders = 1;
    vpx_codec_flags_t flags = 0;
    vpx_rational_t dsf = {1, 1}; // Default rational number
    int ver = VPX_ENCODER_ABI_VERSION;

    // Initialize the configuration with default values
    if (vpx_codec_enc_config_default(iface, &cfg, 0) != VPX_CODEC_OK) {
        return 0;
    }

    // Fuzz the function-under-test
    vpx_codec_err_t res = vpx_codec_enc_init_multi_ver(&codec_ctx, iface, &cfg, num_encoders, flags, &dsf, ver);

    // Cleanup: Destroy the codec context if it was initialized successfully
    if (res == VPX_CODEC_OK) {
        vpx_codec_destroy(&codec_ctx);
    }

    return 0;
}