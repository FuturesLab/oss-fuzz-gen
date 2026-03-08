#include <stdint.h>
#include <stddef.h>
#include <vpx/vpx_encoder.h>
#include <vpx/vp8cx.h>

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    // Initialize variables for the function call
    vpx_codec_ctx_t codec;
    vpx_codec_enc_cfg_t cfg;
    vpx_image_t img;
    vpx_codec_err_t res;

    // Initialize codec context and configuration
    res = vpx_codec_enc_config_default(vpx_codec_vp8_cx(), &cfg, 0);
    if (res != VPX_CODEC_OK) {
        return 0; // Exit if configuration initialization fails
    }

    // Initialize the codec
    res = vpx_codec_enc_init(&codec, vpx_codec_vp8_cx(), &cfg, 0);
    if (res != VPX_CODEC_OK) {
        return 0; // Exit if codec initialization fails
    }

    // Initialize the image
    if (!vpx_img_wrap(&img, VPX_IMG_FMT_I420, 640, 480, 1, (uint8_t *)data)) {
        vpx_codec_destroy(&codec);
        return 0; // Exit if image wrapping fails
    }

    // Set the image data to the input data (ensure non-NULL)
    img.planes[0] = (uint8_t *)data;

    // Set other parameters for encoding
    vpx_codec_pts_t pts = 0; // Presentation timestamp
    unsigned long duration = 1; // Duration of the frame
    vpx_enc_frame_flags_t flags = 0; // Frame flags
    vpx_enc_deadline_t deadline = VPX_DL_REALTIME; // Encoding deadline

    // Call the function-under-test
    res = vpx_codec_encode(&codec, &img, pts, duration, flags, deadline);

    // Clean up
    vpx_img_free(&img);
    vpx_codec_destroy(&codec);

    return 0;
}