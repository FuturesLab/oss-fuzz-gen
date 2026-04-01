#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

extern "C" {
    #include <vpx/vpx_decoder.h>
    #include <vpx/vpx_codec.h>
    #include <vpx/vp8dx.h>
}

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    vpx_codec_ctx_t codec_ctx;
    vpx_codec_iter_t iter = NULL;
    vpx_image_t *image = NULL;

    // Initialize codec context
    if (vpx_codec_dec_init(&codec_ctx, vpx_codec_vp8_dx(), NULL, 0) != VPX_CODEC_OK) {
        return 0;
    }

    // Decode the input data
    if (vpx_codec_decode(&codec_ctx, data, size, NULL, 0) != VPX_CODEC_OK) {
        vpx_codec_destroy(&codec_ctx);
        return 0;
    }

    // Get the decoded frame
    while ((image = vpx_codec_get_frame(&codec_ctx, &iter)) != NULL) {
        // Process the image to ensure code paths are exercised
        printf("Decoded frame: %d x %d\n", image->d_w, image->d_h);
        
        // Additional processing to increase coverage
        for (int plane = 0; plane < 3; ++plane) {
            if (image->planes[plane]) {
                // Example processing: just accessing the data
                for (int y = 0; y < image->d_h; ++y) {
                    for (int x = 0; x < image->d_w; ++x) {
                        // Access pixel data
                        uint8_t pixel = image->planes[plane][y * image->stride[plane] + x];
                        // Dummy operation
                        pixel = pixel ^ 0xFF; // Invert pixel value

                        // Further processing to ensure more code paths
                        if (pixel == 0) {
                            printf("Pixel is zero at (%d, %d)\n", x, y);
                        } else if (pixel == 255) {
                            printf("Pixel is max at (%d, %d)\n", x, y);
                        }
                    }
                }
            }
        }
    }

    // Clean up
    vpx_codec_destroy(&codec_ctx);

    return 0;
}