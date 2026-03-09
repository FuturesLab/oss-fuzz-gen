#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <algorithm> // Include this for std::min
#include <vpx/vpx_encoder.h>

extern "C" {
    #include <vpx/vpx_codec.h>
    #include <vpx/vp8cx.h> // This header file declares vpx_codec_vp8_cx
}

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Initialize the codec context
    vpx_codec_ctx_t codec_ctx;
    vpx_codec_enc_cfg_t cfg;
    vpx_codec_err_t res;

    // Initialize the codec configuration with default values
    res = vpx_codec_enc_config_default(vpx_codec_vp8_cx(), &cfg, 0);
    if (res != VPX_CODEC_OK) {
        return 0;
    }

    // Set some configuration parameters
    cfg.g_w = 640;  // Set width
    cfg.g_h = 480;  // Set height
    cfg.g_timebase.num = 1;
    cfg.g_timebase.den = 30;

    // Use fuzz data to modify configuration parameters
    if (size >= 2) {
        cfg.g_w = data[0] % 1920; // Width between 0 and 1919
        cfg.g_h = data[1] % 1080; // Height between 0 and 1079
    }

    // Set up the codec context with the modified configuration
    res = vpx_codec_enc_init(&codec_ctx, vpx_codec_vp8_cx(), &cfg, 0);
    if (res != VPX_CODEC_OK) {
        return 0;
    }

    // Create a raw image to encode
    vpx_image_t raw;
    if (!vpx_img_alloc(&raw, VPX_IMG_FMT_I420, cfg.g_w, cfg.g_h, 1)) {
        vpx_codec_destroy(&codec_ctx);
        return 0;
    }

    // Copy fuzz data into the raw image buffer
    size_t copy_size = std::min(size, static_cast<size_t>(raw.w * raw.h * 3 / 2)); // I420 format
    std::memcpy(raw.planes[0], data, copy_size);

    // Encode the image
    res = vpx_codec_encode(&codec_ctx, &raw, 0, 1, 0, VPX_DL_REALTIME);
    if (res != VPX_CODEC_OK) {
        vpx_img_free(&raw);
        vpx_codec_destroy(&codec_ctx);
        return 0;
    }

    // Initialize an iterator
    vpx_codec_iter_t iter = NULL;
    const vpx_codec_cx_pkt_t *pkt;

    // Retrieve and process encoded data packets
    while ((pkt = vpx_codec_get_cx_data(&codec_ctx, &iter)) != NULL) {
        if (pkt->kind == VPX_CODEC_CX_FRAME_PKT) {
            // Process encoded frame packet
        }
    }

    // Clean up
    vpx_img_free(&raw);
    vpx_codec_destroy(&codec_ctx);

    return 0;
}