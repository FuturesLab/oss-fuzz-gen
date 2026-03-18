#include <stdint.h>
#include <stddef.h>
#include <cstring>  // Include for memset

extern "C" {
    #include <vpx/vpx_codec.h>
    #include <vpx/vpx_decoder.h>
    #include <vpx/vpx_image.h>

    // Declare the function prototype for vpx_codec_get_preview_frame
    const vpx_image_t *vpx_codec_get_preview_frame(vpx_codec_ctx_t *ctx);

    // Declare the function prototype for vpx_codec_vp8_dx
    vpx_codec_iface_t *vpx_codec_vp8_dx(void);
}

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to initialize vpx_codec_ctx_t and some input data
    if (size < sizeof(vpx_codec_ctx_t) + 1) {
        return 0;
    }

    // Initialize vpx_codec_ctx_t
    vpx_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(vpx_codec_ctx_t));

    // Initialize codec with a decoder interface
    vpx_codec_iface_t *iface = vpx_codec_vp8_dx();
    if (vpx_codec_dec_init(&codec_ctx, iface, nullptr, 0)) {
        return 0; // Initialization failed
    }

    // Decode the input data
    if (vpx_codec_decode(&codec_ctx, data, size, nullptr, 0)) {
        vpx_codec_destroy(&codec_ctx);
        return 0; // Decoding failed
    }

    // Call the function-under-test
    const vpx_image_t *image = vpx_codec_get_preview_frame(&codec_ctx);

    // Use the result to prevent compiler optimizations
    if (image != NULL) {
        // Access some fields to simulate usage
        (void)image->fmt;
        (void)image->d_w;
        (void)image->d_h;
    }

    // Clean up
    vpx_codec_destroy(&codec_ctx);

    return 0;
}