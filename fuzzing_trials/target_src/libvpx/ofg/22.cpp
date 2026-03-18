#include <stdint.h>
#include <stddef.h>
#include <vpx/vpx_decoder.h>
#include <vpx/vp8dx.h>

extern "C" int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    // Initialize codec context
    vpx_codec_ctx_t codec;
    vpx_codec_dec_cfg_t cfg = {0};
    vpx_codec_err_t res;

    // Initialize the codec
    res = vpx_codec_dec_init(&codec, vpx_codec_vp8_dx(), &cfg, 0);
    if (res != VPX_CODEC_OK) {
        return 0; // Initialization failed, exit early
    }

    // Ensure size is greater than zero to avoid passing null input
    if (size > 0) {
        // Prepare parameters for vpx_codec_decode
        const uint8_t *data_ptr = data;
        unsigned int data_sz = static_cast<unsigned int>(size);
        void *user_priv = nullptr; // Use nullptr for user private data
        long deadline = 0; // No deadline

        // Call the function under test
        vpx_codec_err_t decode_res = vpx_codec_decode(&codec, data_ptr, data_sz, user_priv, deadline);

        // Check if decoding was successful
        if (decode_res == VPX_CODEC_OK) {
            // Retrieve frame to ensure the function is fully utilized
            vpx_codec_iter_t iter = nullptr;
            vpx_image_t *img = nullptr;
            while ((img = vpx_codec_get_frame(&codec, &iter)) != nullptr) {
                // Process the image (dummy processing for fuzzing)
                (void)img;
            }
        }
    }

    // Clean up
    vpx_codec_destroy(&codec);

    return 0;
}