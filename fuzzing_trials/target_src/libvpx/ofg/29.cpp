#include <cstdint>
#include <cstdlib>
#include <vpx/vpx_decoder.h>
#include <vpx/vp8dx.h>

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
    // Check if the input size is greater than zero
    if (size == 0 || data == nullptr) {
        return 0;
    }

    // Declare and initialize variables
    vpx_codec_ctx_t codec_ctx;
    vpx_codec_iface_t *iface = vpx_codec_vp8_dx(); // Use VP8 decoder interface
    vpx_codec_dec_cfg_t dec_cfg = {0}; // Initialize the decoder configuration
    vpx_codec_flags_t flags = 0;
    int ver = VPX_DECODER_ABI_VERSION;

    // Initialize codec context
    vpx_codec_err_t res = vpx_codec_dec_init_ver(&codec_ctx, iface, &dec_cfg, flags, ver);

    // Check result of initialization
    if (res != VPX_CODEC_OK) {
        return 0; // Return if initialization failed
    }

    // Decode the input data
    res = vpx_codec_decode(&codec_ctx, data, size, nullptr, 0);

    // Check if decoding was successful
    if (res == VPX_CODEC_OK) {
        // Retrieve the decoded frame
        vpx_codec_iter_t iter = nullptr;
        vpx_image_t *img = nullptr;

        while ((img = vpx_codec_get_frame(&codec_ctx, &iter)) != nullptr) {
            // Process the image here if needed
            // For fuzzing purposes, we can access some properties of the image
            int width = img->d_w;
            int height = img->d_h;
            int format = img->fmt;

            // Access the image data to ensure it is being processed
            if (img->planes[VPX_PLANE_Y]) {
                // Example: Access the first pixel in the Y plane
                uint8_t first_pixel = img->planes[VPX_PLANE_Y][0];
                (void)first_pixel; // Use the pixel value to avoid unused variable warning
            }
        }
    }

    // Destroy the codec context
    vpx_codec_destroy(&codec_ctx);

    return 0;
}