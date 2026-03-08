#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy
#include <vpx/vpx_codec.h>
#include <vpx/vpx_encoder.h>

extern "C" {
    #include <vpx/vp8cx.h>
}

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    if (size < 640 * 480 * 3 / 2) {
        return 0; // Exit early if there's not enough data to fill a frame
    }

    vpx_codec_ctx_t codec_ctx;
    vpx_codec_err_t res;
    vpx_codec_enc_cfg_t cfg;

    // Get the default codec configuration
    res = vpx_codec_enc_config_default(vpx_codec_vp8_cx(), &cfg, 0);
    if (res != VPX_CODEC_OK) {
        return 0; // Exit if getting default config fails
    }

    // Set basic configuration parameters
    cfg.g_w = 640; // Width of the video frame
    cfg.g_h = 480; // Height of the video frame
    cfg.rc_target_bitrate = 1000; // Target bitrate in kbps

    // Initialize codec context with the configuration
    res = vpx_codec_enc_init(&codec_ctx, vpx_codec_vp8_cx(), &cfg, 0);
    if (res != VPX_CODEC_OK) {
        return 0; // Exit if initialization fails
    }

    // Set up image data
    vpx_image_t img;
    if (!vpx_img_alloc(&img, VPX_IMG_FMT_I420, cfg.g_w, cfg.g_h, 1)) {
        vpx_codec_destroy(&codec_ctx);
        return 0; // Exit if image allocation fails
    }

    // Calculate the size of the buffer to copy
    size_t y_size = img.stride[VPX_PLANE_Y] * img.h;
    size_t u_size = img.stride[VPX_PLANE_U] * (img.h >> img.y_chroma_shift);
    size_t v_size = img.stride[VPX_PLANE_V] * (img.h >> img.y_chroma_shift);

    // Copy fuzz data into the image buffer
    memcpy(img.planes[VPX_PLANE_Y], data, y_size);
    memcpy(img.planes[VPX_PLANE_U], data + y_size, u_size);
    memcpy(img.planes[VPX_PLANE_V], data + y_size + u_size, v_size);

    // Encode the frame
    res = vpx_codec_encode(&codec_ctx, &img, 0, 1, 0, VPX_DL_REALTIME);
    if (res != VPX_CODEC_OK) {
        vpx_img_free(&img);
        vpx_codec_destroy(&codec_ctx);
        return 0; // Exit if encoding fails
    }

    // Retrieve and process encoded data
    vpx_codec_iter_t iter = NULL;
    const vpx_codec_cx_pkt_t *pkt;
    while ((pkt = vpx_codec_get_cx_data(&codec_ctx, &iter)) != NULL) {
        if (pkt->kind == VPX_CODEC_CX_FRAME_PKT) {
            // Process encoded frame packet (e.g., save or analyze)
        }
    }

    // Free image and destroy codec context
    vpx_img_free(&img);
    vpx_codec_destroy(&codec_ctx);

    return 0;
}