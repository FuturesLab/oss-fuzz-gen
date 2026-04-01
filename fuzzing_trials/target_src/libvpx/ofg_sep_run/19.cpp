#include <stddef.h>
#include <stdint.h>
#include <vpx/vpx_decoder.h>
#include <vpx/vp8dx.h>

extern "C" {
    // Include the function-under-test
    vpx_codec_iface_t * vpx_codec_vp8_dx();
}

extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
    // Initialize codec context
    vpx_codec_ctx_t codec;
    vpx_codec_err_t res;

    // Call the function-under-test to get the codec interface
    vpx_codec_iface_t *codec_interface = vpx_codec_vp8_dx();

    // Perform some basic checks
    if (codec_interface == NULL || size == 0) { // Allow processing of any non-zero size
        return 0; // Early exit if the codec interface is NULL
    }

    // Initialize the codec with the interface
    res = vpx_codec_dec_init(&codec, codec_interface, NULL, 0);
    if (res != VPX_CODEC_OK) {
        return 0; // Exit if codec initialization fails
    }

    // Decode the input data
    res = vpx_codec_decode(&codec, data, size, NULL, 0);
    if (res != VPX_CODEC_OK) {
        vpx_codec_destroy(&codec);
        return 0; // Exit if decoding fails
    }

    // Retrieve the decoded frames
    vpx_codec_iter_t iter = NULL;
    vpx_image_t *img;
    while ((img = vpx_codec_get_frame(&codec, &iter)) != NULL) {
        // Process the image (for fuzzing purposes, we might just access some fields)
        // Accessing some fields to ensure code coverage
        if (img->d_w > 0 && img->d_h > 0) { // Check if dimensions are valid
            (void)img->d_w;
            (void)img->d_h;
            (void)img->fmt;
        }
    }

    // Clean up and destroy the codec context
    vpx_codec_destroy(&codec);

    return 0;
}