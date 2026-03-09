#include <stdint.h>
#include <stddef.h>
#include <vpx/vpx_decoder.h>
#include <vpx/vp8dx.h>  // Include the VP8/VP9 decoder header

extern "C" {
    vpx_codec_iface_t * vpx_codec_vp9_dx();
}

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for meaningful decoding
    if (size < 10) {
        return 0;
    }

    // Call the function-under-test
    vpx_codec_iface_t *iface = vpx_codec_vp9_dx();

    // Check if the returned interface is not NULL
    if (iface != NULL) {
        // Initialize decoder with the interface
        vpx_codec_ctx_t codec;
        vpx_codec_err_t res = vpx_codec_dec_init(&codec, iface, NULL, 0);

        // If initialization is successful, decode the input data
        if (res == VPX_CODEC_OK) {
            // Decode the input data
            res = vpx_codec_decode(&codec, data, size, NULL, 0);

            // Check if decoding was successful
            if (res == VPX_CODEC_OK) {
                // Retrieve the decoded frames
                vpx_codec_iter_t iter = NULL;
                vpx_image_t *img;
                while ((img = vpx_codec_get_frame(&codec, &iter)) != NULL) {
                    // Process the decoded image (e.g., accessing img->planes)
                    // To ensure code coverage, let's access some properties of the image
                    if (img->fmt != VPX_IMG_FMT_NONE) {
                        int width = img->d_w;
                        int height = img->d_h;
                        // Accessing the first plane as an example
                        uint8_t *plane = img->planes[0];
                        (void)width;
                        (void)height;
                        (void)plane;
                    }
                }
            }

            // Destroy the codec
            vpx_codec_destroy(&codec);
        }
    }

    return 0;
}