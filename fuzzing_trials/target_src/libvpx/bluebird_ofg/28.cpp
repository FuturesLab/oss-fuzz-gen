#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" {
    #include "/src/libvpx/vpx/vpx_codec.h"
    #include "vpx/vpx_decoder.h"
    #include "vpx/vp8dx.h" // Include the header for VP8 decoder interface

    // Define a dummy callback function
    void dummy_put_slice_cb(void *user_priv, const vpx_image_t *img, const vpx_image_rect_t *valid, const vpx_image_rect_t *update) {
        // This is a dummy callback function, it does nothing.
    }

    int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
        if (size < 10) { // Ensure there's enough data to potentially be a valid VP8 bitstream
            return 0; // Return early if there is insufficient data
        }

        vpx_codec_ctx_t codec_ctx;
        vpx_codec_err_t result;
        void *user_priv = reinterpret_cast<void *>(0x1); // Non-null user data

        // Initialize the codec context
        result = vpx_codec_dec_init(&codec_ctx, vpx_codec_vp8_dx(), NULL, 0);
        if (result != VPX_CODEC_OK) {
            return 0;
        }

        // Register the dummy callback function
        result = vpx_codec_register_put_slice_cb(&codec_ctx, dummy_put_slice_cb, user_priv);
        if (result != VPX_CODEC_OK) {
            vpx_codec_destroy(&codec_ctx);
            return 0;
        }

        // Allocate memory for the input data and ensure it's not null
        uint8_t *input_data = static_cast<uint8_t *>(malloc(size));
        if (!input_data) {
            vpx_codec_destroy(&codec_ctx);
            return 0;
        }
        memcpy(input_data, data, size);

        // Decode the input data
        result = vpx_codec_decode(&codec_ctx, input_data, static_cast<unsigned int>(size), NULL, 0);
        free(input_data); // Free the allocated memory after use
        if (result != VPX_CODEC_OK) {
            vpx_codec_destroy(&codec_ctx);
            return 0;
        }

        // Get the decoded frame
        vpx_codec_iter_t iter = NULL;
        const vpx_image_t *img = NULL;
        while ((img = vpx_codec_get_frame(&codec_ctx, &iter)) != NULL) {
            // Process the decoded frame (currently does nothing)
        }

        // Clean up and destroy the codec context
        vpx_codec_destroy(&codec_ctx);

        return 0;
    }
}