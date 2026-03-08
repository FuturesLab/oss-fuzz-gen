#include <stdint.h>
#include <stddef.h>
#include <vpx/vpx_encoder.h>

extern "C" {
    #include <vpx/vpx_codec.h>
    #include <vpx/vp8cx.h> // Include the header for vpx_codec_vp8_cx
}

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    vpx_codec_iface_t *iface = vpx_codec_vp8_cx(); // Using VP8 codec interface
    vpx_codec_enc_cfg_t cfg;
    unsigned int usage = 0; // Default usage

    // Ensure the data is not NULL and has a reasonable size
    if (data == NULL || size < 3) { // Adjusted minimum size to 3 bytes
        return 0;
    }

    // Call the function-under-test
    vpx_codec_err_t res = vpx_codec_enc_config_default(iface, &cfg, usage);
    if (res != VPX_CODEC_OK) {
        return 0;
    }

    // Use input data to set some configuration parameters
    cfg.g_w = 640 + (data[0] % 640); // Set width based on input data
    cfg.g_h = 480 + (data[1] % 480); // Set height based on input data
    cfg.rc_target_bitrate = 100 + (data[2] % 2000); // Set bitrate based on input data

    // Calculate minimum required size for image data
    size_t min_img_size = cfg.g_w * cfg.g_h * 3 / 2; // I420 format

    // Ensure the input data is large enough to contain image data
    if (size < min_img_size + 3) { // Adjusted to account for the first 3 bytes
        return 0;
    }

    // Initialize the codec context
    vpx_codec_ctx_t codec;
    if (vpx_codec_enc_init(&codec, iface, &cfg, 0)) {
        return 0;
    }

    // Set up the image data
    vpx_image_t img;
    if (!vpx_img_wrap(&img, VPX_IMG_FMT_I420, cfg.g_w, cfg.g_h, 1, const_cast<uint8_t*>(data + 3))) {
        vpx_codec_destroy(&codec);
        return 0;
    }

    // Encode the image
    if (vpx_codec_encode(&codec, &img, 0, 1, 0, VPX_DL_REALTIME)) {
        vpx_img_free(&img);
        vpx_codec_destroy(&codec);
        return 0;
    }

    // Cleanup
    vpx_img_free(&img);
    vpx_codec_destroy(&codec);

    return 0;
}