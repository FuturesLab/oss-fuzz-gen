extern "C" {
    #include <vpx/vpx_decoder.h>
    #include <vpx/vp8dx.h>
}

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    // Call the function-under-test
    vpx_codec_iface_t *iface = vpx_codec_vp9_dx();

    // Check if the interface is not NULL
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

    // Clean up
    vpx_codec_destroy(&codec);

    return 0;
}