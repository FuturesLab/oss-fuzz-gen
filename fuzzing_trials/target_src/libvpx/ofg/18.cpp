#include <cstdint>
#include <cstdlib>
#include <cstring> // For std::memcpy
#include <algorithm> // For std::min

extern "C" {
#include <vpx/vpx_encoder.h>
#include <vpx/vp8cx.h>
}

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    // Check if the input size is sufficient for meaningful processing
    // Ensure the size is large enough to fill the Y plane of a 640x480 I420 image
    const size_t min_size = 640 * 480 * 3 / 2; // I420 format requires 1.5 bytes per pixel
    if (size < min_size) {
        return 0;
    }

    // Declare and initialize variables
    vpx_codec_ctx_t codec_ctx;
    vpx_codec_err_t err;
    vpx_image_t raw;
    vpx_codec_enc_cfg_t cfg;

    // Initialize the codec configuration
    err = vpx_codec_enc_config_default(vpx_codec_vp8_cx(), &cfg, 0);
    if (err != VPX_CODEC_OK) {
        return 0;
    }

    // Initialize the codec context
    err = vpx_codec_enc_init(&codec_ctx, vpx_codec_vp8_cx(), &cfg, 0);
    if (err != VPX_CODEC_OK) {
        return 0;
    }

    // Set up the image
    if (!vpx_img_alloc(&raw, VPX_IMG_FMT_I420, 640, 480, 1)) {
        vpx_codec_destroy(&codec_ctx);
        return 0;
    }

    // Copy data into the image buffer
    // I420 format has Y, U, and V planes. We need to fill all of them.
    size_t y_plane_size = raw.d_w * raw.d_h;
    size_t uv_plane_size = y_plane_size / 4;

    std::memcpy(raw.planes[0], data, y_plane_size); // Y plane
    std::memcpy(raw.planes[1], data + y_plane_size, uv_plane_size); // U plane
    std::memcpy(raw.planes[2], data + y_plane_size + uv_plane_size, uv_plane_size); // V plane

    // Encode the image
    err = vpx_codec_encode(&codec_ctx, &raw, 0, 1, 0, VPX_DL_REALTIME);
    if (err != VPX_CODEC_OK) {
        vpx_img_free(&raw);
        vpx_codec_destroy(&codec_ctx);
        return 0;
    }

    // Retrieve the encoded data
    vpx_codec_iter_t iter = nullptr;
    const vpx_codec_cx_pkt_t *pkt = nullptr;
    while ((pkt = vpx_codec_get_cx_data(&codec_ctx, &iter)) != nullptr) {
        if (pkt->kind == VPX_CODEC_CX_FRAME_PKT) {
            // Process the encoded frame (for demonstration, we do nothing)
        }
    }

    // Free the image and destroy the codec context
    vpx_img_free(&raw);
    vpx_codec_destroy(&codec_ctx);

    return 0;
}