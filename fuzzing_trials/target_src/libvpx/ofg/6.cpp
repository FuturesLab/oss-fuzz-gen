#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

extern "C" {
    #include <vpx/vpx_codec.h>
    #include <vpx/vpx_decoder.h>
    #include <vpx/vp8dx.h>  // Include the header for VP8 decoder
}

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    if (data == NULL || size == 0) {
        return 0;  // No input data to process
    }

    vpx_codec_ctx_t codec;
    vpx_codec_iter_t iter = NULL;
    vpx_image_t *img = NULL;
    vpx_codec_err_t res;

    // Initialize the codec context
    res = vpx_codec_dec_init(&codec, vpx_codec_vp8_dx(), NULL, 0);
    if (res != VPX_CODEC_OK) {
        fprintf(stderr, "Failed to initialize codec: %s\n", vpx_codec_err_to_string(res));
        return 0;
    }

    // Decode the input data
    res = vpx_codec_decode(&codec, data, size, NULL, 0);
    if (res != VPX_CODEC_OK) {
        fprintf(stderr, "Failed to decode data: %s\n", vpx_codec_err_to_string(res));
        vpx_codec_destroy(&codec);
        return 0;
    }

    // Get the frame
    while ((img = vpx_codec_get_frame(&codec, &iter)) != NULL) {
        // Process the image frame if needed
        fprintf(stdout, "Retrieved a frame: %dx%d\n", img->d_w, img->d_h);

        // Additional processing to ensure code coverage
        // Accessing some image data to ensure it's utilized
        if (img->fmt == VPX_IMG_FMT_I420) {
            // Access the Y plane
            for (int y = 0; y < img->d_h; y++) {
                for (int x = 0; x < img->d_w; x++) {
                    uint8_t pixel = img->planes[VPX_PLANE_Y][y * img->stride[VPX_PLANE_Y] + x];
                    // Simple operation to use the pixel value
                    pixel = (pixel + 1) % 256;
                }
            }
            // Access the U and V planes
            for (int y = 0; y < img->d_h / 2; y++) {
                for (int x = 0; x < img->d_w / 2; x++) {
                    uint8_t u_pixel = img->planes[VPX_PLANE_U][y * img->stride[VPX_PLANE_U] + x];
                    uint8_t v_pixel = img->planes[VPX_PLANE_V][y * img->stride[VPX_PLANE_V] + x];
                    // Simple operations to use the pixel values
                    u_pixel = (u_pixel + 1) % 256;
                    v_pixel = (v_pixel + 1) % 256;
                }
            }
        }
    }

    // Clean up
    vpx_codec_destroy(&codec);

    return 0;
}