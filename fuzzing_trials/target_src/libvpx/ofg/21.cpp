#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio> // Include for 'stderr'

extern "C" {
    #include <vpx/vpx_decoder.h>
    #include <vpx/vp8dx.h>
}

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    if (size < 10) { // Ensure minimum size for a valid VP8 frame
        return 0;
    }

    vpx_codec_ctx_t codec;
    vpx_codec_err_t res;
    vpx_codec_iface_t *iface = vpx_codec_vp8_dx(); // Use VP8 decoder interface

    // Initialize the codec context
    res = vpx_codec_dec_init(&codec, iface, NULL, 0);
    if (res != VPX_CODEC_OK) {
        return 0;
    }

    // Ensure the size is within a reasonable range
    unsigned int data_size = static_cast<unsigned int>(size);

    // Call the function under test
    vpx_codec_err_t decode_res = vpx_codec_decode(&codec, data, data_size, NULL, 0);

    // Check if decoding was successful
    if (decode_res == VPX_CODEC_OK) {
        // Retrieve frame information
        vpx_codec_iter_t iter = NULL;
        vpx_image_t *img;
        while ((img = vpx_codec_get_frame(&codec, &iter)) != NULL) {
            // Process the image frame (dummy processing)
            volatile int width = img->d_w;
            volatile int height = img->d_h;
            (void)width;
            (void)height;
        }
    } else {
        // Handle decoding errors more robustly
        const char *error_detail = vpx_codec_error_detail(&codec);
        if (error_detail) {
            // Log or handle the error detail if needed
            // For fuzzing, we can print the error to help diagnose issues
            fprintf(stderr, "Decoding error: %s\n", error_detail);
        }
    }

    // Clean up
    vpx_codec_destroy(&codec);

    return 0;
}