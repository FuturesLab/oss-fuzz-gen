#include <stdint.h>
#include <stddef.h>
#include <vpx/vpx_codec.h>
#include <vpx/vpx_decoder.h>
#include <vpx/vp8dx.h> // Include the header for vpx_codec_vp8_dx

extern "C" {

// Define a simple callback function
void put_frame_callback(void *user_priv, const vpx_image_t *img) {
    // This is a simple callback function that does nothing
    // In a real-world scenario, you might process the image here
    // For fuzzing, we can just ensure this function gets called
    if (img != NULL) {
        // Example processing: access some image properties
        volatile int width = img->d_w;
        volatile int height = img->d_h;
        (void)width;
        (void)height;
    }
}

// Fuzzing harness for vpx_codec_register_put_frame_cb
int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    if (size < 10) { // Ensure there is enough data for meaningful input
        return 0;
    }

    vpx_codec_ctx_t codec_ctx;
    vpx_codec_err_t err;

    // Initialize the codec context with some dummy values
    vpx_codec_dec_cfg_t cfg = {0};
    err = vpx_codec_dec_init(&codec_ctx, vpx_codec_vp8_dx(), &cfg, 0);
    if (err != VPX_CODEC_OK) {
        return 0; // Early exit if initialization fails
    }

    // Use the first byte of data as a dummy pointer
    void *user_priv = (void *)(uintptr_t)data[0];

    // Call the function under test
    err = vpx_codec_register_put_frame_cb(&codec_ctx, put_frame_callback, user_priv);
    if (err != VPX_CODEC_OK) {
        vpx_codec_destroy(&codec_ctx);
        return 0; // Early exit if registration fails
    }

    // Feed the data to the codec to trigger the callback
    // Ensure the data is not null and has a valid size for decoding
    if (size > 0) {
        err = vpx_codec_decode(&codec_ctx, data, size, NULL, 0);
        if (err != VPX_CODEC_OK) {
            vpx_codec_destroy(&codec_ctx);
            return 0; // Early exit if decoding fails
        }

        // Retrieve the frame to trigger the callback
        vpx_codec_iter_t iter = NULL;
        const vpx_image_t *img = vpx_codec_get_frame(&codec_ctx, &iter);
        while (img != NULL) {
            // Process the image if needed
            img = vpx_codec_get_frame(&codec_ctx, &iter);
        }
    }

    // Destroy the codec context
    vpx_codec_destroy(&codec_ctx);

    return 0;
}

}