#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" {
    #include <vpx/vpx_codec.h>
    #include <vpx/vp8cx.h> // Include the VP8 encoder interface
}

extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    // Ensure the input size is large enough to be meaningful
    if (size < 10) {
        return 0;
    }

    // Initialize the codec context
    vpx_codec_ctx_t codec_ctx;
    vpx_codec_enc_cfg_t cfg;
    vpx_codec_err_t res;

    // Set up a dummy codec interface for VP8
    vpx_codec_iface_t *iface = vpx_codec_vp8_cx();

    // Initialize the codec configuration
    if (vpx_codec_enc_config_default(iface, &cfg, 0) != VPX_CODEC_OK) {
        return 0;
    }

    // Set some configuration parameters to utilize the input data
    cfg.g_w = data[0] + 1; // Use the first byte to set width
    cfg.g_h = data[1] + 1; // Use the second byte to set height
    cfg.rc_target_bitrate = (data[2] % 5000) + 100; // Use the third byte to set bitrate

    // Initialize the codec context
    if (vpx_codec_enc_init(&codec_ctx, iface, &cfg, 0) != VPX_CODEC_OK) {
        return 0;
    }

    // Prepare a vpx_fixed_buf_t
    vpx_fixed_buf_t fixed_buf;
    fixed_buf.buf = (void*)data;
    fixed_buf.sz = size;

    // Use some arbitrary non-zero values for the additional unsigned int parameters
    unsigned int pad_before = 1;
    unsigned int pad_after = 1;

    // Call the function under test
    res = vpx_codec_set_cx_data_buf(&codec_ctx, &fixed_buf, pad_before, pad_after);

    // Check the result of the function call
    if (res != VPX_CODEC_OK) {
        vpx_codec_destroy(&codec_ctx);
        return 0;
    }

    // Optionally, encode a frame to further increase code coverage
    vpx_image_t img;
    if (!vpx_img_alloc(&img, VPX_IMG_FMT_I420, cfg.g_w, cfg.g_h, 1)) {
        vpx_codec_destroy(&codec_ctx);
        return 0;
    }

    // Simulate a frame with the input data
    size_t plane_size = img.d_w * img.d_h; // Calculate the size of the Y plane
    memcpy(img.planes[0], data + 3, size < plane_size ? size - 3 : plane_size); // Offset by 3 to avoid using width, height, and bitrate bytes

    // Encode the frame
    res = vpx_codec_encode(&codec_ctx, &img, 0, 1, 0, VPX_DL_REALTIME);

    // Free the image
    vpx_img_free(&img);

    // Destroy the codec context
    vpx_codec_destroy(&codec_ctx);

    return 0;
}