#include <cstdint>
#include <cstdlib>
#include <cstring>
#include "/src/libvpx/vpx/vpx_encoder.h"
#include "/src/libvpx/vpx/vp8cx.h"

extern "C" int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
    // Initialize variables for the function-under-test
    vpx_codec_ctx_t codec_ctx;
    vpx_codec_enc_cfg_t cfg;
    vpx_image_t raw;
    vpx_codec_err_t res;

    // Initialize the codec configuration
    res = vpx_codec_enc_config_default(vpx_codec_vp8_cx(), &cfg, 0);
    if (res != VPX_CODEC_OK) return 0;

    // Initialize codec context
    res = vpx_codec_enc_init(&codec_ctx, vpx_codec_vp8_cx(), &cfg, 0);
    if (res != VPX_CODEC_OK) return 0;

    // Ensure the input data is large enough to fill an image
    if (size < 640 * 480 * 3 / 2) {
        vpx_codec_destroy(&codec_ctx);
        return 0;
    }

    // Initialize image
    if (!vpx_img_alloc(&raw, VPX_IMG_FMT_I420, 640, 480, 1)) {
        vpx_codec_destroy(&codec_ctx);
        return 0;
    }

    // Copy input data to the image buffer
    std::memcpy(raw.planes[0], data, 640 * 480); // Y plane
    std::memcpy(raw.planes[1], data + 640 * 480, 640 * 480 / 4); // U plane
    std::memcpy(raw.planes[2], data + 640 * 480 + 640 * 480 / 4, 640 * 480 / 4); // V plane

    // Set some arbitrary values for the parameters
    vpx_codec_pts_t pts = 1;
    unsigned long duration = 1;
    vpx_enc_frame_flags_t flags = 0;
    vpx_enc_deadline_t deadline = VPX_DL_REALTIME;

    // Call the function-under-test
    res = vpx_codec_encode(&codec_ctx, &raw, pts, duration, flags, deadline);

    // Cleanup
    vpx_img_free(&raw);
    vpx_codec_destroy(&codec_ctx);

    return 0;
}