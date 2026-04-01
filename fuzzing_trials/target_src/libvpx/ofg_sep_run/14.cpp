#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include the necessary header for memcpy

extern "C" {
    #include <vpx/vpx_encoder.h>
    #include <vpx/vp8cx.h>
}

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    vpx_codec_ctx_t codec_ctx;
    vpx_codec_enc_cfg_t enc_cfg;
    vpx_codec_err_t res;

    // Initialize codec context with default configuration
    res = vpx_codec_enc_config_default(vpx_codec_vp8_cx(), &enc_cfg, 0);
    if (res != VPX_CODEC_OK) {
        return 0;
    }

    // Initialize codec context
    res = vpx_codec_enc_init(&codec_ctx, vpx_codec_vp8_cx(), &enc_cfg, 0);
    if (res != VPX_CODEC_OK) {
        return 0;
    }

    // Ensure data is not NULL and size is sufficient
    if (data != NULL && size >= sizeof(vpx_codec_enc_cfg_t)) {
        // Copy data to enc_cfg, ensuring it doesn't exceed size
        memcpy(&enc_cfg, data, sizeof(vpx_codec_enc_cfg_t));

        // Call the function-under-test
        vpx_codec_err_t result = vpx_codec_enc_config_set(&codec_ctx, &enc_cfg);

        // Handle the result if necessary (e.g., logging, assertions)
        if (result == VPX_CODEC_OK) {
            // Example: Encode a dummy frame (to ensure function is exercised)
            vpx_image_t img;
            if (vpx_img_alloc(&img, VPX_IMG_FMT_I420, enc_cfg.g_w, enc_cfg.g_h, 1)) {
                vpx_codec_encode(&codec_ctx, &img, 0, 1, 0, VPX_DL_REALTIME);
                vpx_img_free(&img);
            }
        }
    }

    // Destroy codec context
    vpx_codec_destroy(&codec_ctx);

    return 0;
}