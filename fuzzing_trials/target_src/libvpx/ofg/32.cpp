#include <stdint.h>
#include <stddef.h>
#include <vpx/vpx_decoder.h>
#include <vpx/vp8dx.h>

extern "C" {
    vpx_codec_iface_t * vpx_codec_vp9_dx();
}

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    // Call the function-under-test
    vpx_codec_iface_t *iface = vpx_codec_vp9_dx();

    // Ensure that the returned interface is not NULL
    if (iface == NULL) {
        return 0;
    }

    // Initialize codec context
    vpx_codec_ctx_t codec;
    vpx_codec_err_t res;

    // Initialize codec with the interface
    res = vpx_codec_dec_init(&codec, iface, NULL, 0);
    if (res != VPX_CODEC_OK) {
        return 0;
    }

    // Decode the input data
    res = vpx_codec_decode(&codec, data, size, NULL, 0);
    if (res != VPX_CODEC_OK) {
        vpx_codec_destroy(&codec);
        return 0;
    }

    // Destroy the codec context
    vpx_codec_destroy(&codec);

    return 0;
}