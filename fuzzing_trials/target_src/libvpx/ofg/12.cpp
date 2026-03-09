#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" {
    #include <vpx/vpx_codec.h>
    #include <vpx/vpx_decoder.h>
    #include <vpx/vp8dx.h> // Include the header for VP8 decoder

    // Dummy callback function
    void put_slice_callback(void *user_priv, const vpx_image_t *img, const vpx_image_rect_t *valid, const vpx_image_rect_t *update) {
        // Do nothing
    }

    int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
        if (size < 10) { // Ensure there's at least some data to process
            return 0;
        }

        vpx_codec_ctx_t codec_ctx;
        vpx_codec_err_t err;

        // Initialize codec context with default configuration
        vpx_codec_dec_cfg_t cfg = {0};
        err = vpx_codec_dec_init(&codec_ctx, vpx_codec_vp8_dx(), &cfg, 0);
        if (err != VPX_CODEC_OK) {
            return 0;
        }

        // Use the data as a dummy user_priv pointer
        void *user_priv = (void *)data;

        // Register the callback
        err = vpx_codec_register_put_slice_cb(&codec_ctx, put_slice_callback, user_priv);
        if (err != VPX_CODEC_OK) {
            vpx_codec_destroy(&codec_ctx);
            return 0;
        }

        // Decode the input data
        // Ensure the input data is not null and has at least a minimal size
        if (size > 10) {
            // Attempt to decode the data multiple times to increase coverage
            for (size_t i = 0; i < 5; ++i) {
                err = vpx_codec_decode(&codec_ctx, data, size, user_priv, 0);
                if (err != VPX_CODEC_OK) {
                    break; // Exit loop if decoding fails
                }

                // Retrieve the decoded frame
                vpx_codec_iter_t iter = NULL;
                const vpx_image_t *img = NULL;
                while ((img = vpx_codec_get_frame(&codec_ctx, &iter)) != NULL) {
                    // Process the image if needed
                    // For example, access image properties to ensure they are valid
                    (void)img->d_w;
                    (void)img->d_h;
                    (void)img->fmt;
                }
            }
        }

        // Destroy codec context
        vpx_codec_destroy(&codec_ctx);

        return 0;
    }
}