#include <stdint.h>
#include <stddef.h>
#include <vpx/vpx_decoder.h>
#include <vpx/vp8dx.h>

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    vpx_codec_ctx_t codec_ctx;
    vpx_codec_stream_info_t stream_info;
    vpx_codec_err_t res;

    // Initialize codec context
    vpx_codec_dec_cfg_t cfg = {0};
    cfg.threads = 1; // Use a single thread

    res = vpx_codec_dec_init(&codec_ctx, vpx_codec_vp8_dx(), &cfg, 0);
    if (res != VPX_CODEC_OK) {
        return 0;
    }

    // Initialize stream_info with some default values
    stream_info.sz = sizeof(vpx_codec_stream_info_t);
    stream_info.w = 640; // Default width
    stream_info.h = 480; // Default height

    // Feed the decoder with the input data
    res = vpx_codec_decode(&codec_ctx, data, size, NULL, 0);
    if (res != VPX_CODEC_OK) {
        vpx_codec_destroy(&codec_ctx);
        return 0;
    }

    // Retrieve frame to ensure the decoder processes the input
    vpx_codec_iter_t iter = NULL;
    vpx_image_t *img = NULL;
    while ((img = vpx_codec_get_frame(&codec_ctx, &iter)) != NULL) {
        // Process the image if needed
        // For example, access image properties to simulate processing
        int width = img->d_w;
        int height = img->d_h;
        int stride = img->stride[0];
        // Simulate some processing on the image data to increase code coverage
        for (int y = 0; y < height; ++y) {
            const uint8_t *row = img->planes[0] + y * stride;
            for (int x = 0; x < width; ++x) {
                uint8_t pixel = row[x];
                (void)pixel; // Use pixel value to avoid unused variable warnings
            }
        }
    }

    // Cleanup
    vpx_codec_destroy(&codec_ctx);

    return 0;
}