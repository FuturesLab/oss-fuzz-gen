#include <stdint.h>
#include <stddef.h>

extern "C" {
#include <vpx/vpx_codec.h>
#include <vpx/vpx_decoder.h>
#include <vpx/vp8dx.h>  // Include the header for vpx_codec_vp8_dx

// Dummy callback function to be used with vpx_codec_register_put_frame_cb
void dummy_put_frame_cb(void *user_priv, const vpx_image_t *img) {
    // This is a no-op function for testing purposes.
}

int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    // Check if the input data is valid
    if (data == NULL || size == 0) {
        return 0;  // Exit if input is invalid
    }

    // Declare and initialize variables
    vpx_codec_ctx_t codec_ctx;
    vpx_codec_err_t res;
    void *user_priv = (void*)data;  // Using data as user_priv for testing

    // Initialize the codec context
    res = vpx_codec_dec_init(&codec_ctx, vpx_codec_vp8_dx(), NULL, 0);
    if (res != VPX_CODEC_OK) {
        return 0;  // Exit if initialization fails
    }

    // Register the dummy callback
    res = vpx_codec_register_put_frame_cb(&codec_ctx, dummy_put_frame_cb, user_priv);
    if (res != VPX_CODEC_OK) {
        vpx_codec_destroy(&codec_ctx);
        return 0;  // Exit if callback registration fails
    }

    // Feed the data to the decoder
    res = vpx_codec_decode(&codec_ctx, data, size, NULL, 0);
    if (res != VPX_CODEC_OK) {
        vpx_codec_destroy(&codec_ctx);
        return 0;  // Exit if decoding fails
    }

    // Retrieve the decoded frame
    vpx_codec_iter_t iter = NULL;
    const vpx_image_t *img = NULL;
    while ((img = vpx_codec_get_frame(&codec_ctx, &iter)) != NULL) {
        // Process the decoded frame (for fuzzing, we can just loop over the frames)
    }

    // Destroy the codec context
    vpx_codec_destroy(&codec_ctx);

    return 0;
}

}