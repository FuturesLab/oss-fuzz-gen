#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <aom/aom_codec.h>
    #include <aom/aom_image.h>
    #include <aom/aom_decoder.h>
    #include <aom/aomdx.h>  // Include this header for aom_codec_av1_dx
}

extern "C" int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
    // Initialize the codec context
    aom_codec_ctx_t codec_ctx;
    aom_codec_iface_t *iface = aom_codec_av1_dx();
    aom_codec_dec_cfg cfg = {0, 0, 0};

    // Initialize the codec
    if (aom_codec_dec_init(&codec_ctx, iface, &cfg, 0) != AOM_CODEC_OK) {
        return 0;
    }

    // Decode the input data
    if (aom_codec_decode(&codec_ctx, data, size, NULL) != AOM_CODEC_OK) {
        aom_codec_destroy(&codec_ctx);
        return 0;
    }

    // Initialize the iterator
    aom_codec_iter_t iter = NULL;
    aom_image_t *img = NULL;

    // Call the function-under-test
    img = aom_codec_get_frame(&codec_ctx, &iter);

    // Cleanup
    aom_codec_destroy(&codec_ctx);

    return 0;
}