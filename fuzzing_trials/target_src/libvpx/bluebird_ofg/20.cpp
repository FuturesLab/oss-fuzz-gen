#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libvpx/vpx/vpx_codec.h"
    #include "/src/libvpx/vpx/vpx_encoder.h"
}

// Declare the function prototype for vpx_codec_vp8_cx
extern "C" vpx_codec_iface_t *vpx_codec_vp8_cx();

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    // Initialize variables
    vpx_codec_ctx_t codec_ctx;
    vpx_codec_enc_cfg_t cfg;
    vpx_codec_err_t res;

    // Set default values for codec context and configuration
    res = vpx_codec_enc_config_default(vpx_codec_vp8_cx(), &cfg, 0);
    if (res != VPX_CODEC_OK) {
        return 0;
    }

    // Initialize the codec context
    res = vpx_codec_enc_init(&codec_ctx, vpx_codec_vp8_cx(), &cfg, 0);
    if (res != VPX_CODEC_OK) {
        return 0;
    }

    // Call the function-under-test
    vpx_fixed_buf_t *global_headers = vpx_codec_get_global_headers(&codec_ctx);

    // Clean up
    if (global_headers != NULL) {
        free(global_headers->buf);
        free(global_headers);
    }
    vpx_codec_destroy(&codec_ctx);

    return 0;
}