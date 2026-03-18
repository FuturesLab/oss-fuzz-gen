#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include the necessary header for memset

extern "C" {
    #include <vpx/vpx_decoder.h>
    #include <vpx/vp8dx.h>
}

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    // Declare and initialize all necessary variables
    vpx_codec_ctx_t codec_ctx;
    vpx_codec_iface_t *iface = vpx_codec_vp8_dx();
    vpx_codec_dec_cfg_t dec_cfg;
    vpx_codec_flags_t flags = 0;
    int ver = VPX_DECODER_ABI_VERSION;

    // Initialize the codec context to zero
    memset(&codec_ctx, 0, sizeof(codec_ctx));

    // Initialize the decoder configuration to zero
    memset(&dec_cfg, 0, sizeof(dec_cfg));

    // Call the function-under-test
    vpx_codec_err_t res = vpx_codec_dec_init_ver(&codec_ctx, iface, &dec_cfg, flags, ver);

    // Clean up the codec context if it was initialized successfully
    if (res == VPX_CODEC_OK) {
        vpx_codec_destroy(&codec_ctx);
    }

    return 0;
}