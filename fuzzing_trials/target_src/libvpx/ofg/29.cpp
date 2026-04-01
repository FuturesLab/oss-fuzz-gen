#include <cstdint>
#include <cstdlib>
#include <vpx/vpx_decoder.h>
#include <vpx/vp8dx.h>

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0; // No input data to process
    }

    // Declare and initialize variables
    vpx_codec_ctx_t codec_ctx;
    vpx_codec_iface_t *iface = vpx_codec_vp8_dx(); // Use VP8 interface
    vpx_codec_dec_cfg_t dec_cfg = {0}; // Initialize with zero
    vpx_codec_flags_t flags = 0;
    int ver = VPX_DECODER_ABI_VERSION;

    // Initialize the decoder configuration
    dec_cfg.threads = 1; // Use a single thread
    dec_cfg.w = 640;     // Set default width
    dec_cfg.h = 480;     // Set default height

    // Call the function-under-test
    vpx_codec_err_t res = vpx_codec_dec_init_ver(&codec_ctx, iface, &dec_cfg, flags, ver);

    // If initialization was successful, decode the input data
    if (res == VPX_CODEC_OK) {
        // Decode the data
        res = vpx_codec_decode(&codec_ctx, data, size, NULL, 0);
        
        if (res == VPX_CODEC_OK) {
            // Iterate over the decoded frames
            vpx_codec_iter_t iter = NULL;
            vpx_image_t *img;
            while ((img = vpx_codec_get_frame(&codec_ctx, &iter)) != NULL) {
                // Process the decoded frame (img)
                // For fuzzing purposes, we don't need to do anything with the frame
            }
        }

        // Cleanup
        vpx_codec_destroy(&codec_ctx);
    }

    return 0;
}