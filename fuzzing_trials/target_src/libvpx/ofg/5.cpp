#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <vpx/vpx_codec.h>
    #include <vpx/vpx_image.h>
    #include <vpx/vp8dx.h>
    #include <vpx/vpx_decoder.h>
}

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    // Check for null data or size too small to be a valid VP8 frame
    if (data == NULL || size == 0) {
        return 0;
    }

    // Declare and initialize variables
    vpx_codec_ctx_t codec_ctx;
    vpx_codec_iter_t iter = NULL;
    vpx_image_t *image = NULL;

    // Initialize the codec context
    vpx_codec_err_t res = vpx_codec_dec_init_ver(&codec_ctx, vpx_codec_vp8_dx(), NULL, 0, VPX_DECODER_ABI_VERSION);
    if (res != VPX_CODEC_OK) {
        return 0; // Initialization failed, exit early
    }

    // Decode the input data
    res = vpx_codec_decode(&codec_ctx, data, size, NULL, 0);
    if (res != VPX_CODEC_OK) {
        vpx_codec_destroy(&codec_ctx);
        return 0; // Decoding failed, exit early
    }

    // Retrieve and process the decoded frame
    while ((image = vpx_codec_get_frame(&codec_ctx, &iter)) != NULL) {
        // Example processing: Access image properties
        int width = image->d_w;
        int height = image->d_h;
        int stride = image->stride[VPX_PLANE_Y];
        const uint8_t *buffer = image->planes[VPX_PLANE_Y];

        // Perform operations on the image data to ensure coverage
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                // Example operation: Access pixel value
                uint8_t pixel_value = buffer[y * stride + x];
                // Perform some operation on pixel_value if needed
                (void)pixel_value; // Use pixel_value to prevent unused variable warning
            }
        }
    }

    // Clean up
    vpx_codec_destroy(&codec_ctx);

    return 0;
}