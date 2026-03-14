#include <stdint.h>
#include <stddef.h>
#include <aom/aom_decoder.h>
#include <aom/aomdx.h>

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    // Call the function-under-test
    aom_codec_iface_t *iface = aom_codec_av1_dx();

    // Ensure that the returned interface is not NULL
    if (iface == NULL) {
        return 0;
    }

    // Initialize a codec context
    aom_codec_ctx_t codec;
    aom_codec_err_t res;

    // Initialize the codec with the interface
    res = aom_codec_dec_init(&codec, iface, NULL, 0);
    if (res != AOM_CODEC_OK) {
        return 0;
    }

    // Decode the input data
    res = aom_codec_decode(&codec, data, size, NULL);
    if (res != AOM_CODEC_OK) {
        aom_codec_destroy(&codec);
        return 0;
    }

    // Retrieve the decoded frame
    aom_codec_iter_t iter = NULL;
    aom_image_t *img = aom_codec_get_frame(&codec, &iter);

    // Clean up
    aom_codec_destroy(&codec);

    return 0;
}