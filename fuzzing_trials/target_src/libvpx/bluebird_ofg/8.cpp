#include <cstdint>
#include <cstdlib>
#include <cstring>  // Include for memcpy

extern "C" {
    #include "/src/libvpx/vpx/vpx_encoder.h"
    #include "/src/libvpx/vpx/vp8cx.h"
}

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // Initialize variables
    vpx_codec_ctx_t codec_ctx;
    vpx_codec_enc_cfg_t cfg;
    vpx_image_t img;
    vpx_codec_err_t res;

    // Initialize codec configuration
    res = vpx_codec_enc_config_default(vpx_codec_vp8_cx(), &cfg, 0);
    if (res != VPX_CODEC_OK) {
        return 0;
    }

    // Initialize codec context
    res = vpx_codec_enc_init(&codec_ctx, vpx_codec_vp8_cx(), &cfg, 0);
    if (res != VPX_CODEC_OK) {
        return 0;
    }

    // Initialize image
    if (!vpx_img_alloc(&img, VPX_IMG_FMT_I420, cfg.g_w, cfg.g_h, 1)) {
        vpx_codec_destroy(&codec_ctx);
        return 0;
    }

    // Calculate the image size
    size_t img_size = img.h * img.stride[VPX_PLANE_Y];

    // Fill image with data from fuzzer input
    if (size > 0) {
        size_t copy_size = size < img_size ? size : img_size;
        memcpy(img.planes[0], data, copy_size);
    }

    // Define parameters for encoding
    vpx_codec_pts_t pts = 0;
    unsigned long duration = 1;
    vpx_enc_frame_flags_t flags = 0;
    vpx_enc_deadline_t deadline = VPX_DL_REALTIME;

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 4 of vpx_codec_encode
    res = vpx_codec_encode(&codec_ctx, &img, pts, duration, size, deadline);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up
    vpx_img_free(&img);
    vpx_codec_destroy(&codec_ctx);

    return 0;
}