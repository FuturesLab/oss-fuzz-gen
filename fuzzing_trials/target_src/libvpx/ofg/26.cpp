#include <cstdint>
#include <cstdlib>
#include <cstring>  // Include for memset
#include <vpx/vpx_codec.h>
#include <vpx/vpx_decoder.h>
#include <vpx/vp8dx.h>  // Include for VPX_CODEC_USE_POSTPROC

extern "C" {

// Dummy callback functions for getting and releasing frame buffers
int get_frame_buffer(void *user_data, size_t min_size, vpx_codec_frame_buffer_t *fb) {
    // Allocate a buffer and assign it to fb->data.
    fb->data = static_cast<uint8_t *>(malloc(min_size));
    fb->size = min_size;
    return fb->data ? 0 : -1;
}

int release_frame_buffer(void *user_data, vpx_codec_frame_buffer_t *fb) {
    // Free the allocated buffer
    free(fb->data);
    fb->data = nullptr;
    fb->size = 0;
    return 0;
}

int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    if (size < 10) {  // Ensure the input size is reasonable
        return 0;
    }

    // Check for a simple VP8 signature to increase the chance of valid input
    if (data[0] != 0x9D || data[1] != 0x01 || data[2] != 0x2A) {
        return 0;
    }

    vpx_codec_ctx_t codec_ctx;
    vpx_codec_err_t result;
    vpx_codec_dec_cfg_t cfg = {0};  // Configuration structure
    cfg.threads = 1;  // Use a single thread

    // Initialize codec context
    memset(&codec_ctx, 0, sizeof(vpx_codec_ctx_t));

    // Initialize decoder with VPX_CODEC_USE_POSTPROC to enable post-processing
    result = vpx_codec_dec_init(&codec_ctx, vpx_codec_vp8_dx(), &cfg, VPX_CODEC_USE_POSTPROC);
    if (result != VPX_CODEC_OK) {
        return 0;
    }

    // Set frame buffer functions
    result = vpx_codec_set_frame_buffer_functions(
        &codec_ctx,
        get_frame_buffer,
        release_frame_buffer,
        nullptr
    );
    if (result != VPX_CODEC_OK) {
        vpx_codec_destroy(&codec_ctx);
        return 0;
    }

    // Decode the input data
    result = vpx_codec_decode(&codec_ctx, data, size, nullptr, 0);
    if (result != VPX_CODEC_OK) {
        vpx_codec_destroy(&codec_ctx);
        return 0;
    }

    // Retrieve decoded frames
    vpx_codec_iter_t iter = nullptr;
    vpx_image_t *img;
    while ((img = vpx_codec_get_frame(&codec_ctx, &iter)) != nullptr) {
        // Process the image (if necessary)
        // Example: Access image properties
        int width = img->d_w;
        int height = img->d_h;
        int fmt = img->fmt;
        
        // Simulate some processing on the image data
        for (int plane = 0; plane < 3; ++plane) {
            uint8_t *plane_data = img->planes[plane];
            int stride = img->stride[plane];
            for (int y = 0; y < img->d_h; ++y) {
                for (int x = 0; x < img->d_w; ++x) {
                    // Simple operation to simulate processing
                    plane_data[y * stride + x] = plane_data[y * stride + x] ^ 0xFF;
                }
            }
        }

        (void)width;  // Use these variables to prevent unused variable warnings
        (void)height;
        (void)fmt;
    }

    // Clean up
    vpx_codec_destroy(&codec_ctx);

    return 0;
}

}