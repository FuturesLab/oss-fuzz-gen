#include <stdint.h>
#include <stddef.h>
#include <vpx/vpx_encoder.h>
#include <vpx/vp8cx.h>

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    // Declare and initialize the variables needed for the function call
    vpx_codec_ctx_t codec_ctx;
    vpx_codec_iface_t *iface = vpx_codec_vp8_cx();
    vpx_codec_enc_cfg_t cfg;
    vpx_codec_flags_t flags = 0;
    int ver = VPX_ENCODER_ABI_VERSION;

    // Initialize the configuration with default values
    if (vpx_codec_enc_config_default(iface, &cfg, 0) != VPX_CODEC_OK) {
        return 0;
    }

    // Modify the configuration based on input data to maximize coverage
    if (size > 0) {
        cfg.g_w = data[0]; // Set width based on first byte of input
    }
    if (size > 1) {
        cfg.g_h = data[1]; // Set height based on second byte of input
    }
    if (size > 2) {
        cfg.rc_target_bitrate = data[2]; // Set bitrate based on third byte of input
    }

    // Call the function-under-test
    vpx_codec_err_t result = vpx_codec_enc_init_ver(&codec_ctx, iface, &cfg, flags, ver);

    // If initialization is successful, encode a frame
    if (result == VPX_CODEC_OK) {
        vpx_image_t img;
        if (vpx_img_alloc(&img, VPX_IMG_FMT_I420, cfg.g_w ? cfg.g_w : 1, cfg.g_h ? cfg.g_h : 1, 1)) {
            // Feed the codec with a dummy frame
            vpx_codec_encode(&codec_ctx, &img, 0, 1, 0, VPX_DL_REALTIME);
            vpx_img_free(&img);
        }
        vpx_codec_destroy(&codec_ctx);
    }

    return 0;
}