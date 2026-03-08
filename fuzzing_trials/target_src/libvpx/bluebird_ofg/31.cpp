#include <cstring> // Include cstring for memcpy

extern "C" {
#include "/src/libvpx/vpx/vpx_encoder.h"
#include "/src/libvpx/vpx/vp8cx.h"
}

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    vpx_codec_ctx_t codec_ctx;
    vpx_codec_enc_cfg_t enc_cfg;
    vpx_image_t raw;
    vpx_codec_err_t res;

    // Initialize codec context and encoder configuration
    res = vpx_codec_enc_config_default(vpx_codec_vp8_cx(), &enc_cfg, 0);
    if (res != VPX_CODEC_OK) {
        return 0;
    }

    // Modify the encoder configuration based on the input data
    if (size >= sizeof(vpx_codec_enc_cfg_t)) {
        memcpy(&enc_cfg, data, sizeof(vpx_codec_enc_cfg_t));
    }

    // Initialize the codec context

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from vpx_codec_enc_config_default to vpx_codec_enc_init_multi_ver
    vpx_codec_ctx_t diqfpgvh;
    memset(&diqfpgvh, 0, sizeof(diqfpgvh));

    vpx_codec_err_t ret_vpx_codec_enc_init_multi_ver_rwqbj = vpx_codec_enc_init_multi_ver(&diqfpgvh, NULL, &enc_cfg, 0, 0, NULL, VPX_TS_MAX_LAYERS);

    // End mutation: Producer.APPEND_MUTATOR

    res = vpx_codec_enc_init(&codec_ctx, vpx_codec_vp8_cx(), &enc_cfg, 0);
    if (res != VPX_CODEC_OK) {
        return 0;
    }

    // Allocate and initialize a raw image
    if (!vpx_img_alloc(&raw, VPX_IMG_FMT_I420, enc_cfg.g_w, enc_cfg.g_h, 1)) {
        vpx_codec_destroy(&codec_ctx);
        return 0;
    }

    // Ensure the input data is large enough to fill the image
    if (size >= sizeof(vpx_codec_enc_cfg_t) + raw.d_w * raw.d_h * 3 / 2) {
        memcpy(raw.planes[0], data + sizeof(vpx_codec_enc_cfg_t), raw.d_w * raw.d_h); // Y
        memcpy(raw.planes[1], data + sizeof(vpx_codec_enc_cfg_t) + raw.d_w * raw.d_h, raw.d_w * raw.d_h / 4); // U
        memcpy(raw.planes[2], data + sizeof(vpx_codec_enc_cfg_t) + raw.d_w * raw.d_h * 5 / 4, raw.d_w * raw.d_h / 4); // V
    }

    // Encode the frame

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 4 of vpx_codec_encode
    res = vpx_codec_encode(&codec_ctx, &raw, 0, 1, -1, VPX_DL_REALTIME);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    
    // Clean up
    vpx_img_free(&raw);
    vpx_codec_destroy(&codec_ctx);

    return 0;
}