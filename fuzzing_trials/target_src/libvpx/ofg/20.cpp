extern "C" {
    #include <vpx/vpx_codec.h>
    #include <vpx/vp8dx.h>
    #include <vpx/vpx_decoder.h> // Include the vpx_decoder.h to access VPX_DECODER_ABI_VERSION
}

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    // Call the function-under-test
    vpx_codec_iface_t *iface = vpx_codec_vp8_dx();

    // Check if the interface is not NULL
    if (iface != NULL) {
        // Initialize a codec context
        vpx_codec_ctx_t codec;
        vpx_codec_err_t res;

        // Initialize codec with the interface
        res = vpx_codec_dec_init_ver(&codec, iface, NULL, 0, VPX_DECODER_ABI_VERSION);

        // If initialization is successful, try to decode the data
        if (res == VPX_CODEC_OK) {
            // Decode the input data
            res = vpx_codec_decode(&codec, data, size, NULL, 0);

            // Check if decoding was successful
            if (res != VPX_CODEC_OK) {
                // Handle decoding error if necessary
            }

            // Destroy the codec context
            vpx_codec_destroy(&codec);
        }
    }

    return 0;
}